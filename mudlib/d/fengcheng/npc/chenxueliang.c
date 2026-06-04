// chenxueliang.c -- 陳學亮：風城劍甲門傳人，為持「炫芒」而又得火神之證的少俠
//                   施那「開光強化之術」，將劍中沉睡的剛烈劍意徹底喚醒的開光師。
//
//   (canon：docs 01-世界觀與劇情/05-主線任務與NPC.md L119
//    「陳學亮 (Chen xue liang) @ 風城 → 開光炫芒（需火神之眼）；劍甲門傳人，
//     授強化之術」)
//
// 故事背景：
//   風城城北一脈劍甲門，世傳「以劍為甲、以攻代守」的剛猛劍術，亦傳一柄門中
//   信物利劍——炫芒(d/fengcheng/npc/obj/xuanmang.c)。陳學亮是劍甲門這一代傳
//   人，盤桓於風城，見有緣的少俠便授以炫芒，更深研一門「開光強化之術」：以
//   離火為引，將炫芒劍中那一縷沉睡的剛烈劍意徹底喚醒，令這趁手利器脫胎換骨。
//   docs 原訂以「火神之眼」為開光門檻；然「火神之眼」非現開源樣本之物，玩家
//   未必有得。本實作鏡 d/tianling/npc/shaoyang.c 之開光範式，改 gate 於玩家
//   確曾於第六章四神任務取得火神之印(火神乃司南方離火、三昧真火之神，正合
//   「以離火開光」之設定)——
//
//   **採用之 gate（雙保險，二者居一即可，且不奪不耗任何玩家物事）**：
//     (a) 玩家身上現有『火神之印』(seal of fire/fire seal，d/longdao/npc/obj/
//         seal_fire.c)；或
//     (b) 玩家已具旗標 quest/main_canon6_seal_fire == 1（曾取得火神之印；之後
//         縱已將其嵌入星光環 d/chimei/npc/obj/starlight_ring 而印已 destruct，
//         仍認得此功業）。
//   選 (b) 為輔，是因火神之印一經嵌入星光環即 destruct——只認 (a) 會把已推進
//   至星光環階段的玩家反鎖在外。二者居一，既忠於「需火神(離火)之力」的 docs
//   旨，又不致 soft-lock。**火神之印一概不收不耗**——它另須嵌入星光環成就終
//   局，開光僅借其「離火之證」為憑。
//
// 服務流程（旗標存玩家身上：quest/chenxueliang_done）：
//   1. 若玩家身上無炫芒——劍甲門傳人本就授劍，先同步授以一柄炫芒(new+move)；
//   2. 玩家具火神之證——逕對其身上那把炫芒施「開光強化之術」：
//        a. 以 setup_sword(5,16,130,8) 重設三式傷害(單手/副手/雙手)，較原
//           setup_sword(3,16,70,5) 全面提升乘數/bonus/roll，皆在 cmds/std/
//           enchant.c::enchant_cap 之 sword(110/150/5)、twohanded(210/225/5)
//           上限之內；
//        b. set("apply_weapon/sword", ([...]))：開光版炫芒手持時另賦
//           dex/str/attack/parry 加成(鏡 d/snow/npc/obj/slasher_sword.c 之
//           apply_weapon/sword；wield 時生效)；
//        c. 升 value、改名為「開光版」、set("consecrated",1) 留可驗證痕跡。
//      無火神之證者——授劍但不開光，只勸其去尋火神之證。
//   3. 已開光(quest/chenxueliang_done >= 1)：純劇情對白，不重發(防重領)。
//
// 同步交付 / 防重複（本專案頭號 bug class 之防範）：授劍、開光一律在 do_ask
//   handler 內「即時」對玩家施作、且在設完成旗標之前——絕不放進延遲的
//   do_chat/closure。do_chat 只擺氣氛對白。quest/chenxueliang_done 防重複開光
//   (已開光者再問只給純劇情)。穩健性：旗標已記但身上那把炫芒竟未開光(遺失原
//   劍另得新劍之類)，則補開光一次、不重置進度。
//
// runtime 鐵則：本 NPC 有 do_ask，**不** replace_program(#11)；is_fighting/
//   is_chatting guard 於 do_ask(#11)。全程無 ::die()/destruct()，旗標/訊息皆
//   在施作之後、return 之前寫妥(#10 不適用，然仍依其旨：先施作→後記旗標→再
//   對白)。

