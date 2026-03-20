// Room: /d/city/yamen.c

inherit ROOM;

void create()
{
	set("short", "府衙");
	set("long", @LONG
威嚴的府衙大門緊閉，門前立著兩面「肅靜」、「迴避」的牌子。
幾名衙役手持水火棍站在門外，目光嚴厲地巡視著過往行人。衙門上
方的匾額寫著「明鏡高懸」四個大字，兩側石柱上刻著一副對聯。這
裡是城中官府的所在地，尋常百姓輕易不敢靠近。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}
