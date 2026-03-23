// Room: /d/qianchang/street2.c

inherit ROOM;

void create()
{
	set("short", "西大街");
	set("long", @LONG
前場鎮的西大街，比東大街安靜許多。街邊有幾間作坊，隱約傳來
叮叮噹噹的敲打聲。幾戶人家的門前晾著衣物，一隻黃狗懶洋洋
地趴在牆角曬太陽。街道盡頭可以望見西城門的輪廓。
LONG
	);
	set("outdoors", "city");
	set("exits", ([
		"east"  : __DIR__"square",
		"west"  : __DIR__"wgate",
		"south" : __DIR__"smithy",
	]));

	setup();
	replace_program(ROOM);
}
