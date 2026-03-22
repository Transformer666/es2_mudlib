// Room: /d/graveyard/entrance.c

inherit ROOM;

void create()
{
	set("short", "亂葬崗入口");
	set("long", @LONG
官道往西北方向延伸﹐路面漸漸變得坑窪不平﹐兩旁的積雪上隱約
可見一些凌亂的腳印。前方的樹木越來越稀疏﹐取而代之的是一片片
枯黃的荒草。空氣中隱約飄來一股腐土的味道﹐遠遠望去﹐可以看到
一片荒涼的墳塚散佈在灰濛濛的天際線下。路旁歪歪斜斜地插著一塊
木牌﹐上面用褪色的紅漆寫著「亂葬崗──生人迴避」。
LONG
	);
	set("outdoors", "wasteland");
	set("exits", ([
		"southeast" : "/d/snow/wgate",
		"north" : __DIR__"grave1",
	]));

	setup();
	replace_program(ROOM);
}
