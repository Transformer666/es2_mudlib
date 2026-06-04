// dark_ring.c -- 暗市異人凌筠語以重金私換的魔道至寶：闇之魔戒。
//
// 來歷（承接 canon：docs 05 L126「凌筠語 — 換闇之魔戒 (str+5)」）：
//   凌筠語是個來路不明、掛單於朱雀大街小樓客店的暗市異人。她隨身揣著一枚自
//   魔道一脈流出的古戒——『闇之魔戒』，戒身吞光噬影，內蘊一縷至剛至烈的魔
//   力，戴之能教人筋骨暴張、氣力倍增（str+5）。然這魔力反噬亦烈，尋常人駕馭
//   不住，故她從不白送，只肯與識貨、且出得起重金的江湖客私下交易——銀貨兩訖，
//   各取所需。
//
// 機制（指環類 F_FINGER_EQ，戴於指上由 equip.c 套用 apply）：
//   apply_armor/finger_eq 之 mapping ([ "str": 5 ])——戴上 finger_eq 一格時，
//   equip.c::wear() 取此 mapping 呼 apply()，於佩戴者 set_temp("apply/str", +5)，
//   feature/attribute.c::query_attr("str") 即回 base+5（褪戒時 unapply 自動扣回）。
//   忠實落實 docs 之「str+5 指環」。
//
//   設 no_sell：魔戒乃凌筠語以重金私換的至寶，玩家自當留用，不宜變賣。
//   逐玩家 clone+move 交付（每位成交的江湖客各得一枚），鏡 chuanling.c/ghost_ring.c
//   之做法：僅 set("unique",1) 作風味標記，不 inherit F_UNIQUE，免多人持戒時意外自毀。

#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
	set_name(HIR "闇之魔戒" NOR, ({ "dark ring", "demon ring", "ring", "闇之魔戒", "魔戒" }) );
	set_weight(400);
	setup_finger_eq();

	if( !clonep() ) {
		set("wear_as", "finger_eq");
		set("unit", "枚");
		set("value", 1);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"一枚通體烏黑、入手冰沉的古戒。戒身不知是何材質鑄成﹐凝視\n"
			"之下竟似有縷縷幽暗的光影在其上吞吐流轉﹐光照其上﹐光輝亦被\n"
			"它無聲地噬去大半。戒面盤踞著一頭詰屈猙獰、似龍非龍的魔物浮\n"
			"雕﹐雙目嵌著兩點暗紅的細芒﹐隱隱透出一股至剛至烈、教人心頭\n"
			"發悸的魔力。握之在手﹐但覺一股蠻橫的氣力自戒中奔湧而出﹐直\n"
			"灌四肢百骸﹐筋骨為之暴張——凌筠語言道﹕此乃魔道一脈流出的『\n"
			"闇之魔戒』﹐戴之能教人氣力倍增﹐然其魔力反噬亦烈﹐非有定力者\n"
			"駕馭不住。(戴於指上﹕wear ring)\n");
		set("wear_msg",
			"$N將那枚烏黑的闇之魔戒緩緩套上手指﹐戒面魔物的暗紅雙目驟然一亮﹐"
			"一股蠻橫的魔力自戒中奔湧而出﹐灌入$N四肢百骸﹗\n");
		set("remove_msg",
			"$N將那枚闇之魔戒自指上褪下﹐戒中那股奔湧的魔力與暴張的筋骨方才稍斂。\n");
		// docs：str+5 指環。戴上 finger_eq 一格時 equip.c 套用此 apply。
		set("apply_armor/finger_eq", ([
			"str" : 5,
		]) );
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
