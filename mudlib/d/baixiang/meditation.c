// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "禪房");
    set("long", @LONG
一間清幽的禪房，地上鋪著簡素的蒲團。一盞油燈散發出柔和的光
芒，照亮了牆上掛著的一幅書法，上書「明心見性」四個大字。房間裡
瀰漫著淡淡的檀香，令人心神寧靜。
LONG
    );
    set("exits", ([
        "east" : __DIR__"main_hall",
    ]));
    set("no_fight", 1);

    setup();
    replace_program(ROOM);
}
