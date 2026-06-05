// Room: /d/hanmei/gate.c

inherit ROOM;

void create()
{
	set("short", "冷梅莊大門");
	set("long", @LONG
這裡是冷梅莊的大門﹐兩扇朱漆大門半開半掩﹐門楣上懸著一塊烏
木匾額﹐上書「冷梅莊」三個遒勁的大字。門前一道青石階梯通往鎮中
的街道﹐階旁植著數株老梅﹐枝幹虯曲﹐每逢寒冬便傲然吐蕊。往北穿
過大門便是莊內的前院﹐往東北沿著石階下去﹐便回到雪亭鎮廣場的西
南角。
LONG
	);
	set("detail", ([
		"匾額" : "烏木匾額上「冷梅莊」三字筆力沉雄﹐據說是莊主梅影風親筆所題。
",
		"老梅" : "幾株老梅栽在石階兩側﹐枝椏蒼勁﹐隱隱透著一股清冷孤傲的氣
息。
",
	]));
	set("outdoors", "snow");
	set("exits", ([
		"north" : __DIR__"yard",
		"northeast" : "/d/snow/square_sw",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
