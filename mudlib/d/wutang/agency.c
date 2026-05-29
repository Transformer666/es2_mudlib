// Room: /d/wutang/agency.c

inherit ROOM;

void create()
{
	set("short", "鎮遠鏢局");
	set("long", @LONG
這是鎮遠鏢局的前廳﹐廳堂寬敞﹐正中一張太師椅後的牆上掛著一
面「鏢行天下」的橫匾﹐兩側的兵器架上整整齊齊地插著刀、槍、棍、
棒。牆角堆著幾口準備起運的鏢箱﹐箱上貼著紅紙封條﹐寫明了押運的
去處。幾名精壯的鏢師正在廳中擦拭兵刃﹐神情肅然。出口在南邊﹐通
往鎮中的十字路口。
LONG
	);
	set("detail", ([
		"橫匾" : "「鏢行天下」四個鎏金大字氣勢不凡﹐落款是本鏢局的總鏢頭。\n",
		"兵器架" : "兵器架上的刀槍棍棒都擦得雪亮﹐看得出鏢局上下都是練家子。\n",
		"鏢箱" : "幾口沉甸甸的鏢箱貼著紅紙封條﹐上面寫著押往喬陰、雪亭等地的字樣。\n",
	]));
	set("objects", ([
		__DIR__"npc/biaotou" : 1,
	]));
	set("outdoors", "wutang");
	set("no_fight", 1);
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"cross",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
