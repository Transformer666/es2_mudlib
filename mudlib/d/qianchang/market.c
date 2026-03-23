// Room: /d/qianchang/market.c

inherit ROOM;

void create()
{
	set("short", "東市集");
	set("long", @LONG
東城門邊的一片空地上，搭起了不少簡易的棚子和攤位。因為靠近
城門，來往的商旅行人較多，所以這裡的買賣比鎮上其他地方熱鬧
些。攤位上擺著從各地運來的貨物——龍安的絲綢、文國的陶器、
還有山裡獵戶帶來的皮貨。吆喝聲此起彼落，好不熱鬧。
LONG
	);
	set("outdoors", "city");
	set("objects", ([
		__DIR__"npc/market_vendor" : 1,
	]));
	set("detail", ([
		"攤位" : "各式各樣的攤位擠在一起，賣什麼的都有。\n",
		"絲綢" : "幾匹色澤鮮豔的絲綢，據說是從龍安城運來的。\n",
	]));
	set("exits", ([
		"north" : __DIR__"egate",
	]));

	setup();
	replace_program(ROOM);
}
