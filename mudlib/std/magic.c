// /std/magic.c -- 法術(magic)技能 daemon 共用基底：主動施法 (cast) 機制。
//
// 使用者 2026-06-02 拍板：道士系 magic 招式以「主動 cast」運作（非 auto-attack）。
// 玩法：玩家 `enable spells with <技能>` 後，`cast <咒文> [on <對象>]`；NPC 由
// std/char/npc.c::cast_spell(spell) 觸發。本基底實作 valid_enable + cast_spell；
// 各 magic daemon 只需覆寫 query_spells()(咒文表) 與 magic_skill()(本門技能名)。
//
// 既有基建：cmds/std/cast.c(玩家指令)、cmds/usr/enable.c(指派 spells)、
//           std/char/npc.c::cast_spell(NPC)。三者皆呼叫 SKILL_D(spells)->cast_spell。
// 原 magic daemon 的 valid_enable 回 0、且無 cast_spell → 法術全休眠；本基底接通之。
//
// 法術傷害以「神(sen) + magic 技能」驅動（非力道 strength），扣神、有吟誦時間(busy)。
// 傷害套用走 victim->receive_damage()，與物理攻擊同一終點。

#include <ansi.h>

inherit SKILL;

// ── 子 daemon 須覆寫 ──────────────────────────────────────────────
// query_spells(): 中文咒名 -> ([ "id":英文id, "sen":耗神, "power":威力基數,
//                                 "type":傷害型, "action":施法訊息($N/$n),
//                                 "effect":特效(選填 "freeze"…) ])
mapping query_spells() { return ([]); }
// magic_skill(): 本門 magic 技能名（如 "taoism-fire"）。
string magic_skill() { return 0; }

// 允許 `enable spells with <本技能>`。原 SKILL 無此函式 / magic daemon 原回 0。
int valid_enable(string usage)
{
    return usage == "spells";
}

// cast_spell(me, spl, [target])
//   玩家：cmds/std/cast.c 傳 (me, 咒名, 對象或0)。
//   NPC ：std/char/npc.c 傳 (me, 咒名)，target 省略 → 取當前敵人。
// 失敗回 0（並 notify_fail 給玩家路徑），成功回 1。
varargs int
cast_spell(object me, string spl, object target)
{
    mapping spells, sp;
    string sk, nm, action, dtype;
    int cost, power, skill, damage;
    object fu;

    if( !objectp(me) || !stringp(spl) ) return 0;

    sk = magic_skill();
    spells = query_spells();
    if( !sk || !mapp(spells) || !sizeof(spells) ) {
        notify_fail("你還沒有可施展的法術。\n");
        return 0;
    }

    // 找咒文：先比中文名、再比英文 id。
    sp = spells[spl];
    if( !mapp(sp) ) foreach( nm, mapping m in spells )
        if( mapp(m) && m["id"] == spl ) { sp = m; break; }
    if( !mapp(sp) ) {
        notify_fail("你不會「" + spl + "」這道法術。\n");
        return 0;
    }

    // 須已習得本門法術。
    if( me->query_skill(sk) <= 0 && !me->query_learn(sk) ) {
        notify_fail("你並未習得「" + to_chinese(sk) + "」。\n");
        return 0;
    }

    // 取施法對象（cast 未指定時取當前敵人）。select_opponent 為 private、
    // 須用公開的 query_enemy()（回敵人陣列）取首個。
    if( !objectp(target) ) {
        object *es = me->query_enemy();
        if( arrayp(es) ) {
            es -= ({ 0 });
            if( sizeof(es) ) target = es[0];
        }
    }
    if( !objectp(target) || !living(target)
    ||  target->query("life_form") == "ghost" ) {
        notify_fail("你要對誰施展法術？（cast " + spl + " on <對象>）\n");
        return 0;
    }
    if( target == me ) {
        notify_fail("你不能對自己施展攻擊法術。\n");
        return 0;
    }
    if( environment(me) != environment(target) ) {
        notify_fail("施法對象不在這裡。\n");
        return 0;
    }

    // 非戰之地不可施展攻擊法術（與 combatd.c::fight 的 no_fight 規則一致、
    // 否則玩家可在和平房如客棧內隔空打人）。
    if( environment(me)->query("no_fight")
    && !target->query("unprotect_mark") && !me->query("unprotect_mark") ) {
        notify_fail("這裡是清靜之地，不可動手施法。\n");
        return 0;
    }

    // 神(sen)消耗檢查。
    cost = sp["sen"];
    if( me->query_stat("sen") < cost ) {
        notify_fail("你的神識不足以運使這道法術。\n");
        return 0;
    }

    // 符(talisman)消耗檢查 ── 僅當咒文表標了 "fu" 鍵(茅山符咒)才生效；
    // 未標 fu 的咒術(天師 taoism-fire/freeze/wind/thunder/cloud、moon-magic)
    // 此段完全略過、不受影響。標 fu 者(茅山 youmin 幽冥三箭系)須身上備有對
    // 應的符且張數>=1，否則施法失敗(不扣神/不開戰)。
    fu = 0;
    if( stringp(sp["fu"]) ) {
        fu = present(sp["fu"], me);
        if( !objectp(fu) || (int)fu->query_amount() < 1 ) {
            notify_fail("你身上沒有施展此法所需的"
                + (fu ? (string)fu->name() : (string)sp["fu"]) + "。\n");
            return 0;
        }
    }

    // ── 通過所有檢查，正式施法（之後不再失敗）──
    // 若尚未交戰則開戰。
    if( !me->is_fighting(target) ) {
        me->kill_ob(target);
        if( userp(target) ) target->fight_ob(me);
        else target->kill_ob(me);
    }

    me->consume_stat("sen", cost);

    // 燃符：標了 "fu" 鍵的茅山符咒﹐施法成功時焚去一張對應的符
    // (符歸零時 combined.c 會自動 destruct)。未標 fu 的咒術 fu 為 0﹐此段略過。
    if( objectp(fu) )
        fu->add_amount(-1);

    // 法術傷害：神/技能驅動。skill 0→~power；100→~2-3x；200→~3-4.5x。可調。
    skill = me->query_skill(sk);
    power = sp["power"];
    damage = power * (100 + skill) / 100;
    damage += random(damage / 2 + 1);

    // 施法訊息。
    action = sp["action"];
    if( !stringp(action) ) action = "$N唸動咒文﹐一道法力激射向$n！";
    message_vision(action + "\n", me, target);

    // 套用傷害（與物理攻擊同走 receive_damage）。
    dtype = sp["type"]; if( !stringp(dtype) ) dtype = "法術";
    target->receive_damage(damage, me, me);
    COMBAT_D->report_status(target);

    // 特效：凍結 → 對象短暫無法行動（並出訊息，使凍結可見）。
    if( sp["effect"] == "freeze" && objectp(target) && living(target)
    && !target->is_busy() ) {
        message_vision(HIC "$n被森森寒氣凍得周身一滯，動作為之一頓！" NOR "\n", me, target);
        target->start_busy(1);
    }

    // 練法術技能 + 精熟（僅玩家；NPC 技能固定）。
    if( userp(me) )
        me->improve_skill(sk, 1 + random(2));

    // 吟誦/運法後短暫無法行動（施法時間）。
    me->start_busy(2);

    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
