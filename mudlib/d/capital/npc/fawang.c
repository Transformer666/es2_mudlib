// fawang.c -- 玄天教法王；京畿小酒館（小樓客店）裡微服匿跡的玄天教高人，
//             docs 支線「法王論武」的贈物人。
//
// 故事背景（docs/01-世界觀與劇情/05-主線任務與NPC.md L116：
//   「玄天教法王 @ 京畿小酒館 → 給金絲翡翠帶」；玄天教主東方孤冥見同表 L88）：
//   玄天教一脈廣布帝都耳目，這位教中法王不顯山不露水，每每一襲玄色道袍、微
//   服匿跡在朱雀大街的小樓客店裡，揀個臨窗的角落獨酌一壺濁酒，借閒談論武為
//   名，暗暗品評著往來客店的江湖人物。少俠若肯與他論一論刀劍拳腳上的見地，
//   入了他的法眼，他便自腰間解下一條玄天教世代相傳的「金絲翡翠帶」相贈——這
//   是教中外門弟子熬十年苦功也難得的護身佳物。
//
// 支線「法王論武」（旗標存玩家身上：quest/sq_fawang，本檔自成一套、不碰別的旗標）：
//   ask fawang about 論武 ->
//     * 未得贈（quest/sq_fawang 為 0、且身上無金絲翡翠帶）：法王與少俠論一回武，
//       擊節稱善，同步解帶相贈（new+move），並設 quest/sq_fawang = 1（防重領）。
//     * 已得贈（旗標 1）但帶子失落（present 查無）：念在前情，補贈一條，不重置旗標。
//     * 已得贈且帶仍在身：純氣氛論武，不再贈帶。
//   交付採直接 new + move(who)：move 回 1 即成功落在玩家身上，回 0 才退落到地上，
//   絕不走會因玩家走開而落空的延遲 do_chat 回呼（見 content-town-questtemplate.md 鐵則）。
//
// 注意：本 NPC 自帶 do_ask，故不可 replace_program（會抹掉 add_action 的 ask）。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIM "玄天教法王" NOR, ({ "fawang", "xuantian fawang", "法王" }) );
	set("nickname", HIM "玄天教法王" NOR);
	set_attr("str", 28);
	set_attr("con", 26);
	set_attr("dex", 26);
	set_attr("int", 28);
	set_attr("wis", 27);
	set_race("human");
	set_class("fighter");
	set_level(35);
	set_skill("unarmed", 80);
	set_skill("dodge", 80);
	set_skill("parry", 70);
	set_skill("force", 90);
	set_skill("sword", 70);

	set("age", 58);
	set("gender", "male");
	set("long",
		"小樓客店臨窗的角落裡﹐獨坐著一位一襲玄色道袍的老者。他鬚\n"
		"眉皆已花白﹐面容卻清癯矍鑠﹐一雙眼睛深得望不見底﹐偶一抬\n"
		"眼掃來﹐便似有兩道精光自眼底一閃而沒。他自斟自飲著一壺濁\n"
		"酒﹐神色慵懶﹐袍袖底下卻隱隱透著一股淵渟嶽峙、深不可測的\n"
		"氣度——尋常客商只當他是個落拓的老道﹐卻不知這便是玄天教中\n"
		"那位深藏不露的法王。他似在借這壺酒、這扇臨街的窗﹐冷眼品\n"
		"評著往來小樓客店的滿天下英雄。\n"
		"你或許可以與他論一論武﹕ask fawang about 論武。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		HIM "玄天教法王" NOR "自斟自飲了一杯濁酒﹐瞇起眼望著街上往來的行人﹐似在出神。\n",
		HIM "玄天教法王" NOR "以指節輕叩桌面﹐口中似在低吟著甚麼拳訣劍經﹐節拍鏗然。\n",
		HIM "玄天教法王" NOR "淡淡道﹕這滿天下習武的後生﹐根骨資質固是要緊﹐這一身的見地心性﹐卻更難得。\n",
	}));
	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( !is_fighting() && this_player() && interactive(this_player()) )
		do_chat((: command,
			"say 這位少俠也是練家子罷﹖坐下﹐陪老道論一論武如何﹖" :));
}

// 把一條金絲翡翠帶解到玩家手上：直接 new + move(who)。
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上﹐
// 不走會因玩家走開而落空的延遲回呼（content-town-questtemplate.md 鐵則 2）。
private void give_girdle(object who)
{
	object girdle;

	if( !who || environment(who) != environment() ) return;

	girdle = new(__DIR__"obj/jade_girdle");
	if( !girdle->move(who) ) girdle->move(environment());

	message_vision(
		"$N自腰間緩緩解下一條泛著暖金之色的金絲翡翠帶﹐雙手遞與$n。\n",
		this_object(), who);
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg )
		return notify_fail("你想問這位老者甚麼﹖（試試 ask fawang about 論武）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("玄天教法王正自斟自飲﹐瞇著眼出神﹐一時沒空理你。\n");

	if( arg == "fawang about 論武"
	||  arg == "xuantian fawang about 論武"
	||  arg == "法王 about 論武"
	||  arg == "fawang about 武"
	||  arg == "fawang about 武功"
	||  arg == "fawang about 金絲翡翠帶"
	||  arg == "fawang about 翡翠帶"
	||  arg == "fawang about 腰帶"
	||  arg == "fawang about 玄天教"
	||  arg == "fawang about wuxue"
	||  arg == "fawang about girdle" ) {

		// 已得贈：帶仍在身則純氣氛論武，不重贈；帶子失落則補贈一條（不重置旗標）。
		if( me->query("quest/sq_fawang") >= 1 ) {
			if( present("jade girdle", me) ) {
				do_chat(({
					(: command, "say 少俠那條金絲翡翠帶﹐可束得趁手麼﹖束氣護命﹐臨敵時最是要緊。" :),
					(: command, "say 後會有期。少俠的武道﹐還長著呢。" :),
				}));
				return 1;
			}
			// 補贈（旗標保持 1，不重置進度）：先同步贈帶，再說氣氛話
			give_girdle(me);
			do_chat(({
				(: command, "say 咦﹖先前贈與少俠那條金絲翡翠帶﹐怎不在身上了﹖" :),
				(: command, "say 罷了﹐念在前番論武的緣分﹐老道再解一條與你。可要收好了。" :),
			}));
			return 1;
		}

		// 未得贈：論一回武，擊節稱善，同步解帶相贈、記旗標（防重領）。
		// 給帶在前、設旗標在後，皆為同步呼叫，玩家此刻必在場。
		give_girdle(me);
		me->set("quest/sq_fawang", 1);
		do_chat(({
			(: command, "say 哦﹖少俠這一身的見地﹐倒不似尋常市井把式。來來來﹐坐下細論。" :),
			(: command, "say 嗯 ...... 拳腳之爭﹐爭的不在一招一式的快慢﹐而在這一口真氣的收發由心。少俠此節﹐已得三分火候了。" :),
			(: command, "say 痛快﹗難得在這帝都的酒肆裡﹐遇上少俠這般可論武的後生。老道一見如故﹗" :),
			(: command, "say 老道腰間這條『金絲翡翠帶』﹐是我玄天教世代相傳的護身之物﹐束在腰間護住命門氣海﹐行功運氣最是得力。便贈與少俠﹐權當今日論武的彩頭罷﹗" :),
		}));
		return 1;
	}

	return notify_fail(
		"玄天教法王瞇眼一笑﹕少俠若有武道上的見地﹐儘管與老道論一論。"
		"（試試 ask fawang about 論武）\n");
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 少俠這是作甚﹖老道與你論的是武﹐可不是要與你動手。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
