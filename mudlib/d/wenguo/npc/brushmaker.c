// brushmaker.c -- 制筆作坊裡紮筆製筆的老筆匠（純氣氛閒談）；
//                 兼文國縣非戰鬥支線「天風筆會」的指路與授匣人。
//
// 本檔為制筆作坊紮筆的氣氛 NPC。為支線「天風筆會」加掛一段對白：
//   玩家須已自天風客棧掌櫃接了任務（quest/wenguo_brush==1），方
//   ask brushmaker about 文房 -> 老筆匠揀一管作坊最好的「天風狼毫」新筆﹐安進一隻
//   隨身的「筆匣」交與玩家﹐記 quest/wenguo_brush_case = 1。指引玩家持筆匣到松煙墨坊
//   尋墨工配墨。
//
// 信物採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記
// 旗標﹐不把交付放進延遲的 do_chat 回呼（與 d/shuiyue herbman、d/louxian gardener 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老筆匠", ({ "brushmaker", "old brushmaker", "laobijiang" }) );
	set("nickname", "老筆匠");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 63);
	set("gender", "male");
	set("long",
		"一位制筆作坊的老筆匠﹐生得清癯硬朗﹐裹著件沾了膠漬的\n"
		"短褐﹐就著天光在水盆邊一根根挑理著筆毫。他在這作坊裡紮了\n"
		"大半輩子的筆﹐那『天風狼毫』軟硬配料的分寸、紮鋒收尖的訣\n"
		"竅﹐沒有他不摸透的。得閒也可問問他﹕ask brushmaker about 文房。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老筆匠俯身在水盆邊﹐小心地挑理著一簇筆毫﹐口中念念有詞地數著毫的根數。\n",
		"老筆匠直起腰捶了捶背﹐瞇眼端詳著手裡半成的筆鋒道﹕這筆啊﹐尖、齊、圓、健﹐四樣缺一不可。\n",
		"老筆匠拈起一管紮好的新筆﹐就著天光看了看鋒﹐滿意地點點頭﹐又倒懸到樑上晾著。\n",
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
		return notify_fail("你想問這老筆匠甚麼﹖（試試 ask brushmaker about 文房）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老筆匠正俯身挑理著筆毫﹐一時沒理會你。\n");

	// 文房 / 筆 / 天風狼毫：支線「天風筆會」——指路、授筆匣（內安新筆）
	if( arg == "brushmaker about 文房"
	||  arg == "brushmaker about 筆"
	||  arg == "brushmaker about 墨"
	||  arg == "brushmaker about 狼毫"
	||  arg == "brushmaker about 筆匣"
	||  arg == "brushmaker about brush"
	||  arg == "brushmaker about ink" ) {
		object me = this_player();
		int q = me->query("quest/wenguo_brush");

		// 已完成：純氣氛收尾
		if( q >= 2 ) {
			do_chat((: command,
				"say 那副文房雅禮辦成了﹖那敢情好﹗難為客官替掌櫃跑這一趟。咱作坊的天風狼毫配上墨坊的松煙好墨﹐果然是天造地設的一對。" :));
			return 1;
		}

		// 進行中（已自掌櫃接任務）：揀新筆、安筆匣、交付、記旗標
		if( q == 1 ) {
			// 已交付過（筆匣失落／誤毀）：補發一隻﹐進度旗標不重置﹐免卡關
			if( me->query("quest/wenguo_brush_case") ) {
				if( !present("brush case", me) && !present("writing case", me) ) {
					object c = new(__DIR__"obj/brush_case");
					if( !c->move(me) ) c->move(environment());
					do_chat((: command,
						"say 咦﹐先前與客官的那隻筆匣呢﹖莫不是失落了﹖罷罷罷﹐老朽這兒再安一管好筆與客官——快拿去松煙墨坊尋墨工配墨罷。" :));
				} else {
					do_chat((: command,
						"say 那筆匣不是早與客官了麼﹖快持去翰墨廣場東邊的松煙墨坊﹐尋那位墨工﹐配一錠相稱的松煙好墨進匣（ask inkmaker about 文房﹐或 give brush case to inkmaker），莫教客棧的掌櫃久等。" :));
				}
				return 1;
			}

			// 首次交付：先同步交物、後記旗標（玩家此刻必在場）
			{
				object c = new(__DIR__"obj/brush_case");
				if( !c->move(me) ) c->move(environment());
			}
			me->set("quest/wenguo_brush_case", 1);
			do_chat(({
				(: command, "say 天風客棧的掌櫃打發客官來討文房雅禮的筆﹖嗯﹐這事老朽再清楚不過了。咱作坊這『天風狼毫』﹐取的是北地黃鼠狼秋後最健的尾毫﹐配上幾根羊毫定鋒﹐軟硬恰好﹐尋常地方可尋不著。" :),
				(: command, "say 客官稍候——老朽這就揀一管紮得最好的﹐尖、齊、圓、健﹐挑不出一根岔毫﹐與客官安進這隻筆匣裡。這匣子是老朽隨身的家什﹐就與客官使罷。" :),
				(: command, "say 喏﹐這隻安了新筆的筆匣﹐方纔已奉到客官手裡了。光有好筆還不成一副文房﹐客官拿著它﹐到翰墨廣場東邊的松煙墨坊﹐尋那位墨工﹐配一錠相稱的松煙好墨進匣（ask inkmaker about 文房﹐或 give brush case to inkmaker）﹐再持回客棧交與掌櫃便是。" :),
			}));
			return 1;
		}

		// 未接任務：純風味帶過，不推進（文房的事先去問客棧掌櫃）
		do_chat((: command,
			"say 文房﹖客官說的是咱作坊紮的這天風狼毫罷。這筆是好筆﹐只是無端端的﹐老朽也不好平白與人——客官若為這文房的事﹐還是先去天風客棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：制筆作坊／紮筆
	if( arg == "brushmaker about 作坊"
	||  arg == "brushmaker about 制筆"
	||  arg == "brushmaker about 紮筆"
	||  arg == "brushmaker about studio" ) {
		do_chat(({
			(: command, "say 這制筆的工夫啊﹐看著粗﹐做著細。一管筆從選毫、去絨、墊胎、紮鋒到裝桿﹐七十二道工序﹐一道也馬虎不得﹐老朽做了一輩子﹐方敢說摸著了門道。" :),
			(: command, "say 咱文國這『翰墨之鄉』的名號﹐一半是這作坊裡一管管好筆掙來的。後生家得空﹐也來看看老朽紮筆﹐這手藝﹐眼看著就要尋不著傳人嘍。" :),
		}));
		return 1;
	}

	return notify_fail("老筆匠瞇眼一笑﹕客官問這個做甚﹖這作坊裡都是些紮筆的粗活﹐看看便罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖老朽一個紮筆的山野匠人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