#include <ansi.h>
#include <npc.h>
// 註：開光乃對玩家身上的炫芒「物件」呼叫 sword->setup_sword()/set("apply_weapon/...")，
//     方法呼叫於武器物件、本 NPC 毋須引 <weapon.h>；引之反與 F_VILLAGER 之 nomask
//     weight/encumbrance 衝突致本檔編譯失敗、NPC 無法載入（承 shaoyang.c 同坑，故移除）。

#define XUANMANG_OB	"/d/fengcheng/npc/obj/xuanmang"

int do_ask(string arg);

void create()
{
	set_name(HIY "陳學亮" NOR,
		({ "chen xue liang", "chenxueliang", "chen", "consecrator", "陳學亮" }) );
	set("nickname", HIY "陳學亮" NOR);
	set_attr("int", 23);
	set_attr("wis", 24);
	set_attr("dex", 26);
	set_attr("con", 24);
	// 慣例：本 mudlib 之 villager 一律 set_race("human")/set_class——daemon 未必註冊他族。
	set_race("human");
	set_class("commoner");
	set_level(25);
	set_skill("unarmed", 45);
	set_skill("dodge", 45);
	set_skill("sword", 60);
	set_skill("force", 48);
	set_skill("parry", 50);
	set_skill("literate", 38);

	set("gender", "male");
	set("age", 42);
	set("long",
		"一位青衫負劍、身形挺拔的中年劍客，按劍立於風城聚風茶樓的一\n"
		"角，目光沉靜而銳利，自有一股以攻代守的凜然劍氣。聽風城的老\n"
		"輩說，這人喚作陳學亮，是城北劍甲門這一代的傳人。劍甲門世傳\n"
		"『以劍為甲、以攻代守』的剛猛劍術，門中更有一柄一脈相傳的利\n"
		"劍『炫芒』——劍光一展，炫人耳目，最是剛烈難當。陳學亮見有緣\n"
		"的少俠，便肯授以炫芒，更深研得一門『開光強化之術』：唯有借\n"
		"那司南方離火的火神之力為引，將炫芒劍中那一縷沉睡的剛烈劍意\n"
		"徹底『開光』喚醒，這柄利劍方能脫胎換骨、鋒芒大盛。他打量著\n"
		"你按劍的手，似在掂量你可有那一段與離火之神的因緣。\n"
		"你或許可以問問他：ask chen about 炫芒。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"陳學亮按劍而立，目光掃過茶樓中往來的江湖客，眼中精光一閃。\n",
		"陳學亮輕撫腰間劍鞘，沉聲道：劍甲門以劍為甲、以攻代守，這炫芒尚有一段未醒的劍意哪。\n",
		"陳學亮淡淡道：手裡有炫芒、身上又得火神之證的，不妨讓陳某替你開光強化。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !this_player()->query("quest/chenxueliang_done") )
			do_chat((: command,
				"say 陳學亮瞧了瞧你按劍的手，沉聲道：可是要學劍甲門的劍法？陳某可授你一柄炫芒；你若得過火神之證，更可替它開光強化。(ask chen about 炫芒)" :));
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

// 取玩家身上那把炫芒（id 精確比對；不會誤認 d/caobang 之旋芒"xuanmang"）。
private object find_xuanmang(object who)
{
	object ob;
	if( !who ) return 0;
	ob = present("xuanmang blade", who);
	if( !ob ) ob = present("炫芒", who);
	if( ob && (ob->id("xuanmang blade") || ob->id("炫芒")) )
		return ob;
	return 0;
}

// 同步授劍：劍甲門傳人本就授劍——逕 new+move 一柄炫芒給玩家。
// 先試 move 到玩家身上，不成（負重等）則落在環境地上——絕不靜默丟失。
private object give_xuanmang(object who)
{
	object sword;

	if( !who || environment(who) != environment() ) return 0;

	sword = new(XUANMANG_OB);
	if( !sword->move(who) ) sword->move(environment());

	message_vision(
		HIC "陳學亮自背上劍囊中抽出一柄青白瑩瑩的長劍，劍光一閃，炫人耳"
		"目。他將這柄劍甲門信物兵刃『炫芒』鄭重地交到$N手中。\n" NOR,
		who);
	return sword;
}

// 同步開光強化：逕對玩家身上那把炫芒施作（提升三式傷害 + 賦予 apply_weapon
// 加成 + 升值改名）。玩家此刻必在場（於 do_ask handler 內呼叫）。
// 回傳 1 表已成功開光，0 表那把劍找不著。
private int consecrate_sword(object who)
{
	object sword;
	int was_equipped;
	string equipped_as;

	if( !who || environment(who) != environment() ) return 0;

	sword = find_xuanmang(who);
	if( !sword ) return 0;

	// 已是開光版（補開光的穩健路徑會走到這；首次開光則否）——不重覆施作，回報成功即可。
	if( sword->query("consecrated") ) return 1;

	// 若玩家此刻正持此劍，先記下並卸下——令稍後新設的 apply_weapon/sword 能於重 wield 時生效。
	was_equipped = (sword->query("equipped") == "weapon/sword"
				||	sword->query("equipped") == "weapon/twohanded sword");
	if( was_equipped ) {
		equipped_as = sword->query("equipped");	// "weapon/sword" 或 "weapon/twohanded sword"
		sword->unequip();
	}

	// 1. 三式傷害全面提升（鏡 xuanmang.c::setup_sword(3,16,70,5) → 開光後 5,16,130,8）。
	//    皆在 cmds/std/enchant.c::enchant_cap 之 sword(110/150/5)、twohanded(210/225/5) 內。
	sword->setup_sword(5, 16, 130, 8);

	// 2. 開光版手持時另賦屬性加成（鏡 slasher_sword.c::apply_weapon/sword；wield 時生效）。
	sword->set("apply_weapon/sword", ([
		"dex"       : 3,
		"str"       : 5,
		"attack"    : 25,
		"parry"     : 15,
	]) );

	// 3. 升值、改名為開光版、留可驗證痕跡。
	sword->set("value", 100);
	sword->set("consecrated", 1);
	sword->set_name(HIR "炫芒" HIY "(開光)" NOR,
		({ "xuanmang blade", "炫芒", "dazzling blade", "sword" }) );
	sword->set("long",
		"這便是風城劍甲門一脈相傳的利劍『炫芒』了——只是經陳學亮以離\n"
		"火開光強化之後，已是脫胎換骨。劍身青白之中泛起一層赤金的火\n"
		"芒，那道道宛若流光的細紋之間，原本只是沉睡的一縷剛烈劍意，\n"
		"此刻竟被離火徹底喚醒，化作一層流轉不息的炫目光華，沿著劍脊\n"
		"游走，奪人神魄。一經抖開，劍光如潑灑的赤金碎芒漫天炫舞，較\n"
		"昔日更盛十倍——以劍為甲、以攻代守的劍甲門劍意，自此在這柄炫\n"
		"芒之中徹底圓滿。開光之後的炫芒，鋒芒遠勝昔日，已是當之無愧\n"
		"的一等利劍。\n");

	// 若先前正持此劍，重新 wield 回原本的持法——令新設的 apply_weapon 加成即時附身、可驗。
	if( was_equipped ) {
		if( equipped_as == "weapon/twohanded sword" )
			sword->wield("twohanded sword");
		else
			sword->wield("sword");
	}

	message_vision(
		HIR "陳學亮將$N手中(或身上)的炫芒鄭重接過，橫於身前。他屈指一彈"
		"劍脊，口中低喝，引那離火之力灌入劍中——青白劍光與赤金火芒在劍\n"
		"脊的流光紋路間激烈交纏、奔湧，許久，陳學亮長劍一振，將那柄火芒"
		"炫舞的炫芒遞還$N。這柄利劍，自此開光強化！\n" NOR,
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

	if( !arg || (arg != "chen about 炫芒"
		&&   arg != "chen about 開光"
		&&   arg != "chen about 開光炫芒"
		&&   arg != "chen about 強化"
		&&   arg != "chen about 劍甲門"
		&&   arg != "chen about 火神之印"
		&&   arg != "chen about 火神"
		&&   arg != "chen about 陳學亮"
		&&   arg != "chenxueliang about 炫芒"
		&&   arg != "chen xue liang about 炫芒"
		&&   arg != "consecrator about 炫芒"
		&&   arg != "chen about consecrate"
		&&   arg != "chen about xuanmang") )
		return notify_fail("你想問陳學亮甚麼？（試試 ask chen about 炫芒）\n");

	// runtime 鐵則 #11：do_ask 須 guard 戰鬥/對白中。
	if( is_fighting() || is_chatting() )
		return notify_fail("陳學亮正按劍凝神，似在參詳一路劍法，沒空理你。\n");

	q = me->query("quest/chenxueliang_done");

	// 已開光過：純劇情對白，不重發（防重領）。
	if( q >= 1 ) {
		// 穩健性：旗標在、身上那把炫芒卻未開光（遺失原劍、另得一把新的之類）-> 補開光一次，
		//   不重置進度。consecrate_sword 對已開光之劍會直接回 1、不重覆施作。
		sword = find_xuanmang(me);
		if( sword && !sword->query("consecrated") ) {
			// 須仍具火神之證方補開光——免有人棄印後憑舊旗標反覆刷新劍。
			if( !has_fire_token(me) ) {
				do_chat((: command,
					"say 陳學亮端詳著你手中這把未開光的炫芒，搖頭道：你身上已無火神之證，陳某縱有心，也引不動那離火了。" :));
				return 1;
			}
			// 同步補開光：consecrate_sword 為即時施作（玩家此刻必在場）；do_chat 只留氣氛對白。
			consecrate_sword(me);
			do_chat((: command,
				"say 陳學亮瞧了瞧你手中這把竟未開光的炫芒，略一沉吟，便又引離火重新替你開光強化一回——這回可要好生收著了。" :));
			return 1;
		}
		do_chat(({
			(: command, "say 陳學亮瞧了瞧你那柄火芒炫舞的開光炫芒，撫劍微笑：剛烈劍意既已喚醒，此劍已盡其性，再開也是徒勞了。" :),
			(: command, "say 陳學亮按劍而立，沉聲道：劍甲門以攻代守，盼的便是炫芒重光的這一日。少俠持此利劍，好生降魔衛道去罷。" :),
		}));
		return 1;
	}

	// 首次：若玩家身上無炫芒，劍甲門傳人本就授劍——同步授以一柄炫芒。
	sword = find_xuanmang(me);
	if( !sword ) {
		sword = give_xuanmang(me);
		if( !sword || environment(sword) != me ) {
			// 授劍落地（負重等）——提示玩家拾起再來，不誤判、不記旗標。
			do_chat((: command,
				"say 陳學亮道：這柄炫芒你似拿不穩，且拾起、收妥了再來尋陳某開光罷。(ask chen about 炫芒)" :));
			return 1;
		}
	}

	// 須具火神之證方可開光；無則授劍而不開光，勸其去尋火神之證。
	if( !has_fire_token(me) ) {
		do_chat((: command,
			"say 陳學亮端詳著你手中的炫芒，搖頭道：開光炫芒，須借那司南方離火的火神之力為引。你身上既無火神之印、亦無曾得火神之證的徵象，這離火，陳某引不動哪。你且去尋得火神之證，再來尋我開光。" :));
		return 1;
	}

	// 同步開光、即記旗標（consecrate_sword 為即時施作，玩家此刻必在場）。
	// 先施作、後記旗標——免於回呼前離場致劍沒開光、旗標卻記完成而卡關。
	if( !consecrate_sword(me) ) {
		// 理論上不致走到此（上面已確保有炫芒）；保險回報，不記旗標。
		return notify_fail("陳學亮伸手一探，那柄炫芒卻不在你身上了——你且持劍再來。\n");
	}
	me->set("quest/chenxueliang_done", 1);
	do_chat(({
		(: command, "say 陳學亮定定地看了你良久，又看了看你手中這柄青白瑩瑩的炫芒，緩緩道：好。你既持得劍甲門的炫芒、又得過火神之證，與這柄利劍、與這離火，俱是有緣。" :),
		(: command, "say 陳學亮道：炫芒劍光雖盛，劍中卻有一縷剛烈劍意沉睡其間，未得喚醒。陳某這劍甲門所習的開光強化之術，便是以那司南離火為引，將劍中沉睡的劍意徹底喚醒、令利器脫胎換骨。" :),
		(: command, "say 陳學亮將開光後火芒炫舞的炫芒鄭重交還你手中，叮囑道：開光之後的炫芒，鋒芒遠勝昔日；你 wield 持之，但覺那股剛烈劍意護體生威。以劍為甲、以攻代守，持此利劍，去了結那天下的禍根罷。" :),
	}));
	return 1;
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品（尤不收火神之印、不收炫芒）。
int accept_object(object who, object ob)
{
	if( ob->id("seal of fire") || ob->id("fire seal") ) {
		do_chat((: command,
			"say 陳學亮將你遞來的火神之印輕輕推回：這印另有大用，須嵌那星光環成就終局，陳某斷不能收。開光只借它作個火神之證，你帶在身上便是。" :));
		return 0;
	}
	if( ob->id("xuanmang blade") || ob->id("炫芒") ) {
		do_chat((: command,
			"say 陳學亮擺了擺手，將你遞來的炫芒推回：開光須你親自持劍，陳某當面替你引離火施為，這劍可不能離了你的手。(ask chen about 炫芒)" :));
		return 0;
	}
	do_chat((: command,
		"say 陳學亮瞧了瞧你遞來的物事，搖了搖頭，並不肯接。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 陳學亮往後退開一步，沉聲道：陳某劍甲門開光授劍的傳人，與你無冤無仇，何苦動這刀兵？" :));
	return 0;
}

int accept_kill()
{
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
