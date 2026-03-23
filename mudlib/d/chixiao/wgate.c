// Room: /d/chixiao/wgate.c

inherit ROOM;

void create()
{
	set("short", "赤魈村西口");
	set("long", @LONG
赤魈村西邊的入口﹐幾塊風化的大石頭散落在路旁﹐形成一道天然
的屏障。石頭之間的缺口便是進村的通道﹐旁邊立著一塊佈滿青苔的
石碑﹐上面模糊地刻著「赤魈」二字。從這裡往西是通往荒野的小路﹐
往東走不遠便是村子的入口。石頭旁一個身穿粗布衣衫的老人正靠著
石碑打盹。
LONG
	);
	set("outdoors", "wild");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"west"  : "/d/road/wild_path2",
		"east"  : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}
