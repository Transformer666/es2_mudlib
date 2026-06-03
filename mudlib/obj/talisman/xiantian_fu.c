// xiantian_fu.c -- 先天符，茅山道士施展高階咒術所需的符紙。
//
// 先天符蘊先天罡氣﹐須在特定時辰、以雞冠血調硃砂精心開光方成﹐為三等
// 符中至貴至罕者﹐供靈雲觀「五雷術」之賦予／補給、隱風觀「茅山幻術」
// 一類高階咒術催動。本物為 COMBINED_ITEM(可疊加)﹐結構比照
// obj/talisman/zhengyang_fu.c / obj/reagent/yangqi_pill.c：
// base_value/base_unit/base_weight 僅於 !clonep() 時設一次﹐set_amount(1)﹐
// 自動合併同類、add_amount(-1) 歸零自毀。
//
// 與 /std/magic.c::cast_spell 的「符閘」相接：咒文表 query_spells() 標記
// "fu":"xiantian fu" 者﹐施法時須 present("xiantian fu", me) 且 amount>=1。

inherit COMBINED_ITEM;

void create()
{
	set_name("先天符", ({ "xiantian fu", "xiantian_fu", "先天符", "fu" }));
	if( !clonep() ) {
		set("unit", "張");
		set("long",
			"這是一道茅山「先天符」﹐符紙以陳年黃麻精製﹐入手溫潤﹐朱\n"
			"書「先天」二字隱隱泛著金光﹐符文勾連如周天星斗﹐內蘊先天\n"
			"罡氣。此符須擇先天之時、以雞冠血調辰砂﹐凝神運法一筆而成﹐\n"
			"半點差池便前功盡棄﹐故為三等符中至貴至罕者。茅山高功施展\n"
			"五雷、幻術等大法時方焚此符﹐引先天之氣以成大用。\n");
		set("base_unit", "張");
		set("base_value", 1500);
		set("base_weight", 1);
	}
	set_amount(1);
	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
