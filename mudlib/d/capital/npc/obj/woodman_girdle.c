// woodman_girdle.c -- 釘靈古墓旁老樵夫阿拓所贈的腰帶：縛柴麻絛帶 (woodman girdle)。
//
// 來歷（承 docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC」表 L107：
//   「阿拓 @ 釘靈古墓附近樵夫 → 給 girdle(腰帶)」）：
//   阿拓乃終年在釘靈古墓外那片老樹林裡伐薪燒炭的老樵夫。他這條腰帶﹐原是
//   尋常縛柴的粗麻絛子﹐卻教他一捆一捆地縛了三十年柴﹐又日日在古墓外那股
//   森森地氣裡浸著——絛子早讓汗水與山霧浸得油亮如皮﹐裡頭一條條的麻筋也練
//   得韌逾牛皮﹐束在腰間竟比尋常皮帶還禁得住勒。阿拓伐了大半輩子柴﹐膝下
//   無兒﹐逢著肯虛心向他問起這營生、又肯陪他說兩句話的後生﹐一高興﹐便把
//   這條伴了他半世、束慣了腰桿的縛柴麻絛帶解下相贈﹐圖個有人接著用。
//
// 機制（waist_eq 護腰﹐apply 鍵皆取 driver 確實會讀者﹐鏡 jade_girdle.c）：
//   doc 之效果         本檔 apply 鍵           取用處
//   ──────────        ──────────────         ──────────
//   縛腰束氣（體魄）     "con"    : 1           feature/attribute.c apply/con
//   護腰當身（護甲）     "armor"  : 2           feature/char/combat.c apply/armor
//   勒緊不脫（守勢）     "defense": 2           feature/char/combat.c apply/defense
//   （量級遠遜於玄天教法王所贈的「金絲翡翠帶」(jade_girdle.c：con/str+2、armor4、
//     defense6)——彼乃教中以物易物之佳物﹐此乃老樵夫隨手相贈的粗麻絛帶﹐取「贈與
//     入門腰帶」之最低譜﹐聊勝於無而已。元素/內功類 apply 鍵本 mudlib 版本未實作﹐
//     從略以免無效鍵。）
//   waist_eq 之 setup_waist_eq() 為空殼(feature/armor/waist_eq.c)﹐效力全憑
//   apply_armor/waist_eq 一個 mapping﹐束戴時由 equip.c::wear 套用。
//
// 設 no_sell：老樵夫念著情分相贈的隨身舊物﹐玩家當束在腰間自用﹐不好變賣（鏡
//   jade_girdle.c / ghost_ring.c）。ids 兼收中文與 english（girdle 同 jade_girdle
//   共用無妨——present()/get 以較專名者優先﹐woodman girdle / 麻絛帶 為其專名）。

#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
	set_name(HIY "縛柴麻絛帶" NOR,
		({ "woodman girdle", "hemp girdle", "girdle",
		   "縛柴麻絛帶", "麻絛帶", "麻帶", "腰帶" }) );
	set_weight(500);
	setup_waist_eq();

	if( !clonep() ) {
		set("wear_as", "waist_eq");
		set("unit", "條");
		set("value", 1);
		set("no_sell", 1);
		set("long",
			"這便是老樵夫阿拓束了半世腰桿的『縛柴麻絛帶』了。原不過是\n"
			"一條尋常縛柴用的粗麻絛子﹐卻教他一捆一捆地縛了三十年的柴\n"
			"﹐又日日在釘靈古墓外那股森森的地氣裡浸著——絛身早讓汗水同\n"
			"山霧浸得油亮如皮﹐黝黑發光﹐裡頭一條條的麻筋也練得韌逾牛\n"
			"皮﹐尋常刀也割它不斷。束在腰間沉沉勒緊﹐恰恰護住腰腹一線\n"
			"﹐使人腰桿一挺﹐氣力也彷彿憑空長了三分。帶上猶帶著一縷淡\n"
			"淡的松煙與柴薪的氣味﹐是老樵夫大半輩子伐薪燒炭的營生﹐都\n"
			"縛進這條舊絛帶裡了。\n");
		set("wear_msg",
			"$N將那條黝黑油亮的縛柴麻絛帶在腰間繞了兩匝﹐沉沉勒緊﹐"
			"腰桿登時一挺﹐氣力彷彿也長了三分。\n");
		set("unequip_msg",
			"$N將腰間那條縛柴麻絛帶解下﹐挺直的腰桿這才鬆泛下來。\n");
		set("apply_armor/waist_eq", ([
			"con"     : 1,
			"armor"   : 2,
			"defense" : 2,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
