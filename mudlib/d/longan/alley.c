// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "小巷");
    set("long", @LONG
集市北面的一條幽深小巷，兩旁是高高的磚牆，頭頂只露出一線
天空。巷子裡光線昏暗，地面濕滑，角落裡堆放著一些破舊的木箱和竹
筐。偶爾有幾隻野貓從暗處竄出，發出尖銳的叫聲。這裡平日人跡罕至
，但據說是城中消息最靈通的地方，不少江湖中人喜歡在此暗中接頭。
LONG
    );
    set("exits", ([
        "south" : __DIR__"market",
        "east" : __DIR__"garden",
        "west" : __DIR__"west_street",
    ]));

    set("objects", ([ __DIR__"npc/beggar" : 1 ]));

    setup();
    replace_program(ROOM);
}
