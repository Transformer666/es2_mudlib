// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "神殿正殿");
	set("long", @LONG
這是神殿的正殿，殿堂高聳宏偉，金碧輝煌。正中央供奉著一尊巨大的神像，神像面容莊嚴，手持法器，周身散發著淡淡的金光。神像前的銅鼎中燃著長明香，嫋嫋青煙直上殿頂。兩側各有一排蒲團，供信眾跪拜禱告。
LONG
	);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/high_priest" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"outer_hall",
		"north" : __DIR__"inner_sanctum",
		"west" : __DIR__"garden",
	]));

	setup();
	replace_program(ROOM);
}
