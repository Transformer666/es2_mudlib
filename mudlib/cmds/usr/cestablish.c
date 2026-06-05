// cestablish.c -- 查詢/確立「頂級稱號 (ad_rank)」。
//
// 業力與聲望系統 (docs/02-遊戲系統與機制/04-業力與聲望.md L81-101) 的玩家介面：
//   * cestablish            : 重新評定自己目前可得的最高稱號、換掛其戰鬥加成，並顯示
//                             目前稱號與全部頂級稱號的加成一覽。
//   * cestablish <對象>     : (巫師專用) 重評並查看他人稱號。
//
// 評定/加成邏輯全在 daemon/misc/title.c (TITLE_D)：query_ad_rank 掃 docs 各門檻回最高
// 稱號、apply_title 換掛 apply/* 加成、recalc 兩者兼做並通知。本指令只是薄介面層。
// 中文別名見 cmds/usr/稱號.c。
//
// 模型鏡 cmds/usr/reputation.c (唯讀顯示 + 巫師可查他人) 與 cmds/usr/score.c。

#include <ansi.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    object ob;
    string cur, rank, *order;

    if( !arg || arg == "" )
        ob = me;
    else {
        if( !wizardp(me) )
            return notify_fail("只有巫師能確立別人的稱號。\n");
        ob = present(arg, environment(me));
        if( !ob ) ob = find_player(arg);
        if( !ob ) ob = find_living(arg);
        if( !ob )
            return notify_fail("你要確立誰的稱號﹖\n");
    }

    // 重評並換掛加成 (recalc 內含升格/失格通知)。回目前稱號 key (或 0)。
    cur = TITLE_D->recalc(ob);

    write(sprintf(HIW "【 %s 】" NOR "%s 的頂級稱號\n\n", ob->rank(), ob->short(1)));

    if( cur )
        write(sprintf(HIY " 你目前的頂級稱號是「%s」，加成﹕%s。\n" NOR,
            TITLE_D->title_chinese(cur), TITLE_D->describe_bonus(cur)));
    else
        write(CYN " 你目前尚未達到任何頂級稱號的門檻。\n" NOR);

    // 列出全部頂級稱號及其加成，並標出已達標者，作為長線目標一覽。
    write(HIW "\n 江湖頂級稱號一覽 (詳細門檻請參閱業力與聲望設定)﹕\n" NOR);
    order = TITLE_D->query_rank_order();
    foreach( rank in order ) {
        string mark;
        mark = (rank == cur) ? HIG " ★現任" NOR : "";
        write(sprintf("   %-10s 加成﹕%s%s\n",
            TITLE_D->title_chinese(rank), TITLE_D->describe_bonus(rank), mark));
    }

    write("\n" CYN " (各軸聲望請用 reputation；技能請用 skills。)\n" NOR);
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : cestablish                        (確立並查看自己的頂級稱號)
           cestablish <對象名稱>             (巫師專用)

頂級稱號 (如邪魔、武聖、劍聖、隱士、大元帥、鬼仙人等) 是江湖中的最高榮譽，需
長期累積多軸聲望、殺業/惡行、精熟、屬性與等級才能取得。取得後會自動獲得對應的
戰鬥加成 (傷害、護甲、防禦、攻勢或屬性等)。

這個指令會重新評定你目前可得的「最高」稱號、換掛其加成，並列出所有頂級稱號的
加成一覽供你規劃長線目標。一旦你的條件達標 (或不再達標)，稱號與加成都會即時更新。

中文別名為「稱號」。其他相關指令﹕reputation、score、skills
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
