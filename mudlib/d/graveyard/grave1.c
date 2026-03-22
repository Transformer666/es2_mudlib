// Room: /d/graveyard/grave1.c

inherit ROOM;

void create()
{
	set("short", "荒塚");
	set("long", @LONG
雪亭鎮西北方的一片荒涼之地﹐遍地是雜草叢生的墳塚。大大小小
的墳包散落在枯黃的野草之間﹐有些墓碑已經歪斜倒塌﹐字跡模糊不清。
一股陰森森的寒氣從地底湧上來﹐即使是大白天也讓人渾身發冷。偶爾
能看到幾隻烏鴉停在枯樹上﹐不祥地嘎嘎叫著。
LONG
	);
	set("outdoors", "wasteland");
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"grave2",
	]));

	setup();
	replace_program(ROOM);
}
