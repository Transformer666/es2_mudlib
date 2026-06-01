// brush_case.c -- 文國縣非戰鬥支線「天風筆會」的送件信物（空匣／配好的筆）：
//                 一隻細木製的扁長筆匣，匣中安著一管制筆作坊新紮的「天風狼毫」。
//                 老筆匠見玩家受天風客棧掌櫃之託來備文房禮，便揀一管頂好的新筆
//                 安進這空匣，交與玩家，囑其到松煙廣場東側的松煙墨坊尋墨工，配一
//                 錠相稱的好墨進匣，湊成一副完整的文房。
//
// 用途：純為支線送件信物（quest/wenguo_brush），不堪戰、不能賣、不能偷。
//       由 d/wenguo/npc/brushmaker.c 在玩家接了任務後交付﹐持往
//       d/wenguo/npc/inkmaker.c 配墨（配墨時此匣銷除、改交配齊的 writing_case）。
//       送件進度記在玩家身上的旗標﹐本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("天風筆匣", ({ "brush case", "empty case", "tianfeng case" }) );
	set_weight(300);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "隻");
		set("value", 1);
		set("long",
			"一隻細木製的扁長筆匣﹐匣蓋上烙著小小的「天風」二字﹐\n"
			"揭開來﹐裡頭以軟綢襯著一管制筆作坊新紮的天風狼毫﹐筆鋒\n"
			"尖圓飽滿﹐挑不出一根岔毫。只是這副文房還缺一錠相稱的好\n"
			"墨﹐筆好墨不好﹐到底成不了一副像樣的禮。\n"
			"該拿它到松煙墨坊尋墨工配墨﹕ask inkmaker about 文房﹐或 give brush case to inkmaker。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
