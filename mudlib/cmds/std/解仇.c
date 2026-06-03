// 解仇.c -- 「解仇」的中文指令別名﹐直接轉呼叫 enmity 的 reconcile 流程。
//
// 邏輯全寫在 cmds/std/enmity.c (以 "reconcile <id>" 形式統一處理)。指令以
// 「檔名 == 動詞」查找 (見 adm/daemons/cmd_d.c)﹐故中文動詞「解仇」可直接使用。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    if( !arg || arg == "" )
        return notify_fail("你要跟誰解仇﹖指令格式﹕解仇 <玩家id>\n");
    return (int)"/cmds/std/enmity"->main(me, "reconcile " + arg);
}

int help(object me)
{
    return (int)"/cmds/std/enmity"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
