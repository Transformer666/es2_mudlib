// sect_dispatch.c -- 主線任務三「聖木探封」的信物：
//                    封山派掌門柳東蘆閱過《封鬼遺錄》後﹐命少俠持往京畿
//                    神社、求見守著聖木舊址之老者的一紙封山派文書

inherit ITEM;

void create()
{
	set_name("封山派文書", ({ "sect dispatch", "sect document" }) );
	set_weight(80);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "紙");
		set("value", 1);
		set("long",
			"一紙封山派掌門柳東蘆親自鈐印的文書﹐黃綾為底﹐其上一行行\n"
			"端楷凝重如山﹐落款處並用了「封山掌門」與「藏劍堂」兩方朱\n"
			"印。文書中言明﹕掌門已閱過師叔陸抱朴補齊的《封鬼遺錄》﹐知\n"
			"三百年前皇城聖木被斷、放出侮天鬼之物的舊案不假﹐特命持書之\n"
			"人往京畿神社一行﹐尋訪守著聖木舊址的老者﹐問清那道封印的虛\n"
			"實。憑著這紙文書﹐合該能教那守木的老者吐露些舊事。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
