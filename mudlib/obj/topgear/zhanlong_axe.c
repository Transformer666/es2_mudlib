// zhanlong_axe.c -- 神兵「斬龍斧」(twohanded axe)。頂級裝備(top-tier gear)系列。
//
// 來源(doc)：docs/02-遊戲系統與機制/05-裝備與強化.md「妖塔系列」一節列出
//   「摩雲、混沌珠、斬龍斧、冶磺套、冥龍甲、征衣『血染』」——斬龍斧即此系列
//   神兵。本檔將其落實為一把獸王摩雲(d/tianling/npc/moyun.c)伏誅後可掉落的
//   頂裝斧。
//
// 設計(top-tier，數值「起手即達強化上限」)：
//   神兵之所以為神兵，在於它一出爐便已臻尋常兵器須以「強化之術」(cmds/std/
//   enchant.c)耗盡黃金/神力方能達到的上限。故本斧的傷害分式，恰好頂住
//   enchant_cap 表中 twohanded axe 與 axe 兩欄的天花板，而「不」逾越——
//   如此既彰其神兵之利，又不破壞強化系統所建立的戰鬥平衡(玩家仍無法把它
//   練得更高，因已到頂)。
//
//   setup_axe(x,y,z,r) 依 feature/weapon/axe.c 展開三式：
//     axe(單手)        = init_damage(x,      y,   z,     r)
//     secondhand axe   = init_damage(x,      y/2, z,     r)
//     twohanded axe    = init_damage(x,      y*2, z*4/3, r)
//   identify(cmds/std/identify.c)顯示：傷害力 = roll+mult ~ roll+mult*range，
//   力量修正 = bonus，乘數等級 = mult。
//
//   取 setup_axe(5, 25, 200, 10)：
//     axe(單手)      ：mult5 range25 bonus200 roll10 → 傷害 15-135、力修200%、乘數5
//                      (enchant_cap axe = 135 / 200 / 5 —— 三項皆「恰好」到頂)
//     twohanded axe  ：mult5 range50 bonus266 roll10 → 傷害 15-260、力修266%、乘數5
//                      (enchant_cap twohanded axe = 260 / 300 / 5 —— 傷害與乘數到頂，
//                       力修266<300 仍在上限內)
//   故無論玩家以單手或雙手持之，皆不逾 enchant_cap；強化師再強亦曰「已臻化境」。
//
// unique：set("unique",1) 標記其為獨一無二之神兵——enchant.c 神力(silver)祭煉
//   只毀「非 unique」之器，故此神兵祭煉永不損毀(雖已到頂、強化亦無可再進)。
//   此旗標純為「特殊/不毀」語意，與 driver 的 violate_unique()(clone 計數)無關。

#include <weapon.h>

inherit F_AXE;

void create()
{
	set_name("斬龍斧", ({ "zhanlong axe", "dragonslayer axe", "axe" }) );
	set_weight(13000);
	// 起手即頂住 enchant_cap：單手 15-135/200%/5、雙手 15-260/266%/5。
	setup_axe(5, 25, 200, 10);

	if( !clonep() ) {
		set("wield_as", ({ "axe", "twohanded axe" }) );
		set("unit", "把");
		// 神兵無價，然若變賣亦屬連城之珍。
		set("value", 120000);
		set("rigidity", 60);
		// 神兵標記：獨一無二、神力祭煉不毀(見 enchant.c)。
		set("unique", 1);
		set("long",
			"這便是傳說中淬自妖塔爐火、飲過龍血的神兵『斬龍斧』。斧身\n"
			"闊大如門板﹐通體呈一種沉鬱的玄黑﹐其上以古篆鐫著一條盤曲\n"
			"欲飛的螭龍﹐龍睛處嵌著兩點幽幽的赤芒﹐似有一縷未散的龍魂\n"
			"封鎮其中。斧刃開過鋒的地方泛著一線森冷的青光﹐傳聞當年鑄\n"
			"師以妖塔地火連煉九九八十一日﹐又取真龍之血淬之﹐方成此器\n"
			"——一斧揮出﹐挾風帶雷﹐裂石分金猶在其次﹐當真有斬蛟屠龍之\n"
			"威。執此斧者﹐縱不假強化之力﹐其鋒銳亦已臻於兵器之極﹐再\n"
			"難有寸進。\n");
		set("wield_msg",
			"$N雙手一振﹐將那柄玄黑的斬龍斧自背後抄起﹐斧上螭龍赤芒微閃﹐"
			"隱隱有龍吟之聲破空而出﹗\n");
		set("unwield_msg", "$N將斬龍斧收起﹐那縷龍吟之聲也隨之沉寂了下去。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
