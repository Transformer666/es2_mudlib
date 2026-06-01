// wolf_fang.c -- 蒼狼王伏誅後，自其巨口中拔下的一枚雪亮獠牙——狼窩谷獵場
//                巔峰之獵的憑證與彩頭。由 langwo/npc/wolfking.c 的 die() 於狼王
//                伏誅時掉落。純為打獵戰利品(flavour)，可變賣換些銀錢，不牽涉任何
//                主線旗標。

inherit ITEM;

void create()
{
	set_name("狼王獠牙", ({ "wolf fang", "fang", "langwang liaoya" }) );
	set_weight(400);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "枚");
		// 巔峰猛獸的戰利品，獵戶與藥商皆肯出價收購（可變賣，非無價信物）。
		set("value", 3000);
		set("long",
			"一枚自蒼狼王巨口中拔下的雪亮獠牙﹐約莫三寸來長﹐通體瑩白\n"
			"如玉﹐牙身彎曲如鉤﹐牙尖森冷鋒利﹐握在掌中沉甸甸的﹐猶帶\n"
			"著一股未散的腥煞之氣。這狼王是稱雄一方、為患武陵古道的狼\n"
			"窩之主﹐尋常獵戶終其一世也未必能近牠的身﹐遑論獵殺。能拔\n"
			"得這一枚獠牙的人﹐這身武藝與膽識﹐已足教滿山的獵戶與武陵\n"
			"的行旅都豎起大拇指了。獵戶與藥商皆肯出重金收購這等巔峰猛\n"
			"獸的爪牙。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
