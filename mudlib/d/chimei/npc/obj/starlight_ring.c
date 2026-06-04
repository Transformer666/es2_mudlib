// starlight_ring.c -- 正史主線第五章「四鬼任務」的終局聖物兼交差信物：星光環。
//
// 來歷（承接 canon 主線樹 docs 05 L50「消滅後得星光 ring」、L189「insert seal of
//   fire/storm/water/thunder 把四片 seal 插入星光 ring」）：
//   山林川原四鬼——赤魈、青蛛、濁魚、旱魃——盡數誅於卯天樹下之際，那座鎮鬼三百年
//   的封印徹底崩解，自封印最深處、四鬼元神湮滅所凝的一點清光中，誕出這一枚通體
//   流轉著星河微芒的奇環。它是四鬼之患終獲了結的鐵證，更是日後了結十三靈、再戰
//   侮天鬼的終局之鑰——環上天然生著四道空槽，正待四神(火/天龍/雷/風)之 seal 嵌
//   入；湊全四片完整 seal、插入此環，方能行那技能重置(reset)、開啟十三靈最終任務。
//
// 用法：
//   * 持此環回漕幫禮堂(/d/caobang/hall.c)交與江隕，ask jiangyun about 四鬼，繳交
//     領賞、為四鬼任務作結（亦可 wear ring 戴在指上；交差走 ask-path 為主）。
//   * 此即 docs 主線樹終局所載、四神/十三靈 arc 將需的「星光 ring」——故 ids 兼收
//     英文 "starlight ring"/"ring" 與中文「星光」。
//   設 no_sell：終局聖物干係十三靈最終任務，玩家須一路帶在身邊，斷不可變賣。
//
// 注意：本環為逐玩家掉落/clone 交付的終局聖物，不 inherit F_UNIQUE(鏡 chuanling/
//   ghost_ring 之做法：僅以 set("unique",1) 作風味標記，免多人持環時的任何意外自
//   毀)。可戴在指上(F_FINGER_EQ)。四神 seal 之嵌入(insert seal …)屬後續 arc，本檔
//   僅落實終局聖物本身，不另設嵌槽機制。

#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
	set_name(HIW "星光環" NOR, ({ "starlight ring", "starlight", "ring", "星光" }) );
	set_weight(200);
	setup_finger_eq();

	if( !clonep() ) {
		set("wear_as", "finger_eq");
		set("unit", "枚");
		set("value", 1);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"一枚輕靈剔透、彷彿不染半分塵滓的奇環。環身既非金石、亦非\n"
			"玉璧，而似一縷凝而不散的清光所鑄——通體流轉著一片細碎的星\n"
			"河微芒，明滅閃爍，宛若將一整片夜空的繁星收攏進了這方寸之\n"
			"間。這是山林川原四鬼盡數湮滅於卯天樹下封印之際，自那崩解的\n"
			"亙古封印最深處、四鬼元神所化的一點至清之光中誕出的聖物。凝\n"
			"神細看，環身之上天然生著四道淺淺的空槽，槽中清芒流轉不定，\n"
			"似在無聲地等待著甚麼——傳聞日後當集齊火、天龍、雷、風四方神\n"
			"祇之 seal，一一嵌入此環，方能成就那了結十三靈、再戰侮天鬼的\n"
			"終局大願。握之在手，但覺一股溫煦澄澈的星輝自掌心緩緩漫開，\n"
			"周身百骸俱為之一清。\n");
		set("wear_msg",
			"$N將那枚流轉著星河微芒的奇環套上手指，環上星輝霎時一盛，灑下一片清光。\n");
		set("remove_msg",
			"$N將那枚星光環自指上褪下，環上那一片流轉的星河微芒方才稍斂。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
