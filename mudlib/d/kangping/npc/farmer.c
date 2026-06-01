// farmer.c -- 村外田壟上歇晌的田裡老農（純氣氛閒談）；
//             兼康平村非戰鬥支線「康平新米飯糰」的指路與授器人。
//
// 本檔原為村外田壟看顧莊稼的氣氛 NPC。為支線「新米飯糰」加掛一段對白：
//   玩家須已自康平小店店家接了任務（quest/kangping_rice==1），方
//   ask farmer about 新米 -> 老農道出自家田裡新米的好處﹐當場就石碾碾一缽最新
//   鮮的新米、連陶缽一併交與玩家﹐記 quest/kangping_rice_bowl = 1。指引玩家持
//   新米陶缽到井臺尋灶上嬸子蒸飯。
//
// 信物採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記
// 旗標﹐不把交付放進延遲的 do_chat 回呼（與 d/weiguo welltender、d/ziyan springman 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("田裡老農", ({ "farmer", "old farmer", "tianlilaonong" }) );
	set("nickname", "田裡老農");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 63);
	set("gender", "male");
	set("long",
		"一位在村外田壟侍弄莊稼的老農﹐生得清癯硬朗﹐裹著件汗\n"
		"濕的粗布短褐﹐褲腳沾滿了田泥﹐成日守著自家這一片田﹐犁地、\n"
		"插秧、引水、收割﹐沒有他不在行的。他在這田壟上侍弄了一輩子\n"
		"的莊稼﹐這一方田的脾性、節氣的早晚﹐沒有他不熟的。得閒也可\n"
		"問問他﹕ask farmer about 新米。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"田裡老農拄著鋤頭直起腰﹐捶了捶痠痛的後背﹐瞇眼望著滿田金黃的稻穗﹐臉上掛著掩不住的笑。\n",
		"田裡老農蹲下身﹐捻起一穗稻子在手裡搓了搓﹐吹去穀殼﹐看著掌心裡飽滿的米粒﹐緩緩道﹕今年這米﹐成色好哇。\n",
		"田裡老農抹了把汗﹐喃喃道﹕莊稼人一年到頭﹐圖的就是這秋收進倉的踏實﹐旁的都是虛的。\n",
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
		return notify_fail("你想問這田裡老農甚麼﹖（試試 ask farmer about 新米）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("田裡老農正彎著腰侍弄莊稼﹐一時沒理會你。\n");

	// 新米 / 稻穀 / 米：支線「新米飯糰」——指路、授新米陶缽
	if( arg == "farmer about 新米"
	||  arg == "farmer about 稻穀"
	||  arg == "farmer about 稻"
	||  arg == "farmer about 穀"
	||  arg == "farmer about 米"
	||  arg == "farmer about 陶缽"
	||  arg == "farmer about rice"
	||  arg == "farmer about grain" ) {
		object me = this_player();
		int q = me->query("quest/kangping_rice");

		// 已完成：純氣氛收尾
		if( q >= 2 ) {
			do_chat((: command,
				"say 那籠新米飯糰蒸成了﹖那敢情好﹗難為客官替小店跑這一趟。咱這田裡新收的米﹐上籠一蒸﹐香軟頂飢﹐是咱康平村豐年謝場的喜飯哩。" :));
			return 1;
		}

		// 進行中（已自店家接任務）：道出新米好處、碾米授缽、記旗標
		if( q == 1 ) {
			// 已交付過（新米陶缽失落／誤毀）：補碾一缽﹐進度旗標不重置﹐免卡關
			if( me->query("quest/kangping_rice_bowl") ) {
				if( !present("rice bowl", me) && !present("rice dough", me) ) {
					object c = new(__DIR__"obj/rice_bowl");
					if( !c->move(me) ) c->move(environment());
					do_chat((: command,
						"say 咦﹐先前與客官的那缽新米呢﹖莫不是失落了﹖罷罷罷﹐老朽這就再與客官碾一缽——快拿去井臺尋灶上嬸子蒸飯罷。" :));
				} else {
					do_chat((: command,
						"say 那缽新米不是早與客官了麼﹖快持去村心西北窄巷盡頭的井臺﹐尋那位灶上嬸子﹐請她把新米上籠蒸成飯糰（ask cook about 新米﹐或 give rice bowl to cook），莫教小店的店家久等。" :));
				}
				return 1;
			}

			// 首次交付：先同步碾米交缽、後記旗標（玩家此刻必在場）
			{
				object c = new(__DIR__"obj/rice_bowl");
				if( !c->move(me) ) c->move(environment());
			}
			me->set("quest/kangping_rice_bowl", 1);
			message_vision(
				"田裡老農自田邊的穀堆裡掬了一捧新割的稻穀﹐到村心石碾上碾去\n"
				"了穀殼﹐簸淨了﹐盛了滿滿一缽雪白的新米﹐拿一片乾荷葉虛掩了\n"
				"缽口﹐遞到$N手裡。\n", me);
			do_chat(({
				(: command, "say 康平小店的店家打發客官來備新米飯糰﹖嗯﹐這事老朽再熟不過了。要蒸那飯糰﹐頭一樁便是這田裡剛收、現碾的新米——今年雨水勻、年成好﹐這米顆顆飽滿﹐磨出來雪白晶瑩﹐拿來蒸飯最是香軟﹐隔年的陳米可比不得。" :),
				(: command, "say 喏﹐這缽米﹐是老朽剛在村心石碾上碾的﹐最是新鮮﹐連盛米的陶缽一併與客官使罷。客官拿著它﹐到村心西北窄巷盡頭的井臺去﹐尋那位灶上嬸子——她蒸飯的手藝是村裡一絕﹐請她拿這新米上籠蒸成飯糰（ask cook about 新米﹐或 give rice bowl to cook）﹐再持回小店交與店家便是。" :),
			}));
			return 1;
		}

		// 未接任務：純風味帶過，不推進（新米飯糰的事先去問小店店家）
		do_chat((: command,
			"say 新米﹖客官說的是拿這田裡新收的米蒸的新米飯糰罷﹖那是咱村裡謝場待客的好東西。客官若為這新米飯糰的事﹐還是先去康平小店問問店家罷。" :));
		return 1;
	}

	// 純氣氛閒談：田壟／莊稼／康平村
	if( arg == "farmer about 田"
	||  arg == "farmer about 田壟"
	||  arg == "farmer about 莊稼"
	||  arg == "farmer about 康平村"
	||  arg == "farmer about 康平"
	||  arg == "farmer about kangping" ) {
		do_chat(({
			(: command, "say 康平村啊﹐就這麼巴掌大的一座莊稼村子﹐合村人家都靠著村外這一片田過活。村子取名『康平』﹐圖的就是個身康家平、年年有個好收成。今年這年成﹐可真叫人歡喜。" :),
			(: command, "say 老朽在這田壟上侍弄了一輩子莊稼﹐犁地、插秧、引水、收割﹐一年到頭跟著節氣轉。莊稼人不求大富大貴﹐只求風調雨順、五穀豐登﹐一家老小有口安生飯吃﹐便知足嘍。" :),
		}));
		return 1;
	}

	return notify_fail("田裡老農拄著鋤頭憨憨一笑﹕客官問這個做甚﹖田裡活計忙﹐閒話改日再嘮罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖老朽一個刨土種田的山野之人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
