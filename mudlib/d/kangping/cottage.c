// Room: /d/kangping/cottage.c

inherit ROOM;

void create()
{
	set("short", "農舍");
	set("long", @LONG
一間普通的農舍﹐土牆茅頂﹐門前的籬笆圍著一小塊菜地。屋簷
下掛著幾串紅辣椒和幾穗玉米﹐門口晾著一些粗布衣裳。一隻母雞帶
著幾隻小雞在門前的空地上啄食﹐一派田園風光。
LONG
	);
	set("exits", ([
		"north" : __DIR__"street",
		"east"  : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
