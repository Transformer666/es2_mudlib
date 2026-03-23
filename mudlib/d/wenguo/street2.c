// Room: /d/wenguo/street2.c

inherit ROOM;

void create()
{
	set("short", "西大街");
	set("long", @LONG
西大街比東大街要安靜許多﹐兩旁多是讀書人家的宅院﹐偶爾可
以聽到從院牆內傳來的琅琅讀書聲。街邊種著幾棵老槐樹﹐濃蔭蔽
日﹐樹下放著幾張石桌石凳﹐常有老者在此下棋品茗。往東是縣城廣
場﹐往西可出西城門﹐往南有一間私塾。
LONG
	);
	set("outdoors", "city");
	set("exits", ([
		"east" : __DIR__"square",
		"west" : __DIR__"wgate",
		"south" : __DIR__"study",
	]));

	setup();
	replace_program(ROOM);
}
