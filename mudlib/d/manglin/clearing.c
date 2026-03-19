// Room: /d/manglin/clearing.c

inherit ROOM;

void create()
{
	set("short", "林中空地");
	set("long", @LONG
莽林中難得的一片空地﹐大約有幾丈方圓。地上長滿了青草﹐中央
有一個用石頭壘成的火堆遺跡﹐看來曾有人在此露營。空地邊緣的樹上
掛著幾塊獸皮﹐旁邊插著一把獵刀﹐這裡似乎是獵人常用的歇腳之處。
LONG
	);
	set("outdoors", "forest");
	set("objects", ([
		__DIR__"npc/hunter" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"path1",
		"north" : __DIR__"pond",
	]));

	setup();
	replace_program(ROOM);
}
