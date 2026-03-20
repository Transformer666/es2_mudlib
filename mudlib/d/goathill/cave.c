// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "羊山山洞");
	set("long", @LONG
這是一個天然形成的山洞，洞口不大，但裡面卻相當寬敞。洞壁上掛著一些鐘乳石，地上散落著一些動物的骨頭和皮毛，看來是某種野獸的巢穴。洞內陰暗潮濕，深處傳來滴水的回聲。
LONG
	);
	set("objects", ([
		__DIR__"npc/mountain_hermit" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"hillside",
	]));

	setup();
	replace_program(ROOM);
}
