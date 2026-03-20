// Room: /d/sanyen/square.c

inherit ROOM;

void create()
{
	set("short", "焱硝村廣場");
	set("long", @LONG
焱硝村中的一小片空地﹐算是村裡最寬敞的地方了。地面是夯實的
黃土﹐中央有一口老井﹐井沿磨得光滑﹐看來已經用了很多年。空地
邊上有幾棵歪脖子槐樹﹐樹下放著幾塊大石頭﹐村民們常坐在這裡
歇息聊天。北面是村口的方向﹐南面可以往村子深處走去。
LONG
	);
	set("exits", ([
		"north" : __DIR__"entrance",
		"south" : __DIR__"street",
		"east" : __DIR__"market",
		"west" : __DIR__"west_street",
	]));

	setup();
	replace_program(ROOM);
}
