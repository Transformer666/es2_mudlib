// rice_bowl.c -- 康平村非戰鬥支線「康平新米飯糰」的盛米信物（陶缽盛了新碾的新米）：
//                一隻粗陶燒的小缽﹐是田裡老農碾米的家什。老農見玩家受康平小店店家
//                之託來備新米飯糰﹐便就石碾現碾了一缽自家田裡新收的新米交與玩家﹐
//                囑其持往井臺尋灶上嬸子蒸飯。
//
// 用途：純為支線送件信物（quest/kangping_rice），不堪戰、不能賣、不能偷。
//       由 d/kangping/npc/farmer.c 在玩家接了任務後交付﹐持往
//       d/kangping/npc/cook.c 蒸飯（蒸飯時此缽銷除、改交蒸好的 rice_dough）。
//       送件進度記在玩家身上的旗標﹐本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("新米陶缽", ({ "rice bowl", "bowl", "xinmitaobo" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "隻");
		set("value", 1);
		set("long",
			"一隻粗陶燒的小缽﹐缽口拿一片乾荷葉虛掩著﹐原是田裡老\n"
			"農碾米的家什。缽裡盛著一缽剛在村心石碾上碾出的新米﹐粒粒\n"
			"雪白晶瑩﹐還帶著新穀的清香﹐正好拿去蒸一籠康平新米飯糰。\n"
			"該拿它到井臺尋灶上嬸子蒸飯﹕ask cook about 新米﹐或 give rice bowl to cook。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
