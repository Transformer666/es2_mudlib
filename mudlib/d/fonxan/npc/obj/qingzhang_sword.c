// qingzhang_sword.c -- 青嶂劍 (sword)：封山派掌門柳東蘆的尋常佩劍(非神兵、非 unique)。
//
// 用途：柳東蘆(d/fonxan/npc/master.c)伏誅時，**全服唯一**的鎮派神兵「玄蘇劍」若已被
//   先前的殺者取走(LOOT_D->unique_drop 回 0)，則改自其屍身遺落此普通版本——使每一次
//   擊殺柳東蘆仍有一柄「對應其使用、像樣而非唯一」的封山劍可得，不致空手而回。
//
// 數值定位：介於常見長劍(setup_sword 2,10,50,1)與神兵玄蘇劍(5,20,150,10)之間——
//   一柄精工而不逾矩的好劍，可被強化系統正常強化(非起手頂 cap 之神兵)。

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("青嶂劍", ({ "qingzhang sword", "sword" }) );
	set_weight(7400);
	setup_sword(3, 14, 70, 4);   // 傷害/力修 高於長劍、低於神兵玄蘇劍。

	if( !clonep() ) {
		set("wield_as", "sword" );
		set("unit", "把");
		set("value", 28000);
		set("rigidity", 42);
		set("long",
			"一柄封山派門人慣用的青鋼長劍『青嶂劍』。劍身樸實無華﹐開\n"
			"鋒卻極利﹐劍格上以細線刻著青嶂峰的剪影﹐是封山弟子下山行走\n"
			"江湖時最常佩帶的一路好劍。雖非掌門所執的鎮派神兵﹐論斤兩\n"
			"火候﹐也已是難得的好兵刃了。\n");
		set("wield_msg", "$N「鏘」地一聲拔出青嶂劍﹐青鋼劍光一閃﹐穩穩握在手中。\n");
		set("unwield_msg", "$N收劍還鞘。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
