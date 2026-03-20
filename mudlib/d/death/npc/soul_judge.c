// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("判官", ({"soul_judge", "judge"}));
    set_attr("str", 24);
    set_attr("dex", 22);
    set_attr("con", 24);
    set_attr("int", 28);
    set_attr("spi", 30);
    set_attr("wis", 26);
    set_race("human");
    set_class("commoner");
    set_level(60);
    set_skill("staff", 90);
    set_skill("dodge", 70);
    set_skill("parry", 70);
    set_skill("force", 80);
    set("age", 3000);
    set("gender", "male");
    set("long",
        "判官端坐在冥王座前，一身黑袍，手持生死簿，目光如炬。他負\n"
        "責審判亡魂的善惡功過，決定來世的去處。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "判官翻開生死簿，冷冷道：下一個。\n",
        "判官道：善惡到頭終有報，莫道蒼天不開眼。\n",
    }));
    setup();
    carry_object(STOCK_WEAPON("staff"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    set_temp("apply/vision_of_ghost", 1);
}
