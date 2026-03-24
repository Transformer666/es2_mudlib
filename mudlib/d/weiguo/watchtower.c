// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "瞭望塔");
    set("long", @LONG
一座高聳的木製瞭望塔矗立在廣場西側，塔身以粗壯的原木搭建，
結構堅固。攀上塔頂可以俯瞰整個衛國鎮和周圍的曠野，視野極為開闊。
塔上架著一面巨大的銅鑼，一旦發現敵情便可鳴鑼示警。值守的哨兵手
持長弓，警惕地注視著遠方的地平線。
LONG
    );
    set("exits", ([
        "east"  : __DIR__"square",
        "north" : __DIR__"training_ground",
    ]));

    set("objects", ([ __DIR__"npc/sentry" : 1 ]));

    setup();
    replace_program(ROOM);
}
