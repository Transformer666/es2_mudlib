// Room: /d/wutang/square_w.c

inherit ROOM;

void create()
{
	set("short", "廣場西邊");
	set("long", @LONG
這裡是五堂鎮廣場的西邊﹐靠近城牆的方向﹐可以看到西邊不遠處
厚實的夯土城牆和城門樓。地面鋪著青石板﹐經年累月的踩踏已經磨得
十分光滑。往東回到廣場中央﹐西邊通往西門﹐北邊有一條狹窄的小巷
蜿蜒而去。
LONG
	);
	set("exits", ([
		"east" : __DIR__"square",
		"west" : __DIR__"wgate",
		"north" : __DIR__"lane1",
	]));

	setup();
	replace_program(ROOM);
}
