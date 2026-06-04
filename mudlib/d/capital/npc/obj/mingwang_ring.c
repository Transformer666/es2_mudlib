// mingwang_ring.c -- 支線「珠寶匠的冥王寶戒」的賞物：冥王寶戒(指環)。
//
// 來歷（承接 docs 05 L114「劉二爺 (Jeweller liu) @ 尚書府 → 給冥王寶戒」；
//   並接 docs 05 L126「凌筠語 換闇之魔戒 (str+5)」之同類魔戒量級）：
//   這枚冥王寶戒，是吏部尚書府那位深居簡出的珠寶匠劉二爺，窮半生之力琢成
//   的得意之作。戒身以一塊不知得自何處、入手沁骨生寒的玄黑寒鐵為胎，戒面
//   嵌著一顆瑩黑如墨、其中卻幽幽轉著一線血芒的「冥王石」——相傳是九幽冥府
//   地脈所結的死氣凝成。劉二爺說，這戒中所煉的，是一縷馭使陰煞、催發拙力
//   的冥王之力；戴之在指，但覺一股沉冥的力道自戒中漫入經脈，臨敵時筋骨之
//   力為之一壯。然這沉冥之力非有膽魄者不能駕馭，劉二爺琢成多年，一直不曾
//   尋得個堪受此物的人——直到那位在江湖上闖出了名號的少俠，尋上了尚書府。
//
// apply 鍵（worn finger_eq → 套用 apply_armor/finger_eq mapping，由 equip.c::apply
//   累加為 wearer 之 query_temp("apply/<key>")，feature/char/attribute.c 讀 apply/str
//   入 str 屬性；defense 由 combat.c 取用）：
//   doc 之效果              本檔 apply 鍵            取用處
//   ──────────             ──────────────         ──────────
//   馭陰煞、催拙力(力+)       "str"    : 3            attribute.c apply/str
//   沉冥護身(微禦)           "defense": 4            combat.c    apply/defense
//   （量級略遜凌筠語 str+5 之闇之魔戒——本物乃尚書府支線之賞、非主線終局魔戒。）
//
// finger_eq 之 setup_finger_eq() 為空殼(feature/armor/finger_eq.c)，效力全憑
//   apply_armor/finger_eq 一個 mapping，戴上時由 equip.c 套用。
//
// 注意：本戒為逐玩家 clone+move 交付的支線賞物(每位求戒者各一枚)，不 inherit
//   F_UNIQUE(鏡 ghost_ring/chuanling 之做法：僅以 set("unique",1) 作風味標記，
//   免多人持戒時的任何意外自毀)。可戴在指上(F_FINGER_EQ)。設 no_sell：珠寶匠
//   半生心血所琢，玩家須一路帶在身邊，不可變賣。ids 兼收中文 +英文。

#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
	set_name(HIR "冥王寶戒" NOR, ({ "mingwang ring", "hades ring", "ring",
		"冥王寶戒", "冥王", "寶戒", "戒" }) );
	set_weight(350);
	setup_finger_eq();

	if( !clonep() ) {
		set("wear_as", "finger_eq");
		set("unit", "枚");
		set("value", 1);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"一枚入手沁骨生寒、沉甸甸的玄黑寶戒。戒身以一塊不知得自何處\n"
			"的玄黑寒鐵為胎，鐵色幽暗如墨、其上卻隱隱浮著一層化不開的青\n"
			"煞。戒面正中嵌著一顆瑩黑如墨的『冥王石』，那墨色的石心裡，竟\n"
			"幽幽地轉著一線游絲也似的血芒，凝神久看，但覺一股說不出的沉冥\n"
			"之氣自石中漫出，隱隱與九幽地脈深處某種陰冷的存在遙相呼應。握\n"
			"之在手，掌心便覺一縷催筋發力的沉重力道自戒中沁入經脈——這便是\n"
			"尚書府那位珠寶匠劉二爺窮半生之力，自這冥王石中所煉的『冥王之\n"
			"力』了。戴之臨敵，筋骨之力為之一壯，更有一層沉冥煞氣護持周身。\n"
			"(wear ring 戴上)\n");
		set("wear_msg",
			"$N將那枚玄黑的冥王寶戒緩緩套上手指，戒面冥王石中那一線血芒驟然"
			"一亮，一縷沉冥的力道自戒中漫入$N經脈，筋骨之力似乎為之一壯！\n");
		set("remove_msg",
			"$N將那枚玄黑的冥王寶戒自指上褪下，戒中那縷催筋發力的沉冥之力方才"
			"稍斂，$N周身一鬆。\n");
		set("apply_armor/finger_eq", ([
			"str"     : 3,
			"defense" : 4,
		]) );
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
