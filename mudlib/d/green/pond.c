// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "草原水潭");
	set("long", @LONG
小溪在這裡匯聚成一個天然的水潭，潭水碧綠如玉，水面上漂浮著幾片荷葉。潭邊的泥地上留有不少動物的腳印，看來這裡是草原上各種野獸飲水的地方。水潭四周被高高的蘆葦環繞，十分隱蔽。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"stream",
	]));

	setup();
	replace_program(ROOM);
}
