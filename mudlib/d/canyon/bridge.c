// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "峽谷石橋");
	set("long", @LONG
一座天然形成的石橋橫跨在峽谷之上，橋面只有數尺寬，兩側便是萬丈深淵。橋下的谷底傳來隆隆的水聲，偶爾有水霧從下方噴湧而上。石橋上佈滿了青苔，踏上去滑溜溜的。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"narrow_pass",
		"east" : __DIR__"cliff_face",
		"down" : __DIR__"bottom",
	]));

	setup();
	replace_program(ROOM);
}
