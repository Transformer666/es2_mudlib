// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "地牢");
	set("long", @LONG
監獄的最深處是一間陰森恐怖的地牢，空間狹小而壓抑，天花板低得幾乎要碰到頭頂。地牢四壁佈滿了鐵環和鏈條，地面上有一些可疑的暗色斑跡。空氣中瀰漫著血腥和腐朽的氣味，牆角的一盞油燈發出微弱的光芒，映照出牆壁上觸目驚心的痕跡。
LONG
	);
	set("exits", ([
		"south" : __DIR__"guard_room",
	]));

	setup();
	replace_program(ROOM);
}
