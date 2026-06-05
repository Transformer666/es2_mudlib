// jisheng.c -- 藥鋪掌櫃 (Pharmacy keeper)﹕濟生藥鋪掌櫃﹐專賣煉丹「藥引(mixture)」。
//
// 出處﹕docs/02-遊戲系統與機制/06-煉丹與書本系統.md 煉丹流程 L57﹕
//   「2. 去濟生藥鋪找藥鋪掌櫃 buy mixture for minor heal pill   # 92兩50文/份」。
//   即煉丹正規流程第二步——方士須先向本掌櫃買得對應丹方的藥引(mixture)﹐
//   方能 put mixture in reactor → 入爐起火 → prepare mixture 結成丹藥。
//
// 與既有 NPC 不撞﹕
//   * 雪亭鎮「順生堂」小藥鋪(d/snow/herb_shop)那位掌櫃 id 為 herbalist、名「藥鋪掌
//     櫃」﹐賣的是成藥(black_pill/boar_berry…)。本掌櫃在另一間「濟生藥鋪」﹐專營煉
//     丹藥引﹐id 取 jisheng/keeper/pharmacist…(不含 herbalist)﹐顯示名同為「藥鋪
//     掌櫃」於不同房﹐玩家不會混指。
//   * 大屋正廳的江述仁(d/longtu/npc/jiang)賣成藥/煉丹器材(器材另由器材店 agent 接)﹐
//     本掌櫃只賣 mixture﹐職司分明。
//
// 售賣機制(不走標準 F_VENDOR﹐因語法是「buy mixture for <丹方>」而非「buy X from Y」)﹕
//   * 標準 /cmds/std/buy.c 只認 "buy %s from %s"﹐無法解 "for"。故本 NPC 於 init()
//     add_action("do_buy_mixture", "buy") 攔截 "buy ... for ..." 形式。
//   * 指令優先序(已讀 feature/char/command.c 確認)﹕玩家的 command_hook 是
//     add_action("",1) 萬用攔截﹔房中物件(本 NPC)的具名 add_action("buy") 會先被
//     driver 試。do_buy_mixture 只在 arg 形如「mixture for <丹方>」時 return 1 消化﹔
//     否則 return 0﹐讓 "buy X from Y" 照舊落到 /cmds/std/buy。
//   * 收錢﹕鏡 /cmds/std/buy.c 範式——me->can_afford(price)→me->pay_money(price)。
//   * 出貨﹕new(MIXTURE_PATH) 出一份藥引並以 init_mixture(丹方) 烙上目標丹方(由器材/
//     daemon agent 提供之 mixture 物件實作該 apply)﹐move 到買家身上。本檔**只引用**
//     mixture 物件 id/路徑﹐**不建** mixture 物件本身(由另一 agent 建)。catch 包住
//     new()﹐mixture 檔未就緒時優雅報「暫缺」而不致 NPC 載入失敗。
//
// 認物以英文 id 為準(feature/name.c::id() 只比對 set_name 第二參數)。

#include <npc.h>

inherit F_VILLAGER;

// 前置宣告(lesson #12﹕定義前引用之函式須先宣告)。
int do_buy_mixture(string arg);
int do_list_mixture(string arg);
private mapping recipe_book();
private string canon_recipe(string s);

// 藥引出貨物件——由器材/daemon agent 提供﹐本檔僅引用其路徑/id﹐不建此檔。
#define MIXTURE_PATH    "/obj/medication/alchemist/mixture"

// 每份藥引售價﹕92兩50文 = 9250 文(docs L57)。原作對 mixture 採統一份價(藥引乃
// 半成藥料﹐入爐後方依火候結成各丹)﹐故此處對各丹方採同一份價﹐以 mapping 留作
// 日後分丹方調價之餘地﹔未列者一律 DEFAULT_PRICE。
#define DEFAULT_PRICE   9250

