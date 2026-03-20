// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "東側牢房");
	set("long", @LONG
這間牢房狹小而陰暗，只有牆壁高處一個巴掌大的小窗透進一絲微弱的光線。地上鋪著一些發霉的稻草，角落裡放著一個破瓦罐，權當做水碗使用。牆壁上有許多用指甲刻下的劃痕，記錄著不知多少個日夜。
LONG
	);
	set("objects", ([
		__DIR__"npc/prisoner" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"corridor",
	]));

	setup();
	replace_program(ROOM);
}
