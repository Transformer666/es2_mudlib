// 茅山奇術【遁甲書】 taoism of dunja -- 茅山隱風觀的奇門遁甲祕術(magic 槽 / conjure 指令)
//
// 來歷(docs/03-門派與武功/02-道士-天師與茅山.md L232-254)：遁甲書是茅山隱風觀
// 進階奇術﹐由「歐陽無寂」傳授﹐門檻為「茅山幻術(taoism of nature) ≥90、等級與
// 靈性(spi) ≥30」。它不是攻擊咒術﹐而是測命與授藝的奇門之術﹐故掛在 magic 槽、
// 走 conjure 指令(同 daemon/skill/taoism-cloud.c 素雲書駕雲術的定位)﹐而非 spells
// 槽 / cast 指令。道士可同時 `enable spells with taoism of nature`(攻擊召獸)與
// `enable magic with taoism-of-dunja`(測命授藝)﹐兩槽兩不相礙。
//
// 本檔先實作 docs 載明、且可自足(不依賴未建引擎)的兩式(L236-239)：
//
//   天命 fate       ── `conjure 天命 <技能id> on <目標>`
//       測算「目標玩家」在某技能上的天賦(潛能)。讀 target->query_talent(skill)﹐
//       依 docs L241-253 的遁甲書專用斷語表(用詞與算命先生不同)當眾道出。
//       純讀不改﹐唯耗施法者少量神(sen)為運卦之資。
//
//   心眼 experience ── `conjure 心眼 <技能id> on <目標>`
//       消「施法者自身的法術修為(神 sen)」﹐反哺提升「目標」對應技能的經驗
//       (learned)──即 target->improve_skill(skill, amount)。docs L239 明定
//       「技能 <30 無效」：目標該技能等級不足 30 則點化不入﹐不耗神。
//
// 奇門五式(記憶/翔空/集靈/通靈/噬魂)屬另一進階技能【奇門術】mao-shan mysticism
// (docs L271-281﹐整個 daemon 缺檔)﹐涉及記錄座標、屍體分解、陰魂控制等未建引擎﹐
// 本批不做﹐見檔末 TODO 區塊。
//
// === 派發路徑(cmds/std/conjure.c::main L20-33)===
//   玩家鍵入 `conjure 天命 sword on dengfeng`。conjure.c 以
//   sscanf(arg,"%s on %s",spl,trg) 切出 spl="天命 sword"、trg="dengfeng"﹐
//   present(trg) 解出 target 物件﹐再 spl = replace_string(spl," ","_") 得
//   "天命_sword"﹐取 me->skill_mapped("magic")(= 已掛上的 magic key﹐此處為
//   "taoism-of-dunja")﹐呼 SKILL_D("taoism-of-dunja")->conjure_magic(me,spl,target)。
//   本檔接到 spl﹐以第一個底線切出「式名(天命/心眼/fate/experience)」與「技能id」﹐
//   分派到 do_fate / do_experience。NPC 由 std/char/npc.c::conjure_magic(magic)
//   傳 (me, magic)﹐target 省略﹐本式以測命/授藝為主、對 NPC 無意義﹐優雅回 0。
//
// runtime 鐵則：本式不涉 ::die()/destruct()/replace_program﹔為 magic daemon
// (inherit /std/magic)﹐不 include <weapon.h>。

#include <ansi.h>

inherit "/std/magic";

// === 門檻(docs L234 載明)===
#define DJ_GATE_SKILL   "taoism of nature"  // 前置技能：茅山幻術。
#define DJ_GATE_NATURE  90                  // 茅山幻術火候下限。
#define DJ_MIN_LEVEL    30                  // 等級下限。
#define DJ_MIN_SPI      30                  // 靈性(spi 屬性)下限。

