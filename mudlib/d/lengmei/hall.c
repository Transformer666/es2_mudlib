inherit ROOM;

void create()
{
    set("short", "冷梅莊大廳");
    set("long", @LONG
大廳佈置得素雅清冷﹐正面牆上掛著一幅巨大的寒梅圖﹐畫中梅花
傲雪凌霜﹐氣韻非凡。兩側陳列著幾把精美的寶劍和一些古玩字畫。
LONG
    );
    set("objects", ([
        __DIR__"npc/meiyingfeng" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"yard",
        "west"  : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
