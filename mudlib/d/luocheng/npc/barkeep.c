// barkeep.c -- 羅城客棧的酒保（F_VENDOR 供應乾糧吃食）；
//              兼羅城非戰鬥支線「羅城客棧的尋硯」的尋物信物交付人。
//
// 本檔原為純賣吃食的店小二（list/buy）。為支線「羅城客棧的尋硯」加掛一段對白：
//   玩家須已自掌櫃接了任務（quest/luocheng_yan==1），方
//   ask barkeep about 端硯 -> 店小二自櫃格裡翻出那方誤收的端硯﹐當場交與玩家﹐
//   記 quest/luocheng_yan_found = 1。指引玩家持硯到聽濤茶樓送還候缺選官。
// 不動店小二的買賣（merchandise / list / buy / do_vendor_list）與 accept_fight。
//
// 信物採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記
// 旗標﹐不把交付放進延遲的 do_chat 回呼（與 d/fengcheng peddler 交付卦錢一致）。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("店小二", ({ "luocheng_inn_barkeep", "barkeep", "xiaoer" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 21);
	set("gender", "male");
	set("long",
		"一個手腳麻利的店小二﹐肩上搭著條乾淨的手巾﹐在桌椅之\n"
		"間穿梭招呼﹐替客人篩茶添點。你可以用 list 看可以點什麼﹐\n"
		"用 buy 跟店小二點吃食﹔得閒也可問問他﹕ask barkeep about 端硯。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"店小二脆生生地吆喝道﹕老爺您點什麼﹖小店的細點乾糧樣樣齊備﹗\n",
		"店小二一面替客人續著熱茶﹐一面殷勤地抹著鄰桌的桌面。\n",
	}));
	// 客棧前廳供應乾糧吃食﹐沿用既有的食物物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/dumpling" : 50,
		"/obj/food/mooncake" : 30,
		"/obj/food/pork" : 40,
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位店小二甚麼﹖（試試 ask barkeep about 端硯）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("店小二正忙著招呼客人﹐一時沒空理你。\n");

	// 端硯 / 遺硯：支線「羅城客棧的尋硯」的尋物信物交付
	if( arg == "barkeep about 端硯"
	||  arg == "xiaoer about 端硯"
	||  arg == "barkeep about 硯"
	||  arg == "barkeep about 遺硯"
	||  arg == "barkeep about 失物"
	||  arg == "barkeep about inkstone"
	||  arg == "barkeep about yan" ) {
		object me = this_player();
		int q = me->query("quest/luocheng_yan");

		// 已完成：純氣氛收尾
		if( q >= 2 ) {
			do_chat((: command,
				"say 那方硯送還周老爺啦﹖那敢情好﹗難為客官替小店跑這一趟﹐了結了這樁失物。客官要點吃食只管說。" :));
			return 1;
		}

		// 進行中（已自掌櫃接任務）：自櫃格翻出端硯、交與玩家、記旗標
		if( q == 1 ) {
			// 已交付過（端硯失落／誤毀）：補發一方﹐進度旗標不重置﹐免卡關
			if( me->query("quest/luocheng_yan_found") ) {
				if( !present("duan yan", me) ) {
					object y = new(__DIR__"obj/duan_yan");
					if( !y->move(me) ) y->move(environment());
					do_chat((: command,
						"say 咦﹐先前與客官的那方硯呢﹖莫不是失落了﹖罷罷罷﹐方纔小的在櫃格底下又翻著個硯匣﹐想是一發收進去的——客官拿穩了﹐快給聽濤茶樓的周老爺送回去。" :));
				} else {
					do_chat((: command,
						"say 那方硯不是早與客官了麼﹖快持去隔鄰的聽濤茶樓﹐送還那位姓周的選官（ask tea guest about 端硯﹐或 give 端硯 to tea guest），莫教他久等。" :));
				}
				return 1;
			}

			// 首次交付：先同步交物、後記旗標（玩家此刻必在場）
			{
				object y = new(__DIR__"obj/duan_yan");
				if( !y->move(me) ) y->move(environment());
			}
			me->set("quest/luocheng_yan_found", 1);
			do_chat(({
				(: command, "say 掌櫃的差客官來取周老爺的硯﹖哎喲﹐這事可怨小的眼拙﹗那日待客忙亂﹐小的掃堂時瞧見上房裡擱著個烏木硯匣﹐只當是客人不要的零碎﹐便連著雜物一發收進櫃格去了﹐竟沒想著是周老爺落下的心愛之物。" :),
				(: command, "say 小的這就與客官取來——喏﹐就是這方端硯﹐石質溫潤﹐背上還刻著閒章詩句﹐一瞧便知是讀書人寶愛的舊物﹐難怪掌櫃的這般上心。" :),
				(: command, "say 客官快持這方硯﹐到隔鄰的聽濤茶樓去﹐尋那位姓周的候缺選官﹐把硯送還與他（ask tea guest about 端硯﹐或 give 端硯 to tea guest）。他失而復得﹐必定歡喜﹐也算了結了小的這樁過失。" :),
			}));
			return 1;
		}

		// 未接任務：純風味帶過，不推進（硯的事先去問掌櫃）
		do_chat((: command,
			"say 端硯﹖客官說的是哪一方硯﹖這上房客人來來去去的物事多﹐小的也記不真。客官若有甚遺失的物事﹐還是先問問櫃上的掌櫃罷。" :));
		return 1;
	}

	return notify_fail("店小二陪笑道﹕客官若是要點吃食﹐只管 list 來看﹔旁的小的可幫不上甚麼忙。\n");
}

int accept_fight(object ob)
{
	do_chat("店小二縮著脖子賠笑道﹕老爺息怒﹐小的這就給您換桌好的﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
