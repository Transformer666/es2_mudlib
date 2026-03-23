// vim: syntax=lpc
// Quest item: 老乞婆的翠玉墜子

inherit ITEM;

void create()
{
    set_name("翠玉墜子", ({"jade_pendant", "jade pendant", "pendant"}));
    set_weight(200);

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 500);
        set("long",
            "一枚精巧的翠玉墜子﹐雕工細緻入微﹐玉質溫潤通透。墜子\n"
            "的背面刻著一個小小的「柳」字﹐似乎是家族的印記。雖然在\n"
            "井底泡了許久﹐但玉質依然瑩潤如新。\n");
    }
    setup();
}
