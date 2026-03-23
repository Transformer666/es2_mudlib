// Room: /d/wenguo/wgate.c

inherit ROOM;

void create()
{
	set("short", "西城門");
	set("long", @LONG
文國縣的西城門比東門略為冷清﹐城門外是一條蜿蜒的山路﹐漸
漸消失在遠處的青山之中。城門兩側的城牆上爬滿了青苔﹐顯得頗有
些年歲。偶爾有幾個樵夫或獵戶從山路上走來﹐進城販賣柴薪野味。
城門內是西大街﹐可以通往縣城各處。
LONG
	);
	set("outdoors", "city");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"street2",
	]));

	setup();
	replace_program(ROOM);
}
