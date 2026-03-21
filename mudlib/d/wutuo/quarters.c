inherit ROOM;

void create()
{
    set("short", "居室");
    set("long", @LONG
武陀弟子的居室﹐陳設簡單﹐幾張木床和書桌擺放得井井有條。桌
上放著醫書和筆記﹐牆角堆放著一些曬乾的草藥。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    set("objects", ([
        __DIR__"npc/disciple" : 2,
    ]));

    setup();
    replace_program(ROOM);
}
