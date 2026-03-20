// sacred_root.c

inherit ITEM;

void create()
{
    set_name("聖木殘根", ({"sacred_root", "sacred root", "root"}));
    set_weight(3000);

    if( !clonep() ) {
        set("unit", "段");
        set("value", 100000);
        set("long",
            "一段古老的樹根，雖已枯朽卻散發著淡淡的聖潔光芒，據說\n"
            "乃是上古聖木被毀後殘留的根部，蘊含著強大的淨化之力，\n"
            "是地靈任務道具鏈中的關鍵材料。\n");
    }
    setup();
}
