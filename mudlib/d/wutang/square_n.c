// Room: /d/wutang/square_n.c

inherit ROOM;

void create()
{
	set("short", "廣場北邊");
	set("long", @LONG
這裡是五堂鎮廣場的北邊﹐往北是一條寬闊筆直的街道﹐隱約可以
看到街道盡頭一棟氣派的建築﹐據說那是鎮上的公堂所在。往南回到廣
場中央﹐東邊有一條僻靜的後巷通往鎮子東北方向。這一帶行人較少﹐
顯得比廣場中央清靜了許多。
LONG
	);
	set("exits", ([
		"south" : __DIR__"square",
		"north" : __DIR__"street2",
		"east" : __DIR__"lane2",
	]));

	setup();
	replace_program(ROOM);
}
