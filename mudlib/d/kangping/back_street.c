// Room: /d/kangping/back_street.c

inherit ROOM;

void create()
{
	set("short", "村後小巷");
	set("long", @LONG
村口北邊的一條窄窄的小巷﹐兩旁是歪歪斜斜的籬笆牆。巷子裡
堆著一些柴禾和農具﹐幾隻雞在柴堆間覓食。巷子盡頭有一棵老槐樹﹐
樹下有一個石磨﹐看起來許久沒人使用了。
LONG
	);
	set("exits", ([
		"south" : __DIR__"entrance",
		"east"  : __DIR__"weapon_shop",
		"west"  : __DIR__"creek",
	]));

	setup();
	replace_program(ROOM);
}
