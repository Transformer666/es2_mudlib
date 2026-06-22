// qiyong_book.c -- 黑風寨頭目所藏的兵法奇書：杞庸兵書。
//
// 來源(doc)：docs/02-遊戲系統與機制/05-裝備與強化.md L184-186「黑風寨四頭目」一節，
//   黑風寨頭目掉落物列有「杞庸兵書」一件。本檔取其名落實為黑風寨頭目伏誅後掉落、可
//   study 研讀的兵法秘本。(docs 將四件並列於閰狂風名下﹐本副本將之分屬四頭目各一件﹐
//   見副本設計說明；此書指派為「四頭目」鬼影子掉落。)
//
//   P6-10 並未建立本書(grep "杞庸"/"qiyong" 無既有檔)﹐故於本任務一併建立﹐路徑置於
//   d/heifeng/npc/obj/ 下﹐由黑風寨頭目鬼影子(d/heifeng/npc/gui_yingzi.c)掉落。
//
// 用法：可用 study 研讀的兵法奇書（ITEM + F_STUDY，鏡 d/tianling/npc/obj/wuming_manual.c
//   與 d/snow/obj/literate_book.c 之 manual 做法）。書中所載為一套臨陣調度、攻守相生的
//   兵家武學心要；須有相當的文識(literate)方能讀通其上古奧的兵法陣圖﹐讀通之後於內功
//   (force)與招架(parry)之道俱有所進益——以「運勁如調兵、守勢如布陣」對應 force 為主、
//   佐以 parry。量級貼合 wuming_manual(force45/parry35) 一線﹐定位為頭目珍藏的失傳兵書。
//   設 no_sell：兵法奇書非市井可估﹐得之者自當珍習﹐不宜變賣。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name(HIY "杞庸兵書" NOR,
		({ "qiyong book", "qiyong manual", "art of war", "manual", "book",
		   "杞庸兵書", "兵書" }) );
	set_weight(1100);

	if( !clonep() ) {
		set("unit", "卷");
		set("value", 1);
		set("no_sell", 1);
		set("long",
			"一卷以陳舊絹帛裝裱的兵法奇書，封面以蒼勁的篆字題著『杞庸\n"
			"兵書』四字。書頁泛黃殘破，散著一股陳年的霉香與硝煙的腥氣，\n"
			"想是隨著它的歷代主人征戰殺伐、輾轉江湖，不知過了多少歲月。\n"
			"翻開來，內裡以古奧的小篆密密寫就，其間夾著一幅幅排兵布陣、\n"
			"臨敵調度的陣圖，旁註著運氣行功、攻守相生的訣竅——所論既有\n"
			"沙場決勝的兵家謀略，又暗合武者臨陣應變、以靜制動的武學至\n"
			"理。細辨之下，這套兵法武學立意精深，遠非坊間那些行軍口訣\n"
			"可比，只是那古篆艱澀、陣圖繁奧，非有相當的文識，怕是連讀\n"
			"都讀不通。這卷兵書，原是黑風寨頭目壓寨的珍藏。\n"
			"可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 25,
		]));
		set("content", ([
			"force" : 45,
			"parry" : 35,
		]));
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
