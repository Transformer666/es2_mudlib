// Room: /d/wutang/store.c

inherit ROOM;

void create()
{
	set("short", "雜貨鋪");
	set("long", @LONG
這是一間門面樸實的雜貨鋪﹐店裡的貨架上密密麻麻地堆著各色雜
物﹐油鹽醬醋、針頭線腦、草鞋斗笠﹐應有盡有﹐連牆角都掛滿了一串
串風乾的臘味。櫃臺後一個精明的小販正一邊撥著算盤﹐一邊吆喝著招
攬生意。鋪子裡瀰漫著一股醬料與乾貨混雜的氣味。鋪子後門外一道青
石緩坡往南下到河邊的過河渡口﹐北邊則通往鎮上的大街。
LONG
	);
	set("detail", ([
		"貨架" : "幾排頂到屋樑的木貨架﹐上頭擺滿了過日子用得著的零碎雜物﹐看得人眼花撩亂。\n",
		"臘味" : "牆角掛著一串串風乾的臘肉臘腸﹐油亮油亮的﹐散發著誘人的鹹香。\n",
		"算盤" : "小販手裡那把算盤珠子被撥得啪啪作響﹐看來生意還算不錯。\n",
	]));
	set("objects", ([
		__DIR__"npc/peddler" : 1,
	]));
	set("outdoors", "wutang");
	set("no_fight", 1);
	set("exits", ([ /* sizeof() == 2 */
		"north" : __DIR__"street",
		"south" : __DIR__"ferry",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
