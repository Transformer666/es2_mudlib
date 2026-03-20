// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "神殿花園");
	set("long", @LONG
正殿西側是一處幽靜的花園，園中種植著各種珍稀花草。一條青石鋪就的小路在花叢中蜿蜒，路旁有一方荷花池，池中睡蓮朵朵盛開。園中還有幾株百年老梅，雖然不是花季，但枝幹蒼勁，別有一番韻味。
LONG
	);
	set("no_fight", 1);
	set("outdoors", "wilderness");
	set("exits", ([
		"east" : __DIR__"main_hall",
	]));

	setup();
	replace_program(ROOM);
}
