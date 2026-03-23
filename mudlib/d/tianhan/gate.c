// Room: /d/tianhan/gate.c

inherit ROOM;

void create()
{
	set("short", "天寒村柵門");
	set("long", @LONG
天寒村外圍的柵門﹐用粗糙的木板和樹枝紮成﹐歪歪斜斜地立在
寒風中﹐搖搖欲墜的樣子讓人擔心隨時會倒塌。柵門上掛著一塊木牌
﹐寫著「天寒村」三個字﹐字跡被風雪侵蝕得已有些模糊。柵門旁有
一個小小的草棚﹐裡面放著一張破舊的木凳﹐是守衛歇息的地方。門外
往東北方向是通往官道的小路。
LONG
	);
	set("outdoors", "road");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"northeast" : "/d/road/road2",
		"southwest" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}
