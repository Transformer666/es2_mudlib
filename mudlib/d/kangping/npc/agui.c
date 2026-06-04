// agui.c -- 康平村心曬場邊的老村正阿桂；
//           兼康平村非戰鬥支線「老安懶的毛筆」的授物人。
//
// 來歷（承 docs/01-世界觀與劇情/05-主線任務與NPC.md：阿桂 @ 康平村 → 給老安懶的毛筆，
//   康平村村民、贈老安懶的毛筆〔書生用筆／信物〕）：
//   阿桂是康平村土生土長的老村民﹐昔年與村裡那位窮酸豁達的老書生『老安懶』是相識
//   數十年的老相好。老安懶生平替合村寫狀記賬、教蒙童識字﹐過世前把隨身的一管舊毛
//   筆託與阿桂﹐囑他日後遇著個讀得進書、走得遠路的有心人﹐便把這筆並一句寄語一併交
//   付。阿桂便把這管筆貼身收著﹐成日在曬場邊﹐留心打量過往的行旅生客。
//
// 支線性質：純莊稼村子的人情風味支線﹐沒有戰鬥、不需殺任何東西、不靠任何運氣骰子——
//   一路問著、應著、領了筆即成﹐必定可完成。本支線自成一套旗標（quest/sq_agui）﹐
//   不讀、不動任何別的任務旗標﹐純加深康平村的書生情分（書生一脈不結仇﹐見 docs
//   04-玩家社群與文化/02-結仇與PvP.md）。
//
// 流程（旗標存在玩家身上）：
//   未領 (quest/sq_agui==0) : 玩家 ask agui about 老安懶（或 毛筆／老安懶的毛筆／筆…）
//       -> 阿桂道出老安懶託筆之事﹐認玩家是個讀得進書、走得遠路的有心人﹐
//          同步 new + move 把「老安懶的毛筆」交與玩家﹐記 quest/sq_agui = 1。
//   已領 (quest/sq_agui>=1) : 不再給賞﹐純氣氛收尾閒談。
//       若筆失落（旗標在、筆不在身且不在身畔地上）則補發一管﹐進度不重置﹐免卡關。
//
// 交付採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
//   move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上﹐不走會因玩家
//   走開而落空的延遲回呼（與 d/wenguo brushmaker、d/kangping keeper 一致）。
// 不 replace_program：本 NPC 有 do_ask﹐須保留 init/add_action。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("阿桂", ({ "agui", "old agui", "agui" }) );
	set("nickname", "阿桂");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 64);
	set("gender", "male");
	set("long",
		"這位是康平村土生土長的老村民阿桂﹐生得清瘦慈和﹐臉膛\n"
		"教莊稼日頭曬成了深褐色﹐一笑滿臉的皺紋便都舒展開來。他常\n"
		"在曬場邊的老棗樹下歇晌﹐手裡卻不像旁的莊稼漢攥著旱煙袋﹐\n"
		"而是貼身藏著一管舊毛筆﹐時不時取出來就著天光摩挲端詳﹐眼\n"
		"神裡透著一縷追懷故人的悵惘。村人說﹐阿桂與早年村裡那位窮\n"
		"書生『老安懶』是數十年的老相好﹐老安懶過世前﹐把一樁念想\n"
		"託付給了他。得閒也可問問他﹕ask agui about 老安懶。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"阿桂自懷裡摸出那管舊毛筆﹐就著天光端詳半晌﹐又輕輕揣回懷中﹐悵悵地嘆了口氣。\n",
		"阿桂瞇眼望著曬場上往來的行旅生客﹐似在留心打量﹐口中喃喃道﹕老安懶啊老安懶﹐你託我尋的那個人﹐幾時纔來哩 ...\n",
		"阿桂捋著花白的鬍子和過路人道﹕咱康平村出過一位老書生﹐替合村寫了一輩子的狀子賬本﹐如今這手好字﹐村裡可尋不著第二個嘍。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 交付「老安懶的毛筆」：直接 new + move(who)﹐move 回 1 為成功（落玩家身上）﹐
// 回 0（失敗）才退而落到地上﹐不走延遲回呼。
private void give_brush(object who)
{
	object brush;

	if( !who || environment(who) != environment() ) return;

	brush = new(__DIR__"obj/anlan_brush");
	if( !brush->move(who) ) brush->move(environment());

	message_vision(
		"阿桂自懷裡鄭重取出那管摩挲得溫潤發亮的舊毛筆﹐雙手奉到$N\n"
		"面前﹐眼眶微微泛紅﹕『老安懶﹐你託付的事﹐我今兒總算了了。』\n",
		who);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這老村民阿桂打聽甚麼﹖（試試 ask agui about 老安懶）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("阿桂正出神地摩挲著手裡那管舊毛筆﹐一時沒理會你。\n");

	// 老安懶 / 毛筆 / 老安懶的毛筆 / 筆 / 書生：支線「老安懶的毛筆」——授物
	if( arg == "agui about 老安懶"
	||  arg == "agui about 老安懶的毛筆"
	||  arg == "agui about 毛筆"
	||  arg == "agui about 筆"
	||  arg == "agui about 書生"
	||  arg == "agui about anlan"
	||  arg == "agui about brush" ) {
		object me = this_player();
		int q = me->query("quest/sq_agui");

		// 已領過：純氣氛收尾﹔若筆失落則補發一管﹐進度不重置﹐免卡關
		if( q >= 1 ) {
			if( !present("anlan brush", me) && !present("anlan brush", environment(me)) ) {
				give_brush(me);
				do_chat((: command,
					"say 咦﹐先前與客官的那管筆呢﹖莫不是失落了﹖罷罷罷﹐老安懶的東西丟不得——客官且收好了﹐這是他留在世上唯一的念想哪。" :));
				return 1;
			}
			do_chat(({
				(: command, "say 那管筆既到了客官手裡﹐老安懶在地下也好瞑目了。客官是個讀得進書、走得遠路的人﹐這筆跟著你﹐比擱在我這莊稼老兒懷裡強。" :),
				(: command, "say 老安懶常說﹕筆桿子雖輕﹐寫下的字﹐落紙卻有千鈞重。客官帶著它走江湖﹐遇著該秉筆直書的事﹐莫要含糊了。" :),
			}));
			return 1;
		}

		// 首次：道出託筆之事﹐先同步交物、後記旗標（玩家此刻必在場）
		give_brush(me);
		me->set("quest/sq_agui", 1);
		do_chat(({
			(: command, "say 客官問起老安懶﹖唉﹐他是咱康平村早年的一位窮書生﹐性子懶散﹐心地卻極好﹐替合村寫了一輩子的狀子賬本﹐教蒙童描紅識字﹐村裡老小沒一個不念他的好。前些年﹐他撒手去了。" :),
			(: command, "say 他生平沒甚麼值錢的家當﹐唯有這管隨身數十年的舊毛筆。臨了把它託與我﹐囑我尋個讀得進書、走得遠路的有心人交付——這些年我成日在曬場邊留心打量﹐單等這麼一個人。" :),
			(: command, "say 客官氣度不俗﹐又是走南闖北的人﹐我瞧著﹐這筆便該是客官的。喏﹐方纔已奉到客官手裡了——好生收著﹐這是老安懶留在世上唯一的念想。他有句話要我捎與得筆的人﹕『筆桿子雖輕﹐寫下的字﹐落紙卻有千鈞重。』" :),
		}));
		return 1;
	}

	// 純氣氛閒談：康平村／老書生的舊事
	if( arg == "agui about 康平村"
	||  arg == "agui about 康平"
	||  arg == "agui about 村"
	||  arg == "agui about kangping" ) {
		do_chat((: command,
			"say 咱康平村是個尋常莊稼村子﹐偏在斐縣城西﹐合村百十戶人家﹐靠著村外那一片田過活。年成雖好﹐讀書人卻是稀罕——當年若不是老安懶替合村寫寫算算、教教蒙童﹐這村裡識得幾個字的﹐怕是一隻手都數得過來嘍。" :));
		return 1;
	}

	return notify_fail("阿桂捋著鬍子和氣一笑﹕客官問這個做甚﹖難得到咱村裡﹐隨意逛逛﹐吃碗新米飯罷。（試試 ask agui about 老安懶）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗光天化日的﹐客官這是做甚﹖老朽一個懷揣念想的莊稼老兒﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
