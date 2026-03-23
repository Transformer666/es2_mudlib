// Room: /d/qianchang/square.c

inherit ROOM;

void create()
{
	set("short", "前場鎮廣場");
	set("long", @LONG
前場鎮的中心廣場，一棵枝繁葉茂的大榕樹矗立在廣場中央，粗
壯的氣根垂落而下，樹蔭遮蔽了大半個廣場。榕樹下擺著幾張石桌
石凳，幾個行腳商人正坐在那裡歇腳喝茶。廣場四周零星地擺著一
些攤位，賣著些瓜果乾貨之類的小買賣。雖然不及大城熱鬧，倒也
有幾分鄉鎮的煙火氣息。
LONG
	);
	set("objects", ([
		__DIR__"npc/villager" : 2,
	]));
	set("exits", ([
		"north" : __DIR__"inn",
		"south" : __DIR__"temple",
		"east"  : __DIR__"street1",
		"west"  : __DIR__"street2",
	]));

	setup();
	replace_program(ROOM);
}