void create()
{
	set_name("藥鋪掌櫃", ({ "yaopu keeper", "keeper", "jisheng", "pharmacist", "druggist", "longtu_jisheng" }) );
	set("nickname", "藥鋪掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(8);
	set_skill("unarmed", 8);
	set_skill("dodge", 8);
	set_skill("parry", 8);

	set("age", 49);
	set("gender", "male");
	set("long",
		"這位是濟生藥鋪的掌櫃﹐年近半百﹐生得乾瘦精明﹐一雙手指甲縫\n"
		"裡都嵌著藥末。他常年替上山煉丹的方士秤配藥引﹐閉著眼也分得\n"
		"清辰砂與雄黃﹐戥子一抄便是準分準兩。見了客人便擱下藥碾﹐拱\n"
		"手招呼一聲﹐問可是要配藥引煉丹。你可以用 list 看他配售哪些\n"
		"丹方的藥引﹐用 buy mixture for <丹方> 向他買(如 buy mixture\n"
		"for minor heal pill)﹐每份藥引索價九十二兩零五十文。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"藥鋪掌櫃擱下藥碾﹐拱手笑道﹕客官是上山煉丹的罷﹖要配哪一爐丹方的藥引﹐報個名兒﹐小號替你秤了。\n",
		"藥鋪掌櫃捻著戥子道﹕煉丹先得有藥引(mixture)﹐買回去塞進丹鼎入爐﹐火候到了才結得成丹。\n",
		"藥鋪掌櫃一面包著紙包一面道﹕小號這藥引論份賣﹐一份九十二兩零五十文﹐童叟無欺。\n",
	}));

	setup();
	// carry_money﹕備零錢供找零(鏡 d/longtu/npc/jiang.c)。
	carry_money("coin", 500);
}

void init()
{
	::init();
	add_action("do_buy_mixture", "buy");
	add_action("do_list_mixture", "list");
}

// 可配售的丹方表﹕丹方指認字串 -> 成品丹藥檔路徑。
// 與 cmds/std/refine.c 的 RECIPES 成品一致(藥引乃該丹之半成料)﹐中文名與英文短名
// 雙索引﹐讓 buy mixture for 小還丹 / buy mixture for minor heal pill 皆認得。
// 不含「養氣丹/混合藥丹」等捷徑/錯方丹(那是 refine 直結﹐不走藥引爐煉流程)。
private mapping recipe_book()
{
	return ([
		"烏心丹"        : "/obj/medication/alchemist/black_pill",
		"black pill"    : "/obj/medication/alchemist/black_pill",
		"清腹丹"        : "/obj/medication/alchemist/lavage_pill",
		"lavage pill"   : "/obj/medication/alchemist/lavage_pill",
		"甘靈清毒丹"    : "/obj/medication/alchemist/green_pill",
		"green pill"    : "/obj/medication/alchemist/green_pill",
		"醒神丹"        : "/obj/medication/alchemist/mana_pill",
		"mana pill"     : "/obj/medication/alchemist/mana_pill",
		"金液丹"        : "/obj/medication/alchemist/aquapill",
		"aquapill"      : "/obj/medication/alchemist/aquapill",
		"養心丹"        : "/obj/medication/alchemist/relax_pill",
		"relax pill"    : "/obj/medication/alchemist/relax_pill",
		"金鎖固精丸"    : "/obj/medication/alchemist/refresh_pill",
		"refresh pill"  : "/obj/medication/alchemist/refresh_pill",
		"小還丹"        : "/obj/medication/alchemist/minor_heal_pill",
		"minor heal pill" : "/obj/medication/alchemist/minor_heal_pill",
		"大還丹"        : "/obj/medication/alchemist/major_heal_pill",
		"major heal pill" : "/obj/medication/alchemist/major_heal_pill",
	]);
}

// 正規化玩家輸入的丹方字串﹕去頭尾空白、英文轉小寫(中文高位元組不受 lower_case 影響)。
private string canon_recipe(string s)
{
	if( !stringp(s) ) return 0;
	// 去前後多餘空白。
	while( strlen(s) && s[0]==' ' ) s = s[1..];
	while( strlen(s) && s[<1]==' ' ) s = s[0..<2];
	if( s=="" ) return 0;
	if( recipe_book()[s] ) return s;
	if( recipe_book()[lower_case(s)] ) return lower_case(s);
	return 0;
}

// list﹕列出本鋪配售的全部丹方藥引與份價。
// 只列中文名那條(key[0] 高位元組 >=128)﹐英文別名自然略過﹐每爐丹恰列一次。
int do_list_mixture(string arg)
{
	mapping book;
	string list, key, path, cname;

	if( is_fighting() ) return 0;
	// 帶參數而非指本掌櫃時不應答﹐讓其他 list 行為照舊。
	if( arg && !id(arg) ) return 0;

	book = recipe_book();
	list = "";
	foreach(key, path in book) {
		if( key[0] < 128 ) continue;        // 只取中文名那條
		cname = (string)load_object(path)->query("name");
		if( !cname ) cname = key;
		list += sprintf("  %-30s：%s\n",
			cname + "藥引", price_string(DEFAULT_PRICE));
	}
	if( list=="" ) return 0;

	write(name() + "替你報出可配的丹方藥引(每份" + price_string(DEFAULT_PRICE) + ")﹕\n");
	write("-------------------------------------------------------------\n");
	write(list);
	write("以「buy mixture for <丹方> from keeper」購買﹐如 buy mixture for minor heal pill from keeper。\n");
	return 1;
}

