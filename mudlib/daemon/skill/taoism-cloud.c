// 天師派道法【素雲書】 taoism-cloud -- 駕雲傳送(travel magic)
//
// 這是一門 magic(法術)技能﹐天師派獨傳的駕雲之術。與攻擊咒術(taoism-fire/
// -freeze/youmin 走 spells 槽、cast 指令)不同﹐素雲書走 magic 槽、conjure 指令﹐
// 故道士可同時 `enable spells with taoism-fire`(攻擊) 與 `enable magic with
// taoism-cloud`(趕路)﹐兩不相礙。
//
// 機制：玩家 10 級與張齡(d/tianshi/yard)對話習得﹐`enable magic with
// taoism-cloud` 後﹐`conjure <地點代號|中文地名>` 駕雲飛往該地。每次耗 50 神
// (sen)﹐技能等級決定可達之處(見 query_nodes)。conjure 指令(cmds/std/conjure.c)
// 取玩家 magic 槽所映射的技能 daemon﹐呼叫其 conjure_magic()——本檔實作之。
// NPC 由 std/char/npc.c::conjure_magic(magic) 觸發﹐同樣落到本函式(target 省略)。

#include <ansi.h>

inherit "/std/magic";

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("taoism-cloud");
    // 登錄中文名﹐使 enable / skills 等顯示「素雲書」而非英文代號 taoism-cloud。
    CHINESE_D->add_translate("taoism-cloud", "素雲書");
    setup();
}

// 本技能掛在 magic 槽(趕路)﹐而非 spells 槽(攻擊)。
// 覆寫 /std/magic.c 的 valid_enable(原本只認 "spells")。
int valid_enable(string usage)
{
    return usage == "magic";
}

// ── 傳送節點表：代號 -> ([ level:技能門檻, dest:房間路徑, name:中文地名,
//                          msg:駕雲飛升的特殊訊息 ]) ──
// BUILT 的 dest 已是經查證存在的房間路徑﹔unbuilt 的填上規劃路徑﹐
// conjure_magic 內以 load_object 試載﹐載不起便優雅擋下(「傳送點未開」)。
mapping query_nodes()
{
    return ([
        // code        level  dest                          name        msg
        "snow"    : ([ "level":15,  "dest":"/d/snow/inn_hall",    "name":"飲風客棧", "msg":"一陣松濤過處﹐你已落在雪亭鎮飲風客棧的門前。" ]),
        "month"   : ([ "level":30,  "dest":"/d/shuiyue/falls",    "name":"水月瀑布", "msg":"水霧撲面而來﹐你已立在水月瀑布的飛濺珠簾之下。" ]),
        "sptown"  : ([ "level":45,  "dest":"/d/sptown/altar",     "name":"祭劍臺",   "msg":"罡風漸歇﹐你已踏上肅穆的祭劍臺。" ]),
        "fontown" : ([ "level":60,  "dest":"/d/tianshan/cliff",   "name":"天山孤崖", "msg":"雲開霧散﹐你已落在天山一處孤峭的懸崖之上。" ]),
        "swaylan" : ([ "level":75,  "dest":"/d/wuling/inn",       "name":"武陵客棧", "msg":"桃花香撲鼻﹐你已落在水嵐武陵的五陵客棧前。" ]),
        "yaoy"    : ([ "level":90,  "dest":"/d/zhaoyin/inn",      "name":"天仁客棧", "msg":"山風送爽﹐你已落在兆隱縣城的天仁客棧前。" ]),
        "skysnow" : ([ "level":105, "dest":"/d/skysnow/tree",     "name":"卯天樹",   "msg":"一片清光斂去﹐你已立在參天的卯天樹下。" ]),
        "flower"  : ([ "level":120, "dest":"/d/flower/redinn",    "name":"紅燈客棧", "msg":"脂粉暗香浮動﹐你已落在百花村的紅燈客棧前。" ]),
        "fei"     : ([ "level":135, "dest":"/d/feixian/tavern",   "name":"錢記酒樓", "msg":"酒香撲面﹐你已落在斐縣城中的錢記酒樓前。" ]),
        "tomb"    : ([ "level":150, "dest":"/d/tomb/ancient",     "name":"古墳墓",   "msg":"陰風森森﹐你已落在荒煙蔓草間的古墳墓前。" ]),
        "capital" : ([ "level":165, "dest":"/d/capital/lake",     "name":"後海湖",   "msg":"煙波浩渺映入眼簾﹐你已立在京畿西郊的後海湖畔。" ]),
        "dragon"  : ([ "level":180, "dest":"/d/dragon/isle",      "name":"天龍島",   "msg":"濤聲如雷﹐你已落在縹緲的天龍島上。" ]),
    ]);
}

