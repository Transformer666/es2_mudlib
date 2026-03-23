// NPC: /d/wenguo/npc/villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("縣民", ({"villager", "citizen"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 30);
	set("gender", "male");
	set("long",
		"一個文國縣的普通居民﹐穿著整潔的布衣﹐看起來比鄉下村民\n"
		"要體面一些。他神態從容﹐似乎對縣城的繁華早已習以為常。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"縣民說道﹕文國縣雖然不大﹐但文風鼎盛﹐出了不少舉人呢。\n",
		"縣民說道﹕縣太爺是個好官﹐斷案公正﹐大家都很信服。\n",
		"縣民四處張望了一下﹐匆匆走過。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
