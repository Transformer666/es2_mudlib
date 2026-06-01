// angler.c -- 浣月潭畔垂釣的釣叟（純氣氛閒談）；
//             兼水月村非戰鬥支線「福安客棧的清泉」的盛泉人。
//
// 本檔原為潭畔垂釣的氣氛 NPC（自得其樂、釣的是清靜）。為支線「福安客棧的清泉」
// 加掛盛泉一段：
//   玩家自採藥老叟討得空竹筒後﹐持空竹筒 ask angler about 清泉（或
//   give bamboo jug to angler）-> 釣叟接過空竹筒﹐到潭畔那道疏通好的隱蔽泉眼
//   舀滿一筒甜泉、封好筒口交還玩家﹐記 quest/shuiyue_spring_filled = 1。
//   交付「清泉竹筒」實物的同時銷除手中的「空竹筒」。指引玩家持滿筒回福安客棧。
//   （driver give 指令不認中文「給」﹐故持空竹筒 ask 即視同送件盛泉：同步盛泉、
//     交付滿筒、記旗標、並銷除空竹筒﹐與經 give 指令觸發 accept_object 等效。）
// 不動其原有的閒談 chat_msg 與 accept_fight。
//
// 滿筒採直接 new + move(who) 同步交付——give／ask 皆由玩家觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記旗標
// （與本村 d/shuiyue keeper、herbman、d/luocheng tea_guest 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void fill_jug(object me);

