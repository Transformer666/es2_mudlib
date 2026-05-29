// boatman.c -- 望安港船塢的老船匠，往天龍島渡船的伏筆人物（純劇情，不開任何任務）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("船屋老人", ({ "boatman", "old boatman", "boat man" }) );
	set("nickname", "老船匠");
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 67);
	set("gender", "male");
	set("long",
		"一位上了年紀的老船匠﹐須髮花白﹐脊背被經年的海風吹得\n"
		"佝僂了﹐一張臉曬得黝黑﹐皺紋深得像皴裂的船板。他一雙手\n"
		"佈滿了厚繭與舊疤﹐瞇著的眼睛卻仍利得很﹐望著海口時﹐眼\n"
		"底彷彿盛著大半輩子的潮起潮落。聽聞這港上的船﹐沒有他不\n"
		"識得的水路。你或許可以問問他﹕ask boatman about 天龍島。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"船屋老人瞇眼望著海口﹐枯瘦的手裡無意識地搓著一截麻繩。\n",
		"船屋老人輕輕嘆道﹕這片海啊﹐養人﹐也吞人﹐討海的命﹐都繫在風浪上哩。\n",
		"船屋老人喃喃道﹕外海那道暗流﹐近來邪性得很﹐連跑老了船的都不敢輕易往西去 ...\n",
	}));
	setup();
	carry_money("coin", 40);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 客官也是來打聽船期的麼﹖唉﹐這光景﹐沒船往西去囉 ..." :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位老船匠甚麼﹖（試試 ask boatman about 天龍島）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("船屋老人正出神地望著海口﹐沒空理你。\n");

	// 天龍島：未來海路的伏筆 -- 船在修、風浪未平，開不了任何東西
	if( arg == "boatman about 天龍島"
	||  arg == "old boatman about 天龍島"
	||  arg == "boatman about 天龍"
	||  arg == "boatman about dragon island"
	||  arg == "boatman about dragon" ) {
		do_chat(({
			(: command, "say 天龍島﹖嘿﹐客官也聽說過那地方。打這望安港往西﹐越過外海那片暗礁險灘﹐再行上三五日水路﹐才到得了那座海外仙山。" :),
			(: command, "say 只是這光景去不得喲。渡海的大船上月教風暴打折了主桅﹐這會兒還擱在塢裡修著﹐料還沒備齊呢。" :),
			(: command, "say 況且近來外海風浪未平﹐那道暗流邪性得很﹐便是船修好了﹐沒個風平浪靜的日子﹐老朽也不敢放船。客官且耐心等等罷﹐來日船修好了、風浪平了﹐自有再說。" :),
		}));
		return 1;
	}

	// 渡船 / 船期：同一個伏筆，換個問法
	if( arg == "boatman about 渡船"
	||  arg == "old boatman about 渡船"
	||  arg == "boatman about 船"
	||  arg == "boatman about 船期"
	||  arg == "boatman about ferry"
	||  arg == "boatman about boat" ) {
		do_chat(({
			(: command, "say 渡船﹖唉﹐客官來得不巧。那條跑遠海的大船﹐主桅教上月的風暴打折了﹐這會兒正翻在塢裡修著哩。" :),
			(: command, "say 船料還缺著一截好龍骨﹐慢工出細活﹐急不得。便是修好了﹐也得等外海那道邪性的暗流平了﹐才敢開船。客官要往西去﹐眼下是無船可渡的﹐再等些時日罷。" :),
		}));
		return 1;
	}

	// 望安港 / 海路：閒談海上見聞，純氣氛
	if( arg == "boatman about 望安港"
	||  arg == "boatman about 港"
	||  arg == "boatman about 海"
	||  arg == "boatman about 海路"
	||  arg == "boatman about harbor"
	||  arg == "boatman about sea" ) {
		do_chat(({
			(: command, "say 這望安港啊﹐是檒城的命根子。南來北往的番舶、漁舟﹐都打這兒進出﹐養活了滿城的討海人家。" :),
			(: command, "say 老朽在這塢裡捻了五十年的船縫﹐這港上的水路暗礁﹐閉著眼都摸得清。只可惜往西的遠海﹐這些年是越發去不得了 ..." :),
		}));
		return 1;
	}

	return notify_fail("船屋老人聽不明白你問的﹐只茫然望著海。（試試 ask boatman about 天龍島）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 客官這是做甚﹖老朽一把年紀的船匠﹐與你無冤無仇哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
