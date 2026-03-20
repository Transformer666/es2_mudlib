// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "泉水小徑");
	set("long", @LONG
一條蜿蜒的石板小路沿著泉水流淌的方向延伸，路兩旁不時有熱泉從地面湧出，冒著嫋嫋的白煙。石板上長滿了溫泉特有的綠色藻類，走起來十分濕滑。空氣溫暖而潮濕，讓人感到一陣陣的暖意。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"entrance",
		"north" : __DIR__"hot_spring",
		"south" : __DIR__"waterfall",
	]));

	setup();
	replace_program(ROOM);
}
