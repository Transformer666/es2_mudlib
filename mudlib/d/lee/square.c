// Room: /d/lee/square.c

inherit ROOM;

void create()
{
	set("short", "村中廣場");
	set("long", @LONG
李家村中心的一片空地﹐地上鋪著不太整齊的青石板。廣場中央
有一棵老榕樹﹐枝繁葉茂﹐樹蔭足以遮蔽大半個廣場。樹下有幾
張石桌石凳﹐幾個老人正坐在那裡喝茶閒聊。廣場東邊是村裡的街
道﹐西邊通往村口方向﹐北面可以去客棧歇腳﹐南邊有一間小小的
土地廟。
LONG
	);
	set("exits", ([
		"west" : __DIR__"r2",
		"east" : __DIR__"street",
		"north" : __DIR__"back_street",
		"south" : __DIR__"temple",
	]));

	setup();
	replace_program(ROOM);
}
