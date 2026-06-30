// wuchang.c -- 無腸老人：終日醉在龍安無腸酒店裡、愛喝酒的鶴髮詩翁。
//              docs canon：docs 02-遊戲系統與機制/06-煉丹與書本系統.md L158
//              「煙雨詩錄 → 龍安愛喝酒的無腸老人」。本 NPC 為頂級書「煙雨詩錄」
//              的授書人。
//
// 故事背景：
//   這位老者本是江南一帶頗有些薄名的詩客﹐生平兩樁嗜好——一是吃酒、二是吟
//   詩。年輕時走遍水鄉煙雨﹐把一路看來的橋影、櫓聲、煙波、酒甕﹐都釀成了詩
//   句﹐手抄成一卷『煙雨詩錄』。後來功名蹉跎、家業飄零﹐他索性枕水而居﹐日
//   日泡在這龍安無腸酒店裡﹐三餐就著一壺米酒過活﹐鎮人見他終日醉醺醺、一肚
//   子淨是酒﹐便戲稱他作「無腸老人」。他那卷詩錄是畢生心血﹐尋常人他懶得理
//   會﹐惟獨遇上肯與他談詩論酒、知他心意的有緣人﹐才肯把詩錄相贈﹐盼這一卷
//   煙雨﹐能在江湖上有個知音傳下去。
//
// 授書流程（旗標存玩家身上﹐ask-gated、同步交付、無 give-turn-in soft-lock）：
//   先談詩 : ask wuchang about 詩（或 詩錄/作詩）-> 老人來了興致﹐與你談一段
//            水鄉詩話﹐記下「談詩」鋪墊旗標 quest/longan_poem = 1（純對白、不給物）。
//   求贈書 : ask wuchang about 煙雨詩錄（或 書/酒）->
//            * 未先談詩(longan_poem 未及 1)：老人醉眼一掃﹐見你不解詩中三昧﹐
//              只當尋常醉話搪塞﹐點你「先與他談談詩」(不給書、不記完成)。
//            * 已談過詩(longan_poem >= 1)且未領過書：老人引你為知音﹐同步取出
//              『煙雨詩錄』相贈、即記 quest/longan_book = 1。
//   已領書 : 不再重複贈書（防重領）；ask 只給一段醉吟自得的純劇情對白。
//   穩健性 : 若已記領書旗標但詩錄不在玩家身上(遺失/賣掉)﹐補贈一卷、不重置進度。
//
// 同步交付（本專案頭號 bug class 之防範﹐鏡 d/snow/npc/heiyilaoren.c）：
//   贈書一律在 do_ask handler 內直接 new()+move() 給玩家、且在設完成旗標之
//   前——絕不放進延遲的 do_chat/closure。do_chat 只擺氣氛對白。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()——旗標／訊息逕在 handler 內順序寫就。
//   #14：init 招呼有 interactive(this_player()) 護衛﹔do_ask 開頭有
//        is_fighting()/is_chatting() 護衛。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIY "無腸老人" NOR, ({ "wuchang", "wuchang laoren", "old man", "無腸老人", "老人" }) );
	set("nickname", HIY "無腸老人" NOR);
	set_attr("int", 26);
	set_attr("wis", 22);
	set_attr("con", 14);
	set_attr("spi", 18);
	set_race("human");
	set_class("commoner");
	set_level(12);
	set_skill("literate", 60);
	set_skill("dodge", 20);
	set_skill("unarmed", 20);

	set("gender", "male");
	set("age", 67);
	set("long",
		"一個鶴髮童顏的老者﹐獨坐在臨水的桌旁自斟自飲。他穿一襲洗\n"
		"得發白的青布長衫﹐衣襟上沾著點點酒漬﹐花白的鬚髮卻梳理得一\n"
		"絲不苟。他一手執壺、一手捏著個粗陶酒盅﹐醉眼朦朧地望著窗外\n"
		"一河的煙水﹐時而拍案叫絕、時而搖頭嘆息﹐口中喃喃地念著些殘\n"
		"章斷句。鎮上人見他終日泡在酒裡、一肚子淨是酒﹐便戲稱他作\n"
		"「無腸老人」。你瞧他醉態可掬﹐眉宇間卻自有一股說不出的疏狂\n"
		"灑落﹐想來是個飽讀詩書、看破了功名的有道之人。\n"
		"你或許可以同他談談詩：ask wuchang about 詩。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"無腸老人呷一口米酒﹐瞇起醉眼搖頭晃腦﹐念道﹕『春水碧於天﹐畫船聽雨眠』 ... 好酒﹐好詩﹗\n",
		"無腸老人對著一河煙波拍案長嘆﹕這龍安的煙雨﹐才下得出好詩啊﹗來﹐老夫再敬這煙水一杯﹗\n",
		"無腸老人晃了晃手中的酒壺﹐聽得是空的﹐衝著酒保嚷道﹕小哥﹐再篩一壺熱的來﹗\n",
		"無腸老人指尖蘸了酒﹐在桌上信手塗抹著甚麼﹐塗著塗著又自個兒搖頭抹去了。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	// 只對真人玩家招呼（gotcha #14：缺 interactive 護衛 = say-storm）。
	if( this_player() && interactive(this_player()) ) {
		if( !this_player()->query("quest/longan_book") )
			do_chat((: command,
				"say 咦﹖來客了。客官可也是愛這口酒、愛這煙雨的同道中人麼？來來來﹐同老夫談談詩。(ask wuchang about 詩)" :));
	}
}

