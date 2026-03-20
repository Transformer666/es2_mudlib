// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "隱風觀");
    set("long", @LONG
隱風觀建在一處臨風的懸崖邊上，四周掛滿了風鈴，叮叮噹噹響
個不停。這裡是茅山教授風術的道觀，山風在此格外猛烈，吹得道袍
獵獵作響。觀中的道士們在風中打坐修煉，神態自若。
LONG
    );
    set("objects", ([
        __DIR__"npc/ouyang_wuji" : 1,
        __DIR__"npc/disciple" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"gate",
    ]));

    setup();
    replace_program(ROOM);
}
