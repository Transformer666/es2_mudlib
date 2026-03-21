// Room: /d/lijun/back_street.c

inherit ROOM;

void create()
{
	set("short", "渡口小巷");
	set("long", @LONG
這條僻靜的小巷位於鯉君渡的西側﹐兩旁是低矮的民房﹐牆壁上
爬滿了青苔。巷子裡很少有行人經過﹐偶爾能聽到幾聲狗吠和孩童的
嬉鬧聲。往南走能看到一座小小的城隍廟﹐香火嫋嫋。往東是鎮上的
廣場。
LONG
	);
	set("outdoors", "town");
	set("exits", ([
		"east" : __DIR__"square",
		"south" : __DIR__"temple",
	]));

	setup();
	replace_program(ROOM);
}
