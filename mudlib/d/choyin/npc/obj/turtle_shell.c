// vim: syntax=lpc
// turtle_shell.c - 算命先生的占卜龜殼

inherit ITEM;

void create()
{
    set_name("龜殼", ({"turtle shell", "shell", "turtle_shell"}));
    set_weight(300);
    if( !clonep() ) {
        set("unit", "個");
        set("value", 100);
        set("long",
            "一隻打磨得油光發亮的龜殼﹐殼上刻著密密麻麻的卦象和符號﹐\n"
            "邊緣鑲著一圈銅片﹐做工十分精細。這是算命先生吃飯的傢伙﹐\n"
            "看起來已經有些年頭了。\n");
    }
    setup();
}
