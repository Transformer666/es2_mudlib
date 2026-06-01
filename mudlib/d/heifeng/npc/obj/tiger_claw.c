// tiger_claw.c -- 黑風虎王伏誅後，自其前掌拔下的一枚玄色巨爪——黑風山獵場
//                 巔峰之獵的憑證與彩頭。由 heifeng/npc/tigerking.c 的 die() 於
//                 虎王伏誅時掉落。純為打獵戰利品(flavour)，可變賣換些銀錢，不
//                 牽涉任何主線旗標。

inherit ITEM;

void create()
{
	set_name("黑風虎爪", ({ "tiger claw", "claw", "heifeng huzhua" }) );
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "枚");
		// 巔峰猛獸的戰利品，獵戶與藥商皆肯出價收購（可變賣，非無價信物）。
		set("value", 3000);
		set("long",
			"一枚自黑風虎王前掌拔下的玄色巨爪﹐約莫四寸來長﹐通體黝黑\n"
			"如鐵﹐爪身彎曲如鉤﹐爪尖森冷鋒利﹐握在掌中沉甸甸的﹐猶帶\n"
			"著一股未散的兇煞之氣。這虎王是黑風山稱雄數十年的山君之\n"
			"主﹐尋常獵戶終其一世也未必能近牠的身﹐遑論獵殺。能拔得這\n"
			"一枚虎爪的人﹐這身武藝與膽識﹐已足教滿山的獵戶都豎起大拇\n"
			"指了。獵戶與藥商皆肯出重金收購這等巔峰猛獸的爪牙。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
