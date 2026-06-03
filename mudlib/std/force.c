// /std/force.c -- 內功(force)心法的共用基底
//
// 所有內功 daemon（daemon/skill/*_force.c）應 inherit FORCE（而非直接 inherit
// SKILL）。它補上原系統內功樣板漏掉、卻是內功正常運作所必須的兩件事：
//
//   1. valid_enable() -- 回 usage=="force"，使內功可被 `enable force with <心法>`
//      掛上 force 槽。原樣板寫死 return 0，內功根本掛不上、戰鬥力道放大也就無從談起。
//
//   2. exert 打坐修煉 -- `exert <心法名>` 盤膝運功、耗 gin/kee/sen、隨機精進「該
//      心法」與通用「force」技能。這是 es2 內功正典的修煉途徑（見 cmds/std/exert.c
//      help：「通常你可以用 exert <內功名稱> 來修煉內功」），比照原開源樣本
//      d/snow/skill/dragon_force.c::do_exercise。原樣板的 exert_function 只印氛圍字、
//      不練功，致 force 永不成長——一度被誤搬到 combat 裡練，已於 combatd.c 移除。
//
// 內功的「特殊功能」（運功療傷、護體罡氣…）由各心法 override exert_function、自行
// 處理該 func 後、其餘情形 return ::exert_function(me,func,target) 落回本檔的打坐。
// 各心法可 override cultivate_msg() 換上自家打坐氛圍字。
//
// 註：技能等級的成長由 feature/char/skill.c::improve_skill 內建的 learned→skills
// 轉換（封頂於天賦）統一處理，故本基底毋須自備 skill_improved / skill_advanced。
// query_skill("force") 取「force 槽自身 + 所掛心法」之平均（feature/char/skill.c），
// 因此 do_exercise 同時精進兩者，戰鬥用的 query_skill("force") 方能隨打坐成長。

#include <ansi.h>

inherit SKILL;

// 內功掛在 force 槽。
int valid_enable(string usage)
{
    return usage == "force";
}

// 打坐運功時的氛圍字（各心法可 override 換成自家風味）。
string cultivate_msg()
{
    return HIY "$N盤膝而坐﹐深深吸了一口氣﹐凝神內視﹐運轉真氣周流百脈﹐開始打坐修煉內功。\n" NOR;
}

// 打坐一個 tick：耗 gin/kee/sen，隨機精進「所掛心法」與通用 force 技能。
// 比照 es2 原樣本 d/snow/skill/dragon_force.c::do_exercise（去其 damage_stat 損上限
// 一節——該損耗本應由心法升階時的 advance_stat 補回，茲從簡只作純修煉，不損上限）。
int do_exercise(object me)
{
    string force_skill;

    if( !objectp(me) ) return 1;

    if( me->query_stat("gin") < 10
    ||  me->query_stat("kee") < 10
    ||  me->query_stat("sen") < 10 ) {
        tell_object(me, "你覺得神困力乏﹐沒有辦法繼續打坐運功了。\n");
        me->interrupt_me(me, "exhausted");
        return 1;
    }
    me->consume_stat("gin", 10);
    me->consume_stat("kee", 10);
    me->consume_stat("sen", 10);

    force_skill = me->skill_mapped("force");

    // 有所體悟時方有精進（隨資質 cps/con 與當前 force 火候提高機率）。
    if( random(me->query_attr("cps") + me->query_attr("con")
            + me->query_skill("force", 1)) > 20 ) {
        if( stringp(force_skill) && force_skill != "force" )
            me->improve_skill(force_skill, random(me->query_attr("con") / 10) + 1);
        me->improve_skill("force", random(me->query_attr("int") / 10) + 1);
    }
    return 1;
}

int halt_exercise(object me, object owner, object from, string how)
{
    return 1;
}

// 預設 exert：`exert <本心法名>` 即盤膝打坐、修煉內功。
// 心法欲提供特殊功能者 override 本函式，處理完特殊 func 後、其餘
// 情形 return ::exert_function(me, func, target) 落回此處的打坐。
varargs int exert_function(object me, string func, object target)
{
    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;

    // exert <自己已掛上的內功名> -> 打坐修煉。
    if( stringp(func) && func == me->skill_mapped("force") ) {
        message_vision(cultivate_msg(), me);
        me->start_busy((: do_exercise, me :), (: halt_exercise, me :));
        return 1;
    }
    return notify_fail("這門內功並沒有這種功能。\n");
}

// vim: set ts=4 sw=4 syntax=lpc
