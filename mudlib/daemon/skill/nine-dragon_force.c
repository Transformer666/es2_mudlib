// 九龍神功 nine-dragon force -- 天師派紫衣(雷)弟子的入門內功
//
// docs/03-門派與武功/02-道士-天師與茅山.md「九龍神功 (nine-dragon force)」(L159)
// 為紫衣派(雷)— taoist.thunder 一脈的根本吐納內功﹐九道雷龍盤旋丹田、以雷罡證道。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔註冊心法名、
// override cultivate_msg() 提供紫衣派自家的打坐氣象﹐並 override exert_function 以
// 實作 docs 載明的主動功能 overload(超載引雷)。注意 key 含連字號與空白﹐故檔名為
// nine-dragon_force.c(同 polar-silkworm_force.c 之命名)。
//
// === overload 超載引雷(docs/03-門派與武功/02-道士-天師與茅山.md L163) ===
// docs 原文：「overload：消 75 神，下次天師咒基礎傷害 +50%」。逐項對齊：
//   * 門檻：內功(force / nine-dragon force) >= 10(docs 該門內功本身 lv >= 10)。
//   * 消耗：神(sen)當前值 75(consume_stat("sen", 75, me)﹐只削 current)。
//   * 效果：set 一個 temp 旗標﹐令「下次天師咒基礎傷害 +50%」。本式僅
//       set temp + 消耗 sen + 訊息﹔實際在 cast 時讀此旗標、加成基礎傷害、用後清除
//       屬 cast 端(taoism-thunder/freeze 等)日後之工作(見該檔 TODO: spell-cast
//       wiring)。本檔不臆造 cast 端讀法﹐只立下旗標契約如下：
//
//     ── 旗標契約(供日後 cast 端讀) ────────────────────────────────────
//       me->query_temp(NDF_OVERLOAD_TEMP)  (= NDF_OVERLOAD_BONUS, 即 50)
//         非 0 表「下一道天師咒基礎傷害 +該百分比」。cast 端施咒命中後應
//         以 me->delete_temp(NDF_OVERLOAD_TEMP) 清除﹐使加成僅及「下次」一道。
//       NDF_OVERLOAD_TEMP = "force/taoism_overload"(force/ 命名空間下﹐避免與
//       其他 temp 衝撞﹐同 polar-silkworm 之 force/vapour 旗標慣例)。
//     ──────────────────────────────────────────────────────────────────
//
// 派發路徑(cmds/std/exert.c::main)：玩家鍵入 `exert overload`。exert.c 取
// me->skill_mapped("force")(= 已掛上的內功 key﹐此處為 "nine-dragon force")﹐
// 呼 SKILL_D("nine-dragon force")->exert_function(me, "overload", target)。本檔接到
// func=="overload" 即自行處理﹔其餘 func(含 "nine-dragon force" 本身打坐修煉)落回
// ::exert_function 由 FORCE 基底處理。此同型於姊妹篇 daemon/skill/dao_force.c、
// dragon_force.c、zushang.c 之 override 具名功能、其餘落回基底的結構。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為內功 daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit FORCE;

// === overload 門檻、消耗與旗標(docs 載明) ===
#define NDF_OVERLOAD_LEVEL  10      // 門檻：內功(force/nine-dragon force) >= 10。
#define NDF_OVERLOAD_SEN    75      // 消耗：神(sen)當前值 75。
#define NDF_OVERLOAD_TEMP   "force/taoism_overload"  // 旗標 key(供 cast 端讀)。
#define NDF_OVERLOAD_BONUS  50      // 旗標值：下次天師咒基礎傷害 +50%。

// 前置宣告(lesson #12：凡「定義前引用」之自訂函式一律先前置宣告﹐免編譯
// Undefined function、daemon lazy-load 失敗、SKILL_D 靜默回 0)。
varargs int exert_function(object me, string func, object target);
int ndf_force_level(object me);
int do_overload(object me);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("nine-dragon force");
    setup();
}

// 天師派紫衣弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
    return HIM "$N閉目盤膝﹐緩緩運轉九龍神功﹐周身似有九道雷龍盤旋不散﹐"
               "丹田之中雷氣鼓盪如潮﹐霹靂之中自有一股護體的雷罡。\n" NOR;
}

// 內功火候：取 force 槽自身與所掛「nine-dragon force」心法二者之高者(同
// dragon_force / dao_force 之門檻取法)﹐作為 overload 等級門檻的判準。
int ndf_force_level(object me)
{
    int lv;

    lv = me->query_skill("force", 1);
    if( me->query_skill("nine-dragon force", 1) > lv )
        lv = me->query_skill("nine-dragon force", 1);
    return lv;
}

// exert overload -- 超載引雷：消 75 神﹐立下旗標令「下次天師咒基礎傷害 +50%」。
//   門檻：內功(force/nine-dragon force) >= NDF_OVERLOAD_LEVEL。
//   消耗：神(sen)當前值 NDF_OVERLOAD_SEN。
//   效果：set_temp 旗標(供 cast 端日後讀)﹔本式僅 set temp + 消耗 + 訊息。
int do_overload(object me)
{
    if( ndf_force_level(me) < NDF_OVERLOAD_LEVEL )
        return notify_fail(sprintf(
            "你九龍神功火候未到(需內功 %d)﹐引不動這超載的雷龍。\n",
            NDF_OVERLOAD_LEVEL));

    // 神不足以超載引雷(query_stat 取當前值 = query_stat_current)。
    if( me->query_stat("sen") < NDF_OVERLOAD_SEN )
        return notify_fail(sprintf(
            "你神識不足(需神 %d)﹐運不起這超載引雷之術。\n", NDF_OVERLOAD_SEN));

    // 已立旗標未發者﹐毋須重複超載(避免空耗神識)。
    if( me->query_temp(NDF_OVERLOAD_TEMP) )
        return notify_fail("你周身雷氣已蓄勢待發﹐何須再行超載﹖\n");

    // 消耗神識當前值(consume_stat 只削 current)。
    me->consume_stat("sen", NDF_OVERLOAD_SEN, me);

    // 立下旗標：下次天師咒基礎傷害 +NDF_OVERLOAD_BONUS%(供 cast 端日後讀並清除)。
    me->set_temp(NDF_OVERLOAD_TEMP, NDF_OVERLOAD_BONUS);

    message_vision(HIM
        "$N凝神運轉九龍神功﹐周身九道雷龍轟然盤旋暴漲﹐雷氣鼓盪如潮﹐"
        "蓄起一股蓄勢待發的滔天雷勢！\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你超載引雷﹐下一道天師咒的雷威必當暴漲。(消神 %d﹐下次天師咒基礎傷害 +%d%%)\n"
        NOR, NDF_OVERLOAD_SEN, NDF_OVERLOAD_BONUS));

    return 1;
}

// exert overload -- 九龍神功超載引雷(具名功能)。其餘 func(含 "nine-dragon force"
// 本身打坐修煉)落回 FORCE 基底(打坐修煉 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;

    if( func == "overload" )
        return do_overload(me);

    return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
