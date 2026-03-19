// Room: /d/oldpine/road4.c

inherit ROOM;

void create()
{
	set("short", "松林出口");
	set("long", @LONG
松林漸漸稀疏﹐前方豁然開朗﹐陽光從樹梢間灑落﹐空氣也清新
了許多。往南可以看到一座城鎮的輪廓﹐那便是喬陰縣城了。往北則是
通回松林深處的小徑。路邊有幾個被砍伐過的樹樁﹐看來附近的居民
經常到這裡來砍柴。
LONG
	);
	set("outdoors", "forest");
	set("exits", ([
		"north" : __DIR__"road3",
		"south" : "/d/choyin/ngate",
	]));

	setup();
	replace_program(ROOM);
}
