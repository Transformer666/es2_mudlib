// longjing_leaf.c -- 京畿支線任務「後海茶香」的信物：
//                    後海茶館茶博士遺失、被湖邊百姓拾得的一包雨前龍井茶葉。
//                    茶博士運茶時茶簍翻覆﹐這包頂尖的明前龍井散落湖岸﹐被一
//                    位京城百姓順手拾起收著。把它交還(give)給茶博士﹐這趟差
//                    事便算辦妥了。

inherit ITEM;

void create()
{
	set_name("龍井茶葉", ({ "longjing leaf", "tea leaf", "leaf" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "包");
		set("value", 1);
		set("long",
			"一包用油紙細細裹著的龍井茶葉﹐是清明前採的頭茬嫩芽﹐\n"
			"色澤翠綠﹐扁平挺直如雀舌﹐湊近一聞﹐一股清雅的豆花香撲\n"
			"鼻而來。這原是後海茶館茶博士運茶時翻簍散落湖岸的好茶﹐\n"
			"被湖邊一位京城百姓順手拾了去。把它交(give)還給茶博士﹐\n"
			"想必能教那愛茶如命的茶博士轉憂為喜。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
