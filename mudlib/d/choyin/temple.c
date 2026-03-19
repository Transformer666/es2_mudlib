// Room: /d/choyin/temple.c

inherit ROOM;

void create()
{
	set("short", "城隍廟");
	set("long", @LONG
一座香火不算旺盛的城隍廟﹐廟門有些斑駁﹐但裡面倒還乾淨整齊。
正殿供奉著城隍爺的塑像﹐面容嚴肅﹐手持判官筆。神像前的香爐裡插
著幾根快要燃盡的香﹐嫋嫋的青煙在廟中繚繞。一個廟祝正在慢悠悠地
打掃著殿前的落葉。
LONG
	);
	set("objects", ([
		__DIR__"npc/monk" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}
