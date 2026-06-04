// quake_axe.c -- 正史主線第八章「地靈任務」地靈伏誅所掉的神兵：悍地斧(twohanded axe)。
//
// 來歷（承接 canon 主線樹 docs 05 L63「地靈任務 → 悍地斧(twohanded axe) + heart」；江隕
//   第八章交差所伏「登地氣塔頂可得悍地斧」之 lead）：
//   地氣塔頂那司一方地氣的地靈，掌一柄通體流轉著沉雄土光的巨斧；少俠將地靈降伏，這柄
//   『悍地斧』便隨那枚地靈之心一同自牠遺蛻中落下。斧身闊大沉雄，挾地靈一縷厚土之力，
//   傳聞一斧揮落，地動山搖，裂土崩石，宛若大地之怒盡發於此刃。
//
// 用法：可佩可揮的強力雙手巨斧(F_AXE)——
//   * setup_axe(x,y,z,r) 依 feature/weapon/axe.c 展三式：axe(單手)=init_damage(x,y,z,r)、
//     secondhand axe=(x,y/2,z,r)、twohanded axe=(x,y*2,z*4/3,r)。
//   * 取 setup_axe(5, 24, 190, 10)（稍遜頂裝斬龍斧 setup_axe(5,25,200,10) 之極，仍在
//     enchant_cap 之內）：
//       axe(單手)     ：15-129、力修190%、乘數5、roll10
//       twohanded axe ：15-250、力修253%、乘數5、roll10（皆未逾 enchant_cap）
//   雙手主戰之強力巨斧，不另設任何特殊戰鬥引擎(鏡 zhanlong_axe/chuanling 做法)。
//   設 unique + no_sell：地靈所遺之神兵、干係主線信物一脈，玩家須帶在身邊，斷不可變賣。
//
// 注意：本斧為地靈 die() 逐玩家掉落（每位 diling-slayer 各掉一柄），不 inherit F_UNIQUE
//   （鏡 zhanlong_axe：僅 set("unique",1) 作風味標記，免多人持斧時的任何意外自毀）。

#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
	set_name(HIY "悍地斧" NOR, ({ "quake axe", "earthquake axe", "axe" }) );
	set_weight(12800);
	// 稍遜頂裝斬龍斧之極，仍在 enchant_cap 內：雙手 15-250、力修253%、乘數5、roll10。
	setup_axe(5, 24, 190, 10);

	if( !clonep() ) {
		set("wield_as", ({ "axe", "twohanded axe" }) );
		set("unit", "柄");
		set("value", 1);
		set("rigidity", 60);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"這便是地氣塔頂那司一方地氣的地靈所遺的神兵『悍地斧』了。\n"
			"斧身闊大沉雄如門板，通體呈一種厚重的黃褐，其上隱隱凝著一層\n"
			"流轉的沉雄土光，斧刃開鋒處泛著一線渾濁的黃芒，彷彿封著一縷\n"
			"自地靈而來的厚土之力。握斧在手，沉甸甸地直墜，掌心便覺一股\n"
			"磅礡而沉雄的地氣自斧中緩緩漫出。傳聞執此斧揮落，地動山搖，\n"
			"裂土崩石，宛若大地之怒盡發於這一刃——是以名之曰『悍地斧』。\n"
			"斧身那一縷沉雄的土光，與那枚自地靈所凝的地靈之心同源。\n");
		set("wield_msg",
			"$N雙手一振，將那柄厚重的悍地斧自背後抄起，斧上黃芒微閃，"
			"隱隱有大地震顫般的沉雷自斧中滾出！\n");
		set("unwield_msg",
			"$N將悍地斧收起，那一縷自斧中漫出的沉雄地氣方才稍斂。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
