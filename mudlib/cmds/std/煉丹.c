// 煉丹.c -- 「煉丹」的中文指令別名，直接轉呼叫 refine。
//
// 比照 吐火.c／強化.c：mudlib 指令以「檔名 == 動詞」查找 (見
// adm/daemons/cmd_d.c 的 rehash／find_command：用 get_dir(dir+"*.c") 建
// 快取﹐再拿 verb+".c" 比對)。因此一個中文檔名的指令檔﹐理論上可讓玩家
// 直接打中文動詞「煉丹」。實際邏輯全部寫在 refine.c﹐這裡只是薄薄一層
// 轉呼叫。
//
// 注意：中文檔名指令是否被 driver 的 get_dir() 正確列出／比對﹐與
// 吐火.c／強化.c 一樣尚待實機確認；若無效﹐玩家仍可用英文動詞 refine。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    return (int)"/cmds/std/refine"->main(me, arg);
}

int help(object me)
{
    return (int)"/cmds/std/refine"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
