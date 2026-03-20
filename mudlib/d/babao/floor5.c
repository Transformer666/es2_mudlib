// Room: /d/babao/floor5.c

inherit ROOM;

void create()
{
    set("short", "八寶樓五樓 - 鬼境");
    set("long", @LONG
第五層漆黑一片，空氣中瀰漫著一股腐臭的氣味。角落裡堆放著
一些枯乾的骸骨和腐爛的屍體，令人作嘔。這裡是「神行無蹤」公孫微
的地盤，這個焦僥族的怪人喜歡躲在黑暗中伺機而動，他的暗器功夫出
神入化，往往讓人防不勝防。
LONG
    );
    set("objects", ([
        "/d/wutang/npc/gongsun_wei" : 1,
    ]));
    set("detail", ([
        "骸骨" : "幾具枯乾的骸骨散落在角落，看來已經死去多時。\n",
    ]));
    set("exits", ([
        "down" : __DIR__"floor4",
        "up" : __DIR__"floor6",
    ]));

    setup();
    replace_program(ROOM);
}
