// shaoyang.c -- 少楊：盤桓於天靈山麓、為持劍少俠「開光穿靈」的開光師。
//
//   (canon：docs 01-世界觀與劇情/05 L118「少楊 @ 天靈山 → 開光穿靈（需火神之眼）」)
//
// 故事背景：
//   穿靈(d/capital/npc/obj/chuanling.c)乃第四章「蜈蚣war」斫斷京畿聖木殘節的聖劍——
//   以聖木最堅韌的一段心節為胎、外覆玄鐵鑄鋒。少楊是天靈山麓一脈守木後人，世代精研
//   以離火淬煉聖物之術。docs 原訂以「火神之眼」為開光門檻；然「火神之眼」非現開源樣本
//   之物，玩家未必有得。本實作改 gate 於玩家確曾於第六章四神任務取得火神之印(火神乃
//   司南方離火、三昧真火之神，正合「以離火開光」之設定)——
//
//   **採用之 gate（雙保險，二者居一即可，且不奪不耗任何玩家物事）**：
//     (a) 玩家身上現有『火神之印』(seal of fire/fire seal，d/longdao/npc/obj/seal_fire.c)；或
//     (b) 玩家已具旗標 quest/main_canon6_seal_fire == 1（曾取得火神之印；之後縱已將其嵌入
//         星光環 d/chimei/npc/obj/starlight_ring 而印已 destruct，仍認得此功業）。
//   選 (b) 為輔，是因火神之印一經嵌入星光環即 destruct——只認 (a) 會把已推進至星光環階段
//   的玩家反鎖在外。二者居一，既忠於「需火神(離火)之力」的 docs 旨，又不致 soft-lock。
//   **火神之印一概不收不耗**——它另須嵌入星光環成就終局，開光僅借其「離火之證」為憑。
//
// 開光機制（鏡 cmds/std/enchant.c 之武器強化資料模型——武器以 set("damage/<skill>", dp)
//   存 class damage_parameter；每 clone 各自一份 dp，改 clone 上的 dp 為「逐把」生效，不
//   污染樣板或他人之劍。穿靈逐玩家 clone+move 交付，故開光亦逐玩家、逐劍）：
//   1. 對玩家身上那把穿靈，逕以 setup_sword(5,16,130,8) 重設三式傷害(單手/副手/雙手)——
//      較原 setup_sword(4,15,110,8) 全面提升乘數/範圍/力修，皆在 enchant.c::enchant_cap
//      之 sword(110/150/5)、twohanded sword(210/225/5) 上限之內。
//   2. set("apply_weapon/sword", ([...]))：開光版穿靈手持時另賦 dex/精神/attack/parry 加成
//      （鏡 d/snow/npc/obj/slasher_sword.c::apply_weapon/sword 範式）。apply_weapon 於 wield
//      時生效——若玩家此刻正持穿靈，逕為其 unequip 後重 wield 一次，令加成即時附身、可驗。
//   3. 升 value、改名為「開光版」、set("consecrated",1) 留可驗證痕跡；記旗標 quest/shaoyang_done。
//
// 同步交付 / 防重複（本專案頭號 bug class 之防範）：開光一律在 do_ask handler 內「即時」對玩家
//   身上的穿靈施作、且在設完成旗標之前——絕不放進延遲的 do_chat/closure。do_chat 只擺氣氛對白。
//   quest/shaoyang_done 防重複開光（已開光者再問只給純劇情）。穩健性：旗標已記但身上那把穿靈
//   竟未開光(set("consecrated") 不在；遺失原劍另得新劍之類)，則補開光一次、不重置進度。
//
// runtime 鐵則：本 NPC 有 do_ask，**不** replace_program(#11)；is_fighting/is_chatting guard 於
//   do_ask(#11)。全程無 ::die()/destruct()，旗標/訊息皆在施作之後、return 之前寫妥(#10 不適用，
//   然仍依其旨：先施作→後記旗標→再對白)。

#include <ansi.h>
#include <npc.h>
// 註：開光乃對玩家身上的穿靈「物件」呼叫 sword->setup_sword()/set("apply_weapon/...")，
//     方法呼叫於武器物件、本 NPC 毋須引 <weapon.h>；引之反與 F_VILLAGER 之 nomask
//     weight/encumbrance 衝突，致本檔編譯失敗、NPC 無法載入（已驗踩坑，故移除）。

