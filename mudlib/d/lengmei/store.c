inherit ROOM;

void create()
{
    set("short", "梅林商鋪");
    set("long", @LONG
一間小巧的商鋪﹐門口掛著一幅褪色的布幌﹐上面寫著「百貨」兩字
。鋪子裡陳列著各種日用雜貨和一些兵器防具﹐都是周圍村民和過路旅
人常用的東西。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/vendor" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"square",
    ]));

    setup();
    replace_program(ROOM);
}
