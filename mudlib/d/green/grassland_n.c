// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "北草原");
	set("long", @LONG
這片草原向北延伸，草叢漸漸變得茂密。遠處可見一座低矮的丘陵，草原上零星散佈著幾棵孤獨的老樹。一條小溪從東面蜿蜒流過，溪水清澈見底，偶爾可見魚兒在水中嬉戲。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/celestial_bull" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"hill",
		"east" : __DIR__"stream",
	]));

	setup();
	replace_program(ROOM);
}
