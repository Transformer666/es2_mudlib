// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "月影湖");
	set("long", @LONG
一面靜謐的湖泊倒映著天邊的月亮，湖面上波光粼粼，如同碎銀灑落。湖邊長著一片蘆葦，風吹過時發出沙沙的聲響。湖水深處偶爾泛起漣漪，不知是魚兒浮游還是水底有什麼東西在動。東面的湖岸被一層濃霧籠罩。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"moonlight_path",
		"east" : "/d/waterfog/entrance",
	]));

	setup();
	replace_program(ROOM);
}
