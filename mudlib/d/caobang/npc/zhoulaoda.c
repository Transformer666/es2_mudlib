// zhoulaoda.c -- 周老大：漕運碼頭的漕幫攬頭（管事）。漕幫任務「起點」的發籌人。
//
// 【設定 / canon】docs 01-世界觀與劇情/05-主線任務與NPC.md L103
//   「阿邦、阿義 @ 羿水河邊渡船頭 → 漕幫任務起點」。渡口的氣氛船工阿邦、阿義
//   （見 d/caobang/npc/abang.c、ayi.c，二者為 A-gated 純氣氛 NPC，不接任務）只
//   負責領玩家認識漕幫、指路；真正「發籌入夥、開漕幫這條線」的管事，是漕運碼頭
//   上這位攬頭周老大。玩家循市集乞丐（漕幫任務「起源」線索人，見 beggar.c）的指
//   點來尋他，ask 起漕幫差事，周老大便發給一枚漕幫竹籌、開 quest/caobang_start。
//
// 【任務分工】本檔做的是漕幫這條線的「起點」：
//     - 發信物：漕幫竹籌(/d/caobang/npc/obj/caobang_tally)。
//     - 開旗標：玩家身上 quest/caobang_start = 1（下游 NPC 認此旗標續接）。
//   起點之後的「四鬼問環」整條主線支線，繫於另一樁尚未拍板的主線抉擇(決策 A)，
//   本檔【不】實作、亦【不】讀寫任何 四鬼 / 旋芒 / main_omen / 主線 旗標——
//   只把玩家領進漕幫、指路往禮堂尋宋安江、江隕（canon 角色點題為止）。
//
// 【同步交付】（本專案頭號 bug class 之防範）：發籌一律在 do_ask handler 內直接
//   new()+move() 給玩家、且在設完成旗標之前——絕不放進延遲的 do_chat/closure
//   (玩家中途離場會「物沒了、旗標卻記完成」soft-lock)。do_chat 只擺氣氛對白。
//
// 【runtime 鐵則】本 NPC 有 do_ask / init，**不** replace_program（#11）。
//   do_ask 入口以 is_fighting()/is_chatting() 守衛；旗標/給物寫在 do_chat 之前（#10）。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIY "周老大" NOR, ({ "zhoulaoda", "zhou laoda", "foreman zhou", "foreman", "周老大", "老大", "攬頭" }) );
	set("nickname", HIY "周老大" NOR);
	set_race("human");
	set_class("commoner");
	set_level(18);
	set_attr("str", 26);
	set_attr("con", 24);
	set_skill("unarmed", 30);
	set_skill("dodge", 26);
	set_skill("force", 24);

	set("age", 49);
	set("gender", "male");
	set("long",
		"漕運碼頭上掌事的攬頭，幫眾都喚他一聲周老大。生得身量魁\n"
		"梧，一張被河風日頭烤得黧黑的方臉，頷下一部短而硬的絡腮鬍\n"
		"子，一雙手掌寬厚，骨節粗大，全是經年握篙拽纜磨出來的。他腰\n"
		"裡掛著一桿點貨的竹籌與一串分舵的銅牌，往埠頭上一站，扯開那\n"
		"條過慣了風浪的嗓子吆喝起來，滿碼頭起卸糧包的船工便齊齊應和\n"
		"著號子。他在這運河上跑了大半輩子，自最底下的扛包小工，一篙\n"
		"一纜熬成了京畿渡口管事的攬頭，凡新入夥的、受幫裡差遣辦事\n"
		"的，都得先到他這兒來領一枚記認的竹籌。\n"
		"你或許可以問問他：ask zhoulaoda about 差事。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"周老大握著那桿竹籌，一包一包地替過秤的糧包記著數，嘴裡唱著斤兩。\n",
		"周老大扯開嗓子喝了一聲號子，滿碼頭的船工便齊齊應和，扛著糧包的腳步都齊整了幾分。\n",
		"周老大抹了把汗，瞇眼瞧著一河解纜東去的漕船，沉聲道：這天下的口糧，可都壓在咱這幫跑船人的肩上哪。\n",
	}));
	setup();
	carry_money("coin", 50);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 同步發籌：直接 new()+move() 給玩家。先試 move 到玩家身上，
