// Room: /d/wutang/street2.c

inherit ROOM;

void create()
{
	set("short", "北街");
	set("long", @LONG
這裡是五堂鎮的北街﹐比起南邊的大街﹐這條街道顯得安靜肅穆了
許多。街道兩旁種著幾株老槐樹﹐樹蔭下偶爾可見幾個老者對弈閒談。
往南回到廣場北邊﹐往北可以看到一座門楣莊嚴的官府建築﹐那便是五
堂鎮的公堂了。
LONG
	);
	set("exits", ([
		"south" : __DIR__"square_n",
		"north" : __DIR__"court",
	]));

	setup();
	replace_program(ROOM);
}
