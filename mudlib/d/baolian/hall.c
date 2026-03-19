inherit ROOM;

void create()
{
    set("short", "大雄寶殿");
    set("long", @LONG
大雄寶殿金碧輝煌﹐殿中供奉著三尊金身佛像﹐寶相莊嚴。佛像前
的香案上擺滿了鮮花和供品﹐裊裊的檀香在殿中瀰漫。殿堂兩側整齊
地擺放著蒲團﹐數名僧人正在靜坐參禪。
LONG
    );
    set("objects", ([
        __DIR__"npc/master" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"courtyard",
        "east"  : __DIR__"meditation",
        "west"  : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
