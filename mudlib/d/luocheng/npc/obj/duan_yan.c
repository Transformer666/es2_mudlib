// duan_yan.c -- 羅城非戰鬥支線「羅城客棧的尋硯」的尋物信物：
//               一方端石名硯，是一位匆匆離店的候缺選官遺落在羅城客棧的舊物。
//               店小二掃堂時把它連著雜物一併收進了櫃格裡，擱久了竟忘了原主。
//               那選官如今正在隔鄰的聽濤茶樓對著冷茶出神——這方硯正是他的心愛。
//               玩家自店小二處取回此硯，送還聽濤茶樓的候缺選官。
//
// 用途：純為支線送件信物（quest/luocheng_yan），不堪戰、不能賣、不能偷。
//       由 d/luocheng/npc/barkeep.c 在玩家接了任務後交付﹐送還
//       d/luocheng/npc/tea_guest.c。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("端硯", ({ "duan yan", "inkstone", "duanyan" }) );
	set_weight(400);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "方");
		set("value", 1);
		set("long",
			"一方巴掌大小的端石名硯﹐石質溫潤細膩﹐呵氣便能研墨。硯\n"
			"堂磨得微微下凹﹐顯是日日臨池的舊物﹔硯背刻著一方小小的「\n"
			"硯田自耕」閒章與一行蠅頭小楷的詩句﹐邊角還留著主人摩挲經\n"
			"年的包漿。這原是一位候缺選官隨身的心愛之物﹐前些日子匆匆\n"
			"離店時遺落在羅城客棧﹐教店小二掃堂時連著雜物收進了櫃格﹐\n"
			"擱久了竟忘了原主。\n"
			"該把它送還聽濤茶樓那位候缺選官﹕ask tea guest about 端硯﹐或 give 端硯 to tea guest。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