// 解析咒名：先比代號(key)﹐再比中文地名。回傳該節點 mapping﹐找不到回 0。
private mapping resolve_node(string spl)
{
    mapping nodes, m;
    string code;

    nodes = query_nodes();
    if( !mapp(nodes) ) return 0;

    if( mapp(nodes[spl]) ) return nodes[spl];

    foreach( code, m in nodes )
        if( mapp(m) && m["name"] == spl ) return m;

    return 0;
}

// conjure_magic(me, spl, [target])
//   玩家：cmds/std/conjure.c 傳 (me, 代號/地名, 對象或0)。target 對傳送無用。
//   NPC ：std/char/npc.c::conjure_magic 傳 (me, magic)﹐target 省略。
// 失敗回 0(並 notify_fail 給玩家路徑)﹐成功回 1。
varargs int
conjure_magic(object me, string spl, object target)
{
    mapping node;
    object dest, here;
    string path;

    if( !objectp(me) || !stringp(spl) ) return 0;

    // 須為道士(且為天師派)方能駕雲。
    if( me->query_class() != "taoist" ) {
        notify_fail("素雲書是天師派的駕雲道法﹐你並非道門中人﹐運使不來。\n");
        return 0;
    }
    if( me->query("sect") != "天師派" ) {
        notify_fail("素雲書乃天師派祕傳﹐外人縱知其名﹐亦無從駕馭。\n");
        return 0;
    }

    // 須已習得素雲書。
    if( me->query_skill("taoism-cloud", 1) <= 0 && !me->query_learn("taoism-cloud") ) {
        notify_fail("你並未習得「素雲書」。\n");
        return 0;
    }

    // 解析目的地。
    node = resolve_node(spl);
    if( !mapp(node) ) {
        notify_fail("素雲書中並無「" + spl + "」這一道駕雲口訣。\n");
        return 0;
    }

    // 技能等級門檻。
    if( me->query_skill("taoism-cloud") < node["level"] ) {
        notify_fail("你素雲書的火候尚淺﹐運不起飛往「" + node["name"] + "」的雲訣。\n");
        return 0;
    }

    // 非施法之地不可駕雲(鏡 conjure.c 的 no_magic 守則)。
    here = environment(me);
    if( !objectp(here) ) {
        notify_fail("你身處虛無之地﹐無從駕雲。\n");
        return 0;
    }
    if( here->query("no_magic") ) {
        notify_fail("這裡不准施展法術﹐雲訣亦運使不得。\n");
        return 0;
    }
    // 交戰中心神不寧﹐不可駕雲遁走。
    if( me->is_fighting() ) {
        notify_fail("你正自纏鬥﹐心神不寧﹐難以運使雲訣脫身。\n");
        return 0;
    }

    // 試載目的地房間：未建成(載不起)便優雅擋下﹐且不扣神。
    path = node["dest"];
    if( catch(dest = load_object(path)) || !objectp(dest) ) {
        notify_fail("「" + node["name"] + "」此地尚不可達（傳送點未開）。\n");
        return 0;
    }

    // 神(sen)消耗檢查：須足 50 神。
    if( me->query_stat("sen") < 50 ) {
        notify_fail("你的神識不足以運使素雲書﹐至少需聚足五十神。\n");
        return 0;
    }

    // ── 通過所有檢查﹐正式駕雲(之後不再失敗)──
    me->consume_stat("sen", 50);

    message_vision(
        HIW "$N足下倏地湧起一片素白雲氣﹐捲著$N凌空飛升﹐霎時化作一道白光遠去。" NOR "\n",
        me);

    // 先移動﹐再進入吟誦/運法後的短暫無法行動(start_busy)。
    // 注意：std/char.c::move 在 is_busy() 時會拒絕移動﹐故 start_busy 必須後置。
    me->move(dest);

    message_vision(MAG + node["msg"] + NOR + "\n", me);

    me->start_busy(2);

    // 練技(僅玩家﹔NPC 技能固定)。
    if( userp(me) )
        me->improve_skill("taoism-cloud", 1 + random(2));

    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
