// Room: /d/tianhan/cottage.c

inherit ROOM;

void create()
{
    set("short", "茅屋");
    set("long", @LONG
一間簡陋的茅草屋，牆壁是用黃泥和稻草混合砌成的，屋頂鋪著
厚厚的茅草。屋內陳設極為簡單，一張木床、一張矮桌、幾個陶罐就
是全部家當。靠牆的角落裡堆著一些乾柴，散發著淡淡的松木香氣。
LONG
    );
    set("detail", ([
        "陶罐" : "幾個粗糙的陶罐，裡面裝著一些醃菜和粗鹽。\n",
        "木床" : "一張窄小的木床，上面鋪著一條打了補丁的棉被。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"clearing",
    ]));

    setup();
    replace_program(ROOM);
}
