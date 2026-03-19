// Room: /d/oldpine/camp.c

inherit ROOM;

void create()
{
	set("short", "土匪營地");
	set("long", @LONG
松林中一塊被清理出來的空地﹐搭著幾個簡陋的帳篷﹐中間是一
堆還冒著煙的篝火。地上丟著吃剩的骨頭和空酒罈﹐一面破舊的旗幟
歪歪斜斜地插在地上﹐上面繡著一個「松」字。這裡便是老松寨土匪們
的營地了。
LONG
	);
	set("objects", ([
		__DIR__"npc/bandit" : 2,
	]));
	set("exits", ([
		"east" : __DIR__"road2",
	]));

	setup();
	replace_program(ROOM);
}
