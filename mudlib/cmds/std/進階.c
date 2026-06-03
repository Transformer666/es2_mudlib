// 進階.c -- 門派進階(二轉)指令
//
// 比照 cmds/std/apprentice.c 的拜師流程。玩家在本門 HQ、面對能主持進階的
// 師父(NPC 上有 do_advance 鉤子﹐如冷梅莊主 d/hanmei/npc/master.c)時﹐
// 以「進階 <分支名>」轉入該門的進階分支。
//
//   進階 劍士            -- 轉入冷梅莊「劍士」一路
//   進階 古劍門傳人      -- 轉入冷梅莊「古劍門傳人」一路
//   進階 虎督            -- 轉入冷梅莊「虎督」一路
//
// 指令本身與門派無關﹕只負責找出在場能主持進階的師父、把分支名交給師父的
// do_advance(me, branch) 去驗條件、授技。各門派的進階條件與所授武功由各自
// 師父 NPC 的 do_advance 定義(資料表見冷梅莊主 query_advance_branches())。
//
// 註：本檔為新增的頂層指令﹐註冊需 `rehash /cmds/std/`。

#include <ansi.h>

inherit F_CLEAN_UP;

// 找出此房間裡能主持進階的師父（NPC 上定義了 do_advance 鉤子）。
private object find_advance_master(object me)
{
	object ob;

	foreach(ob in all_inventory(environment(me)))
		if( ob != me && living(ob) && function_exists("do_advance", ob) )
			return ob;
	return 0;
}

int main(object me, string arg)
{
	object master;

	if( !arg || arg == "" )
		return notify_fail("你要進階哪一個分支﹖（用法﹕進階 <分支名>）\n");

	master = find_advance_master(me);
	if( !master )
		return notify_fail("這裡並沒有能指點你進階的師父。\n");

	if( !living(master) )
		return notify_fail(master->name() + "現在沒有辦法回答你。\n");

	// 把分支名交給師父去驗條件、授技。
	// do_advance 自行 do_chat 說明緣由並回 notify_fail("") / 0(失敗) 或 1(成功)。
	notify_fail(master->name() + "似乎無意指點你進階。\n");
	return master->do_advance(me, arg);
}

int help(object me)
{
	write(@Help
指令格式: 進階 <分支名>

當你已拜入某一門派、且功力火候足夠時﹐可在本門宗師面前進階(二轉)﹐
轉入該門更高深的分支﹐習得上乘武功。各分支的轉職條件(等級、入門武功
火候、根骨屬性等)不一﹐須面對能主持進階的師父方能施行。

例﹕冷梅莊弟子可在冷梅莊主面前「進階 劍士」。

英文別名﹕advance <branch>
Help
	);
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
