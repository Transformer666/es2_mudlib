// bone_talisman.c -- 正史序章「逐念入山」的線索信物：骨符殘片。
//
// 來歷：摩雲的潰散殘部為首的吞風獅(npc/windlion.c)伏誅後﹐自其屍身中滑落
//   的一片枯骨殘符。符上以鬼篆刻著「噬魂」一脈的咒紋﹐殘留著一縷指引入幽
//   冥之路的陰識——這正是天靈山更深處那頭把持混沌珠的「骨屍妖王」遣孽畜佩
//   帶、以牽動摩雲一脈的信物。守山道人見得此符﹐便能參出混沌珠今時的下落。
//
// 用法：持此骨符回幽壑(youhe.c)﹐ask shoushan about 混沌珠﹐請守山道人參詳
//   領賞（亦可 give bone talisman to shoushan，惟序章領賞走 ask-path 為主）。

inherit ITEM;

void create()
{
	set_name("骨符殘片", ({ "bone talisman", "talisman" }) );
	set_weight(40);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("value", 1);
		set("long",
			"一片巴掌大小、邊緣殘缺的枯骨﹐色作晦暗的焦黃﹐入手陰寒徹\n"
			"骨。骨片上以一種詰屈如蛇的鬼篆密密刻著咒紋﹐筆畫的溝壑裡\n"
			"嵌著早已乾涸的暗紅﹐隱隱透著一股化不開的腐朽屍氣。湊近細\n"
			"看﹐那咒紋深處彷彿盤桓著一縷未散的陰冷意念﹐似在無聲地指\n"
			"引著一條幽暗的去路。這骨符﹐想是天靈山更深處某個把持邪物\n"
			"的存在﹐遣這群孽畜佩帶、用以牽動其兇性的信物——合該帶去交\n"
			"與那守山道人﹐請他參詳這混沌珠的下落。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
