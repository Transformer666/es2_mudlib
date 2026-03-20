// Room: /d/city/pawnshop.c

inherit ROOM;

void create()
{
	set("short", "當鋪");
	set("long", @LONG
當鋪的門面不大，卻透著一股古舊的氣息。櫃臺後的高架上堆滿
了各種典當之物，從珠寶首飾到兵器衣物應有盡有。掌櫃戴著一副老
花鏡，正借著油燈的光亮仔細端詳一件玉佩。
LONG
	);
	set("objects", ([
		__DIR__"npc/pawnbroker" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"alley",
	]));

	setup();
	replace_program(ROOM);
}
