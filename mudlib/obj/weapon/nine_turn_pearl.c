// nine_turn_pearl.c

inherit ITEM;

void create()
{
    set_name("九轉異龍珠", ({"nine turn dragon pearl", "nine_turn_pearl", "pearl"}));
    set_weight(300);

    if( !clonep() ) {
        set("unit", "顆");
        set("value", 600000);
        set("long",
            "一顆經過九次淬煉的龍珠，珠身泛著奇異的五彩光芒，內含異\n"
            "龍之力，據說乃是上古異龍所遺，蘊藏著不可思議的力量。\n");
    }
    setup();
}
