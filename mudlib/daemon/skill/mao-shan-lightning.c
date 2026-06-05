// 茅山道法【五雷術】 mao-shan lightning -- 茅山派靈雲觀(進階)的上乘雷咒
//
// 這是一門法術(magic)技能﹐茅山派靈雲觀二轉「靈雲觀」所授的上乘道法。
// 比照入門幽冥三箭 youmin.c / 天師雷術 taoism-thunder.c 的結構建立(走
// spells 槽、cast 指令)﹐使技能可被指派、習練、施法。
//
// 設計(docs 03-門派與武功/02-道士-天師與茅山.md「靈雲觀 → 茅山【五雷術】
//   mao-shan lightning」)：docs 載五雷術由林正陽授(需幽冥三箭 ≥90)﹐三式
//   「凝聚 cleanse / 賦予 bless / 補給 consume」屬增益/恢復系﹐皆消神 +
//   靈力 + 先天符。本檔屬靈雲觀(雷/purify)之承襲﹐先實作其攻擊雷咒一系
//   (五行雷罡傷敵)﹐其增益/恢復三式(凝聚/賦予/補給)待咒術效果引擎就緒
//   後再各自承襲。
//
// 註(先天符/正陽符)：docs 五雷術消耗先天符、幽冥三箭消耗正陽符。本門攻擊
//   咒沿幽冥一脈引氣﹐故 query_spells 以 "fu":"正陽符" 接通 /std/magic.c 的
//   符閘(施法前驗符、施成燃符)﹔賦予/補給之「先天符」屬增益式專用資源﹐
//   於三式支援咒(ml_bless/ml_consume)內以 ML_BLESS_FU 自行驗符/燃符。
//
// 注意：key 含空白(「mao-shan lightning」)﹐故檔名以連字號代之
// (mao-shan-lightning.c)﹐register/translate 用的 key 仍為含空白原名。
//
// 增益/恢復特效(2026-06-05 接上元素引擎)：docs L213-215 載五雷術三式
//   「凝聚 cleanse / 賦予 bless / 補給 consume」。元素/增益/恢復引擎已建於
//   /std/magic.c(magic_attr_buff 暫提屬性、magic_element_buff 暫提元素防、
//   supplement_stat 回精氣神當前值)。本檔承襲攻擊雷咒之餘﹐補上這三式支援咒：
//     賦予 bless   -- 消神 + 先天符﹐對目標全面提升屬性 + 元素傷 + 元素抗(docs L214)。
//     凝聚 cleanse -- 消神凝聚靈力﹐回補施法者精氣神當前值(docs L213)。
//     補給 consume -- 消神 + 先天符﹐恢復目標精氣神當前值(docs L215)。
//   三式為支援向(對自身/隊友)﹐非攻擊咒﹐故 override cast_spell 在攻擊流程「之前」
//   先攔下這三道支援咒自行處理(不開戰、不走 ::cast_spell)﹔其餘攻擊咒落回
//   ::cast_spell(base /std/magic.c 逐字未動)。先天符之驗/燃鏡 base 的 fu 閘
//   (present("先天符", me) + add_amount(-1))。

#include <ansi.h>

inherit "/std/magic";

// === 三式支援咒參數(docs：消神 + 先天符)。集中於此便於調校。===
#define ML_BLESS_SEN        50      // 賦予 bless：耗神。
#define ML_BLESS_FU         "先天符" // 賦予/補給所焚的符(set_name id﹐見 obj/talisman/xiantian_fu.c)。
#define ML_BLESS_ATTR       3       // 賦予：全面提升屬性點數(apply/<attr>)。
#define ML_BLESS_ELEM_DMG   15      // 賦予：提升傷害(apply/damage)。
#define ML_BLESS_ELEM_DEF   20      // 賦予：提升四元素防(apply/<elem>_def)。
#define ML_BLESS_DURATION   40      // 賦予：buff 持續秒數。

#define ML_CLEANSE_SEN      30      // 凝聚 cleanse：耗神。
#define ML_CLEANSE_GAIN     40      // 凝聚：回補施法者精氣神當前值。

