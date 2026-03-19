#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
    set_name("鷹爪手套", ({"eagle_glove", "glove"}));
    set_weight(1000);
    setup_wrist_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 5000);
        set("long",
            "一雙黑色的皮手套﹐指尖鑲著鋒利的金屬鷹爪﹐既可防禦\n"
            "又可攻擊。\n");
        set("wear_as", "wrist_eq");
        set("apply_armor/wrist_eq", ([
            "armor": 2,
        ]));
    }
    setup();
}
