inherit ROOM;

void create()
{
    set("short", "教眾居室");
    set("long", @LONG
教眾的居室佈置簡單﹐幾張木床靠牆擺放。每個床頭都掛著一套黑
色的夜行服﹐牆角放著幾個武器架﹐上面插著各式暗器。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "south" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
