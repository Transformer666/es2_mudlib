// enmity.c -- 結仇 / 解仇：玩家之間的「私人仇家」系統 (F-Phase-3, decision F)。
//
// 依 docs/04-玩家社群與文化/02-結仇與PvP.md。本指令處理的是「玩家 對 玩家」
// 的私人結仇，與兩套既有系統嚴格區分﹕
//
//   (1) 紅人系統 (red-name, F-Phase-2, adm/daemons/chard.c 的 unprotect_mark)﹕
//       「非紅人 kill 非紅人 → 自身變紅」的非自願懲罰。任何人都能無代價殺紅人。
//   (2) 門派結仇 (PvE faction grudge)﹕NPC 身上的 "vendetta_mark"﹐玩家殺了
//       會在自己身上累積 query("vendetta/<門派>")﹐使該門派 NPC 主動圍攻
//       (feature/char/attack.c、adm/daemons/combatd.c::start_vendetta)。
//
// 本系統 = 第三種、雙方「自願 / 個人」的恩怨﹕A 正式對 B 宣告結仇﹐記在
// A 身上的 query("enmity/<B的id>")。為避免與門派 grudge 撞名﹐刻意改用
// "enmity/" 而非 "vendetta/" 命名空間。
//
// 資料結構 (存玩家物件﹐隨 SAVE_USER 持久化)﹕
//   query("enmity")          => ([ "<對方id>": ([
//                                   "time"   : 結仇時間戳,
//                                   "reason" : 結仇緣由(字串﹐可空),
//                                   "mutual" : 0/1,      // 是否「相互結仇」
//                               ]) ])
//
// 結仇 (enmity <id> [緣由])  ── 單方宣告對方為仇家。雙方都宣告 → 升為「相互
//                               結仇」(mutual=1)﹐此時 kill 對方屬「正當仇殺」﹐
//                               不會使自己變紅人 (見 adm/daemons/chard.c 的
//                               紅人 gate﹐已加掛 enmity 例外)。
// 解仇 (reconcile <id>)      ── 撤回自己這一方﹐並清掉雙方的 mutual 旗標。
//                               (中文別名指令見 cmds/std/結仇.c、解仇.c)
// 列表 (enmity)              ── 無參數時列出自己所有仇家及狀態。
//
// 設計理由﹕本 mudlib 的 kill/fight 一律「雙方各下一次指令才算數」(見
// cmds/std/kill.c、fight.c) ── 結仇沿用同一套「雙方合意」慣例﹕單方結仇只是
// 表態﹐唯有「相互結仇」才解鎖無紅人代價的仇殺。對稱地﹐解仇也採「任一方撤回
// 即降回單方」。docs 裡 NPC 主持的解仇 (哭無望、海大富、解仇毒刀「胡惑」) 全是
// 門派 grudge 的解法﹐與此私人恩怨無關﹐不在本指令範圍。

#include <ansi.h>

inherit F_CLEAN_UP;

// 撤回 me 對 target_id 的私人結仇﹕清掉 me 身上的紀錄﹐並把對方(若在線上且
// 仍視 me 為仇家)的 mutual 旗標降下。回傳是否真的有撤回任何東西。
private int do_reconcile(object me, string target_id);

private void create()
{
    seteuid(getuid());
}

// 取得 me 身上的 enmity 子 mapping (保證回傳一份可讀的 mapping)。
private mapping my_enmity(object me)
{
    mapping m;

    m = me->query("enmity");
    if( !mapp(m) ) m = ([ ]);
    return m;
}

