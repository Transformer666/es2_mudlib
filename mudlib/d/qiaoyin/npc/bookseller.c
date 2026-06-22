// bookseller.c -- 喬陰書局老書商：賣書(F_VENDOR)的斯文人，兼桐城派支線之「中繼」線索人。
//
// 【桐城派支線 中繼一步】（canon：docs 01/05 L102「桐城派信使 → 真正的桐城派信物」）
//   本檔在賣書本業之外，另兼桐城這條線的「驗印指路」中繼：
//   玩家持桐城派信使所贈的「桐城密信」(tongcheng letter)，循信來城西書局，
//   `ask bookseller about 火漆`（或 印鑑/桐城/密信 …），這位見多識廣的老書商
//   便替玩家認出火漆上那枚模糊舊印乃桐城掌門印鑑，指引玩家往聚仙酒樓尋桐城
//   老蒼頭——並設旗標 quest/tongcheng_step1 = 1（下游 laocangtou.c 認此旗標續接）。
//   書商【不】發任何物、【不】收信、【不】碰終獎；只「認印 + 指路 + 設中繼旗標」。
//
//   全鏈：信使 mailman(起點,給密信) → 書商(本檔,驗印設 step1) → 老蒼頭 laocangtou
//         (終點,驗信發桐城玉牌、設 tongcheng_done)。
//
// 【同步交付】設旗標一律在 do_ask handler 內、do_chat 之前直接做（本檔不發物，純設旗標）。
// 【runtime 鐵則】本 NPC 有 do_ask；既有 init 已 add_action("do_vendor_list","list")，
//   再補 add_action("do_ask","ask")。不 replace_program（NPC 本就不該）。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("書商", ({ "bookseller", "vendor" }) );
	set_race("human");
	set_class("scholar");
	set_level(8);

	set("age", 58);
	set("gender", "male");
	set("long",
		"這位是喬陰書局的老書商﹐頭戴方巾﹐身著一襲洗得發白的青\n"
		"衫﹐手裡總捧著一卷書﹐說起話來文謅謅的﹐一派斯文。你可以\n"
		"用 list 看他賣些什麼書﹐用 buy 向他買書。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"書商捻著鬚﹐搖頭晃腦地低聲吟哦著手裡的書卷。\n",
		"書商和氣地說道﹕公子是來尋書的麼﹖小店藏書雖不算多﹐倒也頗有幾本值得一讀的。\n",
		"書商歎道﹕如今肯靜下心來讀書的人﹐是越發少了。\n",
		"書商說道﹕買了書﹐尋個清靜處 study 細讀﹐方不負這滿紙的學問。\n",
		"書商壓低嗓子道﹕架上還有幾本拳、劍、刀、棍的武功秘笈﹐都是粗淺入門的功夫﹐公子若有興致﹐倒可買去 study 揣摩揣摩。\n",
	}));
	// 喬陰書局販售幾種書冊﹕蒙書、詩抄可 study 增進學識﹐話本則供消遣﹐
	// 另有幾本基礎武功秘笈﹐供初窺武道者 study 入門 (拳、劍、刀、棍、內功)。
	// TODO: 日後可增設更深的武學秘笈、各色經史子集等書籍 (新建 obj)。
	set("merchandise", ([
		"/d/qiaoyin/obj/primer" : 30,
		"/d/qiaoyin/obj/poetry" : 20,
		"/d/qiaoyin/obj/storybook" : 40,
		"/d/qiaoyin/obj/fist_manual" : 5,
		"/d/qiaoyin/obj/sword_manual" : 5,
		"/d/qiaoyin/obj/blade_manual" : 5,
		"/d/qiaoyin/obj/staff_manual" : 5,
		"/d/qiaoyin/obj/force_manual" : 5,
	]));

	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");
}

// 桐城派支線 中繼一步：認火漆舊印、指路往聚仙酒樓尋桐城老蒼頭、設 quest/tongcheng_step1。
// 純「認印 + 指路 + 設旗標」，不發物、不收信、不碰終獎。設旗標寫在 do_chat 之前（鐵則 #10）。
int do_ask(string arg)
{
	object me = this_player();

	if( !arg || (arg != "bookseller about 火漆"
		&&   arg != "bookseller about 印鑑"
		&&   arg != "bookseller about 印"
		&&   arg != "bookseller about 桐城"
		&&   arg != "bookseller about 桐城派"
		&&   arg != "bookseller about 密信"
		&&   arg != "bookseller about 信物"
		&&   arg != "bookseller about seal"
		&&   arg != "bookseller about tongcheng"
		&&   arg != "vendor about 火漆") )
		return notify_fail("你想跟這位書商打聽甚麼？（買書請用 list / buy；問桐城舊印試試 ask bookseller about 火漆）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("書商正捧著書卷低吟，一時沒理會你。\n");

	// 沒接過桐城這條線（信使那封密信都沒有）：純氣氛點題，不設旗標。
	if( !me->query("quest/tongcheng_start") && !present("tongcheng letter", me) ) {
		do_chat((: command,
			"say 火漆舊印？呵呵，公子問起這個——這城裡識得舊年印鑑款識的，怕沒幾個了。公子若手裡有甚麼火漆封緘的舊信，不妨拿來教老朽掌掌眼。" :));
		return 1;
	}

	// 持密信來驗印：認出桐城掌門印鑑、指路往聚仙酒樓、設 step1（首次）。
	if( present("tongcheng letter", me) ) {
		// 已設過 step1：純氣氛重述指路，不重設（idempotent）。
		if( me->query("quest/tongcheng_step1") >= 1 ) {
			do_chat((: command,
				"say 公子那封桐城密信，老朽先前已替你認過了——火漆上是桐城掌門的印鑑。循這線索，往廣場西邊聚仙酒樓走一趟，那位枯守多年的桐城老蒼頭便在那裡。(ask laocangtou about 桐城)" :));
			return 1;
		}
		// 首次驗印：先設旗標（純設旗標、不發物），再擺指路對白（鐵則 #10）。
		me->set("quest/tongcheng_step1", 1);
		do_chat(({
			(: command, "say 公子手裡這封火漆密信，且容老朽掌掌眼……唔，這枚舊印雖已模糊，那『桐』字的篆法、邊上這圈梧桐葉紋，分明是桐城掌門的印鑑無疑！這可是樁了不得的舊事。" :),
			(: command, "say 老朽年輕時販書走南闖北，曾在桐城派的文書上見過這方印。桐城雖已零落，城裡卻還流落著一位桐城的舊人——那是桐城派最後一位執事的老蒼頭，如今枯守在廣場西邊的聚仙酒樓裡，多年來只盼有個肯為桐城舊事奔走的人尋來。" :),
			(: command, "say 公子既持著這封密信，便往聚仙酒樓尋那桐城老蒼頭去罷，問他桐城的舊事——許能解開這封密信所指的真正信物之謎。(ask laocangtou about 桐城)" :),
		}));
		return 1;
	}

	// 接過線、卻把密信弄丟了：點撥回信使補領（書商不發物）。
	do_chat((: command,
		"say 公子方才說的那封桐城密信呢？不見了？無信在手，老朽也認不得那舊印了。快回大街上尋那桐城派信使，討一封密信補上，再來教老朽掌眼罷。" :));
	return 1;
}

int accept_fight(object ob)
{
	do_chat("書商連忙護住書卷﹐賠笑道﹕斯文之地﹐動什麼粗﹖公子息怒、息怒﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
