inherit ROOM;

void create()
{
    set("short", "道舍");
    set("long", @LONG
道舍整潔簡樸﹐幾張木床靠牆擺放﹐被褥疊放得整整齊齊。牆上掛
著幾幅山水畫和道教經文﹐窗前放著一個小書架﹐上面整齊地擺放著道
教典籍。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
