// Room: /d/lijun/entrance.c

inherit ROOM;

void create()
{
	set("short", "鯉君渡口");
	set("long", @LONG
穿過荒野小徑﹐眼前豁然開朗。一座不大的渡口小鎮出現在眼前
﹐門口立著一塊飽經風雨的石碑﹐上面刻著「鯉君渡」三個字﹐字跡
已有些模糊。往南走便是渡口大街﹐可以聽到遠處傳來的流水聲和船
夫的號子聲。往北是通往荒野的小徑。渡口兩旁站著守衛﹐盤查著過
往行人。
LONG
	);
	set("outdoors", "town");
	set("objects", ([
		__DIR__"npc/river_guard" : 2,
	]));
	set("exits", ([
		"north" : "/d/road/wild_path1",
		"south" : __DIR__"street",
	]));

	setup();
	replace_program(ROOM);
}
