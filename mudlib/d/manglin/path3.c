// Room: /d/manglin/path3.c

inherit ROOM;

void create()
{
	set("short", "莽林盡頭");
	set("long", @LONG
小徑到這裡便走到了盡頭﹐前方是一面陡峭的石壁﹐上面爬滿了苔
蘚。石壁的縫隙中滲出細細的泉水﹐匯成一條小溪流向南方。空氣清新
了不少﹐似乎遠離了莽林中央的瘴氣。四周一片寂靜﹐只有泉水叮咚的
聲音。
LONG
	);
	set("outdoors", "forest");
	set("exits", ([
		"south" : __DIR__"path2",
	]));

	setup();
	replace_program(ROOM);
}
