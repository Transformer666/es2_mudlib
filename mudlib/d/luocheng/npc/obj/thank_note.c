// thank_note.c -- 羅城非戰鬥支線「羅城客棧的尋硯」的回執信物：
//                 候缺選官收回失而復得的端硯後﹐感念之餘﹐取自己的名帖在背面
//                 草草寫了幾句謝辭、託玩家轉交羅城客棧掌櫃的一張「謝帖」。
//                 掌櫃見了這帖﹐便知硯已物歸原主﹐方好給玩家酬謝。
//
// 用途：純為支線回報信物（quest/luocheng_yan），不堪戰、不能賣、不能偷。
//       由 d/luocheng/npc/tea_guest.c 在玩家送還端硯後交付﹐交還
//       d/luocheng/npc/keeper.c 領賞。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("謝帖", ({ "thank note", "note", "xietie" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "張");
		set("value", 1);
		set("long",
			"一張裁得方正的灑金名帖﹐正面工楷印著那候缺選官的姓名籍\n"
			"貫﹐背面卻是一行臨時草就的行書﹐墨色猶新﹕「失硯復得﹐感\n"
			"君高義﹐謹此申謝﹐並煩轉達貴棧掌櫃﹐叨擾多日﹐後會有期。」\n"
			"這是那選官收回端硯後﹐感念之餘託你轉交羅城客棧掌櫃的謝帖\n"
			"——掌櫃見了這帖﹐便知那方硯已物歸原主了。\n"
			"該把它交還羅城客棧的掌櫃﹕ask keeper about 端硯﹐或 give 謝帖 to keeper。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
