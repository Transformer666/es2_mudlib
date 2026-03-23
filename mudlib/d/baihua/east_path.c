// Room: /d/baihua/east_path.c

inherit ROOM;

void create()
{
	set("short", "村東小徑");
	set("long", @LONG
村子東邊的一條蜿蜒小徑﹐兩旁種滿了桃樹和李樹。春風吹過﹐
花瓣如雨般飄落﹐鋪了滿地粉白。遠處傳來幾聲鳥鳴﹐與風吹樹
葉的沙沙聲交織在一起﹐好一派田園風光。
LONG
	);
	set("outdoors", "village");
	set("exits", ([
		"south" : __DIR__"pavilion",
		"west" : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
