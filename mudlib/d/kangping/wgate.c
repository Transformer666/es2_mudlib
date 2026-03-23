// Room: /d/kangping/wgate.c

inherit ROOM;

void create()
{
	set("short", "康平村西口");
	set("long", @LONG
康平村西邊的入口﹐幾根削尖的木樁紮成一道簡陋的柵欄﹐中間
留出一個可供牛車通過的缺口。柵欄旁邊搭了一個草棚﹐是守夜人歇
腳的地方。從這裡往西穿過灌木叢便是老松林﹐偶爾可以聽到林中傳
來的鳥叫聲。往東順著土路走便進入了村子。
LONG
	);
	set("outdoors", "village");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"west" : "/d/oldpine/road3",
		"east" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}
