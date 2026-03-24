// Room: /d/sanyen/west_street.c

inherit ROOM;

void create()
{
	set("short", "村西小路");
	set("long", @LONG
廣場西邊延伸出的一條土路﹐兩旁是幾間破舊的土坯房。路邊晾著
幾件補了又補的衣物﹐門前散落著農具。這裡比村中更加冷清﹐只有幾
隻雞在路邊悠閒地啄食。遠處可以看到連綿的山巒﹐山頭上隱約有煙霧
繚繞。
LONG
	);
	set("exits", ([
		"east" : __DIR__"square",
		"west" : __DIR__"abandoned_house",
	]));

	setup();
	replace_program(ROOM);
}
