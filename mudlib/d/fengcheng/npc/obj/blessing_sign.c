// blessing_sign.c -- 風城非戰鬥支線「失算的籤筒」的酬謝信物：
//                    神算子謝玩家替他尋回失落的龜甲卦錢﹐當場搖籤批就、
//                    親筆相贈的一支「上上平安籤」。純風味物件﹐不堪戰﹐
//                    亦不開啟任何功能（不真的判讀天賦、不改任何屬性﹐純作
//                    彩頭氣氛﹐避免動到神算子日後的天賦判讀機制）。

inherit ITEM;

void create()
{
	set_name("平安籤", ({ "blessing sign", "fortune sign", "pingansign" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "支");
		set("value", 20);
		set("long",
			"一支竹製的籤條﹐是風城神算子親手自籤筒裡搖出、又提筆\n"
			"批就相贈的。籤頭硃砂寫著「上上」二字﹐底下一行蠅頭小楷\n"
			"批著籤辭﹕「失而復得﹐塞翁失馬﹐心正運通﹐出入平安」。\n"
			"神算子說﹐你替他尋回了失落的卦錢﹐這支籤是他誠心替你卜\n"
			"的﹐佩在身上﹐圖個出入平安的好彩頭。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
