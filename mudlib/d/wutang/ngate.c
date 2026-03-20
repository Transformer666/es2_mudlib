// Room: /d/wutang/ngate.c

inherit ROOM;

void create()
{
	set("short", "五堂鎮北門");
	set("long", @LONG
這裡是五堂鎮的北門﹐城門不大﹐但修築得十分堅固。門外是一條
蜿蜒的山路﹐通往北邊的群山之中。一名守衛背著手在門前來回踱步﹐
不時抬頭望望北方的山巒。據說北邊的山裡偶爾會有野獸出沒﹐因此這
道門入夜後便會關閉。往南便回到官府前。
LONG
	);
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"court",
		"north" : "/d/manglin/entrance",
		"northeast" : "/d/babao/entrance",
	]));

	setup();
	replace_program(ROOM);
}
