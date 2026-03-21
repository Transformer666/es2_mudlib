inherit ROOM;

void create()
{
    set("short", "靜修室");
    set("long", @LONG
一間幽靜的修行室﹐地上鋪著蒲團﹐牆上掛著玄天上帝的畫像和道
教經文。室內燃著清香﹐空氣中瀰漫著一股寧靜祥和的氣息。
LONG
    );
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    set("objects", ([
        __DIR__"npc/disciple" : 1,
    ]));

    setup();
    replace_program(ROOM);
}
