// Room: /d/lee/r2.c

inherit ROOM;

void create()
{
	set("short", "村口");
	set("long", @LONG
李家村的村口﹐一棵老榕樹下立著一塊青石碑﹐上面刻著「李家村」
三個字。榕樹下有一條石凳﹐幾個老人坐在上面乘涼聊天。村子不大﹐
一眼便能望到頭﹐家家戶戶的房屋都是青磚黛瓦﹐看起來頗為整齊。
LONG
	);
	set("outdoors", "village");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"r1",
		"east" : __DIR__"street",
		"north" : __DIR__"back_street",
	]));

	setup();
	replace_program(ROOM);
}
