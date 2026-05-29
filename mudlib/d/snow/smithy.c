// Room: /d/snow/smithy.c

inherit ROOM;

void create()
{
	set("short", "打鐵鋪子");
	set("long", @LONG
這裡是一間打鐵鋪子﹐鋪子中間一個燒著熊熊火燄的火爐映得你在
牆上的影子一晃一晃的﹐旁邊還有一個沈重的大鐵砧。靠牆的兵器架上
掛著各式打造好的刀、劍、槍、棍﹐寒光閃閃﹐想是供過往的江湖客挑
選防身的。鋪子的出口就在東邊。
LONG
	);
	set("detail", ([ /* sizeof() == 4 */
		"火爐" : "爐中炭火燒得正旺﹐烤得人臉上發燙。\n",
		"鐵砧" : "這個大鐵砧看起來十分沈重﹐上面滿是敲打的痕跡。\n",
		"兵器" : "兵器架上掛著木劍、匕首、短劍、長劍、單刀、長槍、鐵鞭等各\n"
			"色兵刃﹐你可以用 list 看鐵匠賣些什麼。\n",
		"鐵器" : "這些鐵器有鍋子、鏟子、鐵鎚、耕田用的鋤頭、犁等等。\n",
	]));
	set("no_clean_up", 0);
	set("objects", ([ /* sizeof() == 2 */
		__DIR__"npc/smith" : 1,
		__DIR__"npc/swordsmith" : 1,    // 劍甲門傳人 陳學亮，提供 enchant 強化服務
	]));
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"square_s",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
