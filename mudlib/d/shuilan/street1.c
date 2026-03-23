// Room: /d/shuilan/street1.c

inherit ROOM;

void create()
{
    set("short", "水嵐北街");
    set("long", @LONG
這裡是水嵐縣的北街﹐是縣城通往北方渡口的主要道路。街道兩
旁多是客棧和酒肆﹐因為不少過河的旅人會在此歇腳。石板路面因
為潮濕而長滿了青苔﹐走起來有些滑。薄霧中﹐遠處的建築若隱若
現﹐別有一番朦朧之美。
LONG
    );
    set("outdoors", "town");
    set("exits", ([
        "south" : __DIR__"square",
        "north" : __DIR__"ngate",
    ]));

    setup();
    replace_program(ROOM);
}
