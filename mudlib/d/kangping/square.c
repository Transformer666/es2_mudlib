// Room: /d/kangping/square.c

inherit ROOM;

void create()
{
	set("short", "村中廣場");
	set("long", @LONG
村子中央的一塊空地﹐地面被踩得硬邦邦的。空地上有一口老井﹐
井旁放著一隻木桶和一條繩子。幾個老人坐在井邊的石頭上閒話家常。
北邊有一間小客店﹐東邊是一座看起來有些年頭的草堂。
LONG
	);
	set("exits", ([
		"west" : __DIR__"street",
		"north" : __DIR__"inn",
		"east" : __DIR__"thatched_hall",
	]));

	setup();
	replace_program(ROOM);
}
