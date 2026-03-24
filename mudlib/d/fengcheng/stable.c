// Room: /d/fengcheng/stable.c

inherit ROOM;

void create()
{
    set("short", "馬廄");
    set("long", @LONG
城門邊的一間馬廄﹐裡面拴著幾匹北地的矮腳馬﹐膘肥體壯﹐
毛色油亮。馬廄用厚實的石塊砌成﹐頂上蓋著厚厚的茅草﹐足以
抵擋北方的風雪。地上鋪著乾草﹐空氣中飄散著馬匹和乾草混合
的氣味。一個馬伕正在角落裡給一匹棗紅馬刷毛。
LONG
    );
    set("objects", ([
        __DIR__"npc/stable_hand" : 1,
    ]));
    set("detail", ([
        "矮腳馬" : "北地特有的矮腳馬﹐雖然個頭不高﹐但耐寒耐勞﹐是在天山一帶行走的好幫手。\n",
        "乾草" : "地上鋪著厚厚的乾草﹐踩上去軟綿綿的。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"sgate",
    ]));

    setup();
    replace_program(ROOM);
}
