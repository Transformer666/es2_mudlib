// Room: /d/city/weapon_shop.c

inherit ROOM;

void create()
{
	set("short", "兵器鋪");
	set("long", @LONG
兵器鋪中陳列著各式各樣的刀槍劍戟，牆上掛著幾柄寒光閃閃的
寶劍，架子上整齊地排列著長槍和大刀。鋪子後方傳來叮叮噹噹的打
鐵聲，一名壯碩的鐵匠正在爐火旁揮汗如雨地鍛造兵器。
LONG
	);
	set("objects", ([
		__DIR__"npc/weaponsmith" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"market",
	]));

	setup();
	replace_program(ROOM);
}
