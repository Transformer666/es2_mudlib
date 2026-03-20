// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "月光小徑");
	set("long", @LONG
一條鋪著碎石的小徑在月光下泛著銀色的光芒，路兩旁種著成排的銀杏樹，落葉鋪滿了地面。偶爾有螢火蟲在樹叢中閃爍，如同飄動的星星。小徑的盡頭隱約可見一座涼亭的輪廓。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"pavilion",
		"east" : __DIR__"lake",
	]));

	setup();
	replace_program(ROOM);
}
