// clerk.c -- 羅城大街上往來的書辦吏員（純氣氛，閒談京畿官場見聞）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("書辦", ({ "clerk", "shuban" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 41);
	set("gender", "male");
	set("long",
		"一個衙門裡當差的書辦﹐穿著漿洗得齊整的青黑公服﹐袖著\n"
		"一卷文牘﹐步履匆匆。他在這顯貴雲集的羅城裡迎來送往慣了﹐\n"
		"一張臉上堆著恰到好處的謙和﹐眼角眉梢卻透著幾分察言觀色\n"
		"的精明。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"書辦袖著文牘﹐腳步匆匆地穿過大街﹐似有要緊的公事在身。\n",
		"書辦朝你略一拱手﹐謙和地道﹕這位客官面生﹐是頭一回到咱們羅城來罷﹖\n",
		"書辦壓低聲音道﹕咱們羅城別的不多﹐就是當官的多。客官在這城裡走動﹐說話可得留三分神哪。\n",
		"書辦感慨道﹕近畿之地﹐天子腳下﹐這城裡一草一木都沾著官氣﹐連咱們這些當差的﹐腰桿子也比外頭硬三分。\n",
	}));
	setup();
	carry_money("coin", 50);
}

int accept_fight(object ob)
{
	do_chat("書辦慌忙抱住懷裡的文牘﹐連聲道﹕使不得使不得﹗這是天子腳下﹐城門守卒就在街口哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
