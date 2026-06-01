// laoyaonong.c -- 百藥谷幽谷裡採野藥的老藥農（F_VILLAGER﹐純氣氛、非戰鬥）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老藥農", ({ "laoyaonong", "herb farmer", "farmer" }) );
	set("nickname", "老藥農");
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 60);
	set("gender", "male");
	set("long",
		"一個佝僂著背的老藥農﹐布衣草鞋﹐滿手老繭﹐正蹲在崖陰的\n"
		"朽木旁細細地查看那叢野生靈芝。他在谷裡侍弄了一輩子藥草﹐\n"
		"認得這幽谷深處每一株草木的脾性。你或許可以 ask 他些谷中\n"
		"靈藥的事（試試 ask laoyaonong about 靈藥）。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老藥農蹲在朽木旁﹐用枯瘦的手指輕輕撥弄那叢野生靈芝﹐看得入神。\n",
		"老藥農喃喃道﹕這谷底的地氣養人﹐野生的靈芝﹐比藥圃裡種的還要醇些哩。\n",
	}));

	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這老藥農些什麼﹖（試試 ask laoyaonong about 靈藥）\n");

	if( arg == "laoyaonong about 靈藥"
	||  arg == "laoyaonong about 稀世靈藥"
	||  arg == "laoyaonong about 靈芝"
	||  arg == "herb farmer about 靈藥"
	||  arg == "laoyaonong about herb" ) {
		do_chat(({
			(: command, "say 這幽谷不見天日﹐陰潤養藥﹐崖陰朽木上的野生靈芝、當歸最是地道﹐藥性比藥圃裡的還足。要買現成的﹐前頭藥廬尋采藥老人便是。" :),
			(: command, "say 至於谷壁石縫裡那些稀世靈藥嘛 ... 老朽守了這谷大半輩子﹐也不過撞見過寥寥幾回﹐可遇而不可求啊。客官有緣﹐或許瞧得著一兩株。" :),
		}));
		return 1;
	}

	return notify_fail("老藥農憨憨一笑﹕谷裡的藥草事﹐老朽倒還說得上幾句（ask laoyaonong about 靈藥）。\n");
}

int accept_fight(object ob)
{
	do_chat("老藥農直起佝僂的背﹐連連擺手﹕老朽一把年紀的種藥人﹐打不得也打不得呀﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