// 列出 me 所有的私人仇家。
private int list_enemies(object me)
{
    mapping m, e;
    string id, line;
    string *ids;
    int i;

    m = my_enmity(me);
    ids = keys(m);
    if( !sizeof(ids) ) {
        write("你目前與人無冤﹐和氣生財﹐並未對任何人結仇。\n");
        return 1;
    }

    line = HIW "你目前結下的私人仇家﹕\n" NOR;
    for( i = 0; i < sizeof(ids); i++ ) {
        id = ids[i];
        e = m[id];
        if( !mapp(e) ) e = ([ ]);
        line += sprintf("  %s%-12s" NOR " %s  %s\n",
            e["mutual"] ? HIR : HIY,
            capitalize(id),
            e["mutual"] ? HIR "【相互結仇 ─ 仇殺無紅人代價】" NOR
                        : YEL "(單方結仇﹐對方尚未回應)" NOR,
            (stringp(e["reason"]) && e["reason"] != "")
                ? "緣由﹕" + e["reason"] : "");
    }
    line += "\n相互結仇者﹐可對其 kill 而不致淪為紅人﹔欲化解請用 reconcile <id>。\n";
    write(line);
    return 1;
}

int main(object me, string arg)
{
    object who;
    mapping m, e, te;
    string target_id, reason, verb;
    int file_exists;

    if( me->query("life_form") == "ghost" )
        return notify_fail("人都死了﹐還結什麼仇﹖快去找城隍復活吧!!\n");

    // 無參數 → 列出仇家。
    if( !arg || arg == "" )
        return list_enemies(me);

    // 解仇 (reconcile) 由本指令的 reconcile 子動詞﹐或獨立的 reconcile.c 進來。
    // 這裡先攔「reconcile <id>」形式 (方便 enmity 與 reconcile 共用一支實作)。
    if( sscanf(arg, "reconcile %s", target_id) == 1 )
        verb = "reconcile";
    else {
        verb = "enmity";
        // 「enmity <id> [緣由]」﹕第一個 token 為對方 id﹐其餘為緣由。
        if( sscanf(arg, "%s %s", target_id, reason) != 2 ) {
            target_id = arg;
            reason = "";
        }
    }

    target_id = lower_case(target_id);

    if( target_id == me->query("id") )
        return notify_fail("你不能跟自己結仇﹐也無從跟自己解仇。\n");

    if( verb == "reconcile" ) {
        if( !do_reconcile(me, target_id) )
            return notify_fail("你並沒有對「" + capitalize(target_id)
                + "」結仇﹐何來化解﹖\n");
#ifdef SAVE_USER
        me->save();
#endif
        return 1;
    }

    // ---- 以下為結仇 (enmity <id> [緣由]) ----

    // 對方可離線﹕優先取線上物件﹐否則檢查存檔是否存在以確認真有此人。
    who = find_player(target_id);
    if( !who ) {
        seteuid(getuid());
        file_exists = (file_size(user_data(target_id)) > 0);
        if( !file_exists )
            return notify_fail("江湖上並無「" + capitalize(target_id)
                + "」這號人物。\n");
    } else if( wizardp(who) )
        return notify_fail("仙師超然物外﹐豈是你能結仇的對象﹖\n");

    m = my_enmity(me);

    if( mapp(m[target_id]) )
        return notify_fail("你早已視「" + capitalize(target_id)
            + "」為仇家了﹐不必再宣告一次。(欲化解請用 reconcile)\n");

    // 寫下自己這一方的結仇紀錄。
    e = ([
        "time"   : time(),
        "reason" : stringp(reason) ? reason : "",
        "mutual" : 0,
    ]);

    // 若對方也早已視我為仇家 → 立刻升為「相互結仇」。
    if( who ) {
        te = who->query("enmity");
        if( mapp(te) && mapp(te[me->query("id")]) ) {
            e["mutual"] = 1;
            te[me->query("id")]["mutual"] = 1;
            who->set("enmity/" + me->query("id"), te[me->query("id")]);
            tell_object(who, HIR "\n" + me->name() + "(" + me->query("id")
                + ")也對你下了結仇令 ── 你們從此" HIW "相互結仇"
                HIR "﹐生死各安天命﹗\n" NOR);
#ifdef SAVE_USER
            who->save();
#endif
        }
    }

    me->set("enmity/" + target_id, e);

    if( e["mutual"] ) {
        message_vision("\n$N咬牙切齒﹐與" + capitalize(target_id)
            + "正式" HIW "相互結仇" NOR "﹐自此恩怨兩清、生死搏命﹗\n", me);
        tell_object(me, HIR "你與「" + capitalize(target_id)
            + "」已是相互結仇﹐日後 kill 此人乃正當仇殺﹐不致淪為紅人。\n" NOR);
    } else {
        tell_object(me, HIY "你已將「" + capitalize(target_id)
            + "」列為仇家。\n"
            "這只是你單方面的宣告 ── 唯有對方也對你結仇、成為「相互結仇」﹐\n"
            "你 kill 此人才算正當仇殺而不變紅人。\n" NOR);
        if( who )
            tell_object(who, HIR "\n" + me->name() + "(" + me->query("id")
                + ")宣告與你結仇﹗\n" NOR
                "若你也要與此人不死不休﹐請對其下「enmity " + me->query("id")
                + "」﹐你們便成相互結仇。\n");
    }

    log_file("ENMITY", sprintf("[%s] %s(%s) 結仇 %s%s\n",
        ctime(time()), me->name(), me->query("id"), capitalize(target_id),
        e["mutual"] ? " (相互結仇)" : ""));

#ifdef SAVE_USER
    me->save();
#endif
    return 1;
}