int do_ask(string arg);

void create()
{
	set_name(HIY "少楊" NOR,
		({ "shaoyang", "shao yang", "consecrator", "少楊" }) );
	set("nickname", HIY "少楊" NOR);
	set_attr("int", 24);
	set_attr("wis", 26);
	set_attr("dex", 24);
	set_attr("con", 22);
	// 慣例：本 mudlib 之 villager 一律 set_race("human")/set_class——daemon 未必註冊他族。
	set_race("human");
	set_class("commoner");
	set_level(24);
	set_skill("unarmed", 40);
	set_skill("dodge", 40);
	set_skill("sword", 50);
	set_skill("force", 45);
	set_skill("literate", 40);

	set("gender", "male");
	set("age", 46);
	set("long",
		"一位青布短打、身形清健的中年漢子，盤膝坐在天靈山麓一方為爐\n"
		"火薰得發黑的青石上。他面前置著一座古樸的小銅爐，爐中三昧離\n"
		"火幽幽地燃著，明滅之間竟不見半縷柴煙。聽天靈山的老輩說，這\n"
		"人喚作少楊，是這天靈山麓守木一脈的後人——當年那柄斫斷京畿聖\n"
		"木殘節的聖劍『穿靈』，便是出自他這一脈的密藏。少楊世代精研\n"
		"以離火淬煉聖物之術：聖木為胎、玄鐵為鋒的穿靈，雖已是一等一\n"
		"的利器，卻仍未盡其性；唯有以那司南方離火的火神之力為引，將\n"
		"劍中那縷沉睡的清正靈氣徹底「開光」喚醒，這柄聖劍方能脫胎換\n"
		"骨、鋒芒大盛。他抬眼打量著你腰間的兵刃，似在掂量你可有那一\n"
		"段與離火之神的因緣。\n"
		"你或許可以問問他：ask shaoyang about 開光。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"少楊以鐵箸撥了撥銅爐中那簇幽幽的離火，火光在他臉上明滅不定。\n",
		"少楊望著爐中三昧真火，悠悠道：聖木為胎，玄鐵為鋒，這穿靈尚有一段未醒的靈性哪。\n",
		"少楊抬眼瞧了瞧過往的江湖客，淡淡道：手裡有穿靈、身上又得火神之證的，不妨讓少某替你開光。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !this_player()->query("quest/shaoyang_done") )
			do_chat((: command,
				"say 少楊瞧了瞧你腰間的兵刃，眼中精光一閃：那莫不是斫過聖木的穿靈？你若得過火神之證，少某可替它開光。(ask shaoyang about 開光)" :));
	}
}

// 玩家是否具「火神之證」：身上現有火神之印，或曾取得火神之印之旗標(印已嵌環亦認)。
private int has_fire_token(object who)
{
	if( !who ) return 0;
	if( present("seal of fire", who) || present("fire seal", who) )
		return 1;
	if( who->query("quest/main_canon6_seal_fire") == 1 )
		return 1;
	return 0;
}

