// shisanling.c -- 十三靈，正史主線第十一章「十三靈」終局之第一道關隘。
//                 一個 blueprint，由十三靈殿(lingdian.c)clone 出十三隻，共用
//                 玩家身上的擊殺計數旗標 quest/canon11_ling（0→13）。
//
// 故事背景（承接第十章「技能重置」於人靈魂泉(soulwell.c)重凝大成之後）：
//   三百年前，寒於氏與侮天鬼一脈於這天靈絕巔上死生相搏。寒於氏自知不敵，臨死前
//   竟以無上心法將自身一縷元神生生化作十三道精靈，散入這絕巔的天地之氣中，化作
//   十三道應劫而生、盤桓不散的厲魂——是為「十三靈」。三百年來，這十三道厲魂便游
//   蕩在十三靈殿(lingdian.c)中，既不能往生、亦未曾消散，只待後世重凝大成的有緣
//   人，將這十三道未散的元神一一斬滅、了結這三百年的執念，那盤踞幽窟、應劫而生
//   的侮天鬼，方肯自東向的洞口現身，了結這最後一戰。
//
// 設計（本章首關，量大而質中：十三隻共飲一鼎，須逐一了結）：
//   * 身手中等偏弱——max hp(kee) ~250、三圍 gin/kee/sen 適中、skill 適中。較第二章
//     骨屍妖王(kee440)、鬼王噬魂(kee400)遠弱，乃供玩家逐隻清剿之雜魂，非單體 boss。
//   * NOT aggressive：不主動撲噬（沿用 F_VILLAGER 既有 accept_fight 回傳 0 之慣例），
//     玩家須自行 kill 了結那未散的厲魂。十三靈殿(lingdian.c)valid_leave 應就
//     quest/main_canon10_done 把關，此為安全閥。
//   * set_race("human") / set_class("commoner")：沿用本 mudlib 既有獸/靈慣例（多為
//     human/commoner，避免載入失敗）。
//   * 外觀變化：以 random() efun 自五行元神色澤陣列(赤/青/白/玄/黃魂)取一，使 clone
//     出的十三隻略有差異——呼應寒於氏元神化十三精靈之說。
//
// 任務推進（die()，destruct-LAST！）：
//   每隻厲魂伏誅時，若下手者(last_damage_giver)是身負第十章大成旗標
//   (quest/main_canon10_done >= 1)的真實玩家(userp)：將其 quest/canon11_ling 計數
//   +1，並 message_vision 告知殺者「已了結第 n 道、尚餘 (13-n) 道」。當計數達 13，
//   設 quest/main_canon11 = 1，並 message_vision 告知十三靈盡滅、幽窟東向(east)洞
//   開、引向最後的侮天鬼。一切旗標/計數/訊息一律寫在 ::die() 之前（lesson #10
//   destruct-LAST：::die() 會中止其後所有程式碼）。末了恒呼 ::die()。
//
// 鐵則自查：有 die() → 絕不可 replace_program。#include <ansi.h>。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 五行元神色澤：寒於氏一縷元神化作十三道精靈，散入天地五行之氣。每隻 clone 自此
// 隨機取一，使十三隻略有差異（色澤/稱號/外觀皆隨之變）。
private mixed *ling_aspects = ({
	({ "赤魂", "赤",   HIR, "周身纏著一片煊赫如焰的赤色魂光" }),
	({ "青魂", "青",   HIG, "周身漫著一縷幽渺如煙的青色魂氣" }),
	({ "白魂", "白",   HIW, "通體透著一層慘淡如霜的白色魂華" }),
	({ "玄魂", "玄",   HIM, "周身鎖著一團沉鬱如墨的玄色魂霧" }),
	({ "黃魂", "黃",   HIY, "周身浮著一抹枯黯如塵的黃色魂芒" }),
});

