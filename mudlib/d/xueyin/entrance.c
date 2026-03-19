inherit ROOM;

void create()
{
    set("short", "雪吟莊大門");
    set("long", @LONG
雪吟莊大門氣派非凡﹐門前立著兩尊石獅﹐門楣上掛著一塊烏木匾額
﹐上書「雪吟莊」三個遒勁有力的大字。門柱上掛著一副對聯﹐上聯是
「雪壓寒梅凌霜傲」﹐下聯是「吟風弄月劍氣豪」。
LONG
    );
    set("exits", ([
        "west" : "/d/snow/ebridge",
        "east" : __DIR__"yard",
    ]));

    setup();
    replace_program(ROOM);
}
