// poshi_greatsword.c -- 神兵 巨劍『破石』(twohanded sword)。頂級裝備(top-tier gear)系列。
//
// 來源(doc)：docs/02-遊戲系統與機制/05-裝備與強化.md L184-186「黑風寨四頭目」一節載
//   黑風寨頭目「閰狂風」掉落「巨劍『破石』、紫羅點翠戰甲、天地雲衫、杞庸兵書」。
//   本檔取其中「巨劍『破石』」一件，落實為黑風寨大頭目閰狂風(d/heifeng/npc/yan_kuangfeng.c)
//   伏誅後、**全服唯一**掉落之頂裝巨劍——走 LOOT_D->unique_drop(全服至多一柄)；待第二
//   位殺者來時神兵已現世於他處﹐改得普通的「黑風寨刀」(d/heifeng/npc/obj/zhaidao.c)。
//
// 設計同 xuanshuang_sword.c / xuansu_sword.c：起手即頂住 enchant_cap，神兵之利在
//   「一出爐已臻強化之極」。此劍為閰狂風慣用的開山巨劍﹐以雙手揮使為主﹐故傷害量級
//   貼合 twohanded sword 一欄。setup_sword(5, 20, 150, 10)：
//     sword(單手)    ：傷害 15-110、力修 150%、乘數 5 (enchant_cap sword 110/150/5 到頂)
//     twohanded sword：傷害 15-160、力修 200%、乘數 5 (twohanded cap 210/225/5 內)
//   (與玄蘇劍同分式：神兵分式皆頂 cap﹐互不衝突——彼為封山輕劍﹐此為黑風重劍﹐長相迥異。)

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("破石巨劍", ({ "poshi greatsword", "poshi sword", "greatsword", "sword" }) );
	set_weight(13500);
	// 起手即頂住 enchant_cap：單手 15-110/150%/5、雙手 15-160/200%/5。
	setup_sword(5, 20, 150, 10);

	if( !clonep() ) {
		set("wield_as", ({ "twohanded sword", "sword" }) );
		set("unit", "把");
		set("value", 98000);
		set("rigidity", 58);
		set("unique", 1);
		set("long",
			"這便是黑風寨大頭目閰狂風那柄威震一方的開山巨劍『破石』。\n"
			"劍身闊厚如門板﹐通體烏沉沉地不見半點光亮﹐唯獨開了鋒的一\n"
			"線泛著青冷的寒芒。劍脊上鏨著一個斗大的「破」字﹐筆勢狂橫\n"
			"如刀劈斧鑿﹐正是這巨劍剛猛無儔的劍意所託。此劍沉重異常﹐\n"
			"尋常人連舉都舉它不起﹐唯閰狂風天生神力﹐方能雙手掄之如\n"
			"風。相傳當年閰狂風憑此一劍﹐連劈黑風山三道石坊而劍鋒不\n"
			"卷﹐「破石」之名由此而起。劍勢一旦掃出﹐挾風帶響﹐裂石開\n"
			"山猶在其次﹐當真有開碑裂甲之威——縱不假強化之力﹐其鋒其\n"
			"勢已臻巨劍之極。\n");
		set("wield_msg",
			"$N雙手一振﹐將那柄烏沉沉的破石巨劍自背後掄起﹐劍風掃處﹐"
			"挾著一股開山裂石的沉雄之勢﹐颯颯有聲﹗\n");
		set("unwield_msg", "$N將破石巨劍重重頓地﹐而後收於背後﹐那股裂石的沉雄劍勢方才稍斂。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
