// Room: /d/longan/square.c

inherit ROOM;

void create()
{
	set("short", "龍安廣場");
	set("long", @LONG
龍安城的中心廣場，地面鋪著整齊的花崗岩石板，中央矗立著一座
青銅麒麟雕像，據說是建城時所鑄，已有數百年歷史。廣場四周環繞著
氣派的建築，北面是一家頗有名氣的客棧，東面則是熱鬧的集市。幾個
孩童繞著麒麟雕像追逐嬉鬧，一旁的老人坐在石凳上悠閒地下著棋。
LONG
	);
	set("exits", ([
		"south" : __DIR__"street",
		"north" : __DIR__"inn",
		"east"  : __DIR__"market",
		"west"  : __DIR__"temple",
	]));

	set("objects", ([
		__DIR__"npc/storyteller" : 1,
	]));

	setup();
	replace_program(ROOM);
}
