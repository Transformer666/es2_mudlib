// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
一片寬闊的校場映入眼簾，黃土夯實的地面上留著無數操練的痕跡。
場邊整齊地排列著兵器架和練功木樁，幾排士兵正在烈日下操練陣法，
喊殺聲震天。校場北面是帥帳，東面通往營房，西面是練武場。
LONG
    );
    set("objects", ([
        __DIR__"npc/soldier" : 3,
    ]));
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"command",
        "east"  : __DIR__"barracks",
        "west"  : __DIR__"training",
    ]));

    setup();
    replace_program(ROOM);
}
