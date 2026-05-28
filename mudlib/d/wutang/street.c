// Room: /d/wutang/street.c

inherit ROOM;

void create()
{
	set("short", "五堂大街");
	set("long", @LONG
這是五堂鎮的大街﹐青石板路被往來的腳步磨得光滑發亮﹐街道兩
旁是一間間低矮的店鋪﹐簷下掛著各色幌子﹐隨風輕擺。北邊一面紙糊
的酒旗上寫著「飲鶴居」三個字﹐底下便是鎮上唯一的客棧﹔南邊一間
門面樸實的雜貨鋪﹐木門半開著。街道往東通往鎮中的十字路口﹐往西
則回到鎮口的牌坊。
LONG
	);
	set("detail", ([
		"酒旗" : "一面被風吹得有些褪色的酒旗﹐上頭「飲鶴居」三字筆力倒還蒼勁。\n",
		"幌子" : "店鋪簷下掛著各式各樣的幌子﹐有賣布的、賣油鹽的、也有代寫書信的。\n",
		"店鋪" : "街旁的店鋪大多是些小本生意﹐做的是鎮上街坊與過路客商的買賣。\n",
	]));
	set("objects", ([
		__DIR__"npc/townsman" : 1,
	]));
	set("outdoors", "wutang");
	set("exits", ([ /* sizeof() == 4 */
		"east" : __DIR__"cross",
		"west" : __DIR__"gate",
		"north" : __DIR__"inn",
		"south" : __DIR__"store",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
