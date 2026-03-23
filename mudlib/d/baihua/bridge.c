// Room: /d/baihua/bridge.c

inherit ROOM;

void create()
{
	set("short", "小石橋");
	set("long", @LONG
一座古樸的小石橋橫跨溪流之上﹐橋面的石板被歲月磨得光滑圓潤。
橋下溪水潺潺﹐清澈見底﹐幾尾小魚在水草間穿梭嬉戲。兩岸開滿
了不知名的野花﹐隨風搖曳﹐煞是好看。
LONG
	);
	set("outdoors", "village");
	set("exits", ([
		"north" : __DIR__"lake",
		"east" : __DIR__"pavilion",
	]));

	setup();
	replace_program(ROOM);
}
