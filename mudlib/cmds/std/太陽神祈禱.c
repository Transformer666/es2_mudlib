// 太陽神祈禱.c -- 「太陽神祈禱」的中文指令別名，直接轉呼叫 sunpray。
//
// 比照 化水.c / 吐火.c / 採靈氣.c：mudlib 指令以「檔名 == 動詞」查找
// (見 adm/daemons/cmd_d.c 的 find_command / rehash：用 get_dir(dir+"*.c")
// 建快取，再拿 query_verb() 比對 verb+".c")。邏輯全部寫在 sunpray.c，這裡
// 只是薄薄一層轉呼叫。
//
// 注意：中文檔名指令是否被 driver 的 get_dir() 正確列出／比對，與 吐火.c
// 一樣尚待實機確認；若無效，人類族玩家仍可用英文動詞 sunpray。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    return (int)"/cmds/std/sunpray"->main(me, arg);
}

int help(object me)
{
    return (int)"/cmds/std/sunpray"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
