// Room: /d/baihua/entrance.c

inherit ROOM;

void create()
{
	set("short", "百花村村口");
	set("long", @LONG
一個寧靜祥和的小村莊，四周環繞著大片的花田，空氣中瀰漫著
數百種不同花卉的芬芳。村口的木牌坊上寫著「百花村」三個字，牌
坊兩側攀爬著盛開的薔薇。一條碎石小路穿過村莊，通往村子深處。
LONG
	);
	set("exits", ([
		"north" : __DIR__"inn",
	]));

	setup();
	replace_program(ROOM);
}
