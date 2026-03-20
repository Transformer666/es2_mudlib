// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "草原營地");
	set("long", @LONG
這裡是草原上的一處臨時營地，地上還留有篝火燃燒過的痕跡。幾根削尖的木樁插在地上，掛著一些風乾的獸皮。看來經常有旅人或獵人在此歇腳過夜。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"north" : __DIR__"grassland_s",
	]));

	setup();
	replace_program(ROOM);
}
