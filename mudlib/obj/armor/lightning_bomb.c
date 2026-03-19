// lightning_bomb.c

inherit ITEM;

void create()
{
    set_name("霹靂雷火彈", ({"lightning_bomb", "bomb"}));
    set_weight(500);

    if( !clonep() ) {
        set("unit", "顆");
        set("value", 50000);
        set("long",
            "一顆拳頭大小的漆黑球體，表面不時閃過細小的電弧，據說\n"
            "投擲後能引發驚天動地的爆炸，威力無窮。\n");
    }
    setup();
}
