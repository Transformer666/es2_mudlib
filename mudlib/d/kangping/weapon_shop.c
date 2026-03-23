// Room: /d/kangping/weapon_shop.c

inherit ROOM;

void create()
{
	set("short", "鐵匠棚");
	set("long", @LONG
村後小巷東邊搭了一間簡陋的鐵匠棚﹐用幾根粗木柱子撐起一片茅
草頂棚。棚裡有一座小鍛爐﹐爐火時旺時弱﹐映得匠人滿臉通紅。
一個鐵砧上擺著幾件半成品的農具和刀具﹐牆上掛著幾把粗製的柴刀
和鋤頭。雖然手藝粗糙﹐但在這偏僻小村裡已算是難得的鐵匠了。
LONG
	);
	set("objects", ([
		__DIR__"npc/blacksmith" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"back_street",
	]));

	setup();
	replace_program(ROOM);
}
