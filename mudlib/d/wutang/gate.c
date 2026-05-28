// Room: /d/wutang/gate.c

inherit ROOM;

void create()
{
	set("short", "五堂鎮鎮口");
	set("long", @LONG
這裡是五堂鎮東面的鎮口﹐一座以青石壘成的舊牌坊橫跨在官道之
上﹐坊額上「五堂」兩個大字早已被風霜剝蝕得只剩淡淡的痕跡。沿著
牌坊往東是一條穿出老松林、通往鄰鎮雪亭的大路﹐往來的商旅鏢隊多
半由此進出﹐路旁立著一塊指路的木牌。往西踏入鎮中﹐便是五堂鎮的
大街了。
LONG
	);
	set("detail", ([
		"牌坊" : "這座青石牌坊年代久遠﹐坊柱上還隱約刻著幾行勸善的文字﹐如今多已模糊難辨。\n",
		"木牌" : "木牌上以斑駁的硃砂寫著﹕「東往雪亭、西入五堂」﹐底下還有人潦草地添了一行小字﹕「夜行小心松林匪。」\n",
		"官道" : "這條官道由黃土夯成﹐被無數車轍碾出深深的溝痕﹐一直往東伸進老松林裡。\n",
	]));
	set("outdoors", "wutang");
	set("exits", ([ /* sizeof() == 2 */
		"east" : "/d/snow/sgate",
		"west" : __DIR__"street",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
