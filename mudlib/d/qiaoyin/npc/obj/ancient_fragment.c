// ancient_fragment.c -- 主線任務二「殘卷尋蹤」的信物：
//                       喬陰縣衙卷庫封存的《封鬼遺錄》殘卷﹐記著三百年前
//                       斷木放出何物的關鍵一頁﹐須帶回封山派交還陸師叔

inherit ITEM;

void create()
{
	set_name("殘卷", ({ "ancient fragment", "fragment", "scroll" }) );
	set_weight(120);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "卷");
		set("value", 1);
		set("long",
			"一卷在縣衙卷庫深處封存了數十年的殘卷﹐紙色焦黃﹐邊角蟲蛀\n"
			"得只剩半幅﹐展開時簌簌掉著紙屑。卷首尚能辨出「封鬼遺錄」四\n"
			"個篆字﹐其下的文字卻多已殘缺﹕「 ... 聖木既斷﹐其下所鎮之\n"
			"十三 ... 出 ... 非火非水可滅﹐唯 ... 」﹐後文盡墨﹐再難辨\n"
			"認。字裡行間透著一股說不出的森寒﹐教人不敢久看。這等東西﹐\n"
			"合該趕緊帶回封山派﹐交給那位追查此事多年的陸師叔。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
