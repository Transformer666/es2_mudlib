// peddler.c -- 風城市集守小吃攤的北地婦人，賣乾糧吃食的攤販（F_VENDOR）；
//              兼風城非戰鬥支線「失算的籤筒」的第二處線索與信物交付人。
//
// 本檔原為純賣吃食的攤販（list/buy）。為支線「失算的籤筒」加掛一段對白：
//   玩家須已自差役處問著線索（quest/fengcheng_gua_runner），方
//   ask peddler about 龜甲 -> 攤販道出那拾荒小乞兒拿一枚亮晶晶的舊錢
//   跟她換了個奶餅充饑﹐當場把「龜甲卦錢」實物交與玩家﹐記
//   quest/fengcheng_gua_peddler = 1。指引玩家持卦錢回卦攤交還神算子。
// 不動攤販的買賣（merchandise / list / buy / do_vendor_list）與 accept_fight。
//
// 信物採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記
// 旗標﹐不把交付放進延遲的 do_chat 回呼（與 d/feixian keeper 交付收帳冊一致）。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("攤販", ({ "peddler", "vendor" }) );
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 43);
	set("gender", "female");
	set("long",
		"一個嗓門響亮的北地婦人﹐裹著件半舊的羊皮襖﹐守著自家\n"
		"的小吃攤子﹐見了客人便熱絡地招呼。你可以用 list 看她賣\n"
		"些什麼﹐用 buy 向她買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"攤販扯著嗓子吆喝道﹕熱乎的奶餅乾糧﹐風乾的牛羊肉﹐走過路過莫要錯過哩﹗\n",
		"攤販笑著招呼道﹕客官嚐嚐﹖這北地的吃食扛餓得很﹐趕路最是頂用﹗\n",
		"攤販一面收錢一面數落道﹕這朔風一年到頭颳個不停﹐小本生意難做喲。\n",
	}));
	// 市集小吃攤﹐沿用既有的乾糧吃食物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 60,
		"/obj/food/ricedough" : 50,
		"/obj/food/pork" : 30,
		"/obj/food/mooncake" : 30,
	]));

	setup();
	carry_money("coin", 120);
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
		return notify_fail("你想問這位攤販甚麼﹖\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("攤販正忙著招呼生意﹐一時沒空理你。\n");

	// 龜甲 / 卦錢：支線「失算的籤筒」的第二處線索與信物交付
	if( arg == "peddler about 龜甲"
	||  arg == "vendor about 龜甲"
	||  arg == "peddler about 卦錢"
	||  arg == "peddler about 龜甲卦錢"
	||  arg == "peddler about 小乞兒"
	||  arg == "peddler about gua coin"
	||  arg == "peddler about coin" ) {
		object me = this_player();
		int q = me->query("quest/fengcheng_gua");

		// 已完成：純氣氛收尾
		if( q >= 2 ) {
			do_chat((: command,
				"say 那枚舊錢交還神算子啦﹖那敢情好﹗難為你替那老先生跑這一趟。來﹐嚐嚐這剛出爐的奶餅﹖" :));
			return 1;
		}

		// 進行中、且已問著差役的線索：交付龜甲卦錢、記旗標
		if( q == 1 && me->query("quest/fengcheng_gua_runner") ) {
			// 已交付過（卦錢失落／誤毀）：補發一枚﹐進度旗標不重置﹐免卡關
			if( me->query("quest/fengcheng_gua_peddler") ) {
				if( !present("gua coin", me) ) {
					object c = new(__DIR__"obj/gua_coin");
					if( !c->move(me) ) c->move(environment());
					do_chat((: command,
						"say 咦﹐先前與你的那枚舊錢呢﹖莫不是失落了﹖罷罷罷﹐我這攤上零碎物事多﹐再翻一枚與你便是——可得拿穩了﹐快給神算子送回去。" :));
				} else {
					do_chat((: command,
						"say 那枚舊錢不是早與你了麼﹖快持回卦攤交與神算子去﹐莫教那老先生再等。" :));
				}
				return 1;
			}

			// 首次交付：先同步交物、後記旗標（玩家此刻必在場）
			{
				object c = new(__DIR__"obj/gua_coin");
				if( !c->move(me) ) c->move(environment());
			}
			me->set("quest/fengcheng_gua_peddler", 1);
			do_chat(({
				(: command, "say 哎喲﹐你說那個小叫花子啊﹖可不是麼﹗前兩日颳大風那陣﹐他攥著一枚亮晶晶的舊錢跑來我攤上﹐說撿著的﹐餓得慌﹐要拿它換個奶餅充饑。" :),
				(: command, "say 我瞧那錢是龜甲嵌銅鑄的﹐怪模怪樣﹐又使不出去﹐本不想收。可那娃娃餓得直哭﹐我心一軟﹐便給了他兩個熱奶餅﹐把這舊錢留下了——擱在攤上﹐倒也沒個用處。" :),
				(: command, "say 既是神算子卜卦失落的物事﹐那是該物歸原主。喏﹐這枚龜甲卦錢與你﹐你快持回廣場卦攤﹐交還那神算子去（give 龜甲卦錢 給 fortuneteller）﹐也算積德。" :),
			}));
			return 1;
		}

		// 進行中、但還沒問著差役的線索：先指引去茶樓問差役（不交物、不記旗標）
		if( q == 1 ) {
			do_chat((: command,
				"say 龜甲卦錢﹖你問得沒頭沒腦的﹐我一個賣吃食的﹐哪曉得甚麼卦錢。你且先打聽明白了是怎麼回事﹐再來問我罷。" :));
			return 1;
		}

		// 未接任務：純風味帶過，不推進
		do_chat((: command,
			"say 龜甲卦錢﹖那是廣場上神算子卜卦的物事﹐與我這小吃攤有甚相干﹖客官要買吃食只管說﹐旁的我可不曉得。" :));
		return 1;
	}

	return notify_fail("攤販笑道﹕客官若是要買吃食﹐只管 list 來看﹔旁的我這婦道人家可幫不上忙。\n");
}

int accept_fight(object ob)
{
	do_chat("攤販雙手叉腰﹐高聲嚷道﹕光天化日的﹐你想幹什麼﹖來人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
