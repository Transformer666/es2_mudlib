// hunter_necklace.c -- 赤魈森林獵人(d/chimei/npc/lieren.c)相贈的避邪信物：獸牙項鍊。
//
// 來歷（承接 canon：docs 05 L106「獵人@赤魈森林 給 necklace」）：
//   赤魈森林深處那位以打獵為生的老獵人，在這四鬼出沒的凶險山林裡討了半輩子生
//   活。他打村中老輩處得了一串避邪的獸牙項鍊——以森林裡最兇悍的野獸獠牙串成，
//   據說戴在身上，能教那四鬼的陰邪戾氣不敢近身。獵人見少俠是奔著卯天樹下四鬼
//   封印而來，便將這串護身的項鍊相贈，盼少俠多一分護持、平安了結那四鬼之患。
//
// 用法：戴(wear necklace)在頸上即可——純避邪/護身信物，略增一分精神(spi)。
//   設 no_sell：獵人一片心意，玩家留著護身，不宜變賣。

#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
	set_name("獸牙項鍊", ({ "fang necklace", "necklace" }) );
	set_weight(500);
	setup_neck_eq();

	if( !clonep() ) {
		set("wear_as", "neck_eq");
		set("unit", "串");
		set("value", 200);
		set("no_sell", 1);
		set("long",
			"一串以野獸獠牙串成的項鍊，牙身泛著陳年的微黃，根根磨得溫\n"
			"潤光滑，想是貼身戴了許多年了。串繩是揉得極韌的鹿皮筋，牙與\n"
			"牙之間還墜著幾枚刻了避邪古紋的獸骨小牌。赤魈森林那位老獵人\n"
			"說，這是村中老輩傳下的避邪之物，以山林裡最兇悍野獸的獠牙串\n"
			"成，戴在身上，能教那四鬼的陰邪戾氣不敢近身。入手隱隱透著一\n"
			"股山野的腥氣與一縷說不出的安定氣息。\n");
		set("wear_msg",
			"$N將那串獸牙項鍊掛上頸項，牙骨相擊，發出細碎而沉穩的輕響。\n");
		set("remove_msg", "$N將那串獸牙項鍊自頸間取下。\n");
		set("apply_armor/neck_eq/spi", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
