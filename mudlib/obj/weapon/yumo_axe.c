// yumo_axe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("域摩之斧", ({"yumo_axe", "yumo axe", "axe"}));
    set_weight(22000);
    setup_axe(12, 90, 15, 3);

    if( !clonep() ) {
        set("wield_as", "axe");
        set("unit", "把");
        set("value", 1200000);
        set("long",
            "一把極其沉重的雙手巨斧，斧身由一整塊隕鐵鍛造而成，斧刃\n"
            "處散發著幽暗的土黃色光芒。這是擊敗地靈域摩後獲得的至高獎\n"
            "勵，據說持有此斧者能借助大地之力，使出毀天滅地的一擊。斧\n"
            "柄上纏繞著古老的封印符文，隱隱傳來大地深處的震動。\n");
    }
    setup();
}
