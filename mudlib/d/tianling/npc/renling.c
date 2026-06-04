// renling.c -- 人靈之樸，人靈魂泉畔司魂魄輪轉、武學重凝之事的方外尊者。
//              正史主線第十章「技能重置(reset)」的換丹人兼重置之師。
//
// 故事背景（承接第九章 sanctifier.c/sun_moon_relic.c：守木尊者於京畿神社聖木舊址同獻
//   日(天靈之眼)、月(地靈之心)、星(四神之力齊備的星光環)三物、開光熔鑄成終局聖物「日
//   月神薛」，並指引——持此神薛，少俠那一身武學已堪行那「技能重置」、洗去舊力、重凝大
//   成，方堪了結那盤桓三百年、應劫而生的「十三靈」之患、再戰侮天鬼）：
//   天靈絕巔悔天鬼伏誅、霧靄潰散之後，石壇符陣透出清光，循之而上便是人靈魂泉——那一泓
//   應日月星三光而顯的靈泉之畔，趺坐著這位司魂魄輪轉、武學重凝之事的人靈之樸。少俠頸
//   懸日月神薛而至，便堪行那洗去舊習、重凝大成的技能重置。
//
// docs 主線樹（docs/01-世界觀與劇情/05 L67-68、L183-189）的 reset 鏈：
//   日月神薛(Ch.9) → 人靈之樸 換轉生丹(存 exp) → insert 4 seal on ring → reset xxx
//   (技能重置) → 十三靈最終任務(Ch.11)。
//
// 環經濟裁決（已拍板）：星光環的四印之力已於第九章盡數熔入日月神薛——故「日月神薛」即
//   重置之鑰，本章「不」另需星光環或四片散印（皆已沒入薛中）。本章遂收束為：人靈之樸
//   (gated on 日月神薛) 授玩家一枚轉生丹(存 exp)，玩家服丹存閱歷後，再於本師之前行『重
//   置(reset)』、洗去學習進度、重凝大成；重置畢開啟第十一章十三靈終局。
//
// 任務流程（旗標存在玩家身上：quest/main_canon10 + 防重領 quest/main_canon10_done。
//   captures docs 05 L187-189「換轉生丹(存 exp)→reset(技能重置)」）。入門條件：須先完成
//   第九章日月神薛(quest/main_canon9_done >= 1) 且頸懸/隨身日月神薛(present sun moon relic)：
//     _done            : 重置已竟——只給朝向十三靈/侮天鬼(Ch.11)的純劇情伏筆，不重複授丹
//     10 >= 1 (已授丹) : 提示玩家『服 轉生丹』存 exp、再『重置(reset)』洗去舊習
//     9_done 且持薛(初): 接任務——同步授「轉生丹」(npc/obj/rebirth_pill)、set main_canon10=1
//     9_done 但無薛    : 道明須頸懸/隨身日月神薛方堪行重置
//     9_done < 1       : 時機未到——只道魂泉重置的舊事，不開重置
//
// 技能重置機制（本檔 do_reset() 落實，由 init() 為玩家註冊『重置』/『reset』動作）：
//   * 入門：須 main_canon10 >= 1（已接任務/已授丹）且頸懸/隨身日月神薛。docs caveat：
//     reset 後技能 exp 歸零，故宜先服轉生丹存取 exp——若玩家未服丹(quest/reset_stored_exp
//     != 1)，本師先警示、勸其先服丹，不逕行重置（防玩家白白蝕去一身閱歷）。
//   * 重置內容（保守、可再訓練、絕不破壞 class/race/quest/relic）：將玩家 learned[]（學
//     習進度）與 skills[]（技能等級）逐一歸零（set_learn(s,0)+set_skill(s,0)），並
//     reset_skill_gain()。talent/<skill>（天賦潛能上限）保留不動——重置乃洗去「已習之
//     進度與等級」、非洗去「天賦」，故重新拜師/自習即可循原天賦重凝，是為「可再訓練」。
//   * 絕不動：class、race、level、score（一身閱歷／業力／聲望）、quest 旗標、日月神薛及
//     任何裝備/物品。重置畢：先 set main_canon10=2、再 set main_canon10_done=1（皆於任何
//     destruct 之前——本函式無 destruct，惟仍循 destruct-LAST 之序先記旗標），高潮 message，
//     並引入第十一章十三靈/侮天鬼終局。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 日月神薛 id（第九章終局聖物；本章重置之鑰）。玩家頸懸/隨身即可（worn 物仍 present 於背包）。
#define RELIC_ID	"sun moon relic"

