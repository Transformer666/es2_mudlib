// boatman.c -- 老船夫趙篙：枯守五堂鎮過河渡口的擺渡老人。
//              docs 主線疑團「過河的船在哪裡？」(docs/01-世界觀與劇情/
//              05-主線任務與NPC.md:32)之伏筆人物。docs 未指出對岸已建區、亦
//              未給「船怎麼來」之解答，故本 NPC 純作 lore 對白與伏筆 hook——
//              對白給「近日水大、渡船又被人借走/藏走」之鋪陳，不開實際擺渡傳送
//              (對岸區建好後再為 boatman 加 do_cross 擺渡邏輯，caveat)。
//
// 機制：純 lore 對話 NPC(ask-handler) + do_cross 伏筆指令(目前一律回「過不得河」)。
//   不發物、不改技能、不推任務獎勵旗標。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()。
//   #11：本檔為 NPC(非房間)，不涉 replace_program。
//   #14：init() 招呼加 this_player()&&interactive() 護衛；不覆寫 relay_say。
//   handler 守衛：do_ask / do_cross 開頭即 is_fighting()/is_chatting() 守衛。
//
// 範式來源：d/snow/npc/heiyilaoren.c(伏筆老者：ask-about、init 招呼護衛、
//   accept_fight 婉拒)；d/wutang/npc/washerwoman.c(add_action do_ask)。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
int do_cross(string arg);

void create()
{
	set_name("老船夫", ({ "boatman", "lao boatman", "old boatman", "趙篙", "老船夫", "船夫" }) );
	set("nickname", "老船夫趙篙");
	set_attr("str", 20);
	set_attr("con", 22);
	set_attr("dex", 18);
	set_race("human");
	set_class("commoner");
	set_level(8);
	set_skill("unarmed", 20);
	set_skill("dodge", 25);

	set("gender", "male");
	set("age", 61);
	set("long",
		"一個皮膚黝黑、滿手老繭的擺渡老人﹐穿著一件半濕的蓑衣﹐蹲在\n"
		"岸邊的礁石上叼著旱菸袋。他在這渡口擺了一輩子的船﹐這河裡的\n"
		"水文脾性﹐沒人比他更摸得清。此刻他望著滔滔漲起的濁浪﹐眉頭\n"
		"擰成了一個結﹐旱菸袋明滅明滅地閃著﹐半晌不吭一聲——看那神\n"
		"情﹐倒不只是為著這場大水犯愁。\n"
		"你或許可以問問他：ask boatman about 渡船。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"老船夫吧嗒吧嗒地抽著旱菸﹐望著湍急的河水直搖頭。\n",
		"老船夫磕了磕菸灰﹐喃喃道﹕這水 ... 邪性﹐邪性得很哪。\n",
		"老船夫嘆道﹕擺了四十年的船﹐頭一回連船都教人弄沒了 ...\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	add_action("do_cross", ({ "cross", "渡河", "過河", "擺渡" }) );
	if( this_player() && interactive(this_player()) && !is_fighting() ) {
		do_chat((: command,
			"say 這位客官是要過河﹖不巧得很﹐這當口 ... 過不得啊。(ask boatman about 渡船)" :));
	}
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg )
		return notify_fail("你想問老船夫甚麼﹖（試試 ask boatman about 渡船）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老船夫望著河水出神﹐沒空理你。\n");

	if( !me ) return 0;

	// ── 渡船的下落 ──
	if( arg == "boatman about 渡船" || arg == "boatman about 船"
	 || arg == "boatman about boat" || arg == "boatman about 過河" ) {
		do_chat(({
			(: command, "say 客官有所不知。前兒個夜裡﹐一連下了三日的大雨﹐這河水漲得猛﹐尋常的舟子斷不敢下水。" :),
			(: command, "say 更邪門的是 ... 老漢那條渡船﹐昨兒一早起來就不見了﹗繫船的纜繩好端端的﹐船卻沒了影。客官你說邪不邪﹖老漢擺了四十年船﹐還是頭一遭碰上這等怪事。" :),
			(: command, "say 客官若真急著過河﹐且等老漢尋回了船、河水也消停了再說罷。眼下嘛 ... 唉﹐過不得﹐過不得啊。" :),
		}));
		return 1;
	}

	// ── 對岸是何處 ──
	if( arg == "boatman about 對岸" || arg == "boatman about 河對岸" ) {
		do_chat(({
			(: command, "say 河那頭麼 ... 從前是有條道通往別處的去界的。只是這兩年﹐過河的人是越來越少了﹐連老漢都快記不清上回送人過去是甚麼時候了。" :),
			(: command, "say 客官若問老漢那霧裡頭究竟是甚麼地界 ... 老漢一個擺船的﹐也說不上來。橫豎眼下過不去﹐客官也不必多想了。" :),
		}));
		return 1;
	}

	// ── 是誰把船弄走的 ──
	if( arg == "boatman about 偷船" || arg == "boatman about 是誰"
	 || arg == "boatman about 賊" ) {
		do_chat(({
			(: command, "say 是誰弄走的﹖老漢若知道﹐還能在這乾瞪眼﹖（壓低了嗓子）不過 ... 那夜老漢恍惚聽見岸邊有人走動、像是好幾個人合力拖著甚麼往下游去 ... 也許是老漢年紀大了﹐聽岔了罷。" :),
			(: command, "say 客官若是個有心人﹐不妨自個兒沿著河岸找找(search 河岸)﹐興許比老漢這雙老眼看得真切。" :),
		}));
		return 1;
	}

	return notify_fail("老船夫吧嗒著旱菸﹕客官不如問問渡船、對岸的事罷。\n");
}

// 過河伏筆指令：目前一律「過不得」(對岸區未建、解謎未定)。
int do_cross(string arg)
{
	object me = this_player();

	if( is_fighting() || is_chatting() )
		return notify_fail("老船夫望著河水出神﹐沒空理你。\n");

	if( !me ) return 0;

	do_chat((: command,
		"say 客官莫急﹗船都教人弄沒了﹐這河水又漲得這般凶﹐老漢縱有天大的本事﹐也變不出條船來渡你過去啊。且等等罷。" :));
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 哎哎﹗客官這是做甚麼﹖老漢一個擺船的苦哈哈﹐可禁不起你這般唬人﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
