// ancient_dagger.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("古鄔匕", ({"ancient dagger", "ancient_dagger", "dagger"}));
    set_weight(700);
    setup_dagger(5, 16, 80, 2);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 350000);
        set("long",
            "一把古老的短匕，匕身雖已年代久遠卻依然鋒利如新，上面刻\n"
            "有古鄔族的神秘圖騰，乃軍備商販售的精品。\n");
    }
    setup();
}