void create()
{
	mixed *aspect;
	string title, color, hue, look;

	// 隨機取一道色澤——十三隻 clone 各取其一，略有差異。
	aspect = ling_aspects[random(sizeof(ling_aspects))];
	title = aspect[0];      // 稱號，如「赤魂」
	hue   = aspect[1];      // 單字色，如「赤」
	color = aspect[2];      // ansi 顏色碼
	look  = aspect[3];      // 外觀描述句

	set_name("十三靈", ({ "shisanling", "ling", "靈", "十三靈", "厲魂" }) );
	set("nickname", title);

	// 身手中等偏弱——攻防三圍俱屬適中，可被逐隻擊殺。
	set_attr("str", 22);
	set_attr("dex", 24);
	set_attr("int", 18);
	set_attr("wis", 18);
	set_attr("spi", 22);
	set_attr("con", 22);
	set_attr("cor", 20);
	set_race("human");
	set_level(30);
	set_class("commoner");
	set("sect", "寒於氏元神");
	set("rank", title);

	// 中等偏弱的身手：unarmed 主戰、不持兵器；parry/dodge/force 適中。
	set_skill("unarmed", 100);
	set_skill("parry", 90);
	set_skill("dodge", 95);
	set_skill("force", 90);

	// 三圍真氣——max hp(kee) ~250、gin/sen 適中。遠弱於第二章兩大 boss(kee 400/440)。
	advance_stat("gin", 220);
	advance_stat("kee", 250);
	advance_stat("sen", 230);

	set("gender", "無");
	set("age", 300);
	set("long",
		color + "這便是三百年前寒於氏臨終以一縷元神化作的十三道精靈之一。\n"
		"牠並無血肉之軀——只是一道盤桓於這絕巔天地之氣中、應劫而生、三\n"
		"百年來不曾消散的厲魂。" + look + "，\n"
		"勉強凝著一道飄忽不定的人形輪廓，眉目間猶帶著三百年前那場死生相\n"
		"搏裡未消的執念與不甘。據聞這十三道未散的元神須一一斬滅、盡數了\n"
		"結，那盤踞東向幽窟、應劫而生的侮天鬼，方肯現身了結這最後一戰。\n" NOR);
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		color + hue + "魂周身魂光大盛，那道飄忽的人形倏地化作一縷殘煙絞掠而來。\n" NOR,
		color + hue + "魂眉目間執念暴漲，一道無聲的厲嘯直撲識海，攝人心魂。\n" NOR,
		color + hue + "魂自虛空中探出一隻縹緲的魂手，徑往人的天靈蓋怨毒地攫來！\n" NOR,
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。十三隻量大，單隻經驗從中。
	set("bounty", ([
		"survive"         : 220,
		"unarmed mastery" : 55,
		"martial art"     : 30,
		"martial mastery" : 24,
		"combat"          : 28,
	]));
}

// 死亡：第十一章十三靈擊殺計數推進(canon11_ling +1) + 敘事；達 13 則開啟幽窟東向
// (quest/main_canon11 = 1)。一切旗標/計數/訊息寫在 ::die() 之前(lesson #10
// destruct-LAST)；末了恒呼 ::die()（屍體/bounty 善後依之）。
void die()
{
	object killer;
	int n;

	killer = last_damage_giver();

	// 下手者須為身負第十章大成旗標(>=1)的真實玩家，方計入十三靈擊殺數。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon10_done") >= 1 )
	{
		n = killer->query("quest/canon11_ling") + 1;
		killer->set("quest/canon11_ling", n);

		message_vision(
			HIR "那道厲魂發出一聲撕裂識海的無聲悲嚎，飄忽的人形自核心處潰散開"
			"來，纏身的魂光霎時化作一縷青煙，無聲地消融於這絕巔的天地之氣中。"
			"$N斬滅了這一道盤桓三百年、未散的厲魂——這寒於氏元神所化的十三靈，"
			"已了結了第 " + chinese_number(n) + " 道，尚餘 " +
			chinese_number(13 - n) + " 道未散。\n" NOR, killer);

		// 十三道盡滅 → 開啟幽窟東向、引向最後的侮天鬼。
		if( n >= 13 )
		{
			killer->set("quest/main_canon11", 1);
			message_vision(
				HIM "隨著這最後一道厲魂的潰散，盤桓於十三靈殿中那三百年不散的"
				"陰寒怨氣，竟在這一瞬間齊齊鬆動、消融——寒於氏臨終所化的十三道"
				"元神，至此盡數了結了！殿堂東面那一壁原本渾然一體的青黑山石，無"
				"聲地裂開一道幽深的洞口，一股應劫而生、亙古沉雄的滔天魔氣自洞中"
				"緩緩湧出。你心頭一凜——那盤踞幽窟、與寒於氏死生相搏三百年的『侮"
				"天鬼』，終於肯現身了結這最後一戰。(往東 east 可入侮天鬼幽窟)\n"
				NOR, killer);
		}
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略）。
	// 旗標/計數/訊息皆已於上方(::die() 之前)結算妥當——lesson #10 destruct-LAST。
	::die();
}

// vim: set ts=4 sw=4 syntax=lpc
