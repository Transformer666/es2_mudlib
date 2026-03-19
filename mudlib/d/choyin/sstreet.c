// Room: /d/choyin/sstreet.c

inherit ROOM;

void create()
{
	set("short", "南街");
	set("long", @LONG
喬陰縣城的南街﹐比北街稍微熱鬧一些。街邊有幾家賣吃食的小攤
﹐飄著陣陣香氣。一家客棧的旗幡在風中飄搖﹐上面寫著「喬陰客棧」。
往北可以回到縣城廣場﹐往南便是縣城的南門。
LONG
	);
	set("exits", ([
		"north" : __DIR__"square",
		"south" : __DIR__"sgate",
		"east" : __DIR__"inn",
	]));

	setup();
	replace_program(ROOM);
}
