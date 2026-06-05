// escort.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("鏢師", ({ "escort", "biaoshi" }) );
	set_attr("str", 22);
	set_attr("con", 20);
	set_race("human");
	set_class("fighter");
	set_level(18);

	set_skill("blade", 60);
	set_skill("parry", 50);
	set_skill("dodge", 50);
	set_skill("unarmed", 40);

	set("age", 35);
	set("gender", "male");
	set("long",
		"一個身材魁梧的鏢師﹐腰間挎著一柄厚背鋼刀﹐臉上一道淺淺的刀\n"
		"疤更添了幾分悍氣。他抱著肩膀靠在門邊﹐警惕地打量著來往的人。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"鏢師按了按腰間的鋼刀﹐目光在路口來回掃視。\n",
		"鏢師沉聲道﹕走鏢這一行﹐圖的就是個信字。\n",
		"鏢師說道﹕這趟鏢押往喬陰﹐過老松林那一段可得打起十二分精神。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("broadsword") )->wield();
	carry_money("coin", 180);
}

void init()
{
	::init();
	// 同 keeper：只對真人招呼。十字路口是漫遊鎮民(townsman)必經，缺 interactive 護衛會被 NPC
	// 反覆觸發招呼洗版。
	if( this_player() && interactive(this_player()) && !is_fighting() )
		do_chat((: command, "say 這位朋友面生得很﹐是過路的吧﹖" :));
}

// vim: set ts=4 sw=4 syntax=lpc
