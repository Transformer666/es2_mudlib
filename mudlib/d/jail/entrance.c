// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "監獄大門");
	set("long", @LONG
一道厚重的鐵門擋在面前，門上佈滿了鏽跡和刮痕。門框上方刻著「天牢」兩個大字，字跡猙獰恐怖。門前站著兩名手持長槍的獄卒，面無表情地審視著每一個接近的人。鐵門背後傳來隱約的哀嚎聲和鐵鏈碰撞的聲響。
LONG
	);
	set("exits", ([
		"south" : "/d/jingji/yamen",
		"north" : __DIR__"corridor",
	]));

	setup();
	replace_program(ROOM);
}
