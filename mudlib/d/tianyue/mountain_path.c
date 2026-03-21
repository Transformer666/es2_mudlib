// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "天月山路");
    set("long", @LONG
一條幽靜的山間小路在竹林中蜿蜒而上﹐兩旁翠竹亭亭﹐微風吹過
﹐竹葉沙沙作響﹐彷彿有人在低聲吟誦經文。路旁偶爾可見幾朵野花
﹐在竹林的蔭蔽下靜靜綻放。沿著石階往北走﹐隱約可見一座庵堂的
飛簷翹角。
LONG
    );
    set("outdoors", "mountain");
    set("exits", ([
        "south" : "/d/road/mountain_road2",
        "north" : __DIR__"gate",
        "east" : "/d/road/mountain_road2",
    ]));

    setup();
    replace_program(ROOM);
}
