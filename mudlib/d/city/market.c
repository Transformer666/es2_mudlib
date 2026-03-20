// Room: /d/city/market.c

inherit ROOM;

void create()
{
	set("short", "市集");
	set("long", @LONG
熱鬧的市集擠滿了各式各樣的攤販和買客。賣布匹的、賣瓷器
的、賣乾果蜜餞的……琳琅滿目。幾名走南闖北的行商正在大聲吆喝，
招攬生意。空氣中混雜著各種香料和食物的氣味，讓人目不暇接。
LONG
	);
	set("objects", ([
		__DIR__"npc/merchant" : 1,
		__DIR__"npc/peddler"  : 1,
	]));
	set("exits", ([
		"west"  : __DIR__"main_street",
		"north" : __DIR__"weapon_shop",
		"south" : __DIR__"armor_shop",
	]));

	setup();
	replace_program(ROOM);
}
