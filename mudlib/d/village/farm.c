// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "農田");
	set("long", @LONG
一片平坦的農田在村子南面展開，田裡種著稻穀和各種蔬菜。幾個農夫彎腰在田間勞作，頭頂著烈日，汗水浸透了衣衫。田邊有一條灌溉用的小水渠，渠水從南面的泉域引來。東面有一口水井供村民日常使用。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/beggar_crone" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"street",
		"east" : __DIR__"well",
		"south" : "/d/chuenyu/entrance",
	]));

	setup();
	replace_program(ROOM);
}
