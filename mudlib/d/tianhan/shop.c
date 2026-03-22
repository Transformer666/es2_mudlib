// Room: /d/tianhan/shop.c

inherit ROOM;

void create()
{
    set("short", "天寒村雜貨鋪");
    set("long", @LONG
一間低矮的土磚房子，門楣上歪歪斜斜地掛著一塊木牌，上面寫著
「百濟雜貨」四個字。屋裡的貨架上零零落落地擺著一些日用雜貨，雖
然種類不多，但對於這個偏僻的小村來說已經足夠了。一盞昏暗的油燈
掛在樑上，散發著微弱的光芒，勉強照亮這間不大的鋪子。
LONG
    );
    set("no_fight", 1);
    set("detail", ([
        "貨架" : "幾個簡陋的木製貨架，上面擺著乾糧、火把、草繩等日用品。\n",
        "木牌" : "一塊風吹日曬的木牌，上面的字跡有些模糊。\n",
    ]));
    set("objects", ([
        __DIR__"npc/shopkeeper" : 1,
    ]));
    set("exits", ([
        "north" : __DIR__"street2",
    ]));

    setup();
    replace_program(ROOM);
}
