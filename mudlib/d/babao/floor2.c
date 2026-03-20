// Room: /d/babao/floor2.c

inherit ROOM;

void create()
{
    set("short", "八寶樓二樓 - 武器庫");
    set("long", @LONG
第二層是一間巨大的武器庫，牆上掛滿了各式各樣的兵器。正中央
擺放著一尊沉重的武器架，上面陳列著司馬雷引以為傲的霸王系列裝備。
這裡的主人司馬雷是阿修羅族人，原本是天朝的一名參將，後來不知何
故淪為大漠八魔的一員。
LONG
    );
    set("objects", ([
        "/d/wutang/npc/sima_lei" : 1,
    ]));
    set("detail", ([
        "武器架" : "沉重的鐵製武器架，上面的兵器件件都是精品。\n",
    ]));
    set("exits", ([
        "down" : __DIR__"floor1",
        "up" : __DIR__"floor3",
    ]));

    setup();
    replace_program(ROOM);
}
