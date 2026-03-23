// Room: /d/choyin/back_alley.c

inherit ROOM;

void create()
{
	set("short", "後巷");
	set("long", @LONG
店鋪後面的一條窄巷﹐堆著些廢棄的木箱和破舊的竹筐。幾條野
狗在垃圾堆裡翻找著食物﹐見人來也不怎麼害怕。牆角長著青苔﹐
地上濕漉漉的﹐瀰漫著一股潮濕腐朽的氣味。
LONG
	);
	set("exits", ([
		"north" : __DIR__"shop",
		"east" : __DIR__"teahouse",
	]));

	setup();
	replace_program(ROOM);
}
