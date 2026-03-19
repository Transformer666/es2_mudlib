// Room: /d/road/crossroad.c

inherit ROOM;

void create()
{
	set("short", "岔路口");
	set("long", @LONG
這裡是一處重要的岔路口，幾條道路在此交匯。路邊立著幾根木製
指路牌，分別指向不同的方向。東西向是寬闊的官道，往北有一條通往
山上的小路，往南則是一條人跡罕至的荒野小徑。地上散落著一些馬蹄
印和車轍痕跡，看來這裡平日往來的人不少。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"west"  : __DIR__"road3",
		"east"  : __DIR__"road4",
		"north" : __DIR__"mountain_road2",
		"south" : __DIR__"wild_path1",
	]));

	setup();
	replace_program(ROOM);
}
