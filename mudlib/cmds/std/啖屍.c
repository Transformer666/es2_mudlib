// 啖屍.c -- 「啖屍」的中文指令別名，直接轉呼叫 maul。
//
// 比照 化水.c / 吞噬.c：mudlib 指令以「檔名 == 動詞」查找 (見 adm/daemons/cmd_d.c)。
// 邏輯全部寫在 maul.c，這裡只是薄薄一層轉呼叫。
//
// 注意：中文檔名指令是否被 driver 的 get_dir() 正確列出／比對，與 吞噬.c
// 一樣尚待實機確認；若無效，阿修羅玩家仍可用英文動詞 maul。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    return (int)"/cmds/std/maul"->main(me, arg);
}

int help(object me)
{
    return (int)"/cmds/std/maul"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
