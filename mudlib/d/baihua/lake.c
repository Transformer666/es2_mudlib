// Room: /d/baihua/lake.c

inherit ROOM;

void create()
{
	set("short", "湖邊");
	set("long", @LONG
村子南邊有一個小湖﹐湖水清澈見底﹐水面上浮著幾朵粉紅色的蓮
花。湖邊長著幾棵垂柳﹐柳條拂著水面﹐倒映在湖中。幾隻白鷺站在
淺水處﹐不時低頭啄食小魚。這裡環境清幽﹐是個休憩的好地方。
LONG
	);
	set("outdoors", "village");
	set("exits", ([
		"north" : __DIR__"street",
	]));

	setup();
	replace_program(ROOM);
}
