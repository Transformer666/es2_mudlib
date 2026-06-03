// zhengyang_fu.c -- 正陽符，茅山道士施展低階咒術所需的符紙。
//
// 茅山一脈以符籙引動咒術﹐畫符於黃紙、開光而成「符」。正陽符取陽剛之
// 氣、用以驅邪﹐是三等符中最廉、最易得的一種﹐供入門咒術（如靈雲觀
// 「幽冥三箭」）燃符催動。本物為 COMBINED_ITEM(可疊加)﹐比照 obj/reagent/
// yangqi_pill.c：base_value/base_unit/base_weight 僅於 !clonep() 時設一次﹐
// set_amount(1)﹐自動合併同類、add_amount(-1) 歸零自毀。
//
// 與 /std/magic.c::cast_spell 的「符閘」相接：咒文表 query_spells() 標記
// "fu":"zhengyang fu" 者﹐施法時須 present("zhengyang fu", me) 且 amount>=1﹐
// 通過後 add_amount(-1) 燃去一張。

inherit COMBINED_ITEM;

void create()
{
	set_name("正陽符", ({ "zhengyang fu", "zhengyang_fu", "正陽符", "fu" }));
	if( !clonep() ) {
		set("unit", "張");
		set("long",
			"這是一道茅山「正陽符」﹐以硃砂在裁好的黃紙上一筆畫就﹐符\n"
			"頭朱書「正陽」二字﹐符身一道符膽蜿蜒如雷﹐取陽剛之氣以驅\n"
			"邪祟。此符乃三等符中最尋常的一種﹐茅山弟子施展入門咒術時\n"
			"焚之引氣、催動法力。符紙微透墨香﹐邊角已被指尖摩挲得有些\n"
			"起毛。\n");
		set("base_unit", "張");
		set("base_value", 200);
		set("base_weight", 1);
	}
	set_amount(1);
	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
