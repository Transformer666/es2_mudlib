// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "茅山祭壇");
    set("long", @LONG
山巔之上矗立著一座古老的石制祭壇，用於舉行高階的道家法事。
祭壇四周刻滿了古老的符文，在月光下隱隱發出微弱的光芒。從這裡
可以俯瞰整座茅山，雲海翻湧，氣象萬千。
LONG
    );
    set("exits", ([
        "south" : __DIR__"lingyun",
    ]));
    set("no_fight", 1);

    setup();
    replace_program(ROOM);
}
