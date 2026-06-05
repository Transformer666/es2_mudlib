// 冰蠶奇功 polar-silkworm force -- 天師派素衣弟子的入門內功
//
// 天師派素衣一脈以冰證道的根本吐納之術，清冽寒氣氤氳、如玄冰封脈而藏護體罡正。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔註冊心法名、
// override cultivate_msg() 提供天師派素衣自家的打坐氣象，並 override exert_function
// 以實作 docs 載明的高階主動功能 ice-shield(冰罡護體)。
// 注意 key 含連字號與空白，故檔名為 polar-silkworm_force.c。
//
// === ice-shield 冰罡護體(docs/03-門派與武功/02-道士-天師與茅山.md L141) ===
// docs 原文：「ice-shield (冰咒 100、冰蠶 100)：消飲水或 vapour 從戰鬥消失進
// sneak，按 gin/kee/sen 上限比例恢復 50% 最大值與 100% 當前值」。逐項對齊：
//   * 門檻：冰咒(taoism-freeze) >= 100 且 冰蠶(polar-silkworm force) >= 100。
//     任一不足即 notify_fail 說明，不予施展。
//   * 消耗：以「飲水(stat water)」為冰罡之本。先消當前飲水 ISH_WATER_COST﹔
//     飲水不足者，若先前運轉過 vapour(留下 force/vapour 旗標)則改以該旗標頂替
//     (消耗該旗標)，二者皆無則 notify_fail。(vapour 一式屬另檔工作﹐本檔僅在其
//      留有旗標時認帳作替代消耗﹐不臆造其實作。)
//   * 脫戰入 sneak：比照 cmds/std/vanish.c 既驗範式——me->remove_all_killer()
//     徹底脫離一切纏鬥(見 feature/char/attack.c:245)，再
//     me->set_temp("pending/hidden", N) 設引擎隱匿屬性(sneak 成功亦設此值，見
//     cmds/std/sneak.c:125)。本式為原地斂息藏形(不移動)，符合「從戰鬥消失進
//     sneak」之意。
//   * 恢復：對 gin / kee / sen 三者，各按「該 stat 自身上限(maximum)」比例回補——
//       可癒上限(effective/可回上限)以 heal_stat 回補其 maximum 之 50%﹔
//       當前值(current)以 supplement_stat 回補其 maximum 之 100%。
//     supplement_stat 自動封頂於 heal/max、heal_stat 自動封頂於 max(見
//     feature/statistic.c)，故過量回補不溢出。
//
// 派發路徑(cmds/std/exert.c)：玩家鍵入 `exert ice-shield`。exert.c::main 取
// me->skill_mapped("force")(= 已掛上的內功 key﹐此處為 "polar-silkworm force")﹐
// 呼 SKILL_D("polar-silkworm force")->exert_function(me, "ice-shield", target)。
// 本檔接到 func=="ice-shield" 即自行處理﹔其餘 func(含 "polar-silkworm force"
// 本身打坐修煉)落回 ::exert_function 由 FORCE 基底處理。此同型於姊妹篇
// daemon/skill/zushang.c / dragon_force.c 之 override 具名功能結構。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為內功 daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit FORCE;

// === ice-shield 門檻與消耗(docs 載明) ===
#define ISH_MIN_FREEZE  100     // 冰咒(taoism-freeze)火候下限。
#define ISH_MIN_SILK    100     // 冰蠶(polar-silkworm force)火候下限。
#define ISH_WATER_COST  100     // 施展冰罡所消的當前飲水(stat water)。
#define ISH_VAPOUR_TEMP "force/vapour"  // vapour 一式留下的旗標(替代消耗，另檔所設)。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯失敗)。
varargs int exert_function(object me, string func, object target);
int psf_ice_shield(object me);
void psf_restore_stat(object me, string stat);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("polar-silkworm force");
    setup();
}

// 天師派素衣弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
    return HIC "$N閉目盤膝﹐緩緩運轉冰蠶奇功﹐周身似有一股清冽的寒氣氤氳不散﹐"
               "丹田之中一輪寒月冉冉升起﹐沁寒之中自有一股護體的罡正。\n" NOR;
}

