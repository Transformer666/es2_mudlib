// Room: /d/city/armor_shop.c

inherit ROOM;

void create()
{
	set("short", "甲冑店");
	set("long", @LONG
店內擺放著各式護甲和防具，從輕便的皮甲到厚重的鐵鎧一應俱
全。幾副精美的鎖子甲掛在牆上，在燈光下閃爍著金屬的光澤。店主
是個壯實的老漢，正在仔細檢查一副新到的鎧甲。
LONG
	);
	set("objects", ([
		__DIR__"npc/armorer" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"market",
	]));

	setup();
	replace_program(ROOM);
}
