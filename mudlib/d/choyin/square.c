// Room: /d/choyin/square.c

inherit ROOM;

void create()
{
	set("short", "喬陰縣廣場");
	set("long", @LONG
喬陰縣城的中心廣場﹐地面鋪著青石板﹐雖然有些年頭了﹐倒也平
整乾淨。廣場中央有一棵老槐樹﹐樹蔭下坐著幾個乘涼的老人。東邊
是縣衙的大門﹐西邊有一座城隍廟﹐往北是北街﹐往南則通往南街。廣
場一角坐著一個衣衫襤褸的老乞婆和一個擺攤算命的先生。
LONG
	);
	set("objects", ([
		__DIR__"npc/fortune_teller" : 1,
		__DIR__"npc/beggar" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"nstreet",
		"south" : __DIR__"sstreet",
		"east" : __DIR__"yamen",
		"west" : __DIR__"temple",
	]));

	setup();
	replace_program(ROOM);
}
