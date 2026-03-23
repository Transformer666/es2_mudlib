// vim: syntax=lpc

inherit F_DBASE;

void create()
{
    set_name("兵符", ({"military talisman", "military_talisman", "talisman"}));
    set("long",
        "一塊銅製的半虎形兵符﹐正面刻著「振武」二字﹐背面刻著\n"
        "精細的調兵條令。這是振武軍營調動兵馬的信物﹐分量十足﹐\n"
        "拿在手中沉甸甸的。\n");
    set("unit", "塊");
    set("value", 0);

    if( clonep() )
        set("no_drop", "這兵符太重要了﹐你不敢隨便丟棄。\n");

    setup();
}
