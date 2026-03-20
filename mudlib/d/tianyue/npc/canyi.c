// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("殘蟻師太", ({"canyi", "canyi_shitai", "shitai"}));
    set("nickname", "殘蟻師太");
    set_attr("str", 25);
    set_attr("dex", 30);
    set_attr("con", 25);
    set_attr("int", 28);
    set_attr("spi", 32);
    set_attr("wis", 28);
    set_attr("cor", 20);
    set_attr("cps", 24);
    set_race("human");
    set_class("monk");
    set_level(70);
    advance_stat("gin", 260);
    advance_stat("kee", 260);
    advance_stat("sen", 260);

    set_skill("needle", 110);
    set_skill("dodge", 100);
    set_skill("parry", 85);
    set_skill("force", 100);
    set_skill("unarmed", 90);

    set("age", 65);
    set("gender", "female");
    set("long",
        "殘蟻師太是天月庵的前任住持，面容嚴肅，眉宇間透著一股不怒而\n"
        "威的氣勢。她精通針法與內功，在武林中地位崇高。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "殘蟻師太雙手合十﹐低聲誦道﹕阿彌陀佛﹐萬法皆空。\n",
        "殘蟻師太淡淡說道﹕修行之道﹐在於戒律﹐更在於心。\n",
        "殘蟻師太微微閉目﹐似在冥想﹐周身散發著一股肅穆的氣息。\n",
        "殘蟻師太嘆道﹕江湖恩怨﹐何時方能了結？\n",
    }));

    setup();

    add_temp("apply/attack", 80);
    add_temp("apply/defense", 80);
    add_temp("apply/damage", 30);
    add_temp("apply/armor", 70);

    carry_object("/obj/area/obj/cloth")->wear();
}
