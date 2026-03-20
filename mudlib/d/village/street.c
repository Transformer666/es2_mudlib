// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "村中小路");
	set("long", @LONG
村子裡唯一的一條土路，兩旁是低矮的籬笆牆，牆內種著各種蔬菜瓜果。幾隻母雞在路邊悠閒地啄食，一條黃狗懶洋洋地趴在屋簷下。路的東邊有一家簡陋的客棧，西面是村裡的小廟，南面則通往農田。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/village_elder" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"entrance",
		"east" : __DIR__"inn",
		"west" : __DIR__"temple",
		"south" : __DIR__"farm",
	]));

	setup();
	replace_program(ROOM);
}
