// Room: /d/zhenwu/yard.c

inherit ROOM;

void create()
{
	set("short", "振武校場");
	set("long", @LONG
這是振武軍營的校場﹐一片黃土夯實的廣闊空地﹐四周豎著一圈削
尖的木柵。場中塵土飛揚﹐數十名軍士正分作數隊操演陣法﹐喊殺之聲
震天動地。場邊一座兩丈高的點將台居西而立﹐台上旌旗招展﹔場東一
排營房便是收藏刀槍弓弩的兵器庫。往北是主將升帳議事的中軍帳﹐往
東是兵器庫﹐往西是點將台﹐往南則是軍營的轅門。
LONG
	);
	set("detail", ([
		"木柵" : "校場四周圍著一圈削尖的木柵﹐柵縫間隱約可見營外的雪景。
",
		"軍士" : "操演的軍士個個精神抖擻﹐隨著號令進退如一﹐顯是訓練有素
的勁旅。
",
		"塵土" : "馬蹄與步伐踏起漫天黃塵﹐夾著一股濃濃的汗味與鐵腥氣。
",
	]));
	set("outdoors", "snow");
	// 沒有設 no_fight，可在此 kill 草靶練功（沿用 /d/snow/drill.c 範式）。
	set("objects", ([
		__DIR__"npc/dummy" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"hall",
		"east" : __DIR__"armory",
		"west" : __DIR__"altar",
		"south" : __DIR__"gate",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
