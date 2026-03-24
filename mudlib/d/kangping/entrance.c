// Room: /d/kangping/entrance.c

inherit ROOM;

void create()
{
	set("short", "康平村口");
	set("long", @LONG
一個寧靜的小村莊出現在眼前﹐村口立著一塊木牌﹐上面歪歪斜斜
地寫著「康平村」三個字。幾間茅草屋散落在田野之間﹐雞犬之聲相聞。
往西穿過一片灌木叢便是老松林﹐往東一條土路通入村中。
LONG
	);
	set("outdoors", "village");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"west"  : __DIR__"wgate",
		"east"  : __DIR__"street",
		"south" : __DIR__"path",
		"north" : __DIR__"back_street",
	]));

	setup();
	replace_program(ROOM);
}
