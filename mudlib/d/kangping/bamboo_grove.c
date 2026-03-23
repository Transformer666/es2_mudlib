// Room: /d/kangping/bamboo_grove.c

inherit ROOM;

void create()
{
	set("short", "竹林");
	set("long", @LONG
村外一片幽靜的竹林﹐翠竹參天﹐密密匝匝地遮住了大半天光。微
風拂過﹐竹葉沙沙作響﹐彷彿在低聲細語。一條鋪著青石板的小徑穿林
而過﹐石板上覆著薄薄的苔蘚。林間清幽寧靜﹐偶有幾聲鳥鳴傳來。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"north" : __DIR__"creek",
		"east"  : __DIR__"path",
	]));

	setup();
	replace_program(ROOM);
}