int do_ask(string arg);
int do_reset(string arg);
private void give_rebirth_pill(object who);
private int has_relic(object me);
private int do_skill_reset(object me);

void create()
{
	set_name("人靈之樸", ({ "renling", "human spirit", "spirit" }) );
	set("nickname", "人靈之樸");
	set_attr("int", 28);
	set_attr("wis", 30);
	set_attr("spi", 28);
	set_attr("con", 22);
	set_race("human");
	set_class("commoner");
	set_level(20);
	set_skill("unarmed", 30);
	set_skill("dodge", 35);
	set_skill("force", 45);
	set_skill("literate", 50);

	set("gender", "male");
	set("age", 99);
	set("unit", "位");
	set("long",
		"一位趺坐在人靈魂泉畔青石之上的素衣尊者，鬚眉皆白，寶相沖\n"
		"和，一襲不染纖塵的素白長袍隨那泉畔清風微微浮動。他闔目趺坐，\n"
		"周身隱隱籠著一層與這魂泉同源的澄澈清光，彷彿早已與這天地清光\n"
		"融為一體，教人望之便覺心神俱靜。聽聞他便是司這天地間魂魄輪\n"
		"轉、武學重凝之事的人靈之樸——武者一身武學修到了大成的門檻，便\n"
		"須來這人靈魂泉之前，由他引著洗去舊習、重凝大成，方堪了結那盤\n"
		"桓三百年、應劫而生的十三靈之患。\n"
		"你或許可以問問他：ask renling about 重置。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"人靈之樸闔目趺坐，周身那層澄澈的清光隨呼吸明滅，與泉面的日月星三光遙遙相映。\n",
		"人靈之樸喃喃道：舊力不去，新力不生 ... 武學一道，原也須有捨方有得 ...\n",
		"人靈之樸枯瘦的指尖在泉面上輕輕一點，那一圈漣漪盪開，泉心的星河微芒便碎了又聚。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	// 為玩家註冊『重置』/『reset』動作（重置之師當面方得行此，故掛於 NPC init）。
	add_action("do_reset", ({ "重置", "reset" }) );

	// 招呼（須先完成第九章日月神薛）——依第十章旗標(main_canon10)給對應提示。招呼一律走
	// 單一 do_chat（is_chatting 期間 do_ask 早退、待招呼畢方應——承 is_chatting guard）。
	if( this_player() && interactive(this_player()) ) {
		if( this_player()->query("quest/main_canon9_done") >= 1 ) {
			if( this_player()->query("quest/main_canon10_done") >= 1 )
				do_chat((: command,
					"say 少俠舊力已洗、大成已凝——這一身重凝的武學，便是去了結那十三靈、再戰侮天鬼的本錢了。" :));
			else if( this_player()->query("quest/main_canon10") >= 1 )
				do_chat((: command,
					"say 少俠既已得了老朽這枚轉生丹，便先『服 轉生丹』存取那一身閱歷，再於老朽面前『重置(reset)』、洗去舊習、重凝大成罷。" :));
			else
				do_chat((: command,
					"say 少俠頸懸日月神薛而至，可是守木尊者遣來這人靈魂泉，行那重凝大成的技能重置的麼？ask renling about 重置。" :));
		}
	}
}

// 持薛判定：玩家頸懸/隨身日月神薛（worn 物仍 present 於背包，故 present 即可）。
private int has_relic(object me)
{
	if( !me ) return 0;
	return objectp(present(RELIC_ID, me));
}

// 同步授「轉生丹」(npc/obj/rebirth_pill)。who=接任務的玩家；同步交付（於 do_ask handler
//   內直接 new+move，玩家此刻必在場；絕不放進延遲 do_chat closure——承同步交付教訓）。
//   防重複授丹：玩家若已持有轉生丹、或已服丹存過 exp，皆不再重發。
private void give_rebirth_pill(object who)
{
	object pill;

	if( !who || environment(who) != environment() ) return;

	// 防重複授丹：身上已有轉生丹、或已服丹存過 exp 者，不重發。
	if( present("rebirth pill", who) ) return;
	if( who->query("quest/reset_stored_exp") == 1 ) return;

	pill = new(__DIR__"obj/rebirth_pill");
	if( !objectp(pill) ) return;
	if( !pill->move(who) ) pill->move(environment());
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg || (arg != "renling about 重置"
		&&   arg != "renling about 技能重置"
		&&   arg != "renling about 重置武學"
		&&   arg != "renling about 轉生丹"
		&&   arg != "renling about 轉生"
		&&   arg != "renling about 魂泉"
		&&   arg != "renling about 大成"
		&&   arg != "renling about 十三靈"
		&&   arg != "renling about 日月神薛"
		&&   arg != "renling about 神薛"
		&&   arg != "renling about reset"
		&&   arg != "renling about quest"
		&&   arg != "renling about relic"
		&&   arg != "human spirit about 重置"
		&&   arg != "human spirit about 轉生丹"
		&&   arg != "human spirit about reset"
		&&   arg != "spirit about 重置"
		&&   arg != "spirit about 轉生丹"
		&&   arg != "spirit about reset") )
		return notify_fail("你想問這位尊者甚麼？（試試 ask renling about 重置）\n");

	// is_chatting guard：招呼期間/交戰中早退，待招呼畢方應（承 is_chatting guard 教訓）。
	if( is_fighting() || is_chatting() )
		return notify_fail("人靈之樸正闔目趺坐、與這魂泉清光相融，沒空理你。\n");

	// ════════════════════════════════════════════════════════════════════
	// 正史第十章「技能重置」（換丹/重置章、無 boss 戰）：人靈魂泉即重置之地，人靈之樸即
	// 換丹人兼重置之師。旗標 quest/main_canon10 + 防重領 quest/main_canon10_done。入門條件：
	// 須先了結第九章日月神薛(quest/main_canon9_done >= 1) 且頸懸/隨身日月神薛。流程（見檔
	// 頭詳述）：
	//   _done            : 重置已竟——純劇情伏筆(十三靈/侮天鬼 Ch.11)，不重複授丹
	//   10 >= 1 (已授丹) : 提示『服 轉生丹』存 exp、再『重置(reset)』
	//   9_done 且持薛(初): 接任務——同步授轉生丹、set main_canon10=1
	//   9_done 但無薛    : 道明須頸懸/隨身日月神薛方堪行重置
	//   9_done < 1       : 時機未到——只道魂泉重置舊事
	// ════════════════════════════════════════════════════════════════════

	// 第十章已重置畢（main_canon10_done）：重置已竟——只給朝向十三靈/侮天鬼的純劇情伏筆，
	// 不重複授丹、不開新任務。
	if( me->query("quest/main_canon10_done") >= 1 ) {
		do_chat(({
			(: command, "say 少俠那一身武學的舊習已盡數洗去，大成已凝——這人靈魂泉之畔，老朽要為少俠做的，已盡於此了。日之天光、月之地氣、星之神威，連同少俠這一身重凝的大成之軀，俱已齊備。" :),
			(: command, "say 去罷，少俠——往那盤桓三百年、應劫而生的『十三靈』之患去。那十三靈乃天地間十三道未散的厲魂所凝，凶險更勝那天、地二靈；唯有少俠這一身重凝的大成之軀，並頸間日月神薛的三光護持，方堪一一了結。了了十三靈，方能再戰那侮天鬼、了結這天地間最後一樁因果。天下蒼生，都在等著少俠這最後一程了。" :),
		}));
		return 1;
	}

	// 已授丹（main_canon10 >= 1）：提示玩家『服 轉生丹』存 exp、再於本師面前『重置(reset)』。
	if( me->query("quest/main_canon10") >= 1 ) {
		if( me->query("quest/reset_stored_exp") == 1 )
			do_chat(({
				(: command, "say 少俠已服下轉生丹、將一身實戰閱歷封存妥當了。如今便可於老朽面前行那技能重置——只消在這魂泉之畔『重置(reset)』，老朽自引那魂泉清光，為少俠洗去一身武學的舊習進度、重凝大成。" :),
				(: command, "say 少俠且記著：重置只洗去那已習的學習進度與技能等級，少俠的根骨、天賦、閱歷、門派與這一路的因果，俱絲毫無損——洗去舊習，正為循那未改的天賦，重新習得、重凝出一身更醇厚的大成武學。『重置(reset)』罷，少俠。" :),
			}));
		else
			do_chat(({
				(: command, "say 少俠既已得了老朽這枚轉生丹，且聽老朽一言：那技能重置一行，少俠一身武學的學習進度便要盡數洗去歸零——故須『先服轉生丹』(服 轉生丹／eat rebirth pill)，將自身此刻的一身實戰閱歷封存於丹中，那畢生闖蕩江湖換來的閱歷，方不致隨重置而白白蝕去。" :),
				(: command, "say 服了轉生丹、存妥了閱歷，少俠再於這魂泉之畔『重置(reset)』，老朽自引魂泉清光，為少俠洗去舊習、重凝大成。切記：先服丹，後重置。" :),
			}));
		return 1;
	}

	// 接任務：須先了結第九章日月神薛(main_canon9_done >= 1) 且頸懸/隨身日月神薛。
	if( me->query("quest/main_canon9_done") >= 1 ) {
		// 持薛（初次）：同步授轉生丹、啟旗標 1。
		if( has_relic(me) ) {
			give_rebirth_pill(me);
			me->set("quest/main_canon10", 1);
			do_chat(({
				(: command, "say （人靈之樸睜開雙目，那一雙眸子澄澈如這魂泉之水，定定地落在少俠頸間那方流轉著日月星三光的神薛上）少俠頸懸日月神薛而至——守木尊者既以聖木餘力為少俠熔鑄了這方三光交融的終局聖物，少俠這一身武學，便已修到了大成的門檻了。" :),
				(: command, "say 老朽司這天地間魂魄輪轉、武學重凝之事。武學一道，舊力不去則新力不生——少俠這一身武學雖已博雜深厚，卻也夾纏了太多舊習的滯礙，須得在這人靈魂泉之前洗去舊習、重凝大成，方堪去了結那盤桓三百年、應劫而生的十三靈之患。" :),
				(: command, "say （人靈之樸枯瘦的指尖在泉面上一點，自那盪開的漣漪中托起一枚溫潤如玉、隱隱流轉著日月星三光的丹丸，雙手奉上）只是那重置一行，少俠一身武學的學習進度將盡數洗去歸零。少俠且先收下這枚『轉生丹』——重置之前，先『服 轉生丹』(服 轉生丹／eat rebirth pill)，將自身此刻的一身實戰閱歷封存於丹中，那畢生換來的閱歷，方不致隨重置而白白蝕去。存妥了閱歷，再於老朽面前『重置(reset)』。" :),
			}));
			return 1;
		}

		// 已了結第九章但未頸懸/隨身日月神薛：道明須帶薛來方堪行重置。
		do_chat(({
			(: command, "say （人靈之樸睜開雙目，澄澈的目光在少俠周身一掃，微微搖頭）少俠雖至這人靈魂泉之前，身上卻不見那方日月神薛——這重凝大成的技能重置，須以那日之天光、月之地氣、星之神威三力交融的日月神薛為引，方引得動這魂泉的清光。" :),
			(: command, "say 少俠且回京畿神社聖木淨室，尋那守木尊者領了日月神薛、戴穩在頸間(wear relic)，再來這魂泉之畔尋老朽罷。憑那神薛三光護持，老朽自為少俠洗去舊習、重凝大成。" :),
		}));
		return 1;
	}

	// 門檻未達(尚未了結第九章日月神薛)：時機未到——只道魂泉重置的舊事，不開重置。
	do_chat(({
		(: command, "say 少俠也聽說了這人靈魂泉畔的『技能重置』麼？武者一身武學修到大成的門檻，便須臨這魂泉洗去舊習、重凝大成，方堪去了結那盤桓三百年、應劫而生的十三靈之患。" :),
		(: command, "say 只是 ... 那是後話了。少俠頸間若無那方日之天光、月之地氣、星之神威三力交融的日月神薛，這魂泉的清光，老朽便是引了，也引不動少俠一身武學的舊力。少俠且先去京畿神社尋那守木尊者，集齊天靈之眼、地靈之心、星光環三物獻成日月神薛，再來這魂泉之畔尋老朽罷。" :),
	}));
	return 1;
}

