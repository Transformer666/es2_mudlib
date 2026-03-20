// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("張小簽", ({"zhang_xiaoqian", "zhang", "xiaoqian"}));
	set_attr("str", 14);
	set_attr("dex", 22);
	set_attr("con", 14);
	set_attr("int", 18);
	set_attr("spi", 16);
	set_race("human");
	set_class("commoner");
	set_level(15);

	set_skill("dagger", 40);
	set_skill("dodge", 50);

	set("age", 20);
	set("gender", "male");
	set("long",
		"張小簽是個二十出頭的年輕人，穿著白色長衫，腳蹬皮靴，一副沉\n"
		"穩的模樣。他最擅長的就是變戲法，有時能把東西變沒，有時又能再\n"
		"變一個出來。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"張小簽笑瞇瞇地說道：來來來，看看我的新戲法！\n",
		"張小簽從袖中變出一朵花，引來路人的驚嘆。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
