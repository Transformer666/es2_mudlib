// 竹上經心法 zushang -- 龍圖丹派(alchemist.dragon)方士的調息內功
//
// 來歷(docs/03-門派與武功/07-方士-龍圖武陀.md L35、docs/02-遊戲系統與機制/
// 06-煉丹與書本系統.md L92)：竹上經心法是龍圖丹派核心技能之一﹐方士幾無直接
// 戰鬥力﹐卻以「regenerate」一式調息歸元——耗去身上的氣(gin)與精(kee)﹐反哺
// 為神(sen)。煉丹、印封、黃白之術皆耗 sen(神識)﹐竹上經正是龍圖方士把多餘的
// 體力(gin/kee)轉成施術本錢(sen)的看家調息法。典型玩家 Vvcheng 練至竹上經
// 心法 200(+5)。
//
// 共用機制由 FORCE(/std/force.c)基底提供(同 daemon/skill/dragon_force.c、
// mao-shan-force.c 的建檔模型)：valid_enable() 使本心法可被
// `enable force with zushang` 掛上 force 槽﹐`exert zushang` 即盤膝打坐修煉。
// 本檔在此之上 override exert_function 以實作 docs 載明的特殊功能 regenerate。
//
// regenerate(docs：消 gin/kee 回 sen 當前/最大值)：
//   `exert regenerate` 運轉竹上經﹐消耗當前的 gin 與 kee﹐折算成 sen 回補。
//   - 消耗：gin、kee 各扣 GI_COST = ZS_COST(當前值﹐consume_stat 只削 current)。
//   - 回補：把扣去的氣血折為神識﹐sen 之
//       「當前值」以 supplement_stat 補(回 sen 當前)﹐
//       「可癒上限(heal/最大可回值)」以 heal_stat 補(回 sen 最大值)。
//     兩者各補 ZS_GAIN = 折算後的 sen。supplement/heal 皆自動封頂於
//     stats_max["sen"]/stats_heal["sen"]﹐故過量回補不會溢出(見 feature/
//     statistic.c::supplement_stat / heal_stat)。
//   折算比 ZS_RATE：每 (gin+kee) 兩單位換 1 點 sen(調息「化氣為神」本有耗損)﹐
//   隨竹上經火候(query_skill)提高換算效率﹐技能愈高轉換愈不折損。
//
// 派發路徑(cmds/std/exert.c)：玩家鍵入 `exert regenerate`。exert.c::main 取
// me->skill_mapped("force")(= 已掛上的內功 key﹐此處為 "zushang")﹐
// 呼 SKILL_D("zushang")->exert_function(me, "regenerate", target)。本檔接到
// func=="regenerate" 即自行處理﹔其餘 func(含 "zushang" 本身)落回
// ::exert_function 由 FORCE 基底作打坐修煉或回 notify_fail。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為內功 daemon(inherit FORCE)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。

#include <ansi.h>

inherit FORCE;

// regenerate 一式的消耗/折算參數。
#define ZS_COST     30      // 每次運功扣除的 gin、kee 當前值(各)。
#define ZS_RATE     2       // 化氣為神的基礎折算比：每 ZS_RATE 點氣血換 1 點 sen。

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("zushang");
    // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
    CHINESE_D->add_translate("zushang", "竹上經心法");
    setup();
}

// 龍圖丹派方士打坐運轉竹上經時所現的內功氣象。
string cultivate_msg()
{
    return WHT "$N盤膝閉目﹐緩緩運轉竹上經心法﹐周身氣血如竹節節升﹐"
               "一呼一吸間化氣血為神識﹐溫養丹田﹐調息歸元。\n" NOR;
}

// exert regenerate -- 調息歸元：消當前 gin/kee﹐回補 sen 當前值與最大可癒值。
// 其餘 func 落回 FORCE 基底(打坐修煉 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
    int gin_have, kee_have, spent, gain, eff, rate;

    if( !objectp(me) ) me = this_player();
    if( !objectp(me) ) return 0;

    if( func != "regenerate" )
        return ::exert_function(me, func, target);

    gin_have = me->query_stat("gin");
    kee_have = me->query_stat("kee");

    // 氣血不足以運功歸元。
    if( gin_have < ZS_COST || kee_have < ZS_COST )
        return notify_fail("你體內氣血不足﹐沒有辦法運轉竹上經調息歸元。\n");

    // sen 已滿(當前值與可癒上限俱達最大)則毋須回補。
    if( me->query_stat_current("sen") >= me->query_stat_maximum("sen")
    &&  me->query_stat_effective("sen") >= me->query_stat_maximum("sen") )
        return notify_fail("你神識飽滿﹐此刻運轉竹上經並無增益。\n");

    // 消耗當前的氣(gin)與精(kee)。consume_stat 只削 current 值。
    spent = ZS_COST;
    me->consume_stat("gin", spent, me);
    me->consume_stat("kee", spent, me);

    // 化氣為神：折算成回補的 sen。竹上經火候愈高﹐折損愈少(換算愈有效率)。
    rate = ZS_RATE;
    if( rate < 1 ) rate = 1;
    gain = (spent * 2) / rate;                       // gin+kee 共 spent*2 點氣血。
    gain += me->query_skill("zushang", 1) / 20;      // 火候加成：每 20 級多回 1。
    if( gain < 1 ) gain = 1;

    // 回 sen 當前值(supplement_stat 自動封頂於 heal/max)。
    me->supplement_stat("sen", gain);
    // 回 sen 最大可癒值(heal_stat 自動封頂於 max)。
    me->heal_stat("sen", gain);

    message_vision(HIC
        "$N盤膝凝神﹐運轉竹上經心法﹐周身氣血翻湧內斂﹐化作一縷清純神識"
        "緩緩沉入丹田。\n" NOR, me);
    tell_object(me, sprintf(HIW
        "你只覺氣力稍減﹐神識卻為之一振。(消 gin/kee 各 %d﹐回 sen %d)\n" NOR,
        spent, gain));

    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
