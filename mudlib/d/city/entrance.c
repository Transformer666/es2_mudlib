// Room: /d/city/entrance.c

inherit ROOM;

void create()
{
	set("short", "城市南門");
	set("long", @LONG
巍峨的城門高聳入雲，厚重的城牆向兩側延伸，將整座城市環抱
其中。城門洞上方的門樓飛簷翹角，氣勢不凡，門額上鐫刻著「天都
城」三個鎏金大字。幾名守城士兵手持長戟，盤查著進出的商旅行人。
城門外是通往五堂鎮方向的官道。
LONG
	);
	set("outdoors", "city");
	set("exits", ([
		"south" : "/d/road/road5",
		"north" : __DIR__"main_street",
	]));

	setup();
	replace_program(ROOM);
}
