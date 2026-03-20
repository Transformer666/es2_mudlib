// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("村長", ({"village elder", "village_elder", "elder"}));
    set_attr("str", 12);
    set_attr("dex", 10);
    set_attr("con", 14);
    set_attr("int", 18);
    set_attr("spi", 16);
    set_race("human");
    set_class("commoner");
    set_level(15);

    set("age", 60);
    set("gender", "male");
    set("long",
        "村長是個六十多歲的老人，面容和善，在村中頗有威望。他坐在村口\n"
        "的大樹下，搖著蒲扇，看著來來往往的人們。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "村長搖著蒲扇，慢悠悠地說道：年輕人，來坐坐吧。\n",
        "村長說道：這小村子雖然不大，但勝在安寧。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
