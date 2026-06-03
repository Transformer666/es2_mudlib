// 仇家.c -- 「仇家」的中文指令別名﹐列出自己所有的私人仇家 (轉呼叫 enmity)。
//
// 邏輯全寫在 cmds/std/enmity.c (無參數即列表)。指令以「檔名 == 動詞」查找
// (見 adm/daemons/cmd_d.c)。打「仇家」等同打不帶參數的 enmity。
// 若帶參數則一併轉給 enmity (可當「仇家 <id>」= 結仇 用)。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    return (int)"/cmds/std/enmity"->main(me, arg);
}

int help(object me)
{
    return (int)"/cmds/std/enmity"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
