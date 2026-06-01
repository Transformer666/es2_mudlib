// tab_ledger.c -- 斐縣非戰鬥支線「悅客來的散帳」的信物：
//                 悅客來客棧掌櫃託人代收賒帳的一本收帳冊。
//                 城裡幾家鋪子代客棧記過幾筆過路客商的賒帳﹐年深日久﹐
//                 客棧帳簿與各鋪的條子對不攏了。掌櫃央人持這本收帳冊﹐
//                 到三家鋪子各把賒帳的條子核對謄錄回來﹐再交還掌櫃對帳。
//
// 用途：純為支線送件信物（quest/feixian_tab），不堪戰、不能賣、不能偷。
//       由 d/feixian/npc/keeper.c 交付﹐核齊三家賒帳後交還 keeper 領賞。
//       核帳進度記在玩家身上的旗標﹐本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("收帳冊", ({ "tab ledger", "ledger", "shouzhangce" }) );
	set_weight(150);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("value", 1);
		set("long",
			"一本巴掌大小的青布面收帳冊﹐紙頁已被翻得起了毛邊﹐\n"
			"封皮上墨書「悅客來 散帳」四字。裡頭一行行記著過路客商\n"
			"在城裡幾家鋪子賒下的酒飯茶水﹐字跡卻與各鋪自記的條子對\n"
			"不大攏了。悅客來客棧的掌櫃託人持這本冊子﹐到錢記酒樓、\n"
			"清風茶行、雜貨鋪三處﹐各把代記的賒帳條子核對謄錄回來﹐\n"
			"再交還掌櫃對帳。\n"
			"你可以分頭去 ask 酒保 / 茶博士 / 雜貨郎 about 賒帳﹐\n"
			"三家都核過了﹐再回客棧 ask keeper about 散帳對帳\n"
			"（或 give tab ledger to keeper）。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