#define ML_CONSUME_SEN      40      // 補給 consume：耗神。
#define ML_CONSUME_GAIN     50      // 補給：回補目標精氣神當前值。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯 Undefined
//   function﹐進而 daemon lazy-load 靜默失敗、cast 指令靜默回 0)。
varargs int  cast_spell(object me, string spl, object target);
private int  ml_bless(object me, object who);
private int  ml_cleanse(object me);
private int  ml_consume(object me, object who);
private int  ml_check_fu(object me);
private void ml_recover_stats(object who, int amt);
void         ml_bless_end(object who);

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖凝起一點靈雷﹐化作一道雷罡射向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N掐訣引雷﹐一道五行雷罡破空轟向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N袖中正陽符燃起﹐化作一片紫芒雷網罩向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N足踏罡步﹐一式『五雷正法』五道靈雷齊射$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N揮手撒出一蓬雷珠﹐密密匝匝地激射$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N凝神運法﹐一道靈雷化龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團靈雷轟向$n的$l",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『天罡五雷』霹靂沖天暴鳴﹐當頭劈向$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
});

string *interattack = ({
  "$N默運五雷正法﹐指間隱隱透出一縷靈雷紫芒﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("mao-shan lightning");
  // 登錄中文名﹐使 enable / skills 等顯示「五雷術」而非英文代號。
  CHINESE_D->add_translate("mao-shan lightning", "五雷術");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIY + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "mao-shan lightning", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable 由 /std/magic 提供；
//    cast_spell 於本檔 override 以接通元素引擎 + 九龍超載）──
//
// === 元素-效果引擎接通(2026-06-05) ===
// 五雷術屬「純雷元素傷害」上乘一系﹐故各式 elem="thunder"﹐傷害經
// /std/magic.c::magic_element_damage 折算對象雷抗(apply/thunder_def)。每式
// 仍焚一張「正陽符」引氣(沿幽冥一脈﹐"fu":"正陽符" 之驗符/燃符邏輯在 override
// 內比照基底處理)。九龍超載旗標(force/taoism_overload)依任務令對雷咒一體適用：
// 旗標存在則基礎傷 +50% 後清旗標(docs L163 原文限「天師咒」﹐此處依任務「雷咒
// 基礎傷 +50%」之指令﹐將其加成延及茅山雷咒一系﹐已於旗標讀法處註明)。
string magic_skill() { return "mao-shan lightning"; }

// 九龍超載旗標 key(鏡 daemon/skill/nine-dragon_force.c::do_overload 之契約)。
#define NDF_OVERLOAD_TEMP   "force/taoism_overload"

// 茅山靈雲觀【五雷術】攻擊一系。威力高於入門幽冥三箭(youmin)﹐神耗亦較高﹐
// 以對應其二轉上乘道法的定位。每式焚一張「正陽符」引氣(沿幽冥一脈)。
// elem="thunder" → 經引擎折算雷抗；delay 隨威力遞增。
mapping query_spells()
{
  return ([
    "靈雷" :     ([ "id":"linglei", "sen":18, "power":24, "type":"雷殛", "fu":"正陽符",
        "elem":"thunder", "delay":1,
        "action":HIY "$N口誦真言﹐掐訣引雷﹐一道五行雷罡破空而出﹐霹靂轟向$n！" NOR ]),
    "五雷正法" : ([ "id":"wulei",   "sen":40, "power":42, "type":"雷殛", "fu":"正陽符",
        "elem":"thunder", "delay":2,
        "action":HIY "$N足踏罡步﹐袖中正陽符燃起﹐一式『五雷正法』五道靈雷齊發﹐攢射$n！" NOR ]),
    "天罡五雷" : ([ "id":"tiangang","sen":66, "power":60, "type":"雷殛", "fu":"正陽符",
        "elem":"thunder", "delay":3,
        "action":HIY "$N凝神運起五雷至深一式﹐周身雷光暴漲﹐一式『天罡五雷』霹靂沖天暴鳴﹐當頭劈向$n！" NOR ]),
  ]);
}

// ── override cast_spell：沿用 /std/magic 基底驗證流程(含 fu 驗符/燃符)﹐
//    傷害改走元素引擎(折算雷抗)﹐並接通九龍超載(下次基礎傷 +50%)。──
varargs int
cast_spell(object me, string spl, object target)
{
    mapping spells, sp;
    string sk, nm, action, dtype, elem;
    int cost, power, skill, base, damage, busy, overload;
    object fu;

    if( !objectp(me) || !stringp(spl) ) return 0;

    // ── 三式支援咒(賦予/凝聚/補給)在攻擊流程之前先攔下自處理(docs L213-215)──
    // 不開戰、可施於自身或隊友(bless/consume 未指定 on 對象時預設自身﹔cleanse 恆自身)。
    switch( spl ) {
    case "賦予":  case "bless":   return ml_bless(me, objectp(target) ? target : me);
    case "凝聚":  case "cleanse": return ml_cleanse(me);
    case "補給":  case "consume": return ml_consume(me, objectp(target) ? target : me);
    }

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

    // 取施法對象（cast 未指定時取當前敵人）。
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

    // 非戰之地不可施展攻擊法術。
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

    // 符(talisman)消耗檢查(五雷術標 "fu":"正陽符"﹐須備符且張數>=1)。
    fu = 0;
    if( stringp(sp["fu"]) ) {
        fu = present(sp["fu"], me);
        if( !objectp(fu) || (int)fu->query_amount() < 1 ) {
            notify_fail("你身上沒有施展此法所需的"
                + (fu ? (string)fu->name() : (string)sp["fu"]) + "。\n");
            return 0;
        }
    }

    // ── 通過所有檢查，正式施法 ──
    if( !me->is_fighting(target) ) {
        me->kill_ob(target);
        if( userp(target) ) target->fight_ob(me);
        else target->kill_ob(me);
    }

    me->consume_stat("sen", cost);
    if( objectp(fu) )
        fu->add_amount(-1);

    // 基礎傷害(神/技能驅動﹐同基底公式)。
    skill = me->query_skill(sk);
    power = sp["power"];
    base = power * (100 + skill) / 100;
    base += random(base / 2 + 1);

    // ── 九龍超載(docs L163﹐依任務延及雷咒一系)：旗標非 0 則基礎傷 +該% 後清旗標 ──
    overload = (int)me->query_temp(NDF_OVERLOAD_TEMP);
    if( overload > 0 ) {
        base = base * (100 + overload) / 100;
        me->delete_temp(NDF_OVERLOAD_TEMP);
        tell_object(me, HIM "你周身蓄勢的雷龍轟然爆發﹐這一道五雷正法雷威暴漲！\n" NOR);
    }

    // 施法訊息。
    action = sp["action"];
    if( !stringp(action) ) action = "$N唸動咒文﹐一道五行雷罡激射向$n！";
    message_vision(action + "\n", me, target);

    // ── 元素引擎：依雷抗(apply/thunder_def)折算實傷 ──
    elem = stringp(sp["elem"]) ? sp["elem"] : "thunder";
    damage = magic_element_damage(target, base, elem, sp["pierce"]);

    dtype = sp["type"]; if( !stringp(dtype) ) dtype = "雷殛";
    target->receive_damage(damage, me, me);
    COMBAT_D->report_status(target);

    // 練法術技能 + 精熟（僅玩家）。
    if( userp(me) )
        me->improve_skill(sk, 1 + random(2));

    // 吟誦/運法後短暫無法行動(各式 delay﹐無則沿基底 2)。
    busy = sp["delay"]; if( busy <= 0 ) busy = 2;
    me->start_busy(busy);

    return 1;
}

// ════════════════════════════════════════════════════════════════════
// 五雷術三式支援咒實作：賦予 bless / 凝聚 cleanse / 補給 consume(docs L213-215)
// 支援咒不開戰、可施於自身或隊友。屬性/傷害經 magic_attr_buff(apply/<attr>、
// apply/damage)、元素防經 magic_element_buff(apply/<elem>_def)﹐二者皆 /std/magic.c
// 引擎自帶 call_out 到期復原(add_temp(-N)﹐不 delete_temp)。回補走 supplement_stat。
// ════════════════════════════════════════════════════════════════════

// 先天符之驗(present + 張數>=1)﹐鏡基底 cast_spell 的 fu 閘。足回 1。
private int
ml_check_fu(object me)
{
    object fu;

    fu = present(ML_BLESS_FU, me);
    if( !objectp(fu) || (int)fu->query_amount() < 1 ) {
        notify_fail("你身上沒有施展此法所需的先天符。\n");
        return 0;
    }
    return 1;
}

// 回補目標精氣神當前值(supplement_stat 補 current 並自動封頂﹐feature/statistic.c)。
private void
ml_recover_stats(object who, int amt)
{
    if( !objectp(who) || amt <= 0 ) return;
    who->supplement_stat("gin", amt);
    who->supplement_stat("kee", amt);
    who->supplement_stat("sen", amt);
}

// ── 賦予 bless：消神 + 先天符﹐對目標全面提升屬性 + 傷害 + 四元素抗(docs L214)──
private int
ml_bless(object me, object who)
{
    string attr, elem;

    if( !objectp(who) || !living(who) )
        return notify_fail("你要對誰施展『賦予』﹖(cast 賦予 [on <對象>])\n");
    if( me->query_stat("sen") < ML_BLESS_SEN )
        return notify_fail("你的神識不足以運使這道『賦予』。\n");
    if( !ml_check_fu(me) ) return 0;

    // 重複賦予不疊加(避免無限延長)。
    if( who->query_temp("ml_bless_active") )
        return notify_fail("對方身上的五雷賦予之力尚未消退。\n");

    me->consume_stat("sen", ML_BLESS_SEN);
    present(ML_BLESS_FU, me)->add_amount(-1);   // 燃一張先天符
    who->set_temp("ml_bless_active", 1);
    // 到期清旗標(call_out 在本 daemon 上跑﹐故以 who 為參數的 ml_bless_end 回呼清之﹐
    // 不可 call_out("delete_temp",…)——那會去呼 daemon 自身的 delete_temp 而非 who 的)。
    call_out("ml_bless_end", ML_BLESS_DURATION, who);

    // 全面提升八屬性。
    foreach( attr in ({ "str","cor","int","spi","cps","dex","con","wis" }) )
        magic_attr_buff(who, attr, ML_BLESS_ATTR, ML_BLESS_DURATION);
    // 提升傷害(apply/damage 由 combat 讀)。
    magic_attr_buff(who, "damage", ML_BLESS_ELEM_DMG, ML_BLESS_DURATION);
    // 提升四元素防(apply/<elem>_def 由 /std/magic.c::magic_element_resist 讀)。
    foreach( elem in ({ "fire","freeze","wind","thunder" }) )
        magic_element_buff(who, elem, ML_BLESS_ELEM_DEF, ML_BLESS_DURATION);

    message_vision(HIY
        "$N掐訣誦『賦予』真言﹐袖中先天符無風自燃﹐一道五雷靈光灌入$n周身﹐"
        "$n但覺氣血賁張、護體生輝﹗\n" NOR, me, who);
    tell_object(me, sprintf(HIW
        "你以五雷術賦予對方。(消 sen %d、先天符 1﹐持續 %d 秒)\n" NOR,
        ML_BLESS_SEN, ML_BLESS_DURATION));
    me->start_busy(2);
    return 1;
}

// 賦予到期：僅清「不重複疊加」旗標(各屬性/元素 buff 由引擎自帶 call_out 各自復原)。
void
ml_bless_end(object who)
{
    if( !objectp(who) ) return;
    who->delete_temp("ml_bless_active");
    tell_object(who, NOR "你身上那道五雷賦予之力漸漸消退了。\n");
}

// ── 凝聚 cleanse：消神凝聚靈力﹐回補施法者精氣神當前值(docs L213)──
private int
ml_cleanse(object me)
{
    if( me->query_stat("sen") < ML_CLEANSE_SEN )
        return notify_fail("你的神識不足以運使這道『凝聚』。\n");

    me->consume_stat("sen", ML_CLEANSE_SEN);
    ml_recover_stats(me, ML_CLEANSE_GAIN);

    message_vision(HIY
        "$N斂神掐訣﹐周身靈雷紫芒緩緩內收凝聚﹐化作一縷靈力歸入百脈。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你運轉五雷術凝聚靈力。(消 sen %d﹐回精氣神當前值各 %d)\n" NOR,
        ML_CLEANSE_SEN, ML_CLEANSE_GAIN));
    me->start_busy(2);
    return 1;
}

// ── 補給 consume：消神 + 先天符﹐回補目標精氣神當前值(docs L215)──
private int
ml_consume(object me, object who)
{
    if( !objectp(who) || !living(who) )
        return notify_fail("你要對誰施展『補給』﹖(cast 補給 [on <對象>])\n");
    if( me->query_stat("sen") < ML_CONSUME_SEN )
        return notify_fail("你的神識不足以運使這道『補給』。\n");
    if( !ml_check_fu(me) ) return 0;

    me->consume_stat("sen", ML_CONSUME_SEN);
    present(ML_BLESS_FU, me)->add_amount(-1);   // 燃一張先天符
    ml_recover_stats(who, ML_CONSUME_GAIN);

    message_vision(HIY
        "$N掐訣誦『補給』真言﹐先天符化作一蓬溫煦靈光沒入$n體內﹐$n但覺精神為之一振﹗\n" NOR,
        me, who);
    tell_object(me, sprintf(HIW
        "你以五雷術補給對方。(消 sen %d、先天符 1﹐回對方精氣神當前值各 %d)\n" NOR,
        ML_CONSUME_SEN, ML_CONSUME_GAIN));
    me->start_busy(2);
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
