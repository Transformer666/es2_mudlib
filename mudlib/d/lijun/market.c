// Room: /d/lijun/market.c

inherit ROOM;

void create()
{
	set("short", "小市集");
	set("long", @LONG
渡口旁的一個小市集﹐雖然規模不大﹐卻也五臟俱全。幾個攤販
在地上鋪著粗布﹐擺著各種雜貨。有賣乾貨的﹐有賣草藥的﹐還有行
商在此兜售從南方帶來的稀罕物件。來往的旅人和本地居民在攤位間穿
梭挑選﹐討價還價聲此起彼伏。往西是渡口大街﹐往南沿河可以走到河
畔東段。
LONG
	);
	set("outdoors", "town");
	set("objects", ([
		__DIR__"npc/trader" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"street",
		"south" : __DIR__"riverside_e",
	]));

	setup();
	replace_program(ROOM);
}
