// Room: /d/jingji/weapon_shop.c

inherit ROOM;

void create()
{
	set("short", "京畿兵器鋪");
	set("long", @LONG
一間氣派的兵器鋪，店面裝潢考究，陳列著各式上等兵器。牆上
掛著幾柄名劍，架子上擺放著精緻的長槍和大刀。作為京畿重地的兵
器鋪，這裡的貨色比一般地方的要精良許多。
LONG
	);
	set("objects", ([
		__DIR__"npc/weapon_vendor" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"market",
	]));

	setup();
	replace_program(ROOM);
}
