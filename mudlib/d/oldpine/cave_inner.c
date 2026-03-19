// Room: /d/oldpine/cave_inner.c

inherit ROOM;

void create()
{
	set("short", "山洞深處");
	set("long", @LONG
山洞深處比想像中寬敞﹐洞頂掛著幾根石鐘乳﹐滴答滴答地往下
滴水。洞壁上有被煙燻黑的痕跡﹐地上還有一堆早已熄滅的篝火殘骸。
角落裡堆放著一些木箱和麻袋﹐看起來像是土匪藏匿贓物的地方。
LONG
	);
	set("objects", ([
		__DIR__"npc/bandit_chief" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"cave",
	]));

	setup();
	replace_program(ROOM);
}