// 同步開光：逕對玩家身上那把穿靈施作（提升三式傷害 + 賦予 apply_weapon 加成 + 升值改名）。
// 玩家此刻必在場（於 do_ask handler 內呼叫）。回傳 1 表已成功開光，0 表那把劍找不著。
private int consecrate_sword(object who)
{
	object sword;
	int was_equipped;
	string equipped_as;

	if( !who || environment(who) != environment() ) return 0;

	sword = present("chuanling", who);
	if( !sword || !sword->id("chuanling") ) return 0;

	// 已是開光版（補開光的穩健路徑會走到這；首次開光則否）——不重覆施作，回報成功即可。
	if( sword->query("consecrated") ) return 1;

	// 若玩家此刻正持此劍，先記下並卸下——令稍後新設的 apply_weapon/sword 能於重 wield 時生效。
	was_equipped = (sword->query("equipped") == "weapon/sword"
				||	sword->query("equipped") == "weapon/twohanded sword");
	if( was_equipped ) {
		equipped_as = sword->query("equipped");	// "weapon/sword" 或 "weapon/twohanded sword"
		sword->unequip();
	}

	// 1. 三式傷害全面提升（鏡 chuanling.c::setup_sword(4,15,110,8) → 開光後 5,16,130,8）。
	//    皆在 cmds/std/enchant.c::enchant_cap 之 sword(110/150/5)、twohanded(210/225/5) 內。
	sword->setup_sword(5, 16, 130, 8);

	// 2. 開光版手持時另賦屬性加成（鏡 slasher_sword.c::apply_weapon/sword；wield 時生效）。
	sword->set("apply_weapon/sword", ([
		"dex"       : 3,
		"spi"       : 10,
		"attack"    : 25,
		"parry"     : 15,
	]) );

	// 3. 升值、改名為開光版、留可驗證痕跡。
	sword->set("value", 100);
	sword->set("consecrated", 1);
	sword->set_name(HIR "穿靈" HIY "(開光)" NOR,
		({ "chuanling", "piercing sword", "sword" }) );
	sword->set("long",
		"這便是那柄斫斷京畿聖木殘節的聖劍『穿靈』了——只是經少楊以三昧\n"
		"離火開光之後，已是脫胎換骨。劍身青中泛玄，那道道宛若年輪的細\n"
		"密紋路間，原本只是緩緩漫出的一縷清正靈氣，此刻竟被離火徹底喚\n"
		"醒，化作一層流轉不息的赤金火芒，沿著劍脊的木紋遊走，溫潤如玉\n"
		"而又灼灼生輝。叩之金石之鳴更為清越，握之則覺一股沉雄而磅礡的\n"
		"靈氣自劍中直透臂膀——聖木之靈與火神之力，自此在這柄穿靈之中合\n"
		"而為一。開光之後的穿靈，鋒芒遠勝昔日，已是當之無愧的一等聖兵。\n");

	// 若先前正持此劍，重新 wield 回原本的持法——令新設的 apply_weapon 加成即時附身、可驗。
	if( was_equipped ) {
		if( equipped_as == "weapon/twohanded sword" )
			sword->wield("twohanded sword");
		else
			sword->wield("sword");
	}

	message_vision(
		HIR "少楊將$N手中(或身上)的穿靈鄭重接過，橫置於那座古樸的小銅爐之上。"
		"爐中三昧離火驟然騰起，將劍身整個吞沒——青芒與赤金火芒在劍脊的年輪紋\n"
		"路間激烈交纏、奔流，許久，少楊雙手一振，將那柄火芒流轉的穿靈遞還$N。"
		"這柄聖劍，自此開光！\n" NOR,
		who);

	who->gain_score("emprise", 200);
	who->gain_score("reputation", 100);
	who->gain_score("explorer fame", 80);
	return 1;
}

