// firewood.c -- 松柴：青銅丹爐的燃料。
//
// 來源：docs/02-遊戲系統與機制/06-煉丹與書本系統.md
//   L34「松柴 (Firewood) 5 文」、L62「put firewood in furnace（依 kW 範圍 13-15 根松柴）」、
//   L81「二轉醫師後可 order firewood（最少 1000 根，網購）」。
//
// 機制：松柴是「可堆疊的燃料」。沿用 COMBINED_ITEM（與靈芝/當歸/養氣丹同型﹐見
//   obj/reagent/*、cmds/std/refine.c 註解）﹐故一物件帶 amount（根數）﹐買多份移入
//   身上自動合併、put N firewood in furnace 可分批投。每根松柴提供固定 kW 火力﹐
//   爐子點火後依「在爐中的松柴總根數」換算供火功率（見 obj/alchemy/furnace.c）。
//
// 數值（docs L62、L75）：小還丹須 130-150 kW、13-15 根松柴方足﹐故反推「每根松柴
//   約 10 kW」(130/13 = 150/15 = 10)。集中為 FIREWOOD_KW_EACH﹐爐子讀此值換算。
//
// runtime 鐵則：松柴是死物（非 living）﹐本檔不涉 ::die()/destruct() 於 living
//   (#10)﹔為純物件﹐非 F_VILLAGER NPC﹐不 include <weapon.h>(#12)。

inherit COMBINED_ITEM;

// 每根松柴提供的供火功率(kW)。13 根 -> 130 kW、15 根 -> 150 kW﹐恰落小還丹火力窗。
#define FIREWOOD_KW_EACH    10

void create()
{
    set_name("松柴", ({ "firewood", "松柴", "柴" }));
    if( !clonep() ) {
        set("unit", "捆");
        set("long", "一截截曬乾的松木柴薪﹐油脂豐厚﹐極耐燒﹐是煉丹生爐的上好燃料。\n");
        set("base_unit", "根");
        set("base_value", 5);       // docs L34：松柴 5 文。
        set("base_weight", 200);
        // query("firewood")：供爐子辨識「這是燃料」用﹐免靠檔名 inherits 判定。
        set("firewood", 1);
        // query("kw_each")：每根供火功率(kW)﹐爐子讀此值換算總火力。
        set("kw_each", FIREWOOD_KW_EACH);
    }
    set_amount(1);
    setup();
}

// 供 setup_amount 之便：給 NPC / 商店 / order 時直接設根數。
// (COMBINED_ITEM 已有 set_amount/add_amount﹐此處不另造﹐保留註解指明用法。)

// vim: set ts=4 sw=4 syntax=lpc
