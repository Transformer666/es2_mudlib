// Room: /d/lee/back_street.c

inherit ROOM;

void create()
{
	set("short", "村後小路");
	set("long", @LONG
村口北邊的一條小路﹐路旁長著幾棵桃樹﹐落英繽紛﹐地上鋪了一
層粉色的花瓣。路邊有幾間矮小的柴房﹐堆放著劈好的柴禾。一隻黃
狗趴在路邊打盹﹐偶爾豎起耳朵聽聽動靜。
LONG
	);
	set("exits", ([
		"south" : __DIR__"r2",
	]));

	setup();
	replace_program(ROOM);
}
