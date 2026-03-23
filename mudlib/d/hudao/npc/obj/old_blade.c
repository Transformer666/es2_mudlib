// vim: syntax=lpc

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("虎紋斷刀", ({"old blade", "old_blade", "broken blade", "blade"}));
    set_weight(5000);
    setup_blade(3, 30, 5, 3);

    if( !clonep() ) {
        set("wield_as", ({"blade"}));
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把殘破的虎紋大刀﹐刀身佈滿了鏽跡﹐但隱約可見精美的\n"
            "虎頭浮雕。刀柄上纏著已經朽爛的虎皮﹐看起來有數十年的歷\n"
            "史了。據說這是虎刀門前任掌門年輕時的練功之刀。\n");
    }
    setup();
}
