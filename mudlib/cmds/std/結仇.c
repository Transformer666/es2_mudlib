// 結仇.c -- 「結仇」的中文指令別名﹐直接轉呼叫 enmity。
//
// 邏輯全寫在 cmds/std/enmity.c﹐這裡只是薄薄一層轉呼叫。指令以「檔名 == 動詞」
// 查找 (見 adm/daemons/cmd_d.c)﹔本 mudlib 已有 UTF-8 中文檔名指令的先例
// (如 cmds/std/吐火.c、cmds/usr/聲望.c)﹐故中文動詞「結仇」可直接使用。

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
