// gua_coin.c -- 風城非戰鬥支線「失算的籤筒」的信物：
//               神算子賴以卜算的龜甲卦錢，前些日子在廣場朔風裡失落了一枚。
//               一個拾荒的小乞兒在市集邊撿著了它﹐拿去跟小吃攤的婦人換了個
//               奶餅充饑﹔攤販便把這枚亮晶晶的舊錢留在了攤上。玩家循著差役、
//               攤販兩處的線索﹐自攤販手裡尋回這枚卦錢﹐交還神算子。
//
// 用途：純為支線送件信物（quest/fengcheng_gua），不堪戰、不能賣、不能偷。
//       由 d/fengcheng/npc/peddler.c 在玩家問著線索後交付﹐交還
//       d/fengcheng/npc/fortuneteller.c 領賞。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("龜甲卦錢", ({ "gua coin", "tortoise coin", "guaqian" }) );
	set_weight(20);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "枚");
		set("value", 1);
		set("long",
			"一枚古舊的卦錢﹐錢身是用一小片打磨溫潤的龜甲嵌著一圈\n"
			"黃銅鑄成的﹐正面鑄著古拙的卦象紋﹐背面一個篆文的「卜」\n"
			"字﹐被經年的摩挲盤得油亮。這原是風城那位神算子卜算窮通\n"
			"禍福的隨身卦錢之一﹐前些日子在廣場的朔風裡失落了﹐輾轉\n"
			"落到市集小吃攤上。少了這枚卦錢湊不成一副﹐那神算子便掐\n"
			"算不靈了。\n"
			"該把它交還卦攤的神算子﹕ask fortuneteller about 龜甲\n"
			"（或 give gua coin to fortuneteller）。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
