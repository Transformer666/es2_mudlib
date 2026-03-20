// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "峽谷谷底");
	set("long", @LONG
谷底幽暗而潮濕，一條湍急的溪流在碎石間奔騰。兩面的岩壁如刀削般陡峭，向上望去只能看到一條細細的天空。溪流中翻滾著白色的水花，轟鳴聲在谷壁間迴盪。東面的溪流盡頭似乎有一個黑暗的洞穴。
LONG
	);
	set("exits", ([
		"up" : __DIR__"bridge",
		"east" : __DIR__"cave",
	]));

	setup();
	replace_program(ROOM);
}
