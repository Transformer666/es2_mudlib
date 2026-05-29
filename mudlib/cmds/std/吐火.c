// 吐火.c -- 「吐火」的中文指令別名，直接轉呼叫 spitfire。
//
// mudlib 的指令是用「檔名 == 動詞」來查找的 (見 adm/daemons/cmd_d.c 的
// find_command / rehash：用 get_dir(dir+"*.c") 建快取，再拿 query_verb()
// 來比對 verb+".c")。因此一個中文檔名的指令檔，理論上可讓玩家直接打中文
// 動詞「吐火」。實際邏輯全部寫在 spitfire.c，這裡只是薄薄一層轉呼叫。
//
// 注意：本 mudlib 原本沒有任何中文檔名的指令檔，故「中文檔名能否被 driver
// 的 get_dir() 正確列出並比對」尚未驗證。若此別名在實機上無效，玩家仍可用
// 英文動詞 spitfire；屆時可改以其他機制（如選單）補上中文動詞。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    return (int)"/cmds/std/spitfire"->main(me, arg);
}

int help(object me)
{
    return (int)"/cmds/std/spitfire"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
