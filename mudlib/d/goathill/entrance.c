// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "羊山山腳");
	set("long", @LONG
這座被稱為羊山的小山並不高大，但山勢陡峭，岩石嶙峋。山腳下有一片碎石灘，幾棵矮小的松樹頑強地生長在岩縫之中。偶爾可以看到幾隻野山羊在陡峭的岩壁上靈巧地跳躍。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/wild_goat" : 2,
	]));
	set("exits", ([
		"east" : "/d/green/grassland_s",
		"north" : __DIR__"hillside",
	]));

	setup();
	replace_program(ROOM);
}
