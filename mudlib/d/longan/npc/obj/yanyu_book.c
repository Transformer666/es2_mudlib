// yanyu_book.c -- 煙雨詩錄：龍安無腸老人畢生走遍水鄉煙雨、釀成的一卷詩錄頂級書。
//
// 來歷（承接 canon）：
//   docs 02-遊戲系統與機制/06-煉丹與書本系統.md L158：煙雨詩錄 → 龍安愛喝酒的無腸老人。
//   這卷『煙雨詩錄』是龍安無腸酒店那位愛喝酒的詩翁(d/longan/npc/wuchang.c)畢生走遍
//   江南水鄉、把一路橋影櫓聲煙波酒甕都釀成的句子﹐手抄而成的詩卷。欲得此卷﹐須先同
//   無腸老人談詩論酒、引為知音﹐方蒙他相贈(見 wuchang.c::do_ask 授書流程)。
//
// 定位（docs 書本系統三類，docs 06 L116-118）：
//   兼「悟性書」(提升悟性 int)與文識頂級書二者——一卷詩錄﹐讀通了水鄉詩心﹐既精進
//   文識(literate)﹐又開闊悟性(int)。列於 docs 06「頂級書取得地點」一系(L155-170)。
//
// 用法：可用 study 研讀的詩文秘本(ITEM + F_STUDY﹐鏡 d/qiuyi/npc/obj/yaoshi_book.c、
//   d/mengjia/npc/obj/sixyin_manual.c 之頂級書範式)。
//
// 平衡（content 值 = study 可習得的技能上限﹐見 feature/study.c::study_content：僅當
//   query_skill(t) < content[t] 時才 improve）：
//   * literate(文識/詩文造詣) 45：對齊既有頂級書主修高標(sixyin/unarmed45、yaoshi/needle45、
//     wuming/force45)。literate 是 study 的核心進度技能(study.c L74 以 literate 為研讀效率)﹐
//     一卷頂級詩錄把文識封到 45﹐契合「頂級書、詩文造詣精深」之定位。既有書 literate content
//     最高見 35﹐本卷取頂級上緣 45﹐不臆造越界(study.c content 上限即此值、改動不破壞他書)。
//   * required/skill literate 30：同 sixyin/yaoshi 頂級書門檻﹐契合「譜訣艱深、須有相當文識
//     方讀得通」。與 content 45 並存合理(門檻 30、可習至 45)。
//   * enlighten/int 32（悟性書﹐docs 06 L118：悟性書提升 int）：study.c::enlighten_int 僅在
//     本拍確有 gain 時、以遞減機率每次至多 +1 嘗試提升 int﹐並雙重夾於 min(本值, ATTRVAL_MAX=50)。
//     現存 mudlib **無**任何 enlighten/int 書可資對齊尺度(本卷為首例)﹐故取保守中庸值 32——
//     高於常人初始悟性、給有意義的成長空間﹐又遠低於 50 硬上限、不至壟斷悟性來源。**此值為
//     設計決策(無 canon 數字)**﹐見 caveat﹐宜由設計者按全局悟性曲線再行校準。
//   * no_sell：無腸老人畢生心血、引知音方贈的詩卷﹐玩家自當珍習﹐不宜變賣。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name(HIY "煙雨詩錄" NOR,
		({ "yanyu", "yanyu poem", "yanyu book", "poem book", "manual", "book",
		   "煙雨詩錄", "詩錄" }) );
	set_weight(700);

	if( !clonep() ) {
		set("unit", "卷");
		set("value", 1);
		set("no_sell", 1);
		set("long",
			"一卷以陳年絹帛裝裱、邊角磨得起了毛的舊詩卷﹐封皮上『煙\n"
			"雨詩錄』四個飄逸的行書依稀可辨﹐隱隱透著一股久經酒漬水汽\n"
			"浸染的陳舊氣息。翻開來﹐內裡是一首首信手寫就的詩詞﹐字跡\n"
			"時而工整、時而潦草﹐想是寫時帶著幾分醉意﹔所詠盡是這江南\n"
			"水鄉的景致——橋影、櫓聲、煙波、酒甕、雨打芭蕉、舟泊煙\n"
			"渚﹐字裡行間﹐一片化不開的煙雨詩心。卷末還夾著無腸老人隨\n"
			"手塗抹的詩話批註﹐論詩道、談酒趣﹐妙語紛披。細細研讀﹐既\n"
			"能精進文識﹐於那份體察萬物的悟性﹐怕也要開闊幾分。只是這\n"
			"詩錄意境深遠﹐非有相當的文識﹐怕是連讀都讀不通。\n"
			"可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 30,
		]));
		set("content", ([
			"literate" : 45,    // 文識/詩文造詣，對齊頂級書主修高標(study 核心進度技能)。
		]));
		set("enlighten/int", 32);   // 悟性書(docs 06 L118)，提升悟性 int，遞減機率每拍至多 +1，封於 min(本值,50)。
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
