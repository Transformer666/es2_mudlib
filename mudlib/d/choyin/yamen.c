// Room: /d/choyin/yamen.c

inherit ROOM;

void create()
{
	set("short", "喬陰縣衙");
	set("long", @LONG
喬陰縣衙的大門﹐門前立著兩根石柱﹐柱上蹲著一對石獅子。大門
上方掛著一塊黑底金字的匾額﹐上書「喬陰縣衙」四字。門前擺著一面
大鼓﹐那是供百姓告狀擊鼓鳴冤之用。衙門口站著兩名衙役﹐板著臉
盯著來往的行人﹐一副公事公辦的模樣。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"square",
		"north" : __DIR__"east_lane",
	]));

	setup();
	replace_program(ROOM);
}
