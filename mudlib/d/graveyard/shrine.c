// Room: /d/graveyard/shrine.c

inherit ROOM;

void create()
{
	set("short", "破廟");
	set("long", @LONG
一座破敗不堪的小廟﹐屋頂塌了一半﹐牆壁裂開了好幾條大縫。廟
裡的神像早已面目全非﹐只剩下一個模糊的輪廓。供桌上積滿了灰塵﹐
蜘蛛網從屋角一直拉到門框。儘管如此﹐廟中還是住著一個守墓人﹐日
夜看守著這片亂葬崗。
LONG
	);
	set("objects", ([
		__DIR__"npc/grave_keeper" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"grave3",
		"down" : "/d/hell/entrance",
	]));

	setup();
	replace_program(ROOM);
}
