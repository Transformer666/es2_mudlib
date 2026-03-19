// Room: /d/wutang/lane1.c

inherit ROOM;

void create()
{
	set("short", "狹窄小巷");
	set("long", @LONG
這是一條狹窄的小巷﹐兩邊高牆聳立﹐僅容兩人並肩通過。牆頭
探出幾枝翠竹﹐地面因為常年不見陽光而長滿了青苔﹐走起來有些滑腳
。巷子裡瀰漫著一股草藥的清香﹐往北似乎有一家藥鋪。往南可以回到
廣場西邊。
LONG
	);
	set("exits", ([
		"south" : __DIR__"square_w",
		"north" : __DIR__"herb_shop",
	]));

	setup();
	replace_program(ROOM);
}
