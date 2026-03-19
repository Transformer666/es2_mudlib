// Room: /d/lee/farm.c

inherit ROOM;

void create()
{
	set("short", "農田");
	set("long", @LONG
村子南邊是一大片農田﹐田裡種著水稻和蔬菜﹐綠油油的一片十分
喜人。田間有幾條窄窄的田埂﹐一個農夫正在田裡彎腰插秧﹐旁邊的
水牛在田埂上悠閒地吃草。遠處是連綿的青山﹐白雲在山間飄蕩﹐好
一幅田園風光。
LONG
	);
	set("outdoors", "village");
	set("objects", ([
		__DIR__"npc/farmer" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"street",
	]));

	setup();
	replace_program(ROOM);
}
