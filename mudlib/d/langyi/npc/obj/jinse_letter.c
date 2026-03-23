// vim: syntax=lpc
// jinse_letter.c - 金蛇密函 (quest item for jinse_letter quest)

inherit ITEM;

void create()
{
    set_name("金蛇密函", ({"jinse letter", "jinse_letter", "letter"}));
    set_weight(100);

    if( !clonep() ) {
        set("unit", "封");
        set("value", 0);
        set("long",
            "一封用蠟封好的密函﹐封口上蓋著一條盤踞金蛇的印記。信封\n"
            "上沒有署名﹐但紙質上乘﹐顯然出自富貴之家。\n");
    }
    setup();
}
