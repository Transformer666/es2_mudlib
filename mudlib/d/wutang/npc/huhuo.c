// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("毒刀胡惑", ({"huhuo", "hu huo", "poison blade"}));
    set("nickname", "毒刀");
    set_attr("str", 22);
    set_attr("dex", 25);
    set_attr("con", 20);
    set_attr("int", 20);
    set_attr("spi", 18);
    set_attr("wis", 22);
    set_race("human");
    set_class("commoner");
    set_level(40);

    set_skill("blade", 90);
    set_skill("dodge", 70);
    set_skill("parry", 60);
    set_skill("unarmed", 50);

    set("age", 45);
    set("gender", "male");
    set("long",
        "毒刀胡惑是個江湖上有名的掮客，專門替人排解仇怨。他面帶微笑\n"
        "，手持一把泛著幽光的短刀，看似和善，卻令人不寒而慄。他可以幫\n"
        "你消除門派之間的仇恨。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "毒刀胡惑把玩著手中短刀﹐笑道﹕冤家宜解不宜結﹐何必把路走死呢？\n",
        "毒刀胡惑說道﹕仇恨這東西啊﹐背得越久﹐越是沉重。\n",
        "毒刀胡惑瞇起眼睛﹐說道﹕想消除恩怨？這世上沒有免費的午餐。\n",
        "毒刀胡惑輕輕嘆息﹕江湖中人﹐誰不是帶著一身恩怨行走？\n",
    }));

    setup();

    carry_object("/obj/area/obj/dagger")->wield();
    carry_object("/obj/area/obj/cloth")->wear();
}
