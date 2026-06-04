// fate_dagger.c -- 正史主線第八章「天靈任務」天靈伏誅所掉的神兵：天命刃(dagger of fate)。
//
// 來歷（承接 canon 主線樹 docs 05 L60「天靈任務 → 天命刃(dagger of fate) + eye」；江隕
//   第八章交差所伏「往赤魈村許願池可解天命刃」之 lead）：
//   赤魈村後許願池上那司一方天命的天靈，掌一柄通體流轉著澄澈天光的短刃；少俠將天靈降
//   伏，這柄『天命刃』便隨那枚天靈之眼一同自牠遺蛻中落下。刃身雖短，卻挾天靈一縷司命
//   之力，鋒銳迅捷，傳聞執之揮斫，快逾人能見，一刃落處，宛若天命已定。
//
// 用法：可佩可揮的強力短刃(F_DAGGER)——
//   * setup_dagger(x,y,z,r) 依 feature/weapon/dagger.c：dagger(單手) + secondhand dagger
//     兩式皆 init_damage(x,y,z,r)。dagger 各參上限為 mult3/range20/bonus100/roll15。
//   * 取 setup_dagger(3, 20, 100, 15)：頂住 dagger 各欄上限——傷害 18-78、力修100%、乘數
//     3、roll15。短刃中至強，然不另設任何特殊戰鬥引擎(鏡 chuanling/zhanlong_axe 做法)。
//   設 unique + no_sell：天靈所遺之神兵、干係主線信物一脈，玩家須帶在身邊，斷不可變賣。
//
// 注意：本刃為天靈 die() 逐玩家掉落（每位 tianling-slayer 各掉一柄），不 inherit F_UNIQUE
//   （鏡 chuanling/zhanlong_axe：僅 set("unique",1) 作風味標記，免多人持刃時的任何意外
//   自毀）。

#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
	set_name(HIC "天命刃" NOR, ({ "fate dagger", "dagger of fate", "dagger" }) );
	set_weight(2600);
	// 頂住 dagger enchant 上限：單手 18-78、力修100%、乘數3、roll15。短刃中至強。
	setup_dagger(3, 20, 100, 15);

	if( !clonep() ) {
		set("wield_as", ({ "dagger", "secondhand dagger" }) );
		set("unit", "柄");
		set("value", 1);
		set("rigidity", 50);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"這便是赤魈村許願池上那司一方天命的天靈所遺的神兵『天命\n"
			"刃』了。刃身狹短，通體流轉著一層澄澈的天光，青中泛白，刃\n"
			"鋒薄如蟬翼，握之在手卻覺輕若無物，彷彿挾著一縷自天靈而來\n"
			"的司命之力。傳聞執此刃揮斫，快逾人目所能見，一刃落處，宛\n"
			"若天命已定、再無轉圜——是以名之曰『天命刃』。刃脊之上隱隱\n"
			"有星河般的微芒明滅流轉，與那枚自天靈所凝的天靈之眼同源。\n");
		set("wield_msg",
			"$N腕間一抖，青光一閃，那柄通體流轉著澄澈天光的短刃『天命刃』"
			"已倒握在手，刃鋒薄如蟬翼，星河般的微芒幽幽流轉！\n");
		set("unwield_msg",
			"$N將天命刃緩緩收起，那一縷自刃中漫出的司命天光方才稍斂。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
