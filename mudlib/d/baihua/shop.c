// Room: /d/baihua/shop.c

inherit ROOM;

void create()
{
	set("short", "百花雜貨舖");
	set("long", @LONG
一間小巧的雜貨舖﹐門楣上掛著幾串曬乾的花草。貨架上擺著各
種日用雜貨和當地特產﹐空氣中瀰漫著花草的香氣。老闆娘正在
整理貨架﹐見人進來便笑臉相迎。
LONG
	);
	set("objects", ([
		__DIR__"npc/shopkeeper" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"back_street",
	]));

	setup();
	replace_program(ROOM);
}
