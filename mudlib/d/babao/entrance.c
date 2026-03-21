// Room: /d/babao/entrance.c

inherit ROOM;

void create()
{
    set("short", "將軍府門前");
    set("long", @LONG
一座氣勢恢宏的府邸矗立在眼前，門楣上掛著一塊金漆大匾，上書
「將軍府」三個蒼勁有力的大字。府門兩側各蹲著一尊威武的石獅，門
前的石階被磨得光滑發亮。府邸四周圍著高大的院牆，牆頭插滿了鐵刺。
整座府邸散發著一股肅殺之氣，令人不由自主地放慢了腳步。
LONG
    );
    set("detail", ([
        "匾額" : "「將軍府」三個金色大字，筆力雄渾，氣勢不凡。\n",
        "石獅" : "兩尊石獅怒目圓睜，張牙舞爪，栩栩如生。\n",
    ]));
    set("objects", ([
        __DIR__"npc/mansion_guard" : 2,
    ]));
    set("exits", ([
        "southwest" : "/d/wutang/ngate",
        "north" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
