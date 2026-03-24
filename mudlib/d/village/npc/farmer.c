// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老農", ({"farmer", "old farmer"}));
	set_attr("str", 16);
	set_attr("con", 18);
	set_attr("dex", 10);
	set_attr("int", 10);
	set_attr("spi", 12);
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個皮膚黝黑的老農﹐頭上戴著一頂破草帽﹐赤著腳在田裡\n"
		"勞作。他的雙手粗糙龜裂﹐佈滿了老繭﹐這是幾十年耕作留\n"
		"下的印記。雖然辛苦﹐但他臉上總帶著質樸的笑容。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老農擦了擦汗﹐望了望天說道﹕看這天色﹐明兒個該是個好天氣。\n",
		"老農說道﹕今年的收成不錯﹐夠村裡人吃一年了。\n",
		"老農彎下腰﹐繼續仔細地除著田裡的雜草。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 30);
}
