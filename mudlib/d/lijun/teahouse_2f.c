// Room: /d/lijun/teahouse_2f.c

inherit ROOM;

void create()
{
	set("short", "清月樓二樓");
	set("long", @LONG
二樓是清月樓的雅座區﹐比樓下安靜許多。幾間用竹簾隔開的小
雅間沿窗排列﹐透過窗戶可以眺望羿水的壯闊景色。河面上點點白帆
﹐遠處山巒起伏﹐景色宜人。角落裡有幾張棋桌﹐偶爾可見旅人在此
對弈消遣。這裡是歇腳養神的好地方﹐往下走便回到一樓大廳。
LONG
	);
	set("no_fight", 1);
	set("detail", ([
		"窗戶" : "推開窗戶﹐河風迎面吹來﹐帶著水汽和草木的清香。羿水在眼前蜿蜒流過﹐景色令人心曠神怡。\n",
		"棋桌" : "幾張石質棋桌﹐桌面上刻著棋盤格子﹐棋子散落在一旁的竹簍裡。\n",
	]));
	set("exits", ([
		"down" : __DIR__"teahouse",
	]));

	setup();
	replace_program(ROOM);
}