// === 心眼授藝參數 ===
#define DJ_EXP_MIN_SKILL    30      // docs L239：目標技能 <30 無效。
#define DJ_EXP_SEN_COST     50      // 每次點化消施法者神(sen)。
#define DJ_EXP_GAIN_BASE    20      // 授予目標的基礎經驗(learned)增量。

// 前置宣告(lesson #12：自訂函式一律檔頭前置宣告﹐免「定義前引用」編譯失敗﹐
// 亦免 daemon lazy-load 因 Undefined function 靜默失敗)。
varargs int conjure_magic(object me, string spl, object target);
int valid_enable(string usage);
int dj_check_caster(object me);
string dj_fate_verdict(int talent);
int do_fate(object me, string skill, object target);
int do_experience(object me, string skill, object target);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("taoism-of-dunja");
    // 登錄中文名﹐使 enable / skills 等顯示「遁甲書」而非英文代號。
    CHINESE_D->add_translate("taoism-of-dunja", "遁甲書");
    setup();
}

// 本技能掛在 magic 槽(測命授藝)﹐而非 spells 槽(攻擊)。
// 覆寫 /std/magic.c 的 valid_enable(原本只認 "spells")﹐改認 "magic"
// (同 daemon/skill/taoism-cloud.c 素雲書)。
int valid_enable(string usage)
{
    return usage == "magic";
}

// 施法者資格與火候總檢：須為茅山道士、已習遁甲書、且滿足三門檻
// (茅山幻術 ≥90、等級 ≥30、靈性 ≥30)。不足則 notify_fail 說明後回 0。
int dj_check_caster(object me)
{
    if( !objectp(me) ) return 0;

    // 須為道士、且為茅山派。
    if( me->query_class() != "taoist" ) {
        notify_fail("遁甲書是茅山道門的奇門祕術﹐你並非道士﹐運使不來。\n");
        return 0;
    }
    if( me->query("sect") != "茅山派" ) {
        notify_fail("遁甲書乃茅山隱風觀祕傳﹐外人縱知其名﹐亦無從窺其堂奧。\n");
        return 0;
    }

    // 須已習得遁甲書。
    if( me->query_skill("taoism-of-dunja", 1) <= 0
    &&  !me->query_learn("taoism-of-dunja") ) {
        notify_fail("你並未習得「遁甲書」。\n");
        return 0;
    }

    // 門檻一：茅山幻術火候。
    if( me->query_skill(DJ_GATE_SKILL, 1) < DJ_GATE_NATURE ) {
        notify_fail(sprintf(
            "你茅山幻術的根基尚淺(需茅山幻術 %d)﹐推演不動遁甲奇門。\n",
            DJ_GATE_NATURE));
        return 0;
    }

    // 門檻二：等級。
    if( me->query_level() < DJ_MIN_LEVEL ) {
        notify_fail(sprintf(
            "你修為尚淺(需等級 %d)﹐參不透遁甲書的奇門變化。\n", DJ_MIN_LEVEL));
        return 0;
    }

    // 門檻三：靈性(spi)。
    if( me->query_attr("spi") < DJ_MIN_SPI ) {
        notify_fail(sprintf(
            "你靈性不足(需靈性 %d)﹐窺不見遁甲書所示的天機。\n", DJ_MIN_SPI));
        return 0;
    }

    return 1;
}

// ── 天命斷語表(docs L241-253)──
// 遁甲書專用斷語﹐用詞與喬陰縣算命先生(cmds/std/inquire.c)不同。天賦範圍
// 140~200﹐以 >=200/>=190/.../>=150 對應七檔斷語﹐不足 140 一檔「和前輩一樣」。
string dj_fate_verdict(int talent)
{
    if( talent >= 200 ) return "無可限量";
    if( talent >= 190 ) return "笑傲江湖";
    if( talent >= 180 ) return "名揚天下";
    if( talent >= 170 ) return "確實不錯";
    if( talent >= 160 ) return "一番成就";
    if( talent >= 150 ) return "普普通通";
    if( talent >= 140 ) return "沒有前途";
    return "和前輩一樣";        // 天賦不足 140。
}

