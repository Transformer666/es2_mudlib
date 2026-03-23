// vim: syntax=lpc
// jade_offering.c - 古玉供品 (仙女畫卷之謎任務)

inherit ITEM;

void create()
{
    set_name("古玉供品", ({"jade offering", "jade", "offering"}));
    set_weight(200);
    if( !clonep() ) {
        set("unit", "塊");
        set("value", 200);
        set("long",
            "一塊溫潤如脂的古玉﹐雕成花籃形狀﹐和祠堂畫卷上仙女手持\n"
            "的花籃一模一樣。玉的底部刻著幾個古篆字﹕「百花長護﹐四季\n"
            "不衰」。看得出這塊玉已經有很長的歷史了。\n");
    }
    setup();
}
