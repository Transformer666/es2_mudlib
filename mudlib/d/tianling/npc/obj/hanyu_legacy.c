// hanyu_legacy.c -- 寒於氏遺澤，正史主線第十一章「最終決戰」終局信物獎勵。
//
// 來歷（承接 npc/wutiangui.c：侮天鬼伏誅、主線終點）：
//   五千年前，上古聖者「寒於氏」捨身入這天靈絕巔最深的幽窟，與那吞噬人界、自號『天可侮』
//   的至邪巨擘侮天鬼賭命相搏，終以一身道力斬下牠的元神之首、將牠封鎮於此——寒於氏亦因此道
//   消身殞，遂將自身最後一縷遺志、一脈遺澤，連同那頭至邪元神一同封入幽窟，世代守候著重啟
//   封印、續其聖戰的有緣人。少俠了結十三靈、再斬侮天鬼、再封其元神於永劫之際，這封了五千
//   年的「寒於氏遺澤」便自侮天鬼崩散的軀殼最深處墜落，落入這續成聖戰的有緣人手中——是為天
//   朝帝國正史主線的終局信物。
//
// 用法（束在腰間的終局聖物，擇 F_WAIST_EQ 一位——避與第九章日月神薛 F_NECK_EQ 之頸位相沖，
//   令少俠頸懸日月神薛、腰束寒於氏遺澤，兩終局聖物並佩）：
//   * 束(wear hanyu legacy)在腰間即可——寒於氏五千年聖戰的清正遺志護持周身，予適度終局加成
//     （護體 armor + 體魄/神思/根骨諸般屬性）。純護身終局信物，不另設機制。
//   * ids 兼收中文「寒於氏遺澤」/「遺澤」與英文 "hanyu legacy"/"legacy"。
//   設 no_sell：橫亙五千年聖戰所遺的終局信物，干係主線終局之證，玩家當隨身佩束，斷不可變賣
//     （鏡 sun_moon_relic.c/jade_girdle.c）。
//
// apply 鍵皆取 driver 確實會讀者（鏡 jade_girdle.c/sun_moon_relic.c）：
//   護體 armor（feature/char/combat.c apply/armor）：    18  ── 終局聖物，遜於頂裝、勝於常物
//   體魄 con（feature/attribute.c apply/con）：           4  ── 寒於氏聖戰所遺的清正之力壯體
//   神思 spi（feature/attribute.c apply/spi）：           4  ── 上古聖者遺志凝魂、定神
//   臂力 str（feature/attribute.c apply/str）：           3  ── 一脈遺澤所附的搏天之力
//   守勢 defense（feature/char/combat.c apply/defense）： 8  ── 五千年封印之力的護體餘蔭
//   （量級取「終局信物」之譜，整體略勝第九章日月神薛 neck_eq armor12/spi3/per2/con2——主線
//     終點之賞，理當為通關之證的最厚一件護身物。）

#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
	set_name(HIY "寒於氏遺澤" NOR,
		({ "hanyu legacy", "legacy", "寒於氏遺澤", "遺澤" }) );
	set_weight(900);
	setup_waist_eq();

	if( !clonep() ) {
		set("wear_as", "waist_eq");
		set("unit", "脈");
		set("value", 1);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			HIY
			"一脈封了五千年、猶自流轉著一縷清正之光的遺物。它既非金\n"
			"石、亦非玉帛，而似一縷上古聖者捨身相搏所凝的浩然遺志所化——\n"
			"束之在腰，但覺一股溫厚而磅礡的清正之氣自命門氣海緩緩漫開，\n"
			"周身百骸俱為之一暖、一壯、一定。這便是五千年前那位捨身入幽\n"
			"窟、與侮天鬼賭命相搏的上古聖者『寒於氏』，斬下那至邪元神之\n"
			"首、將其封鎮於此之際，連同自身最後一縷遺志、一脈遺澤同封於\n"
			"幽窟深處的終局信物了。寒於氏道消身殞，五千年來這一脈遺澤便\n"
			"在那至邪元神的封印最深處，靜靜守候著重啟封印、續其聖戰的有\n"
			"緣人。如今封解魔滅，這橫亙五千年的聖戰遺志，便傳到了續成此\n"
			"志的少俠身上——它既是寒於氏未竟之志終得告慰的見證，更是少俠\n"
			"了結這天朝帝國億兆生靈劫難、行至主線終點的終局之證。\n"
			NOR);
		set("wear_msg",
			HIY "$N將那一脈流轉著清正之光的寒於氏遺澤束上腰間——遺澤上五千年"
			"未散的浩然之氣霎時一盛，灑下一片溫厚而磅礡的清光，周身百骸俱為之一"
			"暖、一壯。\n" NOR);
		set("unequip_msg",
			"$N將寒於氏遺澤自腰間解下，那一縷護體的清正之氣方才稍稍斂去。\n");
		// 終局信物：護體(armor) + 體魄(con) + 神思(spi) + 臂力(str) + 守勢(defense)。
		set("apply_armor/waist_eq", ([
			"armor"   : 18,
			"con"     : 4,
			"spi"     : 4,
			"str"     : 3,
			"defense" : 8,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
