// xuantie_armor.c -- 玄鐵戰甲 (body armor)：平陽寨主公孫一笑尋常配給賊頭目的好甲
//                    (非頂裝、非 unique)。
//
// 用途：公孫一笑(d/pingyang/npc/gongsunyixiao.c)伏誅時，**全服唯一**的鎮寨神甲「冥龍
//   甲」若已被先前的殺者取走(LOOT_D->unique_drop 回 0)，則改自其屍身遺落此普通版本——
//   使每一次擊殺公孫一笑仍有一件「像樣而非唯一」的好甲可得，不致空手而回。鏡
//   d/fonxan/npc/obj/qingzhang_sword.c 之「普通備援」定位。
//
// 數值定位：介於常見護甲與頂防冥龍甲(armor22/attack16/defense18)之間——一件精工而不逾矩
//   的好甲，可被強化系統正常強化(非起手頂 cap 之頂裝)。apply 鍵只取 driver 確實會讀的
//   armor/attack/defense(見 feature/char/combat.c)，完全鏡 firescale_armor.c 之取捨。

#include <armor.h>

inherit F_ARMOR;

void create()
{
	set_name("玄鐵戰甲", ({ "xuantie armor", "xuantie zhanjia", "armor" }));
	set_weight(12000);
	setup_armor();

	if( !clonep() ) {
		set("unit", "件");
		set("value", 22000);
		set("wear_as", "armor");
		set("long",
			"一件以玄鐵打就的『玄鐵戰甲』。甲身色作沉沉的鐵青﹐胸前鉚\n"
			"著數排粗大的鐵釘﹐甲片厚實﹐護住前胸後背的要害﹐刀砍劍劈\n"
			"其上但聞鏗然之響。這是平陽寨主公孫一笑配給手下賊頭目的制\n"
			"式戰甲﹐雖不及他那件鎮寨的冥龍神甲遠甚﹐論斤兩火候﹐也已\n"
			"是一件難得的好甲了。\n");
		set("wear_msg", "$N將那件鐵青的玄鐵戰甲束上身軀﹐甲片相疊﹐鏗然作響。\n");
		set("unequip_msg", "$N卸下身上的玄鐵戰甲。\n");
		set("apply_armor/armor", ([
			"armor"   : 14,
			"attack"  : 10,
			"defense" : 12,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
