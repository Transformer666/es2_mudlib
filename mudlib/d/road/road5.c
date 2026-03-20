// Room: /d/road/road5.c

inherit ROOM;

void create()
{
	set("short", "官道");
	set("long", @LONG
官道從西邊延伸至此，前方便是五堂鎮的西門，高大的城門樓已經
清晰可見。一旁有條小路岔向西南方，通往茅山的方向。路邊有幾個小攤
販在叫賣著乾糧和草鞋，看來是專門做過路行人生意的。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"west"  : __DIR__"road4",
		"east"  : "/d/wutang/wgate",
		"southwest" : "/d/maoshan/gate",
		"north" : "/d/temple/entrance",
	]));

	setup();
	replace_program(ROOM);
}
