// captain.c -- 檒城衛兵統領劉開，鎮守望安港的港城武官（純氣氛 NPC）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("劉開", ({ "liu kai", "liukai", "captain", "kai" }) );
	set("nickname", "衛兵統領");
	set_attr("str", 24);
	set_attr("con", 22);
	set_attr("int", 18);
	set_race("human");
	set_class("fighter");
	set_level(22);

	set_skill("blade", 70);
	set_skill("parry", 60);
	set_skill("dodge", 50);
	set_skill("unarmed", 45);
	set_skill("force", 50);

	set("age", 41);
	set("gender", "male");
	set("long",
		"這位便是鎮守檒城的衛兵統領劉開。他身形魁梧﹐一張方臉曬\n"
		"得黝黑﹐頷下一部濃密的虬髯﹐眉宇間自有一股久經行伍的剽悍\n"
		"之氣。他披著一領半舊的皮甲﹐腰懸一柄寬刃的朴刀﹐按刀立在\n"
		"公案旁﹐目光如電﹐進出的生面孔都逃不過他的打量。聽聞這港\n"
		"城雖偏處西陲﹐卻多虧有他坐鎮﹐海寇也不敢輕易來犯。你或許\n"
		"可以問問他﹕ask captain about 檒城。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"劉開按著刀柄﹐緩緩踱步﹐銳利的目光掃過進出的人流。\n",
		"劉開沉聲道﹕我這檒城雖小﹐卻是西陲門戶﹐海防半點馬虎不得。\n",
		"劉開捋著虬髯﹐眉頭微皺﹐似在掛心著外海那些不安分的海寇。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("broadsword") )->wield();
	carry_money("coin", 150);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 生面孔﹖到我檒城的地界﹐安分守己便好。" :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問劉統領甚麼﹖（試試 ask captain about 檒城）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("劉開正按刀巡視﹐沒空理你。\n");

	// 檒城：港城的由來與治安
	if( arg == "captain about 檒城"
	||  arg == "liu kai about 檒城"
	||  arg == "captain about city"
	||  arg == "captain about fancheng" ) {
		do_chat(({
			(: command, "say 我檒城臨海而立﹐是這西陲一帶唯一像樣的商港。南來北往的番舶漁舟皆泊在望安港裡﹐城裡城外﹐十之七八都靠這片海吃飯。" :),
			(: command, "say 港城人雜﹐三教九流都有﹐難免有那不開眼的宵小。我手下這幾十號弟兄日夜巡著﹐倒也還鎮得住。你既來了﹐守著規矩﹐自然無事。" :),
		}));
		return 1;
	}

	// 港 / 望安港 / 海寇：港務與海防
	if( arg == "captain about 港"
	||  arg == "captain about 望安港"
	||  arg == "captain about 海寇"
	||  arg == "captain about 海防"
	||  arg == "captain about harbor"
	||  arg == "captain about pirate" ) {
		do_chat(({
			(: command, "say 望安港是檒城的命脈﹐這海防自然是我這統領頭一樁的差事。外海有幾股海寇﹐近來愈發猖獗﹐專劫往來的番舶貨船﹐著實可恨。" :),
			(: command, "say 我已加派了人手上城頭瞭望﹐入夜便敲鐘戒備。只盼上頭早些撥下戰船﹐我也好出海會一會那幫賊子﹗" :),
		}));
		return 1;
	}

	// 雍和：埋一點羅城／雍和首相的傳聞（與設定相關，純氣氛）
	if( arg == "captain about 雍和"
	||  arg == "captain about 羅城"
	||  arg == "captain about yonghe"
	||  arg == "captain about luocheng" ) {
		do_chat(({
			(: command, "say 雍和大人麼 ... 那是當朝的首相﹐位高權重﹐尋常人哪輕易見得著。聽聞羅城那邊﹐近來頗有些與雍和大人相關的風聲。" :),
			(: command, "say 這等朝堂上的大事﹐豈是我這守港的武夫該議論的﹖客官若真有心打聽﹐往東北的羅城走一遭﹐興許能聽著些門道。我可甚麼都沒說。" :),
		}));
		return 1;
	}

	return notify_fail("劉開皺眉道﹕這個 ... 我一介武夫﹐答不上來。（試試 ask captain about 檒城）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 放肆﹗竟敢在我檒城衛兵所裡撒野﹖來人﹐給我拿下﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
