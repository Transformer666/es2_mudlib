// 丹道【神農之術】 alchemy-medication -- 龍圖丹派(alchemist.dragon)方士的封丹之術
//
// 來源：docs/02-遊戲系統與機制/06-煉丹與書本系統.md
//   L56「conjure green seal on reactor（封丹鼎）」、
//   L66「conjure green dispel on reactor（解丹鼎）」、
//   L90「丹道【神農之術】alchemy-medication — green/white/red/purple/yellow/gray/
//        black seal & dispel — 7 種印封解青銅丹鼎」。
//
// 機制：神農之術掛在 magic 槽(走 conjure)﹐玩家
//   `enable magic with alchemy-medication` 後﹕
//     conjure green seal on reactor    -> 封住青銅丹鼎(reactor->set_sealed(1))。
//     conjure green dispel on reactor  -> 解開青銅丹鼎(reactor->set_sealed(0))。
//   docs 另列 white/red/purple/yellow/gray/black 共 7 色印訣。本實作先落實 docs
//   通篇示範的 green(綠印)﹐其餘 6 色暫以「佔位」回覆(尚未啟用﹐標 TODO)﹐
//   待各色對應的特殊封印效果定義後補上(集中於 SEAL_COLORS / handle 分派)。
//
// === 派發路徑(cmds/std/conjure.c) ===
//   conjure <咒> on <目標>：conjure.c::main 將咒名中的空白換成底線(故收到
//   "green_seal" / "green_dispel")﹐取 me->skill_mapped("magic")(此處映射到
//   "alchemy-medication")﹐呼 SKILL_D("alchemy-medication")->conjure_magic(me,
//   spl, target)——本檔實作之。target 為 conjure.c 以 present() 在環境/身上解出的
//   物品(此處應為青銅丹鼎 reactor)。結構鏡 alchemy-wealth.c / taoism-cloud.c。
//
// === 消耗 ===
//   封 / 解各消 SEN_COST 神(sen)﹐通過所有檢查、正式行法時才扣(鏡 alchemy-wealth)。
//   技能門檻：須已習得 alchemy-medication(query_skill > 0 或 query_learn)。
//
// runtime 鐵則：本式只對「死物」青銅丹鼎 set 旗標﹐不涉 living die/destruct(#10)﹐
//   不 replace_program(#11)。為 magic daemon(inherit /std/magic)﹐非 F_VILLAGER
//   NPC﹐不 include <weapon.h>(#12)。前置宣告自訂函式(#12)。

#include <ansi.h>

inherit "/std/magic";

// === 參數 ===
#define AM_SEN_COST     15      // 每次封 / 解消耗的神(sen)﹐鏡黃白之術 15 神。

// 七色印訣(docs L90)。green 已啟用﹔其餘 6 色佔位(TODO：定義各色特殊封印效果)。
#define SEAL_COLORS ({ "green","white","red","purple","yellow","gray","black" })

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯失敗﹐
// 並免 daemon lazy-load 靜默失敗)。
varargs int conjure_magic(object me, string spl, object target);
private int do_seal(object me, object target, int sealing, string color);
private string *parse_seal(string spl);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("alchemy-medication");
    // 自行登錄中文名﹐字典查無此 key 時 to_chinese()/enable/skills 仍工整顯示。
    CHINESE_D->add_translate("alchemy-medication", "神農之術");
    setup();
}

// 神農之術掛在 magic 槽(走 conjure)﹐而非 spells 槽(走 cast)。
// 覆寫 /std/magic.c 的 valid_enable(原本只認 "spells")﹐鏡 alchemy-wealth/taoism-cloud。
int valid_enable(string usage)
{
    return usage == "magic";
}

// parse_seal -- 解析咒名 -> ({ 色, 動作 })。
//   咒名形如 green_seal / green seal / green_dispel / green dispel
//   (conjure.c 已把空白換底線﹐兩式皆容)。
//   回 ({ color, act })(act 為 "seal" / "dispel")﹔不合法回 0。
//   (本驅動不支援純量 by-ref 參數﹐故以陣列回傳﹐由呼叫端拆解﹐避免 &var 慣例。)
private string *parse_seal(string spl)
{
    string c, act;

    if( !stringp(spl) ) return 0;

    // 先試底線式(green_seal)﹐再試空白式(green seal)。
    if( sscanf(spl, "%s_%s", c, act) != 2
    &&  sscanf(spl, "%s %s", c, act) != 2 )
        return 0;

    if( member_array(c, SEAL_COLORS) < 0 ) return 0;
    if( act != "seal" && act != "dispel" ) return 0;

    return ({ c, act });
}

