// Room: /d/city/square.c

inherit ROOM;

void create()
{
	set("short", "城中廣場");
	set("long", @LONG
城中最大的廣場，地面鋪著平整的花崗岩石板。廣場中央矗立著
一座高大的石碑，上面刻著建城的歷史。四周環繞著幾棵百年古槐，
濃密的樹蔭下有石凳供人歇腳。不時有賣藝人在此表演，吸引了不
少圍觀的百姓。
LONG
	);
	set("objects", ([
		__DIR__"npc/guard" : 2,
	]));
	set("detail", ([
		"石碑" : "石碑上密密麻麻地刻著建城以來的大事記，年代久遠，字跡已有些模糊。\n",
		"古槐" : "幾棵粗壯的老槐樹，樹幹至少要兩人才能合抱，看起來有數百年的樹齡。\n",
	]));
	set("exits", ([
		"south" : __DIR__"main_street",
		"north" : __DIR__"yamen",
		"east"  : __DIR__"temple",
		"west"  : __DIR__"inn",
		"northeast" : __DIR__"garden",
	]));

	setup();
	replace_program(ROOM);
}
