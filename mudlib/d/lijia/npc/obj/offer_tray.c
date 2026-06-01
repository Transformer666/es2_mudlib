// offer_tray.c -- 李家村非戰鬥支線「李家祭祖供果」的回報信物（配齊的祭祖供盤）：
//                 一方紅漆木盤﹐三牲鮮果配得齊整。漁戶把果農交與玩家的供果籃接過﹐
//                 又自塘裡撈了一尾頂精神的活鯉、添上自家的牲禮﹐拿果子一併在紅漆木盤
//                 上擺得齊整體面﹐交還玩家﹐囑其速速持回李氏祠堂交與族長祭祖。
//
// 用途：純為支線回報信物（quest/lijia_offer），不堪戰、不能賣、不能偷。
//       由 d/lijia/npc/fisher.c 在玩家持供果籃來配供時交付（同時銷除供果籃）﹐
//       交還 d/lijia/npc/elder.c 領賞。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。
//
// id 註記：本盤的查找專用獨有 id「lijiagongpan」（present/destruct 一律用它）﹐
//          另掛通名 id「offer tray」「tray」便於玩家 give／辨識。獨有 id 不與任何
//          /obj/food 既有物件相混﹐確保 present()/destruct() 只認本任務信物。

inherit ITEM;

void create()
{
	set_name("祭祖供盤", ({ "lijiagongpan", "offer tray", "tray" }) );
	set_weight(1500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "盤");
		set("value", 1);
		set("long",
			"一方擦得鋥亮的紅漆木盤﹐祭祖的供品在上頭擺得齊整體\n"
			"面﹕當中一尾自魚塘現撈、紅鬚紅尾的活鯉﹐取個鯉躍龍門的\n"
			"彩頭﹔兩旁配著漁戶備的牲禮﹐四圍綴著果園新摘的紅桃青李、\n"
			"黃梨紫棗。三牲鮮果俱全﹐正是李氏宗祠祭奠歷代先祖的一盤體\n"
			"面供品。\n"
			"該把它持回李氏祠堂交與族長供奉先祖﹕ask elder about 祭祖﹐或 give offer tray to elder。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
