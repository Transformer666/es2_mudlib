// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "雜貨鋪");
	set("long", @LONG
一間用竹籬和茅草搭成的簡陋鋪子，幾塊木板架在石墩上當作貨架，上面擺著一些日用雜貨。雖然東西不多，但油鹽醬醋、草藥火把一應俱全，是村民們日常採買的唯一去處。
LONG
	);
	set("objects", ([
		__DIR__"npc/merchant" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}
