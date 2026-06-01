// reaper.c -- 村外田壟上割稻捆穀的莊稼漢（純氣氛閒談）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("割稻漢子", ({ "reaper", "harvester", "gedaohanzi" }) );
	set("nickname", "割稻漢子");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 32);
	set("gender", "male");
	set("long",
		"一個赤著膊在田裡割稻的壯實漢子﹐古銅色的脊背教日頭曬\n"
		"得油亮﹐汗珠子一串串往下淌。他彎著腰﹐左手攬稻、右手揮鐮﹐\n"
		"鐮刀起落間﹐一把把沉甸甸的稻子便應聲倒下﹐身後堆起一壟壟捆\n"
		"好的稻穀。雖累得脊背發酸﹐臉上卻掛著豐年的笑。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"割稻漢子彎腰揮鐮﹐唰唰幾下﹐又割倒一把沉甸甸的稻子﹐隨手攏成一束擱在身後。\n",
		"割稻漢子直起腰﹐抹了把臉上的汗﹐望著身後一壟壟捆好的稻穀﹐咧嘴笑了。\n",
		"割稻漢子捶了捶痠痛的後腰﹐嘿嘿一笑﹕累是累﹐看著這滿田的好穀子﹐渾身又來了勁兒﹗\n",
	}));
	setup();
	carry_money("coin", 10);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這割稻漢子打聽甚麼﹖（試試 ask reaper about 收成）\n");

	if( arg == "reaper about 收成"
	||  arg == "reaper about 田"
	||  arg == "reaper about 稻"
	||  arg == "reaper about 割稻"
	||  arg == "reaper about 康平村"
	||  arg == "reaper about harvest" ) {
		do_chat(({
			(: command, "say 客官瞧這滿田的稻子﹗今年雨水勻、日頭足﹐穗子壓得稈子都彎了﹐是十來年難得的好收成。咱莊稼漢一年到頭的辛苦﹐就盼著這幾日割稻進倉哩。" :),
			(: command, "say 這割稻啊﹐得趁著好天緊趕﹐一場秋雨下來﹐倒了的稻子就難收了。客官莫嫌咱渾身汗味﹐莊稼人靠這力氣吃飯﹐心裡踏實。割完了這幾畝﹐回村還趕得上吃一口熱乎的新米飯哩。" :),
		}));
		return 1;
	}

	return notify_fail("割稻漢子直起腰憨憨一笑﹕客官問這個做甚﹖田裡活計緊﹐閒話改日再嘮罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖大夥兒都在田裡忙活﹐動甚麼粗﹗咱與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
