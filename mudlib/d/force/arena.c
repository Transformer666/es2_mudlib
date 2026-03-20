// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "比武擂台");
	set("long", @LONG
一座用青石砌成的擂台矗立在練武場北端，台面寬約三丈，四角立著石獅。擂台上刻著八卦圖紋，中央嵌著一塊太極石板。據說這裡曾經舉辦過無數次的比武大會，不少江湖高手都曾在此一較高下。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/weapon_master" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"training_ground",
		"east" : __DIR__"cliff_edge",
	]));

	setup();
	replace_program(ROOM);
}