// price_string﹕仿 feature/npc/vendor.c::price_string﹐把份價文數轉中文錢。
private string price_string(int v)
{
	if( v%10000 == 0 ) return chinese_number(v/10000) + "兩黃金";
	if( v >= 100 )
		return chinese_number(v/100) + "兩銀子"
			+ ((v%100) ? "又" + chinese_number(v%100) + "文錢" : "");
	return chinese_number(v) + "文錢";
}

// buy﹕攔截 "buy mixture for <丹方> [from <本掌櫃>]"。
//   非此形式(如 "buy X from Y") -> return 0﹐讓 /cmds/std/buy 照舊處理。
int do_buy_mixture(string arg)
{
	object me, mix;
	string what, recipe, targ, path, cname;
	int price;
	mixed err;

	me = this_player();
	if( !me || !arg ) return 0;

	// 只認 "...mixture for ..." 形式﹔不含 " for " 一律放行給標準 buy。
	if( sscanf(arg, "%s for %s", what, recipe) != 2 )
		return 0;

	// 允許 "buy mixture for 小還丹 from keeper"﹕剝掉尾端的 "from <某人>"。
	if( sscanf(recipe, "%s from %s", recipe, targ) == 2 ) {
		// 指名買賣對象時﹐須正是本掌櫃(present 於本室且指認得)﹐否則放行。
		if( !id(targ) ) return 0;
	}

	// 去 what 前後空白﹐須為 "mixture"/"藥引"(本掌櫃只賣藥引)。
	while( strlen(what) && what[0]==' ' ) what = what[1..];
	while( strlen(what) && what[<1]==' ' ) what = what[0..<2];
	// what 不是 mixture/藥引 -> 非本掌櫃業務﹐放行給標準 buy(return 0)。
	if( what!="mixture" && what!="藥引" )
		return 0;

	// 戰鬥/談話中不交易。
	if( is_fighting() || is_chatting() )
		return notify_fail(name() + "正忙著﹐沒空替你配藥。\n");

	// 查丹方是否在本鋪配售之列。
	recipe = canon_recipe(recipe);
	if( !recipe ) {
		// what 已確定是 mixture/藥引﹐故這是「丹方不識」而非別的買賣 -> 消化此指令並報錯。
		do_chat(name() + "搖頭道﹕這丹方小號配不出﹐你 list 瞧瞧本鋪配得哪些藥引。\n");
		return 1;
	}

	path  = recipe_book()[recipe];
	cname = (string)load_object(path)->query("name") || recipe;
	price = DEFAULT_PRICE;

	// 收錢(鏡 /cmds/std/buy.c)﹕can_afford 回 0 不夠、2 零錢不足。
	switch( me->can_afford(price) ) {
	case 0:
		do_chat(name() + "看了看你的荷包﹐婉言道﹕這藥引一份要" + price_string(price)
			+ "﹐客官的錢怕是不夠。\n");
		return 1;
	case 2:
		do_chat(name() + "為難道﹕你這錢小號找不開﹐換些零碎銀錢來罷。\n");
		return 1;
	}

	// 出貨﹕clone 一份藥引並烙上目標丹方。mixture 物件由另一 agent 建﹐故 catch 包住﹔
	// 物件未就緒時報「暫缺」並不扣錢。
	err = catch(mix = new(MIXTURE_PATH));
	if( err || !objectp(mix) ) {
		do_chat(name() + "翻了翻藥屜﹐歉然道﹕不巧﹐配藥引的料剛缺了﹐客官改日再來。\n");
		return 1;
	}

	// 把目標丹方烙上藥引(mixture 物件實作 init_mixture(成品路徑)﹐由另一 agent 提供)﹔
	// 若該 apply 尚未實作﹐至少 set 一個旗標供其讀取﹐不致出錯。
	if( function_exists("init_mixture", mix) )
		mix->init_mixture(path);
	else
		mix->set("mixture_for", path);

	// 確認出貨後才扣錢(前置都過了)。
	me->pay_money(price);
	mix->move(me);

	message_vision("$N向" + name() + "買下一份" + cname + "的藥引。\n", me);
	do_chat(name() + "戥子一抄﹐利落地包了一紙" + cname + "藥引遞過來﹕拿去煉罷﹐火候自個兒拿穩。\n");
	return 1;
}

int accept_fight(object ob)
{
	do_chat(name() + "連忙擺手陪笑﹕客官息怒﹗小號一個秤藥包紙的﹐動不得粗的﹗\n");
	return 0;
}
// vim: set ts=4 sw=4 syntax=lpc
