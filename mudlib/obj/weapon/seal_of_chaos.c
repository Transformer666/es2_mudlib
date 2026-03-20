// seal_of_chaos.c

inherit ITEM;

void create()
{
    set_name("混沌之印", ({"seal of chaos", "seal_of_chaos", "seal"}));
    set_weight(500);

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 500000);
        set("long",
            "一枚散發著混沌之氣的古老印章，印面刻有無法辨認的上古符\n"
            "文，隱約可見火與水的元素在其中流轉。據說可以使用煉化之術\n"
            "將其轉化為火之印記或水之印記。\n");
    }
    setup();
}
