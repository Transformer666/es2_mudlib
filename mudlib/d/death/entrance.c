// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "死域入口");
	set("long", @LONG
空氣中突然瀰漫著一股腐敗和死亡的氣息，地面上的草木枯萎發黑，泥土呈現出一種不健康的灰白色。四周一片死寂，連蟲鳴鳥叫都消失了。前方的道路被一層暗紅色的霧氣所籠罩，隱約可以聽到遠處傳來低沉的嗚咽聲。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : "/d/hell/entrance",
		"north" : __DIR__"dark_path",
	]));

	setup();
	replace_program(ROOM);
}
