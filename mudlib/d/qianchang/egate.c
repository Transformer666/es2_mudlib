// Room: /d/qianchang/egate.c

inherit ROOM;

void create()
{
	set("short", "東城門");
	set("long", @LONG
前場鎮的東城門，一座樸素的石砌門樓，城牆不算高大，但修整得
頗為結實。幾名守衛正在檢查進出商隊的貨車，一旁的石碑上刻著
「前場鎮」三個大字，字跡已被風雨侵蝕得有些模糊。門外是一條
通往龍安城方向的官道，偶有馬車揚起塵土駛過。
LONG
	);
	set("outdoors", "city");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"east" : "/d/longan/entrance",
		"west" : __DIR__"street1",
	]));

	setup();
	replace_program(ROOM);
}
