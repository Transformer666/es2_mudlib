// Room: /d/longan/market.c

inherit ROOM;

void create()
{
	set("short", "龍安集市");
	set("long", @LONG
這裡是龍安城最熱鬧的集市，各式各樣的攤位擠滿了整條街。有賣
絲綢布匹的，有賣瓷器茶具的，也有賣乾果蜜餞的。南來北往的商人
在此交易，討價還價之聲不絕於耳。一股混合著香料和乾貨的氣味撲面
而來，讓人忍不住多看幾眼那些琳琅滿目的貨品。
LONG
	);
	set("exits", ([
		"west"   : __DIR__"square",
		"north"  : __DIR__"alley",
	]));
	set("objects", ([
		__DIR__"npc/merchant" : 1,
	]));

	setup();
	replace_program(ROOM);
}
