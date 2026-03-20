// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "峽谷洞穴");
	set("long", @LONG
溪流消失在這個陰暗的洞穴中，洞壁上閃爍著一些發光的礦石，散發出幽幽的光芒。洞穴深處傳來持續不斷的水聲，地面上積著一層淺淺的水，冰涼刺骨。角落裡散落著一些獸骨和碎石。
LONG
	);
	set("objects", ([
		__DIR__"npc/canyon_bat" : 2,
		__DIR__"npc/jing_yutao" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"bottom",
	]));

	setup();
	replace_program(ROOM);
}
