// Room: /d/lee/gate.c

inherit ROOM;

void create()
{
	set("short", "李家村村門");
	set("long", @LONG
河邊小路的盡頭﹐一道簡樸的石砌門樓橫跨在路中央﹐門楣上嵌著
一塊青石匾額﹐上書「李家村」三個蒼勁有力的大字。門樓兩側各立
著一根石柱﹐柱上雕刻著樸素的雲紋。門前的地上鋪了幾塊平整的
石板﹐打掃得乾乾淨淨。門內可以看到整齊的青磚瓦房和嫋嫋升起
的炊煙﹐一股豆腐的清香從村裡飄了出來。
LONG
	);
	set("outdoors", "village");
	set("exits", ([
		"west" : __DIR__"r1",
		"east" : __DIR__"r2",
	]));

	setup();
	replace_program(ROOM);
}
