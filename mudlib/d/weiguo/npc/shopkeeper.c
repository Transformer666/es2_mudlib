// NPC: /d/weiguo/npc/shopkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("軍需掌櫃", ({"shopkeeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set("age", 45);
	set("gender", "male");
	set_level(12);
	set("long", @LONG
一個精明幹練的中年人﹐身材微胖﹐穿著一件灰布長衫。他原是
軍中的伙頭兵﹐退下來後便在衛國鎮開了這間軍需舖﹐專賣行軍日
用的物資。他面帶笑容﹐一雙眼睛卻精光閃閃﹐一看就是做買賣的
老手。
LONG
	);
	set("chat_chance", 15);
	set("chat_msg", ({
		"軍需掌櫃吆喝道：「好貨便宜賣啦，路過別錯過！」\n",
		"軍需掌櫃擦了擦櫃臺，整理著貨物。\n",
		"軍需掌櫃說道：「要買什麼儘管開口，童叟無欺。」\n",
	}));
	set("merchandise", ([
		STOCK_ARMOR("cloth") : 20,
		STOCK_WEAPON("dagger") : 15,
		STOCK_ITEM("bag") : 30,
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}
