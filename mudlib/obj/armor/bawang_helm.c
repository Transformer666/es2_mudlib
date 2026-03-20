// bawang_helm.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("霸王銅冠", ({"bawang helm", "bawang_helm", "helm"}));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 200000);
        set("long",
            "一頂以精銅澆鑄的霸王冠，冠頂飾以虎牙，威風凜凜，乃是\n"
            "軍中大將的象徵。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 20,
        ]));
    }
    setup();
}
