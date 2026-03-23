// NPC: /d/chixiao/npc/old_woman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("神祕老婦", ({"old woman", "old_woman", "woman"}));
	set_attr("str", 8);
	set_attr("dex", 10);
	set_attr("con", 12);
	set_attr("int", 20);
	set_attr("spi", 18);
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 70);
	set("gender", "female");
	set("long",
		"一個衣著破舊的老婦人﹐白髮蒼蒼﹐面容枯瘦。她蜷縮在老宅\n"
		"的角落裡﹐手裡不停地撥弄著一串古舊的念珠。她的眼神有些迷離\n"
		"﹐時而喃喃自語﹐似乎在說著什麼別人聽不懂的話。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"老婦人喃喃道﹕那些東西 ... 還在井底 ... 別去招惹 ...\n",
		"老婦人抬起頭﹐渾濁的眼珠盯著你看了一會兒﹐又低下頭去。\n",
		"老婦人撥弄著念珠﹐口中唸唸有詞。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
