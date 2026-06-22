// beggar.c -- 老乞丐（市集乞丐）：蹲在漕幫酒館外討飯的漕幫舊人。漕幫任務「起源」線索人。
//
// 【設定 / canon】docs 01-世界觀與劇情/05-主線任務與NPC.md L104
//   「市集乞丐 → 漕幫任務起源」。這老乞丐年輕時也是這運河上跑船的漕幫舊人，
//   後來落魄了，仍守在渡口邊討一口飯吃。他看人最準——見來客是塊跑船的料、
//   肯為人奔走，便指點來客去尋漕運碼頭的攬頭周老大領籌入夥（漕幫任務「起點」，
//   見 zhoulaoda.c）。漕幫這條線「起源」於他這幾句指點。
//
// 【任務分工】本檔身兼漕幫這條線的兩個角色：
//   (1)「起源」——純線索 / 串接：do_ask 給漕幫由來、自身落魄的舊事，並明確指向「漕運
//       碼頭的周老大」領籌（發籌、開 quest/caobang_start 一律由起點周老大負責，本檔不發籌）。
//   (2) 漕幫支線「四鬼問環」第三步（quest/caobang_clue_c）：玩家持籌、循阿邦→阿義一路問
//       到這位最曉得內情的漕幫舊人。老乞丐道出他親歷的四鬼舊環的根底，再指玩家回禮堂尋江
//       隕覆命——同步記 quest/caobang_clue_c = 1。
//     * 未持籌 / 未得 clue_b：只給氣氛、指去先尋阿邦／阿義問起（不記旗標）。
//     * 持籌且已得 clue_b：道線索、記 clue_c、指回江隕（記旗標在 do_chat 之前）。
//   本支線自成 quest/caobang_* 旗標﹐絕不讀寫任何 旋芒 / main_canon / main_omen 旗標。
//
// 【同步交付】本步只設旗標、不交物﹐旗標一律在 do_chat 氣氛對白之前直接 set。
//
// 【runtime 鐵則】本 NPC 有 do_ask / init，**不** replace_program（#11）。
//   do_ask 以 is_fighting()/is_chatting() 守衛（#10）；無延遲交付（純氣氛/劇情對白）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老乞丐", ({ "laoqigai", "old beggar", "beggar", "老乞丐", "乞丐" }) );
	set("nickname", "老乞丐");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 58);
	set("gender", "male");
	set("long",
		"酒館門外蹲著個討飯的老乞丐，鬚髮灰白，糾結蓬亂，一身打了\n"
		"千百個補丁的破袍子辨不出本色，手裡捧著個豁了口的舊瓦缽，缽\n"
		"底零落地躺著三兩枚銅錢。他佝僂著背靠在牆根曬太陽，渾濁的一\n"
		"雙老眼卻時不時掃過渡口上來往的人，目光竟透著幾分當年跑船人\n"
		"的精明。瞧他那雙手——掌心一層厚繭，骨節因常年握篙拽纜而粗\n"
		"大變形，分明也是這運河上熬過大半輩子的漕幫舊人，不知怎的落\n"
		"魄至此，仍守在這渡口邊，討一口飯吃。\n"
		"你或許可以問問他：ask beggar about 漕幫。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老乞丐捧著破瓦缽，衝著過往的客商有氣無力地哼了句：行行好，賞口飯吃 ...\n",
		"老乞丐眯眼曬著太陽，望著一河的漕船，渾濁的眼裡忽地透出一絲神往，半晌又黯了下去。\n",
		"老乞丐咳了兩聲，伸出粗繭的手掌摩挲著瓦缽邊緣，喃喃道：當年老子也是這河上跑船的 ...\n",
	}));
	setup();
	carry_money("coin", 3);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg )
		return notify_fail("你想跟這老乞丐打聽甚麼？（試試 ask beggar about 漕幫）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老乞丐縮在牆根直打哆嗦，沒理會你。\n");

	// 漕幫由來 + 指向起點（周老大）：漕幫這條線的「起源」線索。
	if( arg == "beggar about 漕幫"
	||  arg == "beggar about 渡口"
	||  arg == "beggar about 跑船"
	||  arg == "beggar about 差事"
	||  arg == "beggar about 入夥"
	||  arg == "beggar about caobang"
	||  arg == "old beggar about 漕幫" ) {
		do_chat(({
			(: command, "say 客官面生，頭一回到咱這渡口罷？看你這身手腳，倒像是塊跑船的料 ... 嘿，別嫌老叫花子多嘴。" :),
			(: command, "say 咱漕幫管著這天下的漕運，幫眾數十萬，沿著大運河南北分舵林立，勢力大著哩——難得的是，這麼大一個幫，在江湖上卻從不與人結仇，跑船的圖個四方通達、和氣生財。" :),
			(: command, "say 客官若真有心入夥、替幫裡辦事，老叫花子指你一條道：往東沿河到漕運碼頭去，尋那掌事的攬頭周老大，跟他領一枚漕幫的竹籌——憑那籌子，往北禮堂裡尋宋爺、江爺，自有你的去處。(ask zhoulaoda about 差事)" :),
		}));
		return 1;
	}

	// 四鬼問環 第三步（quest/caobang_clue_c）：道四鬼舊環的根底，指回禮堂尋江隕覆命。
	if( arg == "beggar about 四鬼"
	||  arg == "beggar about 舊環"
	||  arg == "beggar about 問環"
	||  arg == "beggar about 線索"
	||  arg == "beggar about sigui" ) {

		// 未持籌 / 未起差事：只給氣氛、指去先尋周老大領籌，不記旗標。
		if( me->query("quest/caobang_start") < 1 || !present("caobang tally", me) ) {
			do_chat((: command, "say （老乞丐渾濁的眼睛掃過你，搖了搖頭）客官連咱漕幫的籌子都沒揣著，這四鬼的舊事，老叫花子可不敢混說。先往東到碼頭尋周老大領了竹籌，再來問罷。(ask zhoulaoda about 差事)" :));
			return 1;
		}
		// 未得 clue_b（沒循阿邦→阿義問到這兒）：只給氣氛、指去先尋二位船工問起。
		if( me->query("quest/caobang_clue_b") < 1 ) {
			do_chat((: command, "say 客官好端端地，怎跑來問老叫花子這個？這四鬼的舊事，得有個來路。客官先去渡口尋那兩個船工——老的阿邦、小的阿義，順著他二人的話頭問下來，再來尋老子，老子才好接著往下說。(ask abang about 四鬼)" :));
			return 1;
		}

		// 持籌、已得 clue_b：同步記 clue_c（在 do_chat 之前），道根底、指回江隕。
		if( me->query("quest/caobang_clue_c") < 1 )
			me->set("quest/caobang_clue_c", 1);
		do_chat(({
			(: command, "say （老乞丐渾濁的老眼霎時透出一線精光，捧著破瓦缽的手微微一顫）是阿邦、阿義那兩個小子，叫你來問老子的四鬼舊事？嘿……他二人只聽了個風聲，這事的根底，怕是這滿渡口，就剩老子一個還記得清了。" :),
			(: command, "say 客官坐下，聽老子說。當年布鎮那卯天樹下封印的，是位了不得的高人；那枚刻著赤魈、青蛛、濁魚、旱魃四鬼古篆的舊銅環，便是他鎮鬼之後遺下的。老子年輕時跑船，親眼見那高人把環交到江隕江爺手裡，囑他守著、等一個有膽識肯為人奔走的後生，來把這樁四鬼的因果了結了。江爺這一守，便守了幾十年哪。" :),
			(: command, "say 客官你揣著籌子，一路從邦哥、義小子問到老子這兒，肯為這檔子閒事奔走——老子瞧著，你倒真有幾分當年那高人說的『後生』的樣子。去罷，回北頭禮堂尋江爺，把這一路問來的四鬼源流跟他說（ask jiangyun about 問環），他自會認下你這份心。" :),
		}));
		return 1;
	}

	// 老乞丐的身世：純劇情伏筆，落魄的漕幫舊人。
	if( arg == "beggar about 乞丐"
	||  arg == "beggar about 身世"
	||  arg == "beggar about 老乞丐"
	||  arg == "beggar about 舊事"
	||  arg == "beggar about beggar" ) {
		do_chat(({
			(: command, "say 老叫花子？嘿，客官莫笑——當年老子也是這運河上跑船的漢子，一篙一纜，扛過的糧包堆起來比這板棚還高哪。" :),
			(: command, "say 後來嘛 ... 唉，跑船的人，一場病、一回風浪，便甚麼都沒了。如今老了，扛不動包了，也只剩這渡口邊一個討飯的去處——可這雙眼還沒花，誰是塊跑船的料，老子一眼便瞧得出。" :),
		}));
		return 1;
	}

	// 指向漕幫的耆宿（純氣氛點題，不接任務、不設旗標）。
	if( arg == "beggar about 周老大"
	||  arg == "beggar about zhoulaoda"
	||  arg == "beggar about 江隕"
	||  arg == "beggar about 宋安江"
	||  arg == "beggar about 禮堂" ) {
		do_chat(({
			(: command, "say 周老大？就是漕運碼頭上掌事的那位攬頭，往東沿河過去便是。新入夥的，都得先到他那兒領一枚竹籌作記認。(ask zhoulaoda about 差事)" :),
			(: command, "say 至於宋爺、江爺——那是禮堂裡頭的大人物了，老叫花子哪攀得上。客官憑著竹籌往北禮堂去，自有人替你引見，老子就不多嘴啦。" :),
		}));
		return 1;
	}

	return notify_fail("老乞丐渾濁的眼睛眨了眨，咧嘴一笑，露出豁了的牙：客官問這個做甚？賞口飯吃，比甚麼都強。（試試 ask beggar about 漕幫）\n");
}

// 收物防呆：乞丐承玩家施捨即可，不額外吞物、不卡關。
int accept_object(object who, object ob)
{
	do_chat((: command,
		"say 哎喲，多謝客官行好！老叫花子給您磕頭了！" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 哎哎！客官饒命！老叫花子一把骨頭，您可別跟老子一般見識呀！" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