int do_ask(string arg)
{
	object me = this_player();
	object sword;
	int q;

	if( !arg || (arg != "shaoyang about 開光"
		&&   arg != "shaoyang about 穿靈"
		&&   arg != "shaoyang about 開光穿靈"
		&&   arg != "shaoyang about 火神之印"
		&&   arg != "shaoyang about 火神"
		&&   arg != "shaoyang about 少楊"
		&&   arg != "shao yang about 開光"
		&&   arg != "consecrator about 開光"
		&&   arg != "shaoyang about consecrate"
		&&   arg != "shaoyang about chuanling") )
		return notify_fail("你想問少楊甚麼？（試試 ask shaoyang about 開光）\n");

	// runtime 鐵則 #11：do_ask 須 guard 戰鬥/對白中。
	if( is_fighting() || is_chatting() )
		return notify_fail("少楊正凝神撥弄著爐中那簇離火，沒空理你。\n");

	q = me->query("quest/shaoyang_done");

	// 已開光過：純劇情對白，不重發（防重領）。
	if( q >= 1 ) {
		// 穩健性：旗標在、身上那把穿靈卻未開光（遺失原劍、另得一把新的之類）-> 補開光一次，
		//   不重置進度。consecrate_sword 對已開光之劍會直接回 1、不重覆施作。
		sword = present("chuanling", me);
		if( sword && sword->id("chuanling") && !sword->query("consecrated") ) {
			// 須仍具火神之證方補開光——免有人棄印後憑舊旗標反覆刷新劍。
			if( !has_fire_token(me) ) {
				do_chat((: command,
					"say 少楊端詳著你手中這把未開光的穿靈，搖頭道：你身上已無火神之證，少某縱有心，也引不動那離火了。" :));
				return 1;
			}
			// 同步補開光：consecrate_sword 為即時施作（玩家此刻必在場）；do_chat 只留氣氛對白。
			consecrate_sword(me);
			do_chat((: command,
				"say 少楊瞧了瞧你手中這把竟未開光的穿靈，略一沉吟，便又將它架上銅爐，以離火重新替你開光一回——這回可要好生收著了。" :));
			return 1;
		}
		do_chat(({
			(: command, "say 少楊瞧了瞧你那柄火芒流轉的開光穿靈，撫鬚微笑：聖木之靈與火神之力既已合一，此劍已盡其性，再開也是徒勞了。" :),
			(: command, "say 少楊撥了撥爐中離火，悠悠道：這天靈山麓守木一脈，世代盼的便是穿靈重光的這一日。少俠持此聖兵，好生降魔衛道去罷。" :),
		}));
		return 1;
	}

	// 首次：須手持/身負穿靈 + 具火神之證，缺一不可。
	sword = present("chuanling", me);
	if( !sword || !sword->id("chuanling") )
		return notify_fail("少楊搖頭道：你身上並無那柄斫過聖木的穿靈，少某無從替你開光。\n");

	if( !has_fire_token(me) )
		return notify_fail("少楊端詳著你手中的穿靈，搖頭道：開光穿靈，須借那司南方離火的火神之力為引。你身上既無火神之印、亦無曾得火神之證的徵象，這離火，少某引不動哪。\n");

	// 同步開光、即記旗標（consecrate_sword 為即時施作，玩家此刻必在場）。
	// 先施作、後記旗標——免於回呼前離場致劍沒開光、旗標卻記完成而卡關。
	if( !consecrate_sword(me) ) {
		// 理論上不致走到此（上面已驗 present）；保險回報，不記旗標。
		return notify_fail("少楊伸手一探，那柄穿靈卻不在你身上了——你且持劍再來。\n");
	}
	me->set("quest/shaoyang_done", 1);
	do_chat(({
		(: command, "say 少楊定定地看了你良久，又看了看你手中這柄半木半鐵的穿靈，緩緩道：好。你既斫過聖木、又得過火神之證，與這柄聖劍、與這離火，俱是有緣。" :),
		(: command, "say 少楊道：穿靈以聖木心節為胎、玄鐵為鋒，本是一等利器，卻有一縷清正靈氣沉睡劍中，未得喚醒。少某這一脈守木世代所習的，便是以那司南離火為引，將劍中沉睡的靈性徹底開光。" :),
		(: command, "say 少楊將開光後火芒流轉的穿靈鄭重交還你手中，叮囑道：開光之後的穿靈，鋒芒遠勝昔日；你 wield 持之，但覺那股沉雄靈氣護體生威。持此聖兵，去了結那天下的禍根罷。" :),
	}));
	return 1;
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品（尤不收火神之印、不收穿靈）。
int accept_object(object who, object ob)
{
	if( ob->id("seal of fire") || ob->id("fire seal") ) {
		do_chat((: command,
			"say 少楊將你遞來的火神之印輕輕推回：這印另有大用，須嵌那星光環成就終局，少某斷不能收。開光只借它作個火神之證，你帶在身上便是。" :));
		return 0;
	}
	if( ob->id("chuanling") ) {
		do_chat((: command,
			"say 少楊擺了擺手，將你遞來的穿靈推回：開光須你親自持劍，少某當面替你引離火施為，這劍可不能離了你的手。(ask shaoyang about 開光)" :));
		return 0;
	}
	do_chat((: command,
		"say 少楊瞧了瞧你遞來的物事，搖了搖頭，並不肯接。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 少楊往後退開一步，沉聲道：少某守木開光的一脈傳人，與你無冤無仇，何苦動這刀兵？" :));
	return 0;
}

int accept_kill()
{
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
