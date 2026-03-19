inherit ROOM;

void create()
{
    set("short", "教眾居所");
    set("long", @LONG
教眾居所簡樸整潔﹐幾張木床沿牆擺放。牆上掛著玄天上帝的符咒
﹐每個床頭都放著一本道教經典。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "south" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
