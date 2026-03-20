// mirror_of_gods.c

#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("封神寶鏡", ({"mirror of gods", "mirror_of_gods", "blunt"}));
    set_weight(3000);
    setup_blunt(3, 15, 60, 2);

    if( !clonep() ) {
        set("wield_as", "blunt");
        set("unit", "面");
        set("value", 200000);
        set("long",
            "一面古銅色的寶鏡，鏡面光滑如水，隱約能看到奇異的符文在鏡中流轉，\n"
            "據說此鏡能封印神靈之力。\n");
    }
    setup();
}
