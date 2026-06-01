// girl.c -- 浣月潭畔浣紗的村姑（純氣氛閒談﹐不接任務、不動旗標）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("村姑", ({ "girl", "village girl", "cungu" }) );
	set("nickname", "村姑");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 19);
	set("gender", "female");
	set("long",
		"一個荊釵布裙的水月村姑﹐挽著袖子蹲在潭畔的青石上浣\n"
		"紗﹐烏黑的辮子垂在肩頭﹐手腕隨著捶衣的木杵一起一落﹐潭水\n"
		"在她指間漾開一圈圈的漣漪。她生得眉清目秀﹐臉上是水鄉女兒\n"
		"特有的那份恬靜清澈﹐見了生客﹐只是靦腆地一笑。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"村姑舉起木杵﹐輕輕捶著青石上的紗﹐潭面漾開細碎的波光。\n",
		"村姑把浣好的紗擰乾了﹐搭在柳枝上晾著﹐口中低低地哼著水鄉的小調。\n",
		"村姑抬手撩了撩垂下的鬢髮﹐衝你抿嘴一笑﹐又低頭浣她的紗去了。\n",
	}));
	setup();
	carry_money("coin", 6);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這村姑甚麼﹖（試試 ask girl about 浣月潭）\n");

	if( arg == "girl about 浣月潭"
	||  arg == "girl about 潭"
	||  arg == "girl about 水月"
	||  arg == "girl about 月"
	||  arg == "girl about pond" ) {
		do_chat(({
			(: command, "say 客官是外鄉來的罷﹖咱這浣月潭啊﹐潭水清得能照見人影哩。一到月圓的夜裡﹐一輪月亮落在潭心﹐水裡天上兩個月亮﹐好看得很。" :),
			(: command, "say 潭裡的水是村後瀑布引來的活水﹐我們村裡的姑娘都愛來這兒浣紗照影。客官沿著柳堤往北上去﹐就回村心了。" :),
		}));
		return 1;
	}

	return notify_fail("村姑低頭浣著紗﹐衝你靦腆地笑了笑﹐似是不慣與生人多話。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗這位客官好沒道理﹗光天化日的﹐欺負我一個浣紗的姑娘家做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
