// woman.c -- 溪橋邊浣紗的村婦（純氣氛閒談﹐不接任務、不動旗標）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("村婦", ({ "woman", "village woman", "cunfu" }) );
	set("nickname", "村婦");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 31);
	set("gender", "female");
	set("long",
		"一個荊釵布裙的武陵村婦﹐挽著袖子蹲在溪橋下的青石上浣\n"
		"洗衣裳﹐烏黑的髮上斜插一支木簪﹐手腕隨著捶衣的木杵一起一\n"
		"落﹐溪水在她指間嘩嘩地淌過。她生得清秀﹐眉眼間是鄉間婦人\n"
		"特有的那份恬靜安然。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"村婦舉起木杵﹐啪啪地捶著青石上的衣裳﹐溪水濺起細碎的水花。\n",
		"村婦把洗好的衣裳擰乾了﹐搭在橋欄上晾著﹐口中低低地哼著小調。\n",
		"村婦抬手撩了撩垂下的鬢髮﹐衝你抿嘴一笑﹐又低頭浣她的紗去了。\n",
	}));
	setup();
	carry_money("coin", 8);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這村婦甚麼﹖（試試 ask woman about 溪橋）\n");

	if( arg == "woman about 溪橋"
	||  arg == "woman about 橋"
	||  arg == "woman about 溪"
	||  arg == "woman about 武陵"
	||  arg == "woman about bridge" ) {
		do_chat(({
			(: command, "say 客官是外鄉來的罷﹖咱這溪橋啊﹐是鎮上頂老的物事了﹐橋下這道水嵐溪﹐養活了大半個武陵鎮的人哪。" :),
			(: command, "say 過了橋往東是渡口﹐打那兒能渡到溪對岸去。客官走累了﹐沿溪坐坐﹐看桃花落在水裡打著旋兒漂走﹐心也就靜了。" :),
		}));
		return 1;
	}

	return notify_fail("村婦低頭浣著紗﹐衝你靦腆地笑了笑﹐似是不慣與生人多話。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗這位客官好沒道理﹗光天化日的﹐欺負我一個浣衣的婦道人家做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
