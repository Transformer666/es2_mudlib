// Room: /d/longan/entrance.c

inherit ROOM;

void create()
{
	set("short", "龍安城門");
	set("long", @LONG
龍安城氣勢恢宏的城門矗立眼前，高聳的石牆向兩側延伸，一眼
望不到盡頭。城門洞足有三丈多高，門上包著厚重的銅皮，鉚釘排列
整齊。幾名身著亮甲的士兵持槍挺立在門前，目光銳利地審視著每一
個進出城門的行人。
LONG
	);
	set("outdoors", "city");
	set("objects", ([
		__DIR__"npc/guard" : 2,
	]));
	set("exits", ([
		"south" : "/d/road/road2",
		"north" : __DIR__"street",
	]));

	setup();
	replace_program(ROOM);
}