// 對單一 stat 按其自身 maximum 比例回補：可癒上限 +50% max、當前值 +100% max。
// heal_stat/supplement_stat 各自封頂於 max / heal(見 feature/statistic.c)。
void psf_restore_stat(object me, string stat)
{
    int max;

    max = me->query_stat_maximum(stat);
    if( max <= 0 ) return;

    // 先抬可癒上限(回 50% 最大值)，再補當前值(回 100% 最大值，受可癒上限封頂)。
    me->heal_stat(stat, max / 2);
    me->supplement_stat(stat, max);
}

// exert ice-shield -- 冰罡護體：消飲水(或 vapour 旗標)脫戰入 sneak，按 gin/kee/sen
// 上限比例回補可癒上限 50%、當前值 100%。
int psf_ice_shield(object me)
{
    int used_vapour;

    // 門檻：冰咒、冰蠶火候俱足方可施展。取原始技能等級(query_skill 第二參 1)。
    if( me->query_skill("taoism-freeze", 1) < ISH_MIN_FREEZE )
        return notify_fail(sprintf(
            "你冰咒火候未到(需冰咒 %d)﹐凝不出護體的冰罡。\n", ISH_MIN_FREEZE));
    if( me->query_skill("polar-silkworm force", 1) < ISH_MIN_SILK )
        return notify_fail(sprintf(
            "你冰蠶奇功火候未到(需冰蠶 %d)﹐運不起這冰罡護體之術。\n", ISH_MIN_SILK));

    // 消耗：先取當前飲水﹔不足則認 vapour 旗標頂替。
    if( me->query_stat("water") >= ISH_WATER_COST ) {
        me->consume_stat("water", ISH_WATER_COST, me);
        used_vapour = 0;
    } else if( me->query_temp(ISH_VAPOUR_TEMP) ) {
        me->delete_temp(ISH_VAPOUR_TEMP);
        used_vapour = 1;
    } else {
        return notify_fail(
            "你體內水氣不足﹐又無先前運轉的寒氣可引﹐凝不出冰罡。\n");
    }

    // 脫離一切纏鬥(remove_all_killer 連 killer 帶 enemy 一併清掉﹐見 vanish.c)。
    if( me->is_fighting() ) {
        me->remove_all_killer();
        message_vision(HIC
            "\n$N周身寒氣暴漲﹐化作一層瑩白冰罡﹐人已自纏鬥中悄然斂去了形跡！\n"
            NOR, me);
    } else {
        message_vision(HIC
            "$N周身寒氣暴漲﹐化作一層瑩白冰罡﹐護住了周身。\n" NOR, me);
    }

    // 入 sneak：set_temp("pending/hidden", N) 為引擎隱匿屬性(同 sneak.c:125)。
    // 藏匿值 = 冰蠶火候 / 10 + 潛行技巧 + 少許隨機﹐火候愈深愈難被察覺。
    me->set_temp("pending/hidden",
        me->query_skill("polar-silkworm force") / 10
        + me->query_skill("sneak") + random(10) + 10);

    // 回補三維資源：按各 stat 自身上限比例(可癒 +50% max、當前 +100% max)。
    psf_restore_stat(me, "gin");
    psf_restore_stat(me, "kee");
    psf_restore_stat(me, "sen");

    tell_object(me, HIW
        "冰罡護體﹐你斂息藏形﹐周身精氣神隨那一輪寒月緩緩回流﹐通體生寒而精神一振。\n"
        NOR);
    if( used_vapour )
        tell_object(me, CYN "(引動先前運轉的寒氣為引)\n" NOR);

    return 1;
}

// exert ice-shield -- 冰罡護體(具名功能)。其餘 func(含 "polar-silkworm force"
// 本身打坐修煉)落回 FORCE 基底(打坐修煉 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;

    if( func == "ice-shield" )
        return psf_ice_shield(me);

    return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
