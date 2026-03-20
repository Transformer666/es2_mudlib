// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "泉域瀑布");
	set("long", @LONG
泉水在此匯聚，從一面長滿藤蔓的岩壁上傾瀉而下，形成一道壯觀的溫泉瀑布。瀑布下方水霧瀰漫，幾道彩虹在水霧中若隱若現。瀑布周圍的岩石上長滿了各種奇異的植物，似乎是被溫泉的養分滋潤而生。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"north" : __DIR__"spring_path",
	]));

	setup();
	replace_program(ROOM);
}