// 同步贈書：直接 new()+move() 給玩家。先試 move 到玩家身上﹐
// 不成(負重等)則落在環境地上——絕不靜默丟失（鏡 heiyilaoren::give_hairpin）。
private void give_book(object who)
{
	object book;

	if( !who || environment(who) != environment() ) return;

	book = new(__DIR__"obj/yanyu_book");
	if( !book->move(who) ) book->move(environment());

	message_vision(
		"無腸老人顫巍巍地自懷中摸出一卷以陳年絹帛裝裱的舊譜﹐封皮上『煙雨詩錄』"
		"四個字依稀可辨。他捧著它端詳了半晌﹐長嘆一聲﹐方才鄭重地將詩錄交到$N手"
		"中﹐渾濁的醉眼裡漫上一層水光。\n",
		who);

	who->gain_score("emprise", 60);
	who->gain_score("reputation", 30);
	who->gain_score("explorer fame", 30);
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg )
		return notify_fail("你想問這位老人甚麼？（試試 ask wuchang about 詩）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("無腸老人正自顧自地醉吟著﹐恍若未聞﹐沒空理你。\n");

	// 談詩：鋪墊旗標﹐純對白、不給物。
	if( arg == "wuchang about 詩"
	||  arg == "wuchang about 詩錄"
	||  arg == "wuchang about 作詩"
	||  arg == "wuchang about 詩句"
	||  arg == "wuchang about poem"
	||  arg == "wuchang about poetry" ) {
		if( !me->query("quest/longan_poem") )
			me->set("quest/longan_poem", 1);
		do_chat(({
			(: command, "say 哈哈﹗難得難得﹐如今肯同老夫談詩的後生﹐可不多見了。客官請坐﹐老夫敬你一盅。" :),
			(: command, "say 老夫平生兩樁嗜好﹐一是吃酒﹐二是吟詩。年輕時走遍這江南水鄉﹐把一路的橋影櫓聲、煙波酒甕﹐都釀成了句子﹐手抄成一卷詩錄。" :),
			(: command, "say 旁人只當老夫是個醉鬼﹐殊不知這煙雨水鄉裡﹐處處是詩。客官若也識得這煙雨裡的好處﹐不妨向老夫討教那卷詩錄。(ask wuchang about 煙雨詩錄)" :),
		}));
		return 1;
	}

	// 求贈書 / 問酒
	if( arg == "wuchang about 煙雨詩錄"
	||  arg == "wuchang about 書"
	||  arg == "wuchang about 酒"
	||  arg == "wuchang about 米酒"
	||  arg == "wuchang about yanyu"
	||  arg == "wuchang about book"
	||  arg == "wuchang about wine" ) {

		// 已領過詩錄：純劇情對白﹐不重發（防重領）。
		if( me->query("quest/longan_book") >= 1 ) {
			// 穩健性：旗標在、詩錄卻不在身上(遺失/賣掉)-> 補贈一卷﹐不重置進度。
			if( !present("yanyu", me) ) {
				give_book(me);
				do_chat((: command, "say 你那卷詩錄 ... 怎不見了？罷了罷了﹐老夫這裡 ... 還抄得有一卷副本﹐再贈與你便是——這回可要收好﹐莫教這煙雨斷了知音啊。" :));
				return 1;
			}
			do_chat(({
				(: command, "say 那卷煙雨詩錄﹐可還在你身上麼？好 ... 好。老夫畢生的煙雨﹐都在那卷裡頭了。" :),
				(: command, "say 你帶著它走江湖﹐他日臨水憑欄、煙雨入眼時﹐念上幾句﹐便算老夫這糟老頭子﹐還有個知音在江湖上了。來﹐再陪老夫飲一盅﹗" :),
			}));
			return 1;
		}

		// 未先談詩：搪塞﹐點他「先談詩」（不給書、不記完成）。
		if( !me->query("quest/longan_poem") ) {
			do_chat((: command,
				"say 唔？酒麼 ... 酒就在那甕裡﹐自個兒向酒保討去。至於詩錄 ... 嘿﹐那是老夫的命根子﹐豈是隨口能討的？你若真有意﹐先同老夫談談詩﹐讓老夫瞧瞧你解不解得這煙雨裡的三昧。(ask wuchang about 詩)" :));
			return 1;
		}

		// 已談過詩、首次求書：同步贈書、即記旗標。
		// 先給物、後記旗標——免於回呼前離場致書沒領、旗標卻記完成而卡關。
		give_book(me);
		me->set("quest/longan_book", 1);
		do_chat(({
			(: command, "say 好﹐好﹗方才同你談這一席詩﹐老夫便知你是個解煙雨的有心人。難得﹐難得啊。" :),
			(: command, "say 這卷『煙雨詩錄』﹐是老夫畢生走遍水鄉煙雨、釀成的句子。老夫老了﹐這一肚子的詩﹐總得有個知音傳下去。" :),
			(: command, "say 如今便贈與你了。你拿去細細研讀(study)﹐讀通了這煙雨裡的詩心﹐文識自會精進﹐連那份悟性﹐怕也要開闊幾分。去罷﹐莫負了這一卷煙雨。" :),
		}));
		return 1;
	}

	return notify_fail("無腸老人醉眼朦朧地瞅了你一眼﹐又自顧自地呷起酒來。（試試 ask wuchang about 詩）\n");
}

// 收物防呆：婉拒玩家遞來的物事（尤不收回煙雨詩錄）。
int accept_object(object who, object ob)
{
	if( ob->id("yanyu") ) {
		do_chat((: command,
			"say 這詩錄既已贈了你﹐便是你的了 ... 老夫怎能再收回？你替老夫好生讀著﹐莫教這煙雨斷了知音﹐便是了卻老夫一樁心願。" :));
		return 0;
	}
	// 玩家若遞酒來敬老人，欣然領情但不吞物（返 0 退回）。
	do_chat((: command,
		"say 哈哈﹐有酒同飲﹐人生快事﹗老夫先謝過了——這盅你且自個兒留著﹐莫要折煞老夫了。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 哎喲﹐使不得使不得﹗老夫一介醉翁﹐手無縛雞之力﹐你同老夫一個醉鬼動甚麼粗？來來來﹐有氣消在酒裡﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
