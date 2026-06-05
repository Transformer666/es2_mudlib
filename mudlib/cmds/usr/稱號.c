// 稱號.c -- 「稱號」的中文指令別名，直接轉呼叫 cestablish。
//
// mudlib 的指令以「檔名 == 動詞」查找 (見 adm/daemons/cmd_d.c)，故中文檔名的指令檔
// 可讓玩家直接打中文動詞「稱號」。實際邏輯全寫在 cestablish.c，這裡只是薄薄一層轉
// 呼叫 (鏡 cmds/usr/聲望.c 之做法)。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    return (int)"/cmds/usr/cestablish"->main(me, arg);
}

int help(object me)
{
    return (int)"/cmds/usr/cestablish"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
