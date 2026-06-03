// xuanshuang_sword.c -- 神兵「玄霜劍」(sword)。頂級裝備(top-tier gear)系列。
//
// 來源(design)：docs 05 列有大量神兵(穿靈、旋芒、天命刃、白龍牙…)與「玄蘇劍/
//   寒霜劍/玄鐵斬崩刀」等以材質前綴命名之名劍，然並無一把確切喚作「玄霜劍」者。
//   故此名為「依 docs 命名慣式(材質/意象前綴 + 兵器)新擬」之神兵——「玄」取
//   docs 武器材質前綴表中之意象、「霜」承冷冽之劍意﹐合於武俠通則而不與任何
//   doc 既載神兵衝突。落實為獸王摩雲(d/tianling/npc/moyun.c)伏誅後可掉落之頂裝劍。
//
// 設計同 zhanlong_axe.c：起手即頂住 enchant_cap，神兵之利在「一出爐已臻強化之極」。
//   setup_sword(x,y,z,r) 依 feature/weapon/sword.c 展開：
//     sword(單手)      = init_damage(x,      y,     z,     r)
//     secondhand sword = init_damage(x,      y/2,   z,     r)
//     twohanded sword  = init_damage(x,      y*3/2, z*4/3, r)
//   取 setup_sword(5, 20, 150, 10)：
//     sword(單手)    ：mult5 range20 bonus150 roll10 → 傷害 15-110、力修150%、乘數5
//                      (enchant_cap sword = 110 / 150 / 5 —— 三項皆恰好到頂)
//     twohanded sword：mult5 range30 bonus200 roll10 → 傷害 15-160、力修200%、乘數5
//                      (enchant_cap twohanded sword = 210 / 225 / 5 —— 俱在上限內)
//   故單手/雙手持之皆不逾 enchant_cap。

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("玄霜劍", ({ "xuanshuang sword", "frost sword", "sword" }) );
	set_weight(7800);
	// 起手即頂住 enchant_cap：單手 15-110/150%/5、雙手 15-160/200%/5。
	setup_sword(5, 20, 150, 10);

	if( !clonep() ) {
		set("wield_as", ({ "sword", "twohanded sword" }) );
		set("unit", "把");
		set("value", 90000);
		set("rigidity", 55);
		set("unique", 1);
		set("long",
			"這是一柄通體泛著青白寒芒的名劍『玄霜劍』。劍身狹長筆直﹐\n"
			"以一種近乎透明的玄冰之鐵鑄成﹐其上天然生著一層薄薄的白霜\n"
			"似的紋路﹐拂之不去﹐握在手中﹐掌心便覺一陣沁骨的寒意。劍\n"
			"鋒過處﹐空氣裡彷彿都凝起一線細不可察的霜華。傳聞此劍鑄成\n"
			"之時正逢千年不遇的玄霜之夜﹐鑄師借天地至寒之氣封劍於鋒﹐\n"
			"故其刃冷冽絕倫、削鐵如泥﹐縱不假強化之術﹐其利亦已到了尋\n"
			"常兵器再難企及的地步。\n");
		set("wield_msg",
			"$N手腕一抖﹐青光一閃﹐那柄玄霜劍已亮在手中﹐劍上霜華隱隱﹐"
			"周遭似都隨之一冷﹗\n");
		set("unwield_msg", "$N將玄霜劍緩緩入鞘﹐那縷沁骨的寒意方才稍歇。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
