// bookboy.c -- 墨池小園裡替主人洗筆汲水的書僮（純氣氛閒談﹐不接任務、不動旗標）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("書僮", ({ "bookboy", "book boy", "shutong" }) );
	set("nickname", "書僮");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 13);
	set("gender", "male");
	set("long",
		"一個十二三歲的小書僮﹐穿著件半舊的青布直裰﹐挽著袖\n"
		"子蹲在墨池畔﹐替自家先生涮洗一管管用過的筆。他生得眉清目\n"
		"秀﹐手腳麻利﹐筆涮淨了便甩一甩、理好鋒﹐插回筆筒裡﹐間或\n"
		"偷閒望一望亭中對弈的文士﹐眼裡滿是嚮往。見了生客﹐只靦腆\n"
		"地一笑。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"書僮把一管筆在墨池裡輕輕涮著﹐池面漾開一圈圈淡淡的墨痕。\n",
		"書僮涮淨了筆﹐甩一甩水﹐小心地理好筆鋒﹐插回身旁的筆筒裡。\n",
		"書僮偷閒望了望亭中對弈的文士﹐又趕忙低下頭﹐怕教先生瞧見了說他偷懶。\n",
	}));
	setup();
	carry_money("coin", 4);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這書僮甚麼﹖（試試 ask bookboy about 墨池）\n");

	if( arg == "bookboy about 墨池"
	||  arg == "bookboy about 池"
	||  arg == "bookboy about 園"
	||  arg == "bookboy about 墨"
	||  arg == "bookboy about pool" ) {
		do_chat(({
			(: command, "say 客官是外鄉來的罷﹖這墨池啊﹐先生說﹐是縣裡幾輩子的讀書人都在這兒洗筆﹐日子久了﹐把一池清水都染成墨色了哩。" :),
			(: command, "say 小的天天替先生來這兒涮筆汲水﹐聽他們吟詩對句﹐久了竟也記得幾首。客官沿著東邊月洞門出去﹐就回翰墨廣場了。" :),
		}));
		return 1;
	}

	return notify_fail("書僮低頭涮著筆﹐衝你靦腆地笑了笑﹐似是不慣與生人多話。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗這位客官好沒道理﹗欺負我一個涮筆的小書僮做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
