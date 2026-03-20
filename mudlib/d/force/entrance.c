// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "修練場入口");
	set("long", @LONG
一條隱蔽的山間小路通往這處僻靜的修練之地。入口處立著一塊石碑，上面刻著「靜心養氣，以武入道」八個大字，字跡蒼勁有力。四周古木參天，鳥鳴聲聲，是個遠離塵囂的好去處。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"east" : "/d/road/mountain_road1",
		"north" : __DIR__"training_ground",
	]));

	setup();
	replace_program(ROOM);
}
