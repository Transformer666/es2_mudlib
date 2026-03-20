// Room: /d/chixiao/village_square.c

inherit ROOM;

void create()
{
	set("short", "赤魈村廣場");
	set("long", @LONG
這裡是赤魈村的中心廣場﹐一片不大的空地被幾間破舊的房屋圍
繞著。廣場中央有一口古老的石井﹐井台上長滿了青苔。幾個村民
蹲在牆根下曬太陽﹐面色憔悴﹐看起來生活頗為艱辛。北邊傳來一
陣若有若無的水聲﹐似乎有什麼水源在那個方向。
LONG
	);
	set("detail", ([
		"石井" : "一口用青石砌成的古井﹐井沿上佈滿了裂紋和青苔﹐看起來已經枯了。\n",
		"房屋" : "幾間用土坯搭建的矮房﹐屋頂鋪著發黃的茅草﹐牆壁上有不少裂縫。\n",
	]));
	set("objects", ([
		__DIR__"npc/diling" : 1,
	]));
	set("exits", ([
		"west"  : __DIR__"entrance",
		"north" : __DIR__"wishing_pool",
		"south" : __DIR__"inn",
	]));

	setup();
	replace_program(ROOM);
}
