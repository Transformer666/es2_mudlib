// vim: syntax=lpc
// Item: venom_sac.c - 蜈蚣毒囊 (quest item for fog_centipede)

inherit ITEM;

void create()
{
    set_name("蜈蚣毒囊", ({"venom sac", "venom_sac", "sac"}));
    set_weight(800);

    if( !clonep() ) {
        set("unit", "個");
        set("value", 300);
        set("long",
            "從大蜈蚣頭部取下的毒囊﹐外表呈暗紫色﹐裡面充滿了\n"
            "劇毒的液體﹐散發著令人作嘔的腥臭。據說可以入藥。\n");
    }
    setup();
}
