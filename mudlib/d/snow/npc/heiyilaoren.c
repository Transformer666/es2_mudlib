// heiyilaoren.c -- 黑衣老人：枯守雪亭鎮破舊大宅(長樂侯府舊邸)的玄衣老者。
//                  docs 主線疑團「破舊大宅裡面躲著甚麼？」「黑衣老人的閨女跑去
//                  了哪裡？」之伏筆人物，亦是 canon 的 hairpin 贈物人。
//                  (canon：docs 01-世界觀與劇情/05-主線任務與NPC.md L101
//                   「黑衣老人 @ 雪亭鎮破舊大宅 → 給 hairpin」；L25/L26 疑團)
//
// 故事背景：
//   雪亭鎮西巷盡頭，那座焚過半邊、人稱鬧鬼的破舊大宅——門口破匾上「長樂侯府」
//   四字猶在。一場無名大火奪了老人的家業，更奪了他唯一的女兒；自此他一身玄黑
//   舊袍，年復一年枯坐在這斷垣殘璧裡，等著、盼著閨女循舊物尋回。他隨身收著女
//   兒當年留下的一支玉髮簪，是這半生唯一的念想。他不問來客名姓，只看一點本
//   心——若見有人肯駐足聽他一段傷心舊事，便將那支髮簪相贈，做個信物，盼有人
//   替他在江湖上捎回半點女兒的音訊。
//
// 支線流程（旗標存玩家身上：quest/sq_heiyilaoren）：
//   未領 (0)  : 玩家 ask heiyilaoren about 髮簪（或 老人/閨女/玉髮簪/大宅 …）->
//               老人略一打量，見來客肯靜心聽他一段舊事，便取出那支玉髮簪相贈，
//               同步交付、即記旗標為 1。
//   已領 (1)  : 不再重複贈簪（防重領）；ask 只給一段思女傷懷的純劇情對白。
//   穩健性    : 若旗標已記為 1 但髮簪不在玩家身上(中途遺失/賣掉)，補贈一支、
//               不重置進度(step-flag 在、物不在則重給)。
//
// 同步交付(本專案頭號 bug class 之防範)：贈簪一律在 do_ask handler 內直接
//   new()+move() 給玩家、且在設完成旗標之前——絕不放進延遲的 do_chat/closure
//   (玩家中途離場會「物沒了、旗標卻記完成」soft-lock)。do_chat 只擺氣氛對白。
//
// 範式來源(先 grep 既有檔模仿，未臆造 efun)：item-giver 同步交付鏡
//   d/capital/npc/jieyan.c(give_pei→do_ask→quest/sq_jieyan，遺失補贈)。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()——旗標／訊息逕在 handler 內順序寫就。
//   #11：本 NPC 有 do_ask，**不** replace_program(本檔為 NPC 非房間，本不涉)；
//        wire 入 ruin1 亦未對 ruin1 加 init/do_X(ruin1 原有 init，僅在其
//        set("objects") 追加本 NPC，未奪既有物、未動其 init/replace)。
//   handler 守衛：do_ask 開頭即 is_fighting()/is_chatting() 守衛。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIK "黑衣老人" NOR, ({ "heiyilaoren", "heiyi laoren", "laoren", "old man in black", "黑衣老人", "老人" }) );
	set("nickname", HIK "黑衣老人" NOR);
	set_attr("int", 21);
	set_attr("wis", 24);
	set_attr("con", 18);
	set_attr("spi", 16);
	set_race("human");
	set_class("commoner");
	set_level(18);
	set_skill("unarmed", 30);
	set_skill("dodge", 30);
	set_skill("force", 36);

	set("gender", "male");
	set("age", 64);
	set("long",
		"一個身著玄黑舊袍的老者，枯坐在這破舊大宅的斷垣殘璧之間。他生\n"
		"得清瘦佝僂，一張臉布滿風霜的皺紋，花白的頭髮亂蓬蓬地披著，一\n"
		"雙渾濁的老眼卻時時望向宅門外，像是在等甚麼人歸來。他身上那襲\n"
		"黑袍洗得發灰、邊角焦糊，依稀還是當年富貴人家的料子；指間反覆\n"
		"摩挲著一物，藏在袖中看不真切。聽附近的居民說，這宅子早年遭過\n"
		"一場無名大火，老人的家業、連同他唯一的女兒，都在那場火裡沒\n"
		"了；自此他便這般守在這廢宅裡，年復一年地等著閨女尋回。他周身\n"
		"透著一股化不開的悽惶與執念，教人一近前便覺心頭發沉。\n"
		"你或許可以問問他：ask heiyilaoren about 髮簪。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"黑衣老人怔怔地望著宅門外，喃喃道：囡囡 ... 是你回來了麼？\n",
		"黑衣老人自袖中摸出一物，就著殘月細細摩挲，渾濁的老眼裡漫上一層水光。\n",
		"黑衣老人佝著背枯坐在焦黑的樑柱旁，對著滿院的荒草長長嘆了口氣。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !this_player()->query("quest/sq_heiyilaoren") )
			do_chat((: command,
				"say 是哪位 ... 進到這破宅子裡來？你 ... 你可在江湖上見過一個鬢邊簪著青玉的姑娘麼？(ask heiyilaoren about 髮簪)" :));
	}
}

