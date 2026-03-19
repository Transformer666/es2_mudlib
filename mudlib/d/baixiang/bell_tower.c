// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "鐘樓");
    set("long", @LONG
一座高聳的木製鐘樓，樓內懸掛著一口巨大的青銅古鐘，鐘身上
鑄刻著密密麻麻的佛經經文。站在鐘樓上可以遠眺四周的山林景色，
群山疊翠，雲霧繚繞，令人心曠神怡。
LONG
    );
    set("exits", ([
        "west" : __DIR__"courtyard",
    ]));

    setup();
    replace_program(ROOM);
}
