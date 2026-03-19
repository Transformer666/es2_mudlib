// Room: /d/wutang/egate.c

inherit ROOM;

void create()
{
	set("short", "五堂鎮東門");
	set("long", @LONG
這裡是五堂鎮的東門﹐兩扇厚重的包鐵木門大敞著﹐門洞上方的
石額刻著「東來紫氣」四個大字。城門兩側各站著一名腰佩刀劍的守衛
﹐警惕地注視著每一個進出的行人。門外是一條通往東方的官道﹐往西
穿過門洞便回到鎮內。
LONG
	);
	set("objects", ([
		__DIR__"npc/guard" : 2,
	]));
	set("exits", ([
		"west" : __DIR__"square_e",
		"east" : "/d/heifeng/road1",
	]));

	setup();
	replace_program(ROOM);
}
