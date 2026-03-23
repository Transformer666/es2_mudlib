// Room: /d/choyin/east_lane.c

inherit ROOM;

void create()
{
	set("short", "東巷");
	set("long", @LONG
書肆東側的一條僻靜小巷﹐兩旁是斑駁的青石牆壁﹐牆頭上晾著
幾件衣裳。一隻花貓蜷在窗台上打盹﹐偶爾懶洋洋地抬起眼皮。
巷子盡頭隱約可見縣衙的飛簷﹐顯得幽深而寧靜。
LONG
	);
	set("exits", ([
		"west" : __DIR__"bookshop",
		"south" : __DIR__"yamen",
	]));

	setup();
	replace_program(ROOM);
}
