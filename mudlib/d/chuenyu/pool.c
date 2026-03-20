// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "碧玉潭");
	set("long", @LONG
這個深邃的水潭因為泉水中含有的特殊礦物質，呈現出一種美麗的碧綠色，宛如一塊嵌在山間的碧玉。潭水深不可測，水面上漂浮著幾片紅色的花瓣。潭邊有一座小小的石亭，看來是有人特意修建的。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : __DIR__"hot_spring",
		"east" : __DIR__"shrine",
	]));

	setup();
	replace_program(ROOM);
}
