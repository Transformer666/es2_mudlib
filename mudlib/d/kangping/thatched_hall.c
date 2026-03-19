// Room: /d/kangping/thatched_hall.c

inherit ROOM;

void create()
{
	set("short", "草堂");
	set("long", @LONG
一座看起來頗有年頭的草堂﹐比村裡其他房屋大了不少。門上掛著
一副對聯﹐字跡飄逸﹐寫著「閒看庭前花開花落﹐漫隨天外雲卷雲舒」。
堂中陳設簡樸﹐一張書桌﹐一把藤椅﹐牆上掛著一柄拂塵和幾幅山水
畫。一股淡淡的檀香從屋中飄出。
LONG
	);
	set("objects", ([
		__DIR__"npc/taoist" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}
