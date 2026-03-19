inherit ROOM;

void create()
{
    set("short", "禪房");
    set("long", @LONG
一間幽靜的禪房﹐佈置極為簡樸﹐只有一張蒲團、一盞油燈和一部
經書。牆上掛著一幅觀音菩薩的畫像﹐室內瀰漫著淡淡的檀香。在這
裡打坐修行﹐可以感受到一股平靜祥和的力量。
LONG
    );
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
