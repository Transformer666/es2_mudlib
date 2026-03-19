// Room: /d/sanyen/entrance.c

inherit ROOM;

void create()
{
	set("short", "焱硝村口");
	set("long", @LONG
一個偏僻的小村莊﹐村口豎著一根歪斜的木柱﹐上面掛著一塊寫著
「焱硝村」的木牌。村子不大﹐只有十幾戶人家﹐房屋大多是土牆茅頂。
村口北邊的山上隱約可見黑風寨的旗幟﹐村民們似乎對此已經習以為常。
村口東邊的空地上立著一根粗壯的石柱﹐似乎是練功用的。
LONG
	);
	set("outdoors", "village");
	set("exits", ([
		"north" : "/d/heifeng/road2",
		"south" : __DIR__"street",
		"east" : __DIR__"pillar",
	]));

	setup();
	replace_program(ROOM);
}
