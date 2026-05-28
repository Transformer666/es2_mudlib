// Room: /d/wutang/cross.c

inherit ROOM;

void create()
{
	set("short", "十字路口");
	set("long", @LONG
這裡是五堂鎮的十字路口﹐也是鎮上最熱鬧的地方。路口中央立著
一座斑駁的石燈﹐入夜後鎮民會在裡頭點上一盞油燈﹐替夜行的人照路
。北邊一座門臉氣派的院落﹐門楣上懸著「鎮遠鏢局」的金字匾額﹐進
出的多是腰挎刀劍的鏢師。南邊樹蔭下支著一個茶攤﹐幾張矮凳上常坐
著歇腳閒談的人。往西是鎮上的大街﹐往東則是一條僻靜的小巷。
LONG
	);
	set("detail", ([
		"石燈" : "一座以整塊青石鑿成的石燈﹐燈室裡積著厚厚的燈油痕跡﹐顯然夜夜都點著。\n",
		"匾額" : "「鎮遠鏢局」四個金字寫得龍飛鳳舞﹐看得出鏢局在這一帶頗有些名頭。\n",
		"茶攤" : "樹蔭下的茶攤十分簡陋﹐一只大瓦壺﹐幾只粗碗﹐卻是鎮民閒話家常的好去處。\n",
	]));
	set("objects", ([
		__DIR__"npc/escort" : 1,
	]));
	set("outdoors", "wutang");
	set("exits", ([ /* sizeof() == 4 */
		"west" : __DIR__"street",
		"east" : __DIR__"eastlane",
		"north" : __DIR__"agency",
		"south" : __DIR__"teastall",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