// 技能重置動作：重置 / reset。由 init() 為玩家註冊（重置之師當面方得行此）。
//   入門：須 main_canon10 >= 1（已接任務/已授丹）且頸懸/隨身日月神薛。docs caveat：未服
//   轉生丹存 exp 者先勸服丹、不逕行重置。合格則 do_skill_reset()。
int do_reset(string arg)
{
	object me = this_player();

	if( !me ) return 0;

	// 須已接第十章重置之約（main_canon10 >= 1）方能於本師面前行重置。
	if( me->query("quest/main_canon10") < 1 )
		return notify_fail(
			"你並不知這技能重置的門道——須先頸懸日月神薛，向人靈之樸問明重置之"
			"事(ask renling about 重置)，方行得這重凝大成的一步。\n");

	// 重置已竟（防重複重置）。
	if( me->query("quest/main_canon10_done") >= 1 )
		return notify_fail(
			"你那一身武學的舊習早已在這魂泉之畔洗去、大成已凝，無須再重置了。\n");

	// 須頸懸/隨身日月神薛方引得動魂泉清光。
	if( !has_relic(me) )
		return notify_fail(
			"你身上並無那方日月神薛——這重凝大成的技能重置，須以那三光交融的日"
			"月神薛為引，方引得動這魂泉的清光。\n");

	// docs caveat：reset 後技能 exp 歸零，故宜先服轉生丹存 exp。未服丹者先勸服丹、不逕重置。
	if( me->query("quest/reset_stored_exp") != 1 )
		return notify_fail(
			"人靈之樸枯瘦的手掌虛虛一按，止住了你——『慢著，少俠。這重置一行，"
			"少俠一身武學的學習進度便要盡數洗去歸零。少俠且先服下老朽那枚轉生丹"
			"(服 轉生丹／eat rebirth pill)、將一身實戰閱歷封存妥當，再來重置，免"
			"得白白蝕去了那畢生闖蕩江湖換來的閱歷。』\n");

	return do_skill_reset(me);
}

