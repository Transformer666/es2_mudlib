// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "靈雲觀");
    set("long", @LONG
靈雲觀是茅山修煉靈術的道觀，觀門簷下懸掛著一排排符籙，在
風中微微搖曳。空氣中隱隱流動著一股靈氣，令人精神一振。觀內香
煙繚繞，隱約可聞道士們誦經修煉的聲音。
LONG
    );
    set("exits", ([
        "south" : __DIR__"hall",
        "north" : __DIR__"altar",
    ]));

    set("objects", ([
        __DIR__"npc/elder" : 1,
    ]));

    setup();
    replace_program(ROOM);
}
