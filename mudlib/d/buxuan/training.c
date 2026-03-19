inherit ROOM;

void create()
{
    set("short", "劍術房");
    set("long", @LONG
劍術房中擺放著幾個木製的劍架﹐上面插著各式練習用的木劍。牆上
掛著幾幅劍法圖解﹐旁邊還有一面銅鏡﹐供練劍者觀察自己的身法。
LONG
    );
    set("objects", ([
        __DIR__"npc/disciple" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
