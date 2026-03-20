// Room: /d/city/main_street.c

inherit ROOM;

void create()
{
	set("short", "大街");
	set("long", @LONG
寬闊的大街兩旁店鋪林立，酒樓茶肆、綢緞莊、藥鋪、當鋪等
應有盡有，一派繁華景象。青石板路面被無數行人的腳步磨得光滑發
亮，街上車水馬龍，叫賣聲此起彼伏。空氣中瀰漫著各種美食的香
氣，令人垂涎。
LONG
	);
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"square",
		"east"  : __DIR__"market",
		"west"  : __DIR__"alley",
	]));

	setup();
	replace_program(ROOM);
}
