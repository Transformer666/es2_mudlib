// xuansu_sword.c -- 神兵「玄蘇劍」(sword)。頂級裝備(top-tier gear)系列。
//
// 來源(design)：docs/02-遊戲系統與機制/05-裝備與強化.md L151 載封山派掌門柳東蘆
//   掉落「玄蘇劍」。落實為封山掌門柳東蘆(d/fonxan/npc/master.c)伏誅後、**全服唯一**
//   掉落之頂裝劍——走 LOOT_D->unique_drop(全服至多一柄)；待第二位殺者來時神兵已現
//   世於他處﹐改得普通的「青嶂劍」(d/fonxan/npc/obj/qingzhang_sword.c)。
//   (玄霜劍 xuanshuang_sword 已屬天靈山獸王摩雲一系﹐故柳東蘆另立其 docs 本名玄蘇劍﹐
//    互不衝突。)
//
// 設計同 xuanshuang_sword.c / zhanlong_axe.c：起手即頂住 enchant_cap，神兵之利在
//   「一出爐已臻強化之極」。setup_sword(5, 20, 150, 10)：
//     sword(單手)    ：傷害 15-110、力修 150%、乘數 5 (enchant_cap sword 110/150/5 到頂)
//     twohanded sword：傷害 15-160、力修 200%、乘數 5 (twohanded cap 210/225/5 內)

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("玄蘇劍", ({ "xuansu sword", "sword" }) );
	set_weight(7700);
	// 起手即頂住 enchant_cap：單手 15-110/150%/5、雙手 15-160/200%/5。
	setup_sword(5, 20, 150, 10);

	if( !clonep() ) {
		set("wield_as", ({ "sword", "twohanded sword" }) );
		set("unit", "把");
		set("value", 92000);
		set("rigidity", 55);
		set("unique", 1);
		set("long",
			"這是封山派代代相承的鎮派名劍『玄蘇劍』。劍身狹長厚重﹐青\n"
			"鋼之中隱隱透出一脈幽碧﹐如青嶂遠峰上化不開的一線山嵐。劍脊\n"
			"上鏨著「守正」二字﹐筆意樸拙剛硬﹐正是封山一脈以靜制動、守\n"
			"若磐石的劍意所託。握之沉穩如負山嶽﹐出鞘卻又快若奔雷。相傳\n"
			"此劍由封山開派祖師親手所鑄﹐歷代唯掌門一人佩之﹐尋常弟子終\n"
			"其一生亦難得一見。縱不假強化之術﹐其鋒之利、其勢之沉﹐已遠\n"
			"非尋常兵器所能企及。\n");
		set("wield_msg",
			"$N雙手持定那柄玄蘇劍﹐劍尖緩緩下垂指地﹐青鋼幽碧﹐周身\n"
			"氣勢登時如青嶂遠峰般沉沉壓了下來﹗\n");
		set("unwield_msg", "$N長吸一口氣﹐將玄蘇劍穩穩還鞘﹐那股巍然的劍意方才稍斂。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
