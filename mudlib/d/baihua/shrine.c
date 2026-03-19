// Room: /d/baihua/shrine.c

inherit ROOM;

void create()
{
	set("short", "小祠堂");
	set("long", @LONG
一座小小的祠堂﹐供奉著百花村歷代先人的牌位。祠堂雖小﹐但打
掃得一塵不染﹐供桌上擺著幾盤鮮花和幾碟供品。牆上掛著一幅褪色的
畫卷﹐畫的是一個手持花籃的仙女﹐據說是百花村的守護神。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"inn",
	]));

	setup();
	replace_program(ROOM);
}
