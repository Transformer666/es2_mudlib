// Room: /d/sanyen/street.c

inherit ROOM;

void create()
{
	set("short", "村中街道");
	set("long", @LONG
焱硝村中的一條土路﹐兩旁是低矮的民房。街道上行人稀少﹐偶爾
能看到幾個面帶愁容的村民匆匆走過。東邊有一座不大的廟宇﹐隱約可
聞誦經聲。西邊有一間簡陋的客店﹐門前掛著一面酒旗。
LONG
	);
	set("objects", ([
		__DIR__"npc/villager" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"square",
		"east" : __DIR__"temple",
		"west" : __DIR__"inn",
		"south" : __DIR__"back_alley",
	]));

	setup();
	replace_program(ROOM);
}
