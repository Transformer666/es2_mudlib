// 吞噬.c -- 「吞噬」的中文指令別名，直接轉呼叫 devour。
//
// mudlib 的指令是用「檔名 == 動詞」來查找的 (見 adm/daemons/cmd_d.c 的
// find_command / rehash：用 get_dir(dir+"*.c") 建快取，再拿 query_verb()
// 來比對 verb+".c")。因此一個中文檔名的指令檔，理論上可讓玩家直接打中文
// 動詞「吞噬」。實際邏輯全部寫在 devour.c，這裡只是薄薄一層轉呼叫
// (比照 cmds/std/吐火.c)。
//
// 注意：中文檔名指令是否被 driver 的 get_dir() 正確列出並比對，尚待實機確認；
// 若此別名在實機上無效，玩家仍可用英文動詞 devour。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    return (int)"/cmds/std/devour"->main(me, arg);
}

int help(object me)
{
    return (int)"/cmds/std/devour"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
