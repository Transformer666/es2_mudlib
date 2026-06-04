// yang_charm.c -- 京畿支線「公孫志贈符」之賞：正陽符 (Scroll of yang)。
//
// 來歷（承 docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC 一覽」一列：
//   公孫志 @ 百花村紅燈客棧 → 書換正陽符 (Scroll of yang)。京畿域現以朱雀大街
//   「小樓客店」(d/capital/inn.c)為帝都唯一在營的客棧酒肆，這位以符籙渡人、雲遊
//   掛單的符師公孫志便寓居於此客舍）：
//   公孫志乃道門正陽一脈的符師，精研三符——正陽、先天、少陰，分主陽、和、陰三
//   氣。這一道『正陽符』，以辰砂硃筆書於黃麻紙上，內封一縷至剛至正的純陽真火；
//   佩之於身，符中那縷正陽之氣便緩緩漫入持者周身，驅陰除穢、暖體護心，臨敵之
//   際更能借這一點純陽燄壯其攻勢、固其精神。公孫志逢著肯虛心問道、與符有緣的
//   後生，便將這一道親筆書就的正陽符解贈，了一段符緣。
//
// 形制：佩於頸上的符籙(F_NECK_EQ，wear_as "neck_eq")——以「佩於身」的護身符籙呈現
//   最合「符」之意。佩之以 apply_armor/neck_eq 加成(僅用 driver 確實取用之 combat 鍵，
//   見 feature/char/combat.c 及 feature/armor/neck_eq.c：armor/attack/spi/per)——以「正
//   陽純火護心壯神」對應護體(armor)為主、佐以攻勢(attack)與精神(spi/per)，量級貼合一道
//   隨身符籙。設 no_sell：符師親書渡緣之信物，玩家自當留用，不宜變賣。
//
// 注意：逐玩家 clone+move 交付（每位與符有緣者各得一道），鏡 chuanling.c/sun_moon_relic.c
//   之做法：僅以 set("unique",1) 作風味標記，不 inherit F_UNIQUE，免多人佩符時意外自毀。

#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
	set_name(HIR "正陽符" NOR,
		({ "yang charm", "scroll of yang", "yang scroll", "charm",
		   "正陽符", "陽符", "符" }) );
	set_weight(100);
	setup_neck_eq();

	if( !clonep() ) {
		set("wear_as", "neck_eq");
		set("unit", "道");
		set("value", 1);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"一道以辰砂硃筆書於黃麻紙上的符籙。符紙已被摩挲得綿軟微\n"
			"黃，其上一筆一畫盡是盤虬詰曲、燄燄如火的硃紅符文，凝視\n"
			"之下，那一道道朱文竟似有縷縷溫煦的火氣在其間明滅流轉。\n"
			"湊近些，但覺一股至剛至正、暖而不灼的純陽之氣自符中緩緩\n"
			"漫出，拂在身上周身一暖、百穢俱清。據符師公孫志言道：此\n"
			"乃道門正陽一脈的『正陽符』，內封一縷純陽真火，佩之於身\n"
			"能驅陰除穢、暖體護心，臨敵時更可借這一點純陽燄壯攻勢、\n"
			"固精神。這便是江湖傳聞中道門三符之一的『正陽符』了。\n"
			"(佩於頸上：wear charm)\n");
		set("wear_msg",
			HIR "$N將那道燄燄如火的正陽符佩上頸間，符上盤虬的硃紅符文"
			"霎時一盛，一縷至剛至正的純陽之氣自符中漫出，沁入$N周身百"
			"骸，護住了心神。\n" NOR);
		set("remove_msg",
			"$N將那道正陽符自頸間取下，符中那縷溫煦的純陽之氣也隨之斂回符內。\n");
		// 護身符籙：護體(armor) + 攻勢(attack) + 精神(spi/per)——正陽純火護心壯神之賜。
		set("apply_armor/neck_eq", ([
			"armor"  : 8,
			"attack" : 4,
			"spi"    : 3,
			"per"    : 2,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
