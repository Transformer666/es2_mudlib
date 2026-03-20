// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("阿寶", ({"arbao", "abao"}));
	set_attr("str", 15);
	set_attr("dex", 19);
	set_attr("con", 17);
	set_attr("int", 19);
	set_attr("spi", 18);
	set_race("human");
	set_class("commoner");
	set_level(10);

	set_skill("dodge", 35);
	set_skill("dagger", 40);

	set("age", 16);
	set("gender", "female");
	set("long",
		"這個十五、六歲的小姑娘就是「阿寶」了﹐她身上雖然穿著粗布\n"
		"衣服﹐但卻十足是個美人胚子。她是瞎眼老太婆的孫女﹐平日裡\n"
		"幫忙打理家務﹐偶爾也會到鎮上走走。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"阿寶說道：奶奶的眼睛越來越不好了﹐真讓人擔心。\n",
		"阿寶低著頭﹐不知在想些什麼。\n",
		"阿寶好奇地打量著過路的江湖人。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("dagger"))->wield();
	carry_money("coin", 30);
}
