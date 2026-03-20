// Room: /d/kangping/street.c

inherit ROOM;

void create()
{
	set("short", "村中小路");
	set("long", @LONG
一條泥土小路穿過村子﹐路旁長著幾棵老榆樹﹐樹下拴著一頭老黃
牛﹐正悠閒地嚼著草料。路邊有幾間農舍﹐籬笆牆裡種著蔬菜。一個
小孩在路邊玩耍﹐看到外人便好奇地張大了眼睛。
LONG
	);
	set("objects", ([
		__DIR__"npc/agui" : 1,
		__DIR__"npc/villager" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"entrance",
		"east" : __DIR__"square",
		"south" : __DIR__"cottage",
		"north" : __DIR__"herb_garden",
	]));

	setup();
	replace_program(ROOM);
}
