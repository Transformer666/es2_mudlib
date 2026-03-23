// Room: /d/fengbai/street1.c

inherit ROOM;

void create()
{
    set("short", "楓柏村小路");
    set("long", @LONG
這是楓柏村裡唯一的一條路﹐用泥土夯實而成。路旁幾間土房﹐
房前曬著穀子和藥材。這裡的村民大多靠上山採藥和務農為生﹐日
子過得清苦但安穩。路的盡頭能看到幾棵高大的楓樹﹐隨風搖曳。
LONG
    );
    set("outdoors", "village");
    set("exits", ([
        "north" : __DIR__"square",
    ]));

    setup();
    replace_program(ROOM);
}
