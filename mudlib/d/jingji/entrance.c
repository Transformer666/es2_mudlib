// Room: /d/jingji/entrance.c

inherit ROOM;

void create()
{
	set("short", "京畿城門");
	set("long", @LONG
京畿重地的城門巍峨壯觀，巨大的石砌門樓上雕刻著騰雲駕霧的
龍紋，盡顯皇家氣派。城門洞高大寬敞，可容數騎並行。門前的石獅
威武雄壯，守護著這天朝的核心之地。來往的官員車轎和商旅行人絡繹
不絕，一派繁華景象。
LONG
	);
	set("exits", ([
		"north" : __DIR__"inn",
	]));

	setup();
	replace_program(ROOM);
}
