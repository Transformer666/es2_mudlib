// NPC: /d/tianhan/npc/shopkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("雜貨鋪老闆", ({"shopkeeper", "boss"}));
    set_attr("str", 11);
    set_attr("dex", 12);
    set_attr("con", 13);
    set_attr("int", 15);
    set_attr("spi", 12);
    set_race("human");
    set_class("commoner");
    set_level(8);

    set("age", 50);
    set("gender", "male");
    set("long",
        "一個瘦小的老頭兒，穿著一件打了好幾個補丁的棉襖，臉上佈滿\n"
        "了皺紋，卻總是帶著精明的笑容。他在天寒村開了大半輩子的雜貨\n"
        "鋪，什麼東西都能弄到一些。你可以用 list 看看貨物，用 buy 購買。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "雜貨鋪老闆搓了搓手，呵氣取暖。\n",
        "雜貨鋪老闆吆喝道：出門在外，乾糧火把少不了啊！\n",
        "雜貨鋪老闆嘆了口氣道：這鬼天氣，也沒幾個客人上門。\n",
    }));
    set("merchandise", ([
        STOCK_ITEM("ration") : 40,
        STOCK_ITEM("torch") : 20,
        STOCK_ARMOR("cloth") : 80,
        STOCK_WEAPON("staff") : 60,
    ]));

    setup();
    carry_money("coin", 80);
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
