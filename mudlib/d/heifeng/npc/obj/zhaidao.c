// zhaidao.c -- 黑風寨刀 (blade)：黑風寨頭目慣用的尋常厚背刀(非神兵、非 unique)。
//
// 用途：黑風寨大頭目閰狂風(d/heifeng/npc/yan_kuangfeng.c)伏誅時，**全服唯一**的簽名
//   神兵「破石巨劍」若已被先前的殺者取走(LOOT_D->unique_drop 回 0)，則改自其屍身遺落
//   此普通版本——使每一次擊殺閰狂風仍有一柄「像樣而非唯一」的好刀可得，不致空手而回。
//   (鏡 d/fonxan/npc/obj/qingzhang_sword.c 之於玄蘇劍的關係。)
//
// 數值定位：介於常見刀(setup_blade 2,10,50,1)與神兵之間——一柄精工而不逾矩的厚背刀，
//   可被強化系統正常強化(非起手頂 cap 之神兵)。

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("黑風寨刀", ({ "heifeng blade", "zhai blade", "blade" }) );
	set_weight(8600);
	setup_blade(3, 14, 70, 4);   // 傷害/力修 高於常見刀、低於簽名神兵破石巨劍。

	if( !clonep() ) {
		set("wield_as", ({ "blade", "twohanded blade" }) );
		set("unit", "把");
		set("value", 24000);
		set("rigidity", 40);
		set("long",
			"一柄黑風寨頭目慣用的厚背鋼刀。刀身寬厚﹐通體烏黑﹐刀刃開\n"
			"得極利﹐近刀脊處還隱隱可見幾道砍殺留下的缺口﹐刀柄上纏著\n"
			"早已被血汗浸得發黑的粗麻。這刀雖非寨主壓陣的那柄巨劍﹐論\n"
			"斤兩火候﹐也已是一柄殺人不眨眼的好兵刃了。\n");
		set("wield_msg", "$N「鏘」地一聲抽出那柄烏黑的黑風寨刀﹐刀光一閃﹐穩穩握在手中。\n");
		set("unwield_msg", "$N收刀入鞘。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
