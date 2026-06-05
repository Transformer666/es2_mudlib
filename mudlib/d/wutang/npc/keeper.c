// keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({ "keeper", "innkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 49);
	set("gender", "male");
	set("long",
		"這位是飲鶴居的掌櫃﹐生得圓臉細眼﹐一團和氣﹐手裡的算盤撥得\n"
		"飛快﹐見客人進來便笑著招呼。累了的話﹐不妨在客棧裡歇歇腳。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地算著今日的帳。\n",
		"掌櫃招呼道﹕客官打尖還是住店﹖樓上雅淨的客房盡有。\n",
		"掌櫃壓低了聲音說道﹕近來松林裡不太平﹐夜裡趕路可得小心些。\n",
	}));
	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	// 只對「真人玩家」招呼。原僅檢查 !is_fighting()，漫遊鎮民(townsman)或店小二等 NPC 進客棧
	// 也會觸發 do_chat 招呼→玩家視角不斷洗版招呼(使用者回報的「無限迴圈」)。補 interactive()
	// 護衛(與 biaotou/washerwoman 一致)，並除去未來 relay_say NPC 同房時的 say-loop 火種。
	if( this_player() && interactive(this_player()) && !is_fighting() )
		do_chat((: command, "say 客官裡邊請﹗打尖住店都使得﹗" :));
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位客官說笑了﹐小老兒還指著這客棧過活呢。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
