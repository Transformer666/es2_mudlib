// Room: /d/oldpine/cave.c

inherit ROOM;

void create()
{
	set("short", "山洞");
	set("long", @LONG
一個半掩在灌木叢後的山洞﹐洞口不大﹐勉強能讓一個人彎腰進
入。洞口附近散落著一些獸骨和破碎的陶片﹐看來這裡曾有人或野獸棲
息。從洞口往裡看去﹐一片漆黑﹐隱約能感覺到一股陰冷的氣息從洞
中湧出。
LONG
	);
	set("exits", ([
		"west" : __DIR__"road2",
		"north" : __DIR__"cave_inner",
	]));

	setup();
	replace_program(ROOM);
}
