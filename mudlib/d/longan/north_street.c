// Room: /d/longan/north_street.c

inherit ROOM;

void create()
{
	set("short", "北街");
	set("long", @LONG
龍安城的北街比主街安靜許多﹐兩旁是幾戶青磚黛瓦的民居﹐偶爾
傳出幾聲犬吠雞鳴。街角有一間懸著葫蘆招牌的藥鋪﹐空氣中飄散著
草藥的苦香。幾個老人坐在門前的石墩上閒話家常﹐悠然自得。
LONG
	);
	set("exits", ([
		"south" : __DIR__"inn",
		"east"  : __DIR__"smithy",
	]));

	setup();
	replace_program(ROOM);
}
