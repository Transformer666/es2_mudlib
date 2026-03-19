// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "大雄寶殿");
    set("long", @LONG
大雄寶殿內供奉著一尊巨大的金身佛像，寶相莊嚴，慈眉善目。
佛像前的香案上擺滿了鮮花和供品，青煙裊裊。殿內兩側整齊地擺放
著一排排蒲團，供僧眾打坐參禪。西面有一道小門通往禪房。
LONG
    );
    set("exits", ([
        "south" : __DIR__"courtyard",
        "west"  : __DIR__"meditation",
    ]));

    setup();
    replace_program(ROOM);
}