// 天命 fate：測算目標在某技能上的天賦(潛能)﹐照斷語表道出。純讀不改。
// 耗施法者少量神(sen)為運卦之資。
int do_fate(object me, string skill, object target)
{
    int talent, sen_cost;

    if( !stringp(skill) || skill == "" )
        return notify_fail("你要替誰測算哪一門技藝的天命﹖"
            "(格式﹕conjure 天命 <技藝英文代號> on <對象>)\n");

    if( !objectp(target) || !living(target) )
        return notify_fail("你要對誰運起遁甲書的「天命」之術﹖\n");

    if( environment(me) != environment(target) )
        return notify_fail("測算的對象不在這裡。\n");

    // 目標須確有此技藝的天賦顯現(query_talent>0)﹐否則卦象無從推起。
    talent = target->query_talent(skill);
    if( talent <= 0 ) {
        if( target->query_skill(skill, 1) <= 0 )
            return notify_fail(
                target->name() + "連「" + to_chinese(skill)
                + "」的皮毛都未沾過﹐遁甲書推不出個名堂來。\n");
        return notify_fail(
            target->name() + "這門「" + to_chinese(skill)
            + "」是旁人硬塞的﹐自個兒還沒下過苦功﹐根骨未顯﹐天命難測。\n");
    }

    // 運卦耗神(少量)。神不足則卦象不清。
    sen_cost = 20;
    if( me->query_stat("sen") < sen_cost )
        return notify_fail("你神識不足以推演遁甲奇門﹐卦象模糊難辨。\n");
    me->consume_stat("sen", sen_cost, me);

    message_vision(HIM
        "$N閉目掐指﹐口中默運遁甲書的奇門口訣﹐周身隱隱浮起一片幽光﹐"
        "凝神替$n推算起天命來。\n" NOR, me, target);

    tell_object(me, sprintf(HIW
        "遁甲書卦象既成﹐$N在「%s」一道上的天命是──%s。\n" NOR,
        target->name(), dj_fate_verdict(talent)));
    // 讓中文技藝名也顯出來﹐便於玩家對照。
    tell_object(me, sprintf(HIC
        "（你測算的是%s的根骨潛能。）\n" NOR, to_chinese(skill)));

    // 練技(僅玩家﹔NPC 技能固定)。
    if( userp(me) )
        me->improve_skill("taoism-of-dunja", 1 + random(2));

    return 1;
}

// 心眼 experience：消施法者自身法術修為(神 sen)﹐反哺提升目標對應技能的經驗
// (learned)。docs L239：目標該技能 <30 無效。
int do_experience(object me, string skill, object target)
{
    int tskill, gain;

    if( !stringp(skill) || skill == "" )
        return notify_fail("你要點化誰的哪一門技藝﹖"
            "(格式﹕conjure 心眼 <技藝英文代號> on <對象>)\n");

    if( !objectp(target) || !living(target) )
        return notify_fail("你要對誰運起遁甲書的「心眼」之術﹖\n");

    if( environment(me) != environment(target) )
        return notify_fail("點化的對象不在這裡。\n");

    // 目標須已具該技能(且 >=30)方能受心眼點化(docs L239：<30 無效)。
    tskill = target->query_skill(skill, 1);
    if( tskill <= 0 )
        return notify_fail(
            target->name() + "並未習得「" + to_chinese(skill)
            + "」﹐心眼無從點化。\n");
    if( tskill < DJ_EXP_MIN_SKILL )
        return notify_fail(sprintf(
            "%s的「%s」火候尚淺(需 %d 級以上)﹐心眼點化不入。\n",
            target->name(), to_chinese(skill), DJ_EXP_MIN_SKILL));

    // 消施法者法術修為(神 sen)。神不足則點化不成。
    if( me->query_stat("sen") < DJ_EXP_SEN_COST )
        return notify_fail("你的法術修為(神識)不足以運起心眼點化他人。\n");
    me->consume_stat("sen", DJ_EXP_SEN_COST, me);

    // 授予目標經驗(learned)：基礎量隨施法者遁甲書火候微增。
    gain = DJ_EXP_GAIN_BASE + me->query_skill("taoism-of-dunja") / 10;
    if( gain < 1 ) gain = 1;
    target->improve_skill(skill, gain);

    message_vision(HIM
        "$N凝神運起遁甲書的「心眼」之術﹐一指虛點$n眉心﹐"
        "似有一縷靈光自$N指尖渡入$n識海。\n" NOR, me, target);
    tell_object(me, sprintf(HIW
        "你耗去一身法術修為﹐將「%s」的訣竅點化予%s。\n" NOR,
        to_chinese(skill), target->name()));
    if( target != me )
        tell_object(target, sprintf(HIC
            "%s的心眼點化渡入你識海﹐你對「%s」的體悟似有所進。\n" NOR,
            me->name(), to_chinese(skill)));

    // 練技(僅玩家﹔NPC 技能固定)。
    if( userp(me) )
        me->improve_skill("taoism-of-dunja", 1 + random(2));

    return 1;
}

