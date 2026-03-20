// Room: /d/jingji/yamen.c

inherit ROOM;

void create()
{
	set("short", "京畿衙門");
	set("long", @LONG
這裡是京畿的官府衙門，朱紅色的大門上掛著一塊黑底金字的匾額，
上書「明鏡高懸」四個大字。門前立著一面大鼓，據說是供百姓鳴冤所
用。衙門內部看起來莊嚴肅穆，幾名身著皂衣的衙役手持水火棍分列兩
旁，目光警惕地注視著來往的行人。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"square",
		"east" : __DIR__"garden",
		"north" : "/d/jail/entrance",
		"south" : __DIR__"bank",
	]));
	set("objects", ([
		__DIR__"npc/official" : 1,
	]));

	setup();
	replace_program(ROOM);
}
