// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "村中小廣場");
	set("long", @LONG
村子中央有一塊被踩得平平整整的空地，大概算是村子裡的廣場了。空地中間有一棵老槐樹，樹下擺了幾個石墩子，幾個老人坐在那裡閒聊。廣場北面是村口，南面是通往各處的小路，東面有一間雜貨鋪子。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"north" : __DIR__"entrance",
		"south" : __DIR__"street",
		"east" : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
