// xiantian_charm.c

inherit ITEM;

void create()
{
    set_name("先天符", ({"xiantian_charm", "xiantian charm", "charm"}));
    set_weight(100);

    if( !clonep() ) {
        set("unit", "張");
        set("value", 50000);
        set("long",
            "一張泛黃的古老符紙，上面以硃砂繪製著複雜的茅山符文，\n"
            "散發著淡淡的靈氣。此符乃茅山派施展幻術的消耗品，可用\n"
            "於召喚靈獸或施展各種茅山秘術。\n");
    }
    setup();
}
