// Room: /d/wenguo/egate.c

inherit ROOM;

void create()
{
	set("short", "東城門");
	set("long", @LONG
文國縣的東城門巍峨聳立﹐城牆比一般村鎮的要高出許多﹐青磚
砌成的城垛整齊排列。城門上方飄著一面繡有「文國」二字的大旗﹐
在風中獵獵作響。門洞寬敞﹐可容兩輛馬車並行﹐往來的商旅行人絡
繹不絕。城門外是一條通往東方前場鎮的官道﹐城門內則是繁華的東
大街。
LONG
	);
	set("outdoors", "city");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"east" : "/d/qianchang/wgate",
		"west" : __DIR__"street1",
	]));

	setup();
	replace_program(ROOM);
}
