// yinxue.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("飲血", ({"yinxue", "yinxue sword", "sword"}));
    set_weight(6000);
    setup_sword(8, 50, 9, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 850000);
        set("long",
            "一把通體血紅的長劍，劍身上隱約可見流動的血絲紋路，握住\n"
            "劍柄時能感受到一股嗜血的渴望，傳說此劍曾飲盡千人之血，\n"
            "是五堂鎮流傳已久的神秘兇器。\n");
    }
    setup();
}
