// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "迷霧小徑");
	set("long", @LONG
霧氣在這裡更加濃密，幾乎伸手不見五指。腳下的路時有時無，只能摸索著前進。潮濕的空氣中帶著一股腐朽的氣息，周圍的樹木形狀扭曲，像是巨大的鬼影。偶爾有冷風從不知名的方向吹來，帶著陣陣寒意。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/fog_snake" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"bridge",
		"east" : __DIR__"deep_fog",
	]));

	setup();
	replace_program(ROOM);
}
