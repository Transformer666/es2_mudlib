// Room: /d/jingji/street.c

inherit ROOM;

void create()
{
	set("short", "京畿大道");
	set("long", @LONG
通往京畿重地的大道寬敞整潔，路面鋪著平整的大理石板，兩旁栽
種著修剪整齊的松柏。道路兩側是氣派的官邸和府宅，高牆朱門，飛簷
翹角。不時有官轎經過，前面的差役高聲喝道讓行人避讓。空氣中隱隱
飄來焚香的氣息，讓人感受到皇城近在咫尺的威嚴。
LONG
	);
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"square",
		"east"  : __DIR__"market",
		"west"  : __DIR__"library",
	]));

	setup();
	replace_program(ROOM);
}
