// advance.c -- 門派進階(二轉)指令「進階」的英文別名﹐薄薄一層轉呼叫 進階.c。
//
// 比照 強化.c → enchant.c 的做法：mudlib 指令以「檔名 == 動詞」查找
// (見 adm/daemons/cmd_d.c)﹐邏輯全寫在 進階.c﹐這裡只轉呼叫。
//
//   advance 劍士 / advance 古劍門傳人 / advance 虎督
//
// 註：本檔與 進階.c 同為新增的頂層指令﹐註冊需 `rehash /cmds/std/`。

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	return (int)"/cmds/std/進階"->main(me, arg);
}

int help(object me)
{
	return (int)"/cmds/std/進階"->help(me);
}

// vim: set ts=4 sw=4 syntax=lpc
