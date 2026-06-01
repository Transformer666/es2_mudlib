// gardener.c -- 甘泉園侍弄花木茶圃的老圃（純氣氛閒談）；
//               兼婁縣非戰鬥支線「甘泉茶會」的指路與授罐人。
//
// 本檔為甘泉園採茶的氣氛 NPC。為支線「甘泉茶會」加掛一段對白：
//   玩家須已自甘泉客棧掌櫃接了任務（quest/louxian_spring==1），方
//   ask gardener about 甘泉 -> 老圃摘一撮園裡最好的「甘泉雀舌」嫩茶﹐封進一隻
//   隨身的「茶罐」交與玩家﹐記 quest/louxian_caddy = 1。指引玩家持茶罐到甘泉井
//   尋守井老叟注水。
//
// 信物採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記
// 旗標﹐不把交付放進延遲的 do_chat 回呼（與 d/shuiyue herbman 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老圃", ({ "gardener", "old gardener", "laopu" }) );
	set("nickname", "老圃");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 64);
	set("gender", "male");
	set("long",
		"一位侍弄甘泉園的老圃﹐生得清癯硬朗﹐裹著件沾了泥點的\n"
		"短褐﹐荷著一柄小鋤﹐成日價躬身在茶畦花圃間鬆土打理。他在\n"
		"這園裡侍弄了大半輩子的花木茶樹﹐園裡那幾畦『甘泉雀舌』的\n"
		"脾性﹐沒有他不摸透的。得閒也可問問他﹕ask gardener about 甘泉。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老圃躬身在茶畦間﹐小心地給茶樹鬆著土﹐又掐去幾片枯黃的老葉。\n",
		"老圃直起腰捶了捶背﹐瞇眼望著渠水道﹕這茶啊﹐喝的是個水﹐沒咱這甘泉﹐再好的雀舌也出不來味。\n",
		"老圃拈起一片新抽的雀舌嫩芽﹐就著天光端詳﹐滿意地點點頭﹐又小心收進懷裡。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這老圃甚麼﹖（試試 ask gardener about 甘泉）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老圃正俯身給茶畦鬆著土﹐一時沒理會你。\n");

	// 甘泉 / 雀舌 / 茶：支線「甘泉茶會」——指路、授茶罐（內封雀舌嫩茶）
	if( arg == "gardener about 甘泉"
	||  arg == "gardener about 泉"
	||  arg == "gardener about 茶"
	||  arg == "gardener about 雀舌"
	||  arg == "gardener about 茶罐"
	||  arg == "gardener about spring"
	||  arg == "gardener about tea" ) {
		object me = this_player();
		int q = me->query("quest/louxian_spring");

		// 已完成：純氣氛收尾
		if( q >= 2 ) {
			do_chat((: command,
				"say 那席甘泉茶辦成了﹖那敢情好﹗難為客官替掌櫃跑這一趟。咱園裡的雀舌配上井裡的甘泉﹐果然是天造地設的一對。" :));
			return 1;
		}

		// 進行中（已自掌櫃接任務）：摘雀舌、封茶罐、交付、記旗標
		if( q == 1 ) {
			// 已交付過（茶罐失落／誤毀）：補發一隻﹐進度旗標不重置﹐免卡關
			if( me->query("quest/louxian_caddy") ) {
				if( !present("tea caddy", me) && !present("spring caddy", me) ) {
					object c = new(__DIR__"obj/tea_caddy");
					if( !c->move(me) ) c->move(environment());
					do_chat((: command,
						"say 咦﹐先前與客官的那隻茶罐呢﹖莫不是失落了﹖罷罷罷﹐老朽這兒再封一罐雀舌與客官——快拿去甘泉井畔尋守井老叟注水罷。" :));
				} else {
					do_chat((: command,
						"say 那茶罐不是早與客官了麼﹖快持去街心北邊的甘泉井﹐尋那位守井老叟﹐注一罐井裡的甘泉活水（ask welltender about 甘泉﹐或 give tea caddy to welltender），莫教客棧的掌櫃久等。" :));
				}
				return 1;
			}

			// 首次交付：先同步交物、後記旗標（玩家此刻必在場）
			{
				object c = new(__DIR__"obj/tea_caddy");
				if( !c->move(me) ) c->move(environment());
			}
			me->set("quest/louxian_caddy", 1);
			do_chat(({
				(: command, "say 甘泉客棧的掌櫃打發客官來討甘泉茶的茶料﹖嗯﹐這事老朽再清楚不過了。咱園裡這幾畦『甘泉雀舌』﹐用井裡的活水澆灌﹐又得這園中清氣養著﹐是頂好的茶﹐尋常地方可尋不著。" :),
				(: command, "say 客官稍候——老朽這就揀那新抽的嫩芽﹐掐一撮頂尖的雀舌﹐與客官封進這隻小錫罐裡。這罐子是老朽隨身封茶的家什﹐就與客官使罷。" :),
				(: command, "say 喏﹐這隻封了雀舌的茶罐﹐方纔已奉到客官手裡了。光有好茶還不成﹐客官拿著它﹐到街心北邊的甘泉井畔﹐尋那位守井老叟﹐注一罐井裡剛汲的甘泉活水（ask welltender about 甘泉﹐或 give tea caddy to welltender）﹐再持回客棧交與掌櫃便是。" :),
			}));
			return 1;
		}

		// 未接任務：純風味帶過，不推進（甘泉茶的事先去問客棧掌櫃）
		do_chat((: command,
			"say 甘泉茶﹖客官說的是咱園裡這雀舌煮的茶罷。這茶是好茶﹐只是無端端的﹐老朽也不好平白與人——客官若為這茶的事﹐還是先去甘泉客棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：甘泉園／茶圃
	if( arg == "gardener about 甘泉園"
	||  arg == "gardener about 園"
	||  arg == "gardener about 園子"
	||  arg == "gardener about garden" ) {
		do_chat(({
			(: command, "say 這甘泉園啊﹐是縣裡幾位好事的鄉紳合力修的﹐引了井裡的甘泉繞園開渠﹐種些花木茶樹﹐圖個鬧中取靜﹐給縣裡人歇晌閒坐。" :),
			(: command, "say 老朽在這園裡侍弄了大半輩子﹐別的本事沒有﹐單論這伺候茶樹花木的工夫﹐縣裡還真尋不出第二個。後生家得空﹐也來園裡坐坐﹐聽聽這渠水叮咚。" :),
		}));
		return 1;
	}

	return notify_fail("老圃瞇眼一笑﹕客官問這個做甚﹖這園子清幽﹐多坐一坐罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖老朽一個侍弄花草的山野之人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
