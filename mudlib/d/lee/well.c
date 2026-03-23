// Room: /d/lee/well.c

inherit ROOM;

void create()
{
	set("short", "水井邊");
	set("long", @LONG
村中一口用青石砌成的水井﹐井沿上長滿了碧綠的苔蘚﹐顯得古樸而
幽靜。井水清澈見底﹐映著天上的白雲。井邊放著幾個木盆和一只水桶﹐
看來常有村民來此打水洗衣。一旁的石板上晾著幾件剛洗好的衣物﹐水漬
還未乾透。
LONG
	);
	set("outdoors", "village");
	set("exits", ([
		"west" : __DIR__"farm",
		"south" : __DIR__"pond",
	]));

	setup();
	replace_program(ROOM);
}
