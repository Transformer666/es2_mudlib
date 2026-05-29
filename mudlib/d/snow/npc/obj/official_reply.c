// official_reply.c -- 主線任務「卯木之兆」的信物：
//                     鄉校師爺收下密報後批給廟祝的一紙回文

inherit ITEM;

void create()
{
	set_name("批文", ({ "official reply", "reply" }) );
	set_weight(80);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "紙");
		set("value", 1);
		set("long",
			"一紙鄉校師爺批下的公文﹐墨跡未乾﹐角上鈐著一方鄉校的木\n"
			"印。文末批著「卯木夜啼一事﹐已具文呈縣﹐著民人勿得驚擾」\n"
			"幾行小楷﹐字斟句酌﹐倒是把廟祝那封駭人的密報壓得四平八穩。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
