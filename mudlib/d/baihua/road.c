// Room: /d/baihua/road.c

inherit ROOM;

void create()
{
	set("short", "花間小路");
	set("long", @LONG
一條蜿蜒的小路穿行在大片的花田之間﹐兩旁開滿了五顏六色的鮮
花﹐蝴蝶在花間翩翩起舞﹐蜜蜂嗡嗡地忙碌著。空氣中瀰漫著沁人心
脾的花香﹐令人精神為之一振。往北可以回到官道﹐往南便是百花村了。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"north" : "/d/road/road4",
		"south" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}
