// Room: /d/road/road2.c

inherit ROOM;

void create()
{
	set("short", "官道");
	set("long", @LONG
官道穿過一片茂密的竹林，翠綠的竹葉在頭頂交織成一片涼蔭。
林間不時傳來清脆的鳥鳴聲，微風吹過竹梢發出沙沙的響聲。往東有
一條岔路通往虎刀門的方向，路口立著一塊指路的石碑。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"south" : __DIR__"road1",
		"north" : __DIR__"road3",
		"east"  : "/d/hudao/gate",
		"west"  : "/d/longan/entrance",
	]));

	setup();
	replace_program(ROOM);
}
