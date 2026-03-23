// Room: /d/heifeng/road1.c

inherit ROOM;

void create()
{
	set("short", "東郊官道");
	set("long", @LONG
五堂鎮東門外的一條官道﹐路面鋪著碎石﹐兩旁的樹木漸漸稀疏。
遠處的山巒起伏﹐隱約可見山腰上有一面黑色的旗幟在風中飄揚。路
邊不時可以看到被遺棄的貨物和翻倒的車輛﹐看來這一帶並不太平。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"west" : "/d/wutang/egate",
		"east" : __DIR__"road2",
		"south" : "/d/fengbai/ngate",
	]));

	setup();
	replace_program(ROOM);
}
