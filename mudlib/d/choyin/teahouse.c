// Room: /d/choyin/teahouse.c

inherit ROOM;

void create()
{
	set("short", "茶樓");
	set("long", @LONG
南街西側的一間茶樓﹐推門進去便是一股茶香撲鼻而來。幾張
方桌旁坐著三三兩兩的茶客﹐正低聲閒聊著江湖上的奇聞軼事。
櫃台後的銅壺吐著白霧﹐小二提著茶壺穿梭其間﹐吆喝聲此起彼伏。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"sstreet",
		"west" : __DIR__"back_alley",
	]));

	setup();
	replace_program(ROOM);
}
