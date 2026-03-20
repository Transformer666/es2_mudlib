// Room: /d/sanyen/weapon_shop.c

inherit ROOM;

void create()
{
	set("short", "兵器攤");
	set("long", @LONG
與其說是兵器鋪，不如說是一個露天攤位。地上鋪著一塊破布，
上面擺著幾把生了鏽的刀劍和幾根削尖的木矛。攤主是個獨臂漢子，
據說曾經是個江湖好手，如今落魄到此靠賣些破爛兵器度日。
LONG
	);
	set("objects", ([
		__DIR__"npc/weapon_vendor" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}
