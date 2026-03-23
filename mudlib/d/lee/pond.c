// Room: /d/lee/pond.c

inherit ROOM;

void create()
{
	set("short", "池塘邊");
	set("long", @LONG
村邊一方小小的池塘﹐水面上漂浮著幾片碧綠的荷葉﹐偶爾有蜻蜓
點水而過。池塘邊長著幾棵垂柳﹐柳枝低垂﹐輕拂水面。幾隻青蛙蹲
在荷葉上呱呱地叫著﹐此起彼伏﹐倒也平添了幾分鄉野的趣味。
LONG
	);
	set("outdoors", "village");
	set("exits", ([
		"north" : __DIR__"well",
		"east" : __DIR__"east_path",
	]));

	setup();
	replace_program(ROOM);
}
