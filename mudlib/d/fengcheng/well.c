// Room: /d/fengcheng/well.c

inherit ROOM;

void create()
{
    set("short", "古井旁");
    set("long", @LONG
大街旁邊有一口用青石砌成的古井﹐井沿被磨得十分光滑﹐顯然
已經用了很多年。井旁立著一根木架﹐上面掛著打水的繩索和木桶。
幾個婦人正在井邊洗衣﹐閒話家常。一位白髮老者坐在井邊的石墩
上﹐瞇著眼睛曬太陽﹐看起來十分悠閒。
LONG
    );
    set("objects", ([
        __DIR__"npc/old_man" : 1,
    ]));
    set("detail", ([
        "古井" : "一口深不見底的古井﹐往下望去只能看到一圈幽暗的水光。據說這口井已有百年歷史。\n",
        "石墩" : "井邊放著幾個圓形的石墩﹐供人坐著歇息。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"street1",
    ]));

    setup();
    replace_program(ROOM);
}
