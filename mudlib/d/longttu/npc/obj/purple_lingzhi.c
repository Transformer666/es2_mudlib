// vim: syntax=lpc
// purple_lingzhi.c - 紫靈芝 (quest item for jiang_herb_debt)

inherit ITEM;

void create()
{
    set_name("紫靈芝", ({"purple lingzhi", "purple_lingzhi", "lingzhi"}));
    set_weight(500);

    if( !clonep() ) {
        set("unit", "株");
        set("value", 5000);
        set("long",
            "一株罕見的紫色靈芝﹐通體散發著淡淡的紫光﹐香氣撲鼻。\n"
            "這種靈芝生長在陰暗潮濕的井壁上﹐極為難得﹐是煉製\n"
            "解毒丹藥的珍貴材料。\n");
    }
    setup();
}
