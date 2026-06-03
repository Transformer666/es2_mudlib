// canglang_blade.c -- 神兵「蒼狼噬月刀」(blade)。頂級裝備(top-tier gear)系列。
//
// 來源(design)：蒼狼王(d/langwo/npc/wolfking.c)係本「重啟專案」自建之獵場巔峰
//   之獸，非 docs 所載之 canon mob，docs 亦未為其指定任何神兵。故此刀為「依
//   docs 命名慣式新擬」之頂裝——名取狼窩谷之蒼狼意象(蒼狼/噬月)﹐合於武俠通則
//   且不與任何 doc 既載神兵衝突。落實為蒼狼王伏誅後可掉落之頂裝刀(與既有的
//   普通戰利品『狼王獠牙』wolf_fang 並存，獠牙必掉、此刀稀掉)。
//
// 設計同其餘神兵：起手即頂住 enchant_cap blade 欄。
//   setup_blade(x,y,z,r) 依 feature/weapon/blade.c 展開：
//     blade(單手)      = init_damage(x,      y,     z,     r)
//     secondhand blade = init_damage(x,      y/2,   z,     r)
//     twohanded blade  = init_damage(x,      y*4/3, z*3/2, r)
//   取 setup_blade(4, 25, 200, 10)：
//     blade(單手)    ：mult4 range25 bonus200 roll10 → 傷害 14-110、力修200%、乘數4
//                      (enchant_cap blade = 110 / 200 / 4 —— 三項皆恰好到頂)
//     twohanded blade：mult4 range33 bonus300 roll10 → 傷害 14-142、力修300%、乘數4
//                      (enchant_cap twohanded blade = 210 / 300 / 4 —— 俱在上限內)

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("蒼狼噬月刀", ({ "canglang blade", "wolfmoon blade", "blade" }) );
	set_weight(9500);
	// 起手即頂住 enchant_cap：單手 14-110/200%/4、雙手 14-142/300%/4。
	setup_blade(4, 25, 200, 10);

	if( !clonep() ) {
		set("wield_as", ({ "blade", "twohanded blade" }) );
		set("unit", "把");
		set("value", 80000);
		set("rigidity", 50);
		set("unique", 1);
		set("long",
			"這柄『蒼狼噬月刀』背厚刃薄、形如滿月初虧﹐刀身上一道天然\n"
			"的灰白紋路自刀根直貫刀尖﹐宛若一頭引頸向月長嗥的蒼狼。刀\n"
			"刃淬得極利﹐近刀脊處卻仍泛著一層獸鐵特有的青灰光澤﹐握之\n"
			"沉甸甸的﹐隱隱透出一股山野莽獸的腥煞之氣。相傳鑄此刀的鐵\n"
			"取自狼窩谷深處的隕鐵﹐又以巔峰狼王的獠牙為引淬鋒﹐故其刃\n"
			"既猛且韌﹐一刀斫落﹐勢若蒼狼噬月﹐縱不假強化之力﹐其鋒已\n"
			"臻刀器之極。\n");
		set("wield_msg",
			"$N沉腰一沉﹐反手抽出那柄蒼狼噬月刀﹐刀光如一彎冷月當頭斫落﹐"
			"隱隱挾著一股山野的腥煞之氣﹗\n");
		set("unwield_msg", "$N將蒼狼噬月刀還鞘﹐那股莽獸般的腥煞之氣也隨之斂去。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
