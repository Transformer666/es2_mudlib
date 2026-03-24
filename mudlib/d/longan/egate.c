// Room: /d/longan/egate.c

inherit ROOM;

void create()
{
	set("short", "龍安東城門");
	set("long", @LONG
龍安城東面的城門巍峨聳立﹐厚重的城牆足有數丈之高﹐城門洞
用青石砌成﹐拱頂上雕刻著精緻的龍紋。兩扇包鐵木門敞開著﹐門前
站著四名身披甲冑的守城士兵﹐手持長槍﹐面容嚴肅。城門上方的箭
樓裡隱約可見弓箭手的身影。門外是通往官道的大路﹐門內便是龍安
城的主街。
LONG
	);
	set("outdoors", "city");
	set("objects", ([
		__DIR__"npc/guard" : 2,
	]));
	set("exits", ([
		"east"  : "/d/road/road2",
		"west"  : __DIR__"entrance",
		"south" : __DIR__"east_street",
	]));

	setup();
	replace_program(ROOM);
}
