// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "水霧林入口");
	set("long", @LONG
湖岸的盡頭被一片濃密的霧氣所籠罩，走進霧中，視野迅速變得模糊不清。腳下的泥土變得鬆軟，到處都是水窪和積水。霧中不時傳來奇異的鳥叫聲，方向難以辨別，讓人感到一陣陣的不安。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : "/d/latemoon/lake",
		"north" : __DIR__"fog_path",
	]));

	setup();
	replace_program(ROOM);
}
