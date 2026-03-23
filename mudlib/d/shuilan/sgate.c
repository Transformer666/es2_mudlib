// Room: /d/shuilan/sgate.c

inherit ROOM;

void create()
{
    set("short", "水嵐縣南門");
    set("long", @LONG
這裡是水嵐縣的南門﹐城門比北門還要小些﹐門板上的漆皮已經
剝落了大半。門外是一條蜿蜒的土路﹐通往南邊的山野。從城門洞裡
吹進來的風帶著泥土和青草的氣味﹐偶爾能看到一兩個農夫挑著擔子
進出城門。守門的兵士無精打采地站在城門邊﹐百無聊賴地看著來往
的行人。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/guard" : 2,
    ]));
    set("exits", ([
        "north" : __DIR__"temple",
    ]));

    setup();
    replace_program(ROOM);
}
