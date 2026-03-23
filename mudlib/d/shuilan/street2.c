// Room: /d/shuilan/street2.c

inherit ROOM;

void create()
{
    set("short", "水嵐南街");
    set("long", @LONG
這裡是水嵐縣的南街﹐相比北街的繁華﹐南街要安靜許多。路旁
多是普通的民居﹐偶爾能看到幾個孩童在門前嬉戲。街的南端有一
座廟宇﹐青煙裊裊。
LONG
    );
    set("outdoors", "town");
    set("exits", ([
        "north" : __DIR__"square",
        "south" : __DIR__"temple",
    ]));

    setup();
    replace_program(ROOM);
}