// 同步贈簪：直接 new()+move() 給玩家。先試 move 到玩家身上，
// 不成(負重等)則落在環境地上——絕不靜默丟失。
private void give_hairpin(object who)
{
	object pin;

	if( !who || environment(who) != environment() ) return;

	pin = new(__DIR__"obj/jade_hairpin");
	if( !pin->move(who) ) pin->move(environment());

	message_vision(
		"黑衣老人顫巍巍地自袖中取出一支青瑩的玉髮簪，那玉色作雨後春山般的淡青，"
		"簪頭一朵半開的玉蘭鏤得纖毫畢現。老人捧著它端詳了半晌，方才鄭重地將髮簪"
		"交到$N手中，渾濁的老眼裡淌下兩行老淚。\n",
		who);

	who->gain_score("emprise", 80);
	who->gain_score("reputation", 40);
	who->gain_score("explorer fame", 30);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "heiyilaoren about 髮簪"
		&&   arg != "heiyilaoren about 玉髮簪"
		&&   arg != "heiyilaoren about 老人"
		&&   arg != "heiyilaoren about 黑衣老人"
		&&   arg != "heiyilaoren about 閨女"
		&&   arg != "heiyilaoren about 女兒"
		&&   arg != "heiyilaoren about 大宅"
		&&   arg != "laoren about 髮簪"
		&&   arg != "heiyilaoren about hairpin"
		&&   arg != "heiyilaoren about daughter") )
		return notify_fail("你想問這位老人甚麼？（試試 ask heiyilaoren about 髮簪）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("黑衣老人怔怔地望著宅門外出神，恍若未聞，沒空理你。\n");

	q = me->query("quest/sq_heiyilaoren");

	// 已領過髮簪：純劇情對白，不重發(防重領)。
	if( q >= 1 ) {
		// 穩健性：旗標在、髮簪卻不在身上(遺失/賣掉)-> 補贈一支，不重置進度。
		if( !present("jade hairpin", me) ) {
			// 同步補贈：give_hairpin 直接 new+move(玩家此刻必在場)；do_chat 只留氣氛對白。
			// 不可把 give_hairpin 塞進 do_chat 陣列——那會延後數心跳異步執行，違同步交付契約。
			give_hairpin(me);
			do_chat((: command, "say 你那支髮簪 ... 怎不見了？罷了罷了，老朽這裡 ... 還有一支是一模一樣的式樣，再贈與你便是——這回可要收好，那是老朽閨女的念想啊。" :));
			return 1;
		}
		do_chat(({
			(: command, "say 你那支青玉髮簪可還佩在身上？好 ... 好。那是老朽囡囡及笄那年，老朽親手替她簪上的，後來她貼身收著，從不離手 ..." :),
			(: command, "say 老朽守在這破宅子裡，一等便是這許多年。你走這江湖，眼界比老朽寬 ... 他日若見著哪個女子，鬢邊曾簪過這般青玉，務必 ... 務必替老朽捎回半點音訊。去罷，去罷。" :),
		}));
		return 1;
	}

	// 首次：同步贈簪、即記旗標(give_hairpin 為直接 new+move，玩家此刻必在場)。
	// 先給物、後記旗標——免於回呼前離場致簪沒領、旗標卻記完成而卡關。
	give_hairpin(me);
	me->set("quest/sq_heiyilaoren", 1);
	do_chat(({
		(: command, "say 你 ... 你肯駐足聽老朽這糟老頭子說幾句話？這破宅子裡，已許久不曾有客了。" :),
		(: command, "say 老朽原是這長樂侯府的舊主。那一年一場大火，燒去了老朽半生的家業，更燒散了老朽唯一的閨女 ... 自那以後，老朽便守在這裡，日日盼著她循舊物尋回來。" :),
		(: command, "say 這支玉髮簪，是囡囡當年留下的念想，老朽收了這許多年。看你是個有心人——這簪子，老朽便贈與你了。你帶著它走江湖，他日若見著鬢邊簪過這般青玉的女子，便替老朽捎回半點音訊罷。去罷，珍重。" :),
	}));
	return 1;
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品(尤不收回玉髮簪)。
int accept_object(object who, object ob)
{
	if( ob->id("jade hairpin") ) {
		do_chat((: command,
			"say 這簪子既已贈了你，便是你的了 ... 老朽怎能再收回？你替老朽好生收著，便是了卻老朽一樁心願。" :));
		return 0;
	}
	do_chat((: command,
		"say 老朽一個守著廢宅的糟老頭子，了無長物，這個 ... 老朽受不起，你還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 你 ... 你要打殺老朽這糟老頭子麼？老朽一條殘命，早不值甚麼了 ... 只盼還能等著囡囡回來啊 ..." :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
