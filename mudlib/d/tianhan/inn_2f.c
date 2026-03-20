// Room: /d/tianhan/inn_2f.c

inherit ROOM;

void create()
{
    set("short", "域水客棧二樓");
    set("long", @LONG
客棧的二樓是幾間簡陋的客房，走廊上鋪著竹蓆，兩旁各有幾扇
木門。從窗戶望出去，可以看到天寒村的全貌，以及遠處蒼茫的原野。
寒風從窗縫中擠進來，發出嗚嗚的聲響。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "down" : __DIR__"inn",
    ]));

    setup();
    replace_program(ROOM);
}
