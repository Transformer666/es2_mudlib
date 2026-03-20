// Room: /d/baihua/square.c

inherit ROOM;

void create()
{
	set("short", "百花村廣場");
	set("long", @LONG
村子中央的一片小廣場﹐地面鋪著整齊的青石板﹐縫隙間長出了幾
叢野花。廣場中央有一座小小的花壇﹐種滿了各色鮮花﹐散發著沁人
心脾的芬芳。幾個村民坐在花壇邊的石凳上閒聊。往北便是村口﹐往
南是一條蜿蜒的花村小徑﹐往東有一條小巷。
LONG
	);
	set("exits", ([
		"north" : __DIR__"entrance",
		"south" : __DIR__"street",
		"east"  : __DIR__"back_street",
	]));

	setup();
	replace_program(ROOM);
}
