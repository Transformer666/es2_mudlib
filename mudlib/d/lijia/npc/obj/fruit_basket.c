// fruit_basket.c -- 李家村非戰鬥支線「李家祭祖供果」的送件信物（一籃新摘的供祖鮮果）：
//                   一隻竹編的小籃﹐盛著看園果農新摘、揀過的形正色勻的鮮果。果農見玩家受
//                   李家族長之託來備祭祖供品﹐便就園裡揀了一籃最體面的鮮果交與玩家﹐
//                   囑其持往村南魚塘尋漁戶配齊供盤。
//
// 用途：純為支線送件信物（quest/lijia_offer），不堪戰、不能賣、不能偷。
//       由 d/lijia/npc/picker.c 在玩家接了任務後交付﹐持往 d/lijia/npc/fisher.c
//       配供盤（配齊時此籃銷除、改交配好的 offer_tray）。送件進度記在玩家身上的
//       旗標﹐本物件只作憑證﹐自身不記狀態。
//
// id 註記：本籃的查找專用獨有 id「lijiagongguo」（present/destruct 一律用它）﹐
//          另掛通名 id「fruit basket」「basket」便於玩家 give／辨識。獨有 id 不與
//          任何 /obj/food 既有物件相混﹐確保 present()/destruct() 只認本任務信物。

inherit ITEM;

void create()
{
	set_name("供果籃", ({ "lijiagongguo", "fruit basket", "basket" }) );
	set_weight(800);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "籃");
		set("value", 1);
		set("long",
			"一隻竹篾編的小提籃﹐籃裡鋪著一層乾淨的桐葉﹐盛著看園\n"
			"果農新摘、細細揀過的鮮果——紅桃、青李、黃梨、紫棗﹐顆顆\n"
			"形正色勻、不疤不蟲﹐是專為祠堂祭祖供奉先祖揀的體面果子﹐\n"
			"透著一園鮮果的清香。\n"
			"該拿它到村南魚塘尋漁戶配齊供盤﹕ask fisher about 鯉魚﹐或 give fruit basket to fisher。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