// 技能重置之核心。me=this_player()。保守、可再訓練、絕不破壞 class/race/level/score/quest/
//   relic：將 learned[]（學習進度）與 skills[]（技能等級）逐一歸零，並 reset_skill_gain()；
//   talent/<skill>（天賦潛能上限）保留不動。先記旗標(10=2、10_done=1)、再 message（循
//   destruct-LAST 之序——本函式雖無 destruct，仍先記旗標後 message，穩健起見）。
private int do_skill_reset(object me)
{
	mapping skl, lrn;
	string s;
	int v;

	if( !me ) return 0;

	// 先記旗標（10->2->_done；皆於任何 message/收尾之前——循 destruct-LAST 之序）。
	me->set("quest/main_canon10", 2);
	me->set("quest/main_canon10_done", 1);

	// 逐一歸零 learned[]（學習進度）與 skills[]（技能等級）——可再訓練、不動 talent。
	skl = me->query_skills();
	if( mapp(skl) )
		foreach(s, v in skl)
			me->set_skill(s, 0);

	lrn = me->query_learned();
	if( mapp(lrn) )
		foreach(s, v in lrn)
			me->set_learn(s, 0);

	// 清本輪 skill_gain 累計（穩健起見）。
	me->reset_skill_gain();

	message_vision(
		HIY "人靈之樸枯瘦的雙手結起一個古樸的手印，口誦無聲的梵唄，將那一泓人靈魂"
		"泉的澄澈清光盡數引出——只見那清光自泉中漫起，順著$N頸間日月神薛上流轉的日月"
		"星三光，緩緩沒入$N的周身百骸。$N但覺一身武學那夾纏多年的舊習滯礙，竟如倒映入"
		"水的星河被一陣清風拂散一般，一點一滴地洗去、消融——舊力既去，那一身的根骨與天"
		"賦卻巋然不動，反似洗盡鉛華、返璞歸真，隱隱透出一派重凝大成的清明氣象。\n" NOR,
		me);

	do_chat(({
		(: command, "say 成了——少俠一身武學的舊習進度，已盡數洗去歸零了。少俠且放心：洗去的只是那已習的學習進度與技能等級，少俠的根骨、天賦、那一身的閱歷、門派與這一路行來的因果，俱絲毫無損。" :),
		(: command, "say 自此，少俠便循那未改的天賦，重新拜師、自習，重凝出一身更醇厚的大成武學罷——那存於轉生丹中的一身實戰閱歷，亦會在少俠重新習練之際，一分一分地化回少俠的武學裡。" :),
		(: command, "say 大成既凝，少俠便去了結那盤桓三百年、應劫而生的『十三靈』之患罷——那十三靈乃天地間十三道未散的厲魂所凝，凶險更勝天、地二靈；唯有少俠這一身重凝的大成之軀、並頸間日月神薛的三光護持，方堪一一了結。了了十三靈，方能再戰那侮天鬼、了結這天地間最後一樁因果。去罷，少俠，天下蒼生，都在等著少俠這最後一程了。" :),
	}));

	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠息怒——老朽一個司魂魄輪轉的方外之人，與少俠無冤無仇，這魂泉清淨之地，動手的事犯不著。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
