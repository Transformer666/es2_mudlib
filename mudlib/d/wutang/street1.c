// Room: /d/wutang/street1.c

inherit ROOM;

void create()
{
	set("short", "五堂大街");
	set("long", @LONG
這裡是五堂鎮最熱鬧的一條大街﹐兩旁店鋪鱗次櫛比﹐酒旗招展
﹐各式各樣的招牌琳瑯滿目。街上行人絡繹不絕﹐有挑著擔子的貨郎﹐
有牽著毛驢的旅客﹐也有三五成群閒逛的鎮民。往北可以回到廣場東邊
﹐南邊遠遠可以看到一間打鐵鋪子﹐東邊則是一家客棧的入口。
LONG
	);
	set("objects", ([
		__DIR__"npc/patrol" : 1,
		__DIR__"npc/guobu" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"square_e",
		"south" : __DIR__"smithy",
		"east" : __DIR__"inn_hall",
		"west" : __DIR__"store",
	]));

	setup();
	replace_program(ROOM);
}
