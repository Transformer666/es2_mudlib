// spring_jug.c -- 水月村非戰鬥支線「福安客棧的清泉」的回報信物（滿筒）：
//                 一節盛滿了瀑後泉眼甜泉的竹筒。釣叟把採藥老叟交與玩家的空竹筒
//                 接過，到那疏通好的泉眼舀了滿滿一筒清冽的甜泉，封好筒口交還玩家，
//                 囑其速速持回福安客棧交與掌櫃，好教掌櫃驗過這水的甘甜。
//
// 用途：純為支線回報信物（quest/shuiyue_spring），不堪戰、不能賣、不能偷。
//       由 d/shuiyue/npc/angler.c 在玩家持空竹筒來盛泉後交付（同時銷除空竹筒）﹐
//       交還 d/shuiyue/npc/keeper.c 領賞。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("清泉竹筒", ({ "spring jug", "full jug", "qingquanzhutong" }) );
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "節");
		set("value", 1);
		set("long",
			"一節盛得滿滿的粗竹筒﹐筒口拿一截嫩竹葉封著﹐筒身沁出\n"
			"涼涼的水珠。湊近一聞﹐隱隱透著一股清冽的甘甜﹐正是水月\n"
			"瀑布瀑後泉眼舀來的活泉﹐釣叟說﹐這水比尋常井水甜上十\n"
			"分﹐拿來煮茶釀酒最好不過。\n"
			"該把它持回福安客棧交與掌櫃﹕ask keeper about 清泉﹐或 give spring jug to keeper。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
