// Room: /d/sanyen/back_alley.c

inherit ROOM;

void create()
{
	set("short", "村後巷");
	set("long", @LONG
村子後面的一條窄巷，牆根下長著雜草。巷子裡散發著一股潮濕
腐朽的味道，看起來少有人來。牆角堆著一些乾柴和破舊的農具，幾
隻烏鴉棲息在屋頂上，發出沙啞的叫聲。
LONG
	);
	set("objects", ([
		__DIR__"npc/beggar" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"street",
		"west" : __DIR__"market",
	]));

	setup();
	replace_program(ROOM);
}
