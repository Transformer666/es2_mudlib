// Room: /d/shuilan/ngate.c

inherit ROOM;

void create()
{
    set("short", "水嵐縣北門");
    set("long", @LONG
這裡是水嵐縣的北門﹐城門外是一條泥濘的小路﹐蜿蜒通往北方
的羿水南岸渡口。因為靠近水邊﹐空氣中帶著一股潮濕的水腥味。
城門不大﹐但門楣上「水嵐」二字倒是寫得頗有氣勢。守門的兵士
靠在城門邊打著瞌睡﹐似乎對這個偏遠小縣的安危並不太擔心。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/guard" : 2,
    ]));
    set("exits", ([
        "south"     : __DIR__"street1",
        "northeast" : "/d/lijun/ferry_south",
    ]));

    setup();
    replace_program(ROOM);
}
