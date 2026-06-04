// xuanmang.c -- 風城劍甲門傳人陳學亮所授的利劍：炫芒(sword)。
//
//   (canon：docs 01-世界觀與劇情/05-主線任務與NPC.md L119
//    「陳學亮 @ 風城 → 開光炫芒（需火神之眼）；劍甲門傳人，授強化之術」)
//
// 故事背景：
//   炫芒乃風城劍甲門一脈相傳的利劍——「劍甲」者，以劍為甲、以攻代守之謂也。
//   此劍劍身狹長，劍脊上密布著一道道宛若流光的細紋，臨陣一展，劍光大盛、
//   炫人耳目，故名「炫芒」。它本是一柄趁手的中階利器，劍甲門傳人陳學亮見有
//   緣的少俠，便授以此劍，更可為持劍而又得火神之證的少俠施那「開光強化之
//   術」，將劍中那一縷沉睡的剛烈劍意徹底喚醒（見 chenxueliang.c）。
//
// 與 d/caobang 之「旋芒」(xuanmang_sword.c, id "xuanmang") 截然兩物——彼乃漕幫
//   信物『旋芒』(旋/水上旋光)、此乃劍甲門『炫芒』(炫/炫目劍光)。為免羅馬拼音
//   "xuanmang" 與漕幫旋芒之 id 相撞，本劍刻意不取 id "xuanmang"，改取
//   id "xuanmang blade"/"炫芒"——present/id 為精確比對(feature/name.c::id 之
//   member_array)，如此二劍各認各的、互不相涉。
//
// 用法：持(wield xuanmang blade / wield 炫芒 / wield sword)於手即可禦敵。
//   設 no_sell：劍甲門相授之信物兵刃，玩家當留著自用、開光，不宜變賣。
//
// 設計（鏡 d/caobang/npc/obj/xuanmang_sword.c 之 setup_sword 四參式，量級相當）：
//   未開光的炫芒定位在「趁手中階利器」，故 setup_sword(3, 16, 70, 5)——
//   單手 乘數3 range16 bonus70 roll5；經陳學亮開光強化後，由 chenxueliang.c
//   逕對 clone 重設為 setup_sword(5, 16, 130, 8)(皆在 cmds/std/enchant.c::
//   enchant_cap 之 sword(110/150/5)、twohanded sword(210/225/5) 上限之內)。

#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name(HIC "炫芒" NOR, ({ "xuanmang blade", "炫芒", "dazzling blade", "sword" }) );
	set_weight(6600);
	setup_sword(3, 16, 70, 5);

	if( !clonep() ) {
		set("wield_as", ({ "sword", "twohanded sword" }) );
		set("unit", "把");
		set("value", 1);
		set("no_sell", 1);
		set("rigidity", 48);
		set("long",
			"這柄喚作『炫芒』的長劍，是風城劍甲門一脈相傳的利器。劍身狹\n"
			"長筆直、青白瑩瑩，劍脊之上密布著一道道宛若流光的細紋，握在\n"
			"手中入手沉穩。劍甲門講究以劍為甲、以攻代守，這炫芒一經抖開，\n"
			"劍光便如潑灑開來的一蓬碎銀，炫人耳目、奪人神魄，『炫芒』之\n"
			"名便由此而來。只是劍中似還沉睡著一縷未醒的剛烈劍意——劍甲門\n"
			"傳人說，唯有借那司南方離火的火神之力為引，將這劍意徹底『開\n"
			"光』喚醒，這柄炫芒方能脫胎換骨、鋒芒大盛。\n");
		set("wield_msg",
			HIC "$N腕底一沉，那柄炫芒已亮在手中，劍身青白光暈一閃，"
			"劍光如潑灑的碎銀般炫人耳目！\n" NOR);
		set("unwield_msg",
			"$N收劍歸鞘，那一身炫目的劍光方才斂去。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
