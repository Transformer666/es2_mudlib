// official.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("京官", ({ "official", "guanyuan" }) );
	set_attr("str", 18);
	set_attr("con", 16);
	set_race("human");
	set_class("scholar");
	set_level(10);

	set("age", 48);
	set("gender", "male");
	set("long",
		"一位在京為官的文職官員﹐頭戴烏紗﹐身著繡有禽鳥補子的緋\n"
		"色官袍﹐腰繫玉帶﹐手執象牙笏板。他舉止雍容﹐顧盼之間自\n"
		"有一股廟堂之上的威儀﹐想是剛從皇城裡奏對下來。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"京官捋著鬍鬚﹐負手望著巍峨的皇城﹐若有所思。\n",
		"京官矜持地頷首道﹕老夫忝列朝班﹐諸事繁劇﹐恕不能久陪了。\n",
		"京官低聲道﹕近來朝中為著立儲之事爭論不休﹐這京畿城裡﹐看著太平﹐底下卻不知藏著多少暗潮。\n",
	}));
	setup();
	carry_money("coin", 300);
}

int accept_fight(object ob)
{
	do_chat("京官勃然變色﹐喝道﹕放肆﹗你可知毆打命官是何等的死罪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
