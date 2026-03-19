inherit ROOM;

void create()
{
    set("short", "哭笑門");
    set("long", @LONG
哭笑門的門面頗為詭異﹐門楣上掛著一塊匾額﹐上面雕刻著一張半
哭半笑的面具。左門柱上刻著一個「哭」字﹐右門柱上刻著一個「笑」
字﹐令人一見便覺得心裡發毛。
LONG
    );
    set("exits", ([
        "south" : __DIR__"alley",
        "north" : __DIR__"yard",
    ]));

    setup();
    replace_program(ROOM);
}
