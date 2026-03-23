// Room: /d/kangping/creek.c

inherit ROOM;

void create()
{
	set("short", "小溪邊");
	set("long", @LONG
村子西邊有一條清澈的小溪蜿蜒流過﹐溪水潺潺地淌過光滑的鵝
卵石﹐發出悅耳的叮咚聲。幾棵垂柳斜斜地探出枝條﹐柳絲拂過水面﹐
蕩起層層漣漪。溪畔長滿了青苔和野花﹐空氣中瀰漫著草木的清香。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"east"  : __DIR__"back_street",
		"south" : __DIR__"bamboo_grove",
	]));

	setup();
	replace_program(ROOM);
}
