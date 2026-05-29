// omen_report.c -- 主線任務「卯木之兆」的信物：
//                  土地公廟廟祝託人送往鄉校師爺的一封密報

inherit ITEM;

void create()
{
	set_name("密報", ({ "sealed report", "omen report", "report" }) );
	set_weight(150);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "封");
		set("value", 1);
		set("long",
			"一封用黃蠟仔細封緘的素箋﹐封皮上並無官印﹐只用硃砂畫著\n"
			"一株被攔腰折斷的古木﹐筆觸顫抖﹐像是寫的人手都在發抖。\n"
			"封口處依稀透出墨跡﹐隱約是「卯木夜啼﹐其下有異」幾個字。\n"
			"這等駭人之語﹐合該趕緊送到鄉校的師爺手上﹐請官府過目。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