// conjure_magic(me, spl, [target])
//   spl 形如 "天命_sword" / "心眼_force" / "fate_sword" / "experience_force"
//   (conjure.c 已把空白換成底線)。以第一個底線切出「式名」與「技能id」。
//   失敗回 0(並 notify_fail 給玩家路徑)﹐成功回 1。
varargs int
conjure_magic(object me, string spl, object target)
{
    string mode, skill;

    if( !objectp(me) ) me = this_player();
    if( !objectp(me) || !stringp(spl) ) return 0;

    // 施法者資格與火候總檢。
    if( !dj_check_caster(me) ) return 0;

    // 非施法之地不可運使(鏡 conjure.c 的 no_magic 守則﹐taoism-cloud 同此)。
    if( !objectp(environment(me)) )
        return notify_fail("你身處虛無之地﹐無從推演遁甲奇門。\n");
    if( environment(me)->query("no_magic") )
        return notify_fail("這裡不准施展法術﹐遁甲奇門亦運使不得。\n");

    // 切出式名與技能id：以第一個底線為界。
    if( sscanf(spl, "%s_%s", mode, skill) != 2 ) {
        mode = spl;
        skill = "";
    }

    switch( mode ) {
        case "天命":
        case "fate":
            return do_fate(me, skill, target);
        case "心眼":
        case "experience":
            return do_experience(me, skill, target);
    }

    notify_fail(
        "遁甲書現可運使「天命」與「心眼」二式：\n"
        "    conjure 天命 <技藝英文代號> on <對象>   測算對方天賦\n"
        "    conjure 心眼 <技藝英文代號> on <對象>   點化對方技藝\n");
    return 0;
}

// ── TODO(奇門五式：屬另一技能【奇門術】mao-shan mysticism﹐docs L271-281)──
// 記憶之術 memory  ── 記錄當前座標(需玩家座標持久化欄位)。
// 翔空之術 recall  ── 飛回記錄點(同 taoism-cloud 的房間傳送﹐但目的地動態)。
// 集靈之術 collect ── 分解屍體得陰魂(需屍體物件 / 陰魂物件與「控制數=靈性」上限)。
// 通靈之術 slave   ── 陰魂附身控制目標(需附身/NPC 控制引擎﹔對玩家/動物無效)。
// 噬魂之術 devour  ── 犧牲被通靈目標﹐恢復大量氣神(依附 slave 之控制鏈)。
// 以上俱依賴未建的「陰魂 / 屍體分解 / 附身控制 / 座標記錄」引擎﹐另立
// daemon/skill/mao-shan-mysticism.c 實作﹐本批不做。

// vim: set ts=4 sw=4 syntax=lpc
