// shaoyin_fu.c -- 少陰符，茅山道士施展中階咒術所需的符紙。
//
// 少陰符取陰柔之氣﹐較正陽符更為精細﹐為三等符中之中品﹐供幻霧觀
// 「茅山奇術」一類陰系咒術催動。本物為 COMBINED_ITEM(可疊加)﹐結構
// 比照 obj/talisman/zhengyang_fu.c / obj/reagent/yangqi_pill.c：
// base_value/base_unit/base_weight 僅於 !clonep() 時設一次﹐set_amount(1)﹐
// 自動合併同類、add_amount(-1) 歸零自毀。
//
// 與 /std/magic.c::cast_spell 的「符閘」相接：咒文表 query_spells() 標記
// "fu":"shaoyin fu" 者﹐施法時須 present("shaoyin fu", me) 且 amount>=1。

inherit COMBINED_ITEM;

void create()
{
	set_name("少陰符", ({ "shaoyin fu", "shaoyin_fu", "少陰符", "fu" }));
	if( !clonep() ) {
		set("unit", "張");
		set("long",
			"這是一道茅山「少陰符」﹐符紙泛著淡淡的青灰﹐朱書「少陰」\n"
			"二字﹐符文走勢內斂幽曲﹐取陰柔之氣以攝幽冥。此符較正陽符\n"
			"更費心血開光﹐為三等符中之中品﹐茅山弟子施展陰系咒術時焚\n"
			"之以引動陰煞之力。符上隱隱透出一縷涼意﹐似有森森幽氣縈繞\n"
			"其間。\n");
		set("base_unit", "張");
		set("base_value", 500);
		set("base_weight", 1);
	}
	set_amount(1);
	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
