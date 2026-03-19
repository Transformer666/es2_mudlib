// Room: /d/oldpine/road1.c

inherit ROOM;

void create()
{
	set("short", "松林小徑");
	set("long", @LONG
一條雜草叢生的小徑穿入一片老松林中﹐松樹高聳入雲﹐枝幹交
錯遮蔽了大半天光﹐林中顯得幽暗陰森。地上散落著厚厚的松針﹐踩
上去軟綿綿的。偶爾傳來幾聲鳥鳴﹐更襯托出林中的寂靜。往西北方
向可以回到雪亭鎮南門﹐往南則深入松林之中。
LONG
	);
	set("outdoors", "forest");
	set("objects", ([
		__DIR__"npc/snake" : 1,
	]));
	set("exits", ([
		"northwest" : "/d/snow/sgate",
		"south" : __DIR__"road2",
	]));

	setup();
	replace_program(ROOM);
}