// conjure_magic(me, spl, [target])
//   玩家：cmds/std/conjure.c 傳 (me, 咒名(空白已換底線), 以 present 解出的物品或 0)。
//   失敗回 0(並 notify_fail 給玩家路徑)﹐成功回 1。
varargs int
conjure_magic(object me, string spl, object target)
{
    string color;
    int sealing;
    string *parsed;

    if( !objectp(me) || !stringp(spl) ) return 0;

    // 須已習得神農之術。
    if( me->query_skill("alchemy-medication", 1) <= 0
    &&  !me->query_learn("alchemy-medication") ) {
        notify_fail("你並未習得「神農之術」。\n");
        return 0;
    }

    // 解析印訣。
    parsed = parse_seal(spl);
    if( !arrayp(parsed) || sizeof(parsed) != 2 ) {
        notify_fail("神農之術以印訣封解青銅丹鼎﹐用法："
            "conjure green seal on reactor（封）／"
            "conjure green dispel on reactor（解）。\n");
        return 0;
    }
    color   = parsed[0];
    sealing = (parsed[1] == "seal") ? 1 : 0;

    // 七色之中﹐目前只啟用 green(綠印)﹔其餘 6 色佔位(TODO)。
    if( color != "green" ) {
        notify_fail(sprintf(
            "「%s 印」之訣尚未參透（神農之術七色印訣中﹐目前只通綠印 green）。\n",
            color));
        return 0;
    }

    return do_seal(me, target, sealing, color);
}

// do_seal -- 封 / 解青銅丹鼎本體。
//   target ：conjure <咒> on <reactor> 解出的丹鼎。
//   sealing：1 封﹐0 解。
//   守則(動手前全部查完﹐通過才扣神)：
//     - 須指定對象﹐且對象須為青銅丹鼎(query("reactor"))。
//     - 須在可施法之地(no_magic 守則﹐鏡 conjure.c)。
//     - 封時鼎若已封 / 解時鼎若未封 -> 提示﹐不扣神。
//     - 神須足 AM_SEN_COST。
//   通過後消神﹐呼 reactor->set_sealed(sealing)﹐練技。成功回 1。
private int do_seal(object me, object target, int sealing, string color)
{
    object here;

    // 須指定青銅丹鼎。
    if( !objectp(target) )
        return notify_fail("你要對什麼施展神農印訣？(conjure green "
            + (sealing ? "seal" : "dispel") + " on reactor)\n");

    if( !target->query("reactor") )
        return notify_fail("神農之術的印訣只封得住青銅丹鼎﹐"
            + target->name() + "可封它不得。\n");

    // 非施法之地不可行法(鏡 conjure.c / alchemy-wealth 的 no_magic 守則)。
    here = environment(me);
    if( !objectp(here) ) {
        notify_fail("你身處虛無之地﹐無從施展神農之術。\n");
        return 0;
    }
    if( here->query("no_magic") ) {
        notify_fail("這裡不准施展法術﹐神農之術亦運使不得。\n");
        return 0;
    }

    // 狀態檢查：封一座已封的、或解一座沒封的﹐都白費。
    if( sealing && target->query_sealed() )
        return notify_fail(target->name() + "早已封住了。\n");
    if( !sealing && !target->query_sealed() )
        return notify_fail(target->name() + "本就沒封﹐何須解印？\n");

    // 神(sen)消耗檢查。
    if( me->query_stat("sen") < AM_SEN_COST )
        return notify_fail(sprintf(
            "你神識不足(需 %d 神)﹐運不起神農印訣。\n", AM_SEN_COST));

    // ── 通過所有檢查﹐正式行法(之後不再失敗)──
    me->consume_stat("sen", AM_SEN_COST);
    target->set_sealed(sealing);

    if( sealing )
        message_vision(HIG
            "$N捏訣於" + target->name() + "上一拂﹐一道綠光繞鼎一周﹐"
            "霎時封住了鼎口﹐聚住一鼎藥氣。\n" NOR, me);
    else
        message_vision(HIG
            "$N捏訣於" + target->name() + "上輕輕一引﹐繞鼎的綠光應手而散﹐"
            "鼎口的封印解開了。\n" NOR, me);

    tell_object(me, sprintf("(消神 %d)\n", AM_SEN_COST));

    // 練技(僅玩家﹔NPC 技能固定)。
    if( userp(me) )
        me->improve_skill("alchemy-medication", 1 + random(2));

    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
