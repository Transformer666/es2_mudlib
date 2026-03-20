// Room: /d/babao/floor4.c

inherit ROOM;

void create()
{
    set("short", "八寶樓四樓 - 拳屋");
    set("long", @LONG
第四層是一間空曠的練武房，四壁掛著各種拳法的招式圖解。地板
上佈滿了深淺不一的拳印，每一個都深陷入堅硬的石板之中，可見此處
的主人拳力之猛。馬鍾聖是黑齒族人，為人沉默寡言，但出手絕不留情，
據說凡是見過他武功的人都已不在人世。
LONG
    );
    set("objects", ([
        "/d/wutang/npc/ma_zhongsheng" : 1,
    ]));
    set("detail", ([
        "拳印" : "石板上的拳印深達寸許，邊緣整齊，可見功力之深。\n",
        "招式圖" : "牆上掛著幾幅拳法招式圖，筆法精練。\n",
    ]));
    set("exits", ([
        "down" : __DIR__"floor3",
        "up" : __DIR__"floor5",
    ]));

    setup();
    replace_program(ROOM);
}