void create()
{
	set_name("釣叟", ({ "angler", "fisher", "diaosou" }) );
	set("nickname", "釣叟");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 58);
	set("gender", "male");
	set("long",
		"一位戴著箬笠、披著蓑衣的釣叟﹐穩穩地坐在浣月潭畔的青\n"
		"石上﹐支著一竿細細的釣絲﹐半日也不見動一動。他眉目疏朗﹐\n"
		"神色淡然﹐似乎釣的原不是魚﹐而是這一潭的清靜閒適。他在這\n"
		"潭邊坐了許多年﹐潭畔那道隱蔽的泉眼﹐他最是熟悉。得閒也可\n"
		"問問他﹕ask angler about 清泉。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"釣叟穩穩地把著釣竿﹐望著平靜的潭面﹐神色淡然﹐似已物我兩忘。\n",
		"釣叟悠悠地道﹕後生家﹐這潭裡的魚精著呢﹐釣得著釣不著﹐倒不打緊。\n",
		"釣叟拈起釣絲看了看空空的釣鉤﹐呵呵一笑﹐又不慌不忙地拋了回去。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 盛泉：釣叟到潭畔疏通好的隱蔽泉眼舀滿一筒甜泉﹐交付清泉竹筒、記旗標﹐
// 同時銷除玩家手中的空竹筒。直接 new + move(me) 同步交付（玩家此刻必在場）﹐
// 先交滿筒、銷空筒、後記旗標。
private void fill_jug(object me)
{
	object empty = present("bamboo jug", me);
	object full = new(__DIR__"obj/spring_jug");
	if( !full->move(me) ) full->move(environment());
	if( empty ) destruct(empty);
	me->set("quest/shuiyue_spring_filled", 1);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位釣叟甚麼﹖（試試 ask angler about 清泉）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("釣叟正凝神望著潭面的浮標﹐一時沒理會你。\n");

	// 清泉 / 泉眼：支線「福安客棧的清泉」——持空竹筒來盛泉
	if( arg == "angler about 清泉"
	||  arg == "angler about 泉"
	||  arg == "angler about 泉眼"
	||  arg == "angler about 活水"
	||  arg == "angler about 竹筒"
	||  arg == "angler about spring"
	||  arg == "angler about water" ) {
		object me = this_player();
		int q = me->query("quest/shuiyue_spring");

		// 已完成或已盛得清泉：純氣氛收尾
		if( q >= 2 || me->query("quest/shuiyue_spring_filled") ) {
			do_chat((: command,
				"say 那筒甜泉﹐老朽已替客官盛滿了。客官快持回福安客棧交與掌櫃罷﹐莫教那筒好水擱壞了味。" :));
			return 1;
		}

		// 進行中、持空竹筒：ask 即當作盛泉處理——盛泉、交滿筒、銷空筒、記旗標
		// （此路不經 give 指令﹐故由 fill_jug 自行銷除玩家手裡的空竹筒﹐
		//   與 accept_object 經 give 指令回 1 後自動銷除空竹筒等效﹐免玩家
		//   留著空筒重複觸發。）
		if( q == 1 && present("bamboo jug", me) ) {
			message_vision(
				"釣叟接過$N手裡的空竹筒﹐起身撥開潭畔一叢水草﹐露出石下\n"
				"一道汩汩沁水的隱泉﹐俯身舀了滿滿一筒﹐拿竹葉封了筒口。\n", me);
			// 先同步盛泉、交付滿筒、銷空筒、記旗標﹐再以 do_chat 收尾（滿筒已先到玩家手裡）。
			fill_jug(me);
			do_chat(({
				(: command, "say 客官是福安客棧掌櫃打發來盛清泉的罷﹖採藥的老倌兒把泉眼的亂石撥開了﹐這泉水又汩汩地出來了——喏﹐就在這潭畔石下﹐尋常人還真摸不著哩。" :),
				(: command, "say 老朽替客官舀了滿滿一筒﹐拿竹葉封了筒口﹐免得潑灑了。客官嚐嚐﹐這水清冽甘甜﹐比尋常井水強上十分。" :),
				(: command, "say 喏﹐這節清泉竹筒﹐方纔已奉到客官手裡了﹐快持回福安客棧交與掌櫃（ask keeper about 清泉﹐或 give spring jug to keeper）﹐也好教他驗驗這水的甘甜﹐了卻一樁心事。" :),
			}));
			return 1;
		}

		// 進行中、未持空竹筒：提示先去瀑下向採藥老叟討竹筒
		if( q == 1 ) {
			do_chat((: command,
				"say 客官要盛清泉﹖總得有個盛水的傢伙罷。客官且去村後的水月瀑布﹐尋崖下那位採藥老叟討個竹筒來（ask herbman about 清泉）﹐老朽纔好替客官盛。" :));
			return 1;
		}

		// 未接任務：純風味帶過
		do_chat((: command,
			"say 清泉﹖客官說的是潭畔石下那道隱泉罷。那是村裡引水的活水源頭﹐客官若為這水的事﹐還是先去福安客棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：浣月潭／垂釣
	if( arg == "angler about 浣月潭"
	||  arg == "angler about 潭"
	||  arg == "angler about 釣"
	||  arg == "angler about pond" ) {
		do_chat(({
			(: command, "say 這浣月潭啊﹐潭水靜得像面鏡子﹐月圓的夜裡﹐一輪月亮落在潭心﹐連魚兒都不忍攪了那月影哩。" :),
			(: command, "say 老朽在這潭邊坐了半輩子﹐釣的哪裡是魚﹐釣的是這份清靜。後生家若心煩﹐也來坐坐﹐保管把煩心事都忘了。" :),
		}));
		return 1;
	}

	return notify_fail("釣叟淡淡一笑﹕後生家問這個做甚﹖坐下來﹐陪老朽看看這潭水罷。\n");
}

// 收下信物：
//   空竹筒(bamboo jug) -- 支線「福安客棧的清泉」盛泉﹐持空筒且任務進行中時
//   收下、盛泉、交付清泉竹筒、記旗標 shuiyue_spring_filled。
// 不在此 move／destruct 空竹筒——give 指令於本函回 1 後會自行 destruct 有值的
// 空竹筒（與本村其餘送件 NPC、d/luocheng tea_guest 一致）﹔非送件玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("bamboo jug") ) {
		int q = who->query("quest/shuiyue_spring");

		// 未接任務／已完成：婉拒，不收下（避免吞掉空竹筒）
		if( q != 1 ) {
			do_chat((: command,
				"say 這竹筒 ... 客官還是自個兒收著罷，老朽一時也用不上。" :));
			return 0;
		}

		// 已盛過泉（滿筒已交）：婉拒，提示徑去回報客棧
		if( who->query("quest/shuiyue_spring_filled") ) {
			do_chat((: command,
				"say 客官的清泉方纔已盛滿了﹐這空筒就煩客官留著罷。快持那筒甜泉回福安客棧交與掌櫃便是（ask keeper about 清泉﹐或 give spring jug to keeper）。" :));
			return 0;
		}

		// 進行中、持空竹筒盛泉：盛泉、交付滿筒、記旗標（空竹筒由 give 指令於回 1 後自行銷除）
		message_vision(
			"釣叟接過$N遞來的空竹筒﹐起身撥開潭畔一叢水草﹐露出石下\n"
			"一道汩汩沁水的隱泉﹐俯身舀了滿滿一筒﹐拿竹葉封了筒口。\n", who);
		// give 指令會於本函回 1 後自行 destruct 空竹筒﹐故此處 fill_jug 只交滿筒、記旗標﹔
		// 為穩妥﹐fill_jug 內仍會嘗試銷除手中空筒（present 取到的即將被 give 銷除的同一個）。
		fill_jug(who);
		do_chat(({
			(: command, "say 客官是福安客棧掌櫃打發來盛清泉的罷﹖採藥的老倌兒把泉眼的亂石撥開了﹐這泉水又汩汩地出來了——喏﹐就在這潭畔石下﹐尋常人還真摸不著哩。" :),
			(: command, "say 老朽替客官舀了滿滿一筒﹐拿竹葉封了筒口。喏﹐這節清泉竹筒﹐方纔已奉到客官手裡了﹐快持回福安客棧交與掌櫃（ask keeper about 清泉﹐或 give spring jug to keeper）。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老朽用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗後生家好沒道理﹗欺負我一個垂釣的老頭子做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