private int do_reconcile(object me, string target_id)
{
    object who;
    mapping m, te;

    m = my_enmity(me);
    if( !mapp(m[target_id]) ) return 0;

    // 撤回自己這一方。
    me->delete("enmity/" + target_id);

    // 對方若在線上且仍把我列為仇家﹐把他那一筆的 mutual 旗標降回單方。
    who = find_player(target_id);
    if( who ) {
        te = who->query("enmity");
        if( mapp(te) && mapp(te[me->query("id")])
        &&  te[me->query("id")]["mutual"] ) {
            te[me->query("id")]["mutual"] = 0;
            who->set("enmity/" + me->query("id"), te[me->query("id")]);
            tell_object(who, HIY "\n" + me->name() + "(" + me->query("id")
                + ")向你示好﹐撤回了對你的結仇 ── 你們不再是相互結仇。\n"
                "(你對其的結仇仍在﹔若要一併化解請用 reconcile "
                + me->query("id") + ")\n" NOR);
#ifdef SAVE_USER
            who->save();
#endif
        }
    }

    tell_object(me, HIG "你放下了與「" + capitalize(target_id)
        + "」的恩怨﹐撤回結仇。\n" NOR);
    message_vision("\n$N長嘆一聲﹐似是放下了一段恩怨情仇。\n", me);

    log_file("ENMITY", sprintf("[%s] %s(%s) 解仇 %s\n",
        ctime(time()), me->name(), me->query("id"), capitalize(target_id)));
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 ﹕
    enmity                      列出你所有的私人仇家及狀態
    enmity <玩家id> [緣由]      正式對某玩家宣告結仇﹐視其為私人仇家
    reconcile <玩家id>          化解 (撤回) 你對某玩家的結仇

「結仇」是玩家與玩家之間私人的恩怨。當你對某人 enmity﹐只是你單方面的宣告﹔
唯有對方也對你 enmity﹐雙方成為「相互結仇」﹐你才可以對其使用 kill 而不會
因此淪為紅人 ── 這是正當的仇家相搏。

注意﹕「相互結仇」只是免去你殺對方時自己變紅人的代價﹐並不會免除其他後果
(屍體、撿屍、業力等照常)﹔也不影響紅人系統 ── 殺害並未與你相互結仇的清白
玩家﹐你仍會變成紅人。

化解恩怨請用 reconcile﹔任一方撤回﹐即不再是相互結仇。

中文別名﹕結仇 (= enmity)、解仇 (= reconcile)、仇家 (= enmity 列表)。
其他相關指令﹕kill、fight
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
