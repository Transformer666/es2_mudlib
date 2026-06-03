// reconcile.c -- 解仇﹕化解 (撤回) 你對某玩家的私人結仇。
//
// 私人結仇 / 解仇 的完整邏輯都寫在 cmds/std/enmity.c。本指令只是把
// 「reconcile <id>」轉呼叫過去 (enmity 內部以 "reconcile <id>" 形式統一處理)﹐
// 讓玩家可直接打 reconcile 動詞。指令以「檔名 == 動詞」查找 (見
// adm/daemons/cmd_d.c)﹐故須有此薄殼檔。中文別名見 cmds/std/解仇.c。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    if( !arg || arg == "" )
        return notify_fail("你要跟誰解仇﹖指令格式﹕reconcile <玩家id>\n");
    return (int)"/cmds/std/enmity"->main(me, "reconcile " + arg);
}

int help(object me)
{
    return (int)"/cmds/std/enmity"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
