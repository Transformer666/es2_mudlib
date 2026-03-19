// jade_ruler.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("玉戒尺", ({"jade_ruler", "ruler", "blade"}));
    set_weight(2000);
    setup_blade(2, 5, 40, 2);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 150000);
        set("long",
            "一把溫潤如玉的戒尺，乃是文人學士所用之物，據說持此尺者\n"
            "修煉內功時能事半功倍，增進靈慧。\n");
    }
    setup();
}
