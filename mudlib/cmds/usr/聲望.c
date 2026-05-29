// 聲望.c -- 「聲望」的中文指令別名，直接轉呼叫 reputation。
//
// mudlib 的指令以「檔名 == 動詞」查找 (見 adm/daemons/cmd_d.c)，故中文檔名
// 的指令檔可讓玩家直接打中文動詞「聲望」。實際邏輯全寫在 reputation.c，
// 這裡只是薄薄一層轉呼叫。已確認本 mudlib 已有其他中文檔名指令 (如
// cmds/std/吐火.c)，UTF-8 指令檔名在此 mudlib 可用。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    return (int)"/cmds/usr/reputation"->main(me, arg);
}

int help(object me)
{
    return (int)"/cmds/usr/reputation"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