// 不成（負重等）則落在環境地上——絕不靜默丟失。
private void give_tally(object who)
{
	object tally;

	if( !who || environment(who) != environment() ) return;

	tally = new("/d/caobang/npc/obj/caobang_tally");
	if( !tally->move(who) ) tally->move(environment());

	message_vision(
		"周老大自腰間解下一枚烙著「漕」字的竹籌，在掌心掂了掂，鄭重地塞到$N手裡，"
		"在$N肩上重重一拍。\n",
		who);

	who->gain_score("emprise", 80);
	who->gain_score("reputation", 40);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg )
		return notify_fail("你想跟這位攬頭打聽甚麼？（試試 ask zhoulaoda about 差事）\n");

	// 漕幫差事 / 起點：發籌入夥、開 quest/caobang_start。
	if( arg == "zhoulaoda about 差事"
	||  arg == "zhoulaoda about 竹籌"
	||  arg == "zhoulaoda about 漕幫"
	||  arg == "zhoulaoda about 入夥"
	||  arg == "zhoulaoda about tally"
	||  arg == "zhoulaoda about task"
	||  arg == "zhou laoda about 差事"
	||  arg == "foreman about 差事" ) {

		if( is_fighting() || is_chatting() )
			return notify_fail("周老大正扯著嗓子指揮起卸糧包，一時顧不上你。\n");

		q = me->query("quest/caobang_start");

		// 已領過竹籌：純劇情對白，不重發（防重領）。
		if( q >= 1 ) {
			// 穩健性：旗標在、竹籌卻不在身上（遺失/賣掉）-> 補發一枚，不重置進度。
			if( !present("caobang tally", me) ) {
				// 同步補發：give_tally 直接 new+move（玩家此刻必在場）；do_chat 只留氣氛對白。
				// 不可把 give_tally 塞進 do_chat 陣列——那會延後數心跳異步執行，違同步交付契約。
				give_tally(me);
				do_chat((: command, "say 你那竹籌怎沒了？跑船的人，記認可丟不得！罷了，再給你一枚，這回揣牢實了——往北禮堂尋宋爺、江爺去。" :));
				return 1;
			}
			do_chat(({
				(: command, "say 籌子既已給了你，便是咱漕幫的人了。揣著它往北穿過漕幫巷，到禮堂去——分舵主宋安江宋爺、還有咱幫裡那位老前輩江隕江爺，都在禮堂裡頭，憑這籌子自有人替你引見。" :),
				(: command, "say 跑船的圖個和氣生財，咱漕幫在江湖上從不與人結仇——你既入了夥，這份規矩可得記牢。去罷，禮堂裡有你的去處。" :),
			}));
			return 1;
		}

		// 首次：同步發籌、即記旗標（give_tally 為直接 new+move，玩家此刻必在場）。
		// 先給物、後記旗標——免於回呼前離場致籌沒領、旗標卻記完成而卡關。
		give_tally(me);
		me->set("quest/caobang_start", 1);
		do_chat(({
			(: command, "say 哦？是那碼頭上討飯的老花子指你來尋我的？嘿，那老貨眼還毒——他年輕時也是這運河上跑船的漕幫舊人，看人最是準。他既說你是塊跑船的料、肯為人奔走，那我便信他一回。" :),
			(: command, "say 咱漕幫管著這天下的漕運，幫眾數十萬，沿著大運河南北分舵林立。你既有心入夥、替幫裡辦事，這枚竹籌你先收著——這是咱漕幫的記認，憑它沿河各處的弟兄便認得你是自己人。" :),
			(: command, "say 揣好了籌子，往北穿過漕幫巷，到禮堂裡去：分舵主宋安江宋爺管著京畿這一處幫務，咱幫裡那位老前輩江隕江爺也在禮堂裡頭。憑這籌子，自有人替你引見——往後漕幫這條道，便看你自個兒的造化了。去罷！" :),
		}));
		return 1;
	}

	// 指路 / 點題 canon 角色（純氣氛，不接任務、不設旗標）。
	if( arg == "zhoulaoda about 江隕"
	||  arg == "zhoulaoda about 江爺"
	||  arg == "zhoulaoda about jiangyun"
	||  arg == "zhoulaoda about 宋安江"
	||  arg == "zhoulaoda about 宋爺"
	||  arg == "zhoulaoda about songanjiang"
	||  arg == "zhoulaoda about 禮堂"
	||  arg == "zhoulaoda about 乞丐" ) {
		do_chat(({
			(: command, "say 宋爺就是禮堂的分舵主宋安江，管著咱京畿這一處的大小幫務，人最是仗義爽利。江爺嘛——江隕老爺子，輩分高得很，也在禮堂裡頭。要尋他二位，往北穿過漕幫巷便是。" :),
			(: command, "say 你說那碼頭上討飯的老花子？他是咱漕幫的舊人了，落魄了仍守在這渡口邊。你若還沒跟我領籌子，便是他指的路罷？(ask zhoulaoda about 差事)" :),
		}));
		return 1;
	}

	return notify_fail("周老大瞇眼打量你一回：客官問這做甚？要尋漕幫的差事，便直說。（試試 ask zhoulaoda about 差事）\n");
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品（尤不收回漕幫竹籌）。
int accept_object(object who, object ob)
{
	if( ob->id("caobang tally") ) {
		do_chat((: command,
			"say 籌子既給了你，便是你的記認，收回去！這東西在你身上，沿河的弟兄才認得你。" :));
		return 0;
	}
	do_chat((: command,
		"say 你這是做甚？咱攬頭管的是貨包號子，可不興收人東西，自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 哎！使不得！咱漕幫的碼頭，是和氣做生意的地界，動甚麼粗！" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
