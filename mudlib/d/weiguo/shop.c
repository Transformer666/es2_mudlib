// Room: /d/weiguo/shop.c

inherit ROOM;

void create()
{
	set("short", "軍需舖");
	set("long", @LONG
後營小路旁的一間軍需舖子﹐門面不大但貨品齊全。木架上擺放著
各種日用品和行軍必備的物資﹐牆角堆著幾捆粗布和草繩。掌櫃是個
精明的中年人﹐據說曾在軍中當過伙頭兵﹐退下來後便在此開了這間
舖子﹐專做軍民兩用的買賣。
LONG
	);
	set("objects", ([
		__DIR__"npc/shopkeeper" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"back_street",
	]));

	setup();
	replace_program(ROOM);
}
