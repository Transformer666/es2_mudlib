// guide.c -- 江湖嚮導，雪亭鎮廣場的引路前輩
//
// 用途：替新到雪亭鎮的後生指引七大門派的所在與拜師之路。
//   玩家 ask guide about 拜師 / 門派 -> 給七大職業->門派的總覽與大致去向
//   玩家 ask guide about <職業/門派名>      -> 給該派的職業、招牌武學、
//                                            從廣場中央出發的精確路線、
//                                            以及到了山門後如何拜師
//
// 拜師指令：到了各派山門找掌門 NPC（皆可用 master 為 id），鍵入
//           apprentice master 即可（見 cmds/std/apprentice.c）。
//
// 純對話 NPC﹐不涉戰鬥﹔仿 d/snow/npc/cakegammer.c、axing.c 的 ask 模式。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("江湖嚮導", ({ "guide", "xiangdao", "old guide" }) );
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("gender", "male");
	set("age", 55);
	set("long",
		"這是一位鬢角微白的江湖前輩﹐一身洗得發白的勁裝﹐腰間掛著個\n"
		"褪色的酒葫蘆。他在雪亭鎮廣場待了大半輩子﹐走南闖北﹐認得這\n"
		"一帶七大門派的門路﹐最愛替初出茅廬的後生指點迷津。\n"
		"你若想學藝拜師﹐不妨問問他﹕\n"
		"  ask guide about 拜師   （聽他講講雪亭鎮一帶有哪些門派）\n"
		"  ask guide about 門派   （同上）\n"
		"  ask guide about 天師派 （單問某一派的去向與招式﹐其餘類推）\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) )
		do_chat((: command,
			"say 後生面生得很﹐可是要拜師學藝﹖不妨問問老朽﹕"
			"ask guide about 拜師。" :));
}

// 七大門派總覽
private void tell_overview(object me)
{
	do_chat(({
		(: command, "say 咱雪亭鎮一帶﹐共有七大門派﹐分屬七種行當﹐"
			"你瞧瞧合不合脾胃﹕" :),
		(: command, "say 一、武者 —— 冷梅莊﹐使長劍﹐"
			"從廣場中央往西、再往南、再往西南便到。" :),
		(: command, "say 二、道士 —— 天師派﹐以火證道﹐"
			"從廣場中央往東、再往東北上山即到。" :),
		(: command, "say 三、和尚 —— 白象寺﹐使禪杖降魔﹐"
			"從廣場中央往南、再往西南便到。" :),
		(: command, "say 四、書生 —— 步玄派﹐使劍佐文心﹐"
			"從廣場中央往北、再往西北便到。" :),
		(: command, "say 五、小偷 —— 瑯夷派﹐使匕首暗算﹐藏身僻巷地窖﹐"
			"從廣場中央往東、再往東到僻巷、再往下潛入。" :),
		(: command, "say 六、軍人 —— 振武軍營﹐使長槍列陣﹐"
			"從廣場中央往西、再往東北便到。" :),
		(: command, "say 七、方士 —— 龍圖丹派﹐煉丹施針濟世﹐"
			"從廣場中央往東、再往東南便到。" :),
		(: command, "say 想細問哪一派的路與招式﹐便 ask guide about 該派名"
			"﹐譬如 ask guide about 天師派。到了山門找那掌門﹐"
			"鍵入 apprentice master 便可拜師。" :),
	}));
}

// 各派細節：職業、招牌武學、從廣場中央出發的精確路線、到山門後如何拜師
private void tell_hanmei(object me)   // 武者 冷梅莊
{
	do_chat(({
		(: command, "say 冷梅莊﹗那是武者的劍派﹐莊主人稱「傲梅劍客」﹐"
			"一手冷梅劍法﹐劍勢如寒梅綻放﹐冷冽中暗藏殺機。" :),
		(: command, "say 路是這麼走的：從廣場中央 west（西）到廣場西邊﹐"
			"再 south（南）到廣場西南角﹐再 southwest（西南）"
			"便是冷梅莊大門了。" :),
		(: command, "say 進門往北是前院﹐尋著冷梅莊主﹐"
			"鍵入 apprentice master 拜他為師。" :),
	}));
}

private void tell_tianshi(object me)  // 道士 天師派
{
	do_chat(({
		(: command, "say 天師派﹗那是道士一脈﹐朱衣以火證道﹐"
			"掌教真人一身焚天煉地的火術道法﹐了得得很。" :),
		(: command, "say 路是這麼走的：從廣場中央 east（東）到廣場東邊﹐"
			"再 northeast（東北）拾級上山﹐便是天師派山門。" :),
		(: command, "say 進門往北是庭院﹐尋著天師掌教﹐"
			"鍵入 apprentice master 拜他為師。" :),
	}));
}

private void tell_baixiang(object me) // 和尚 白象寺
{
	do_chat(({
		(: command, "say 白象寺﹗那是和尚的佛門﹐羅漢一脈以杖降魔﹐"
			"方丈一手金剛伏魔杖法﹐降魔伏邪。" :),
		(: command, "say 路是這麼走的：從廣場中央 south（南）到廣場南邊﹐"
			"再 southwest（西南）沿山道上去﹐便是白象寺山門。" :),
		(: command, "say 進門往北是庭院﹐尋著白象寺方丈﹐"
			"鍵入 apprentice master 拜他為師。" :),
	}));
}

private void tell_buxuan(object me)   // 書生 步玄派
{
	do_chat(({
		(: command, "say 步玄派﹗那是書生一脈﹐人稱「玄機居士」的掌門﹐"
			"以劍法佐控場、以文心參武道﹐一手步玄劍法。" :),
		(: command, "say 路是這麼走的：從廣場中央 north（北）到廣場北邊﹐"
			"再 northwest（西北）穿過竹林﹐便是步玄派山門。" :),
		(: command, "say 進門往北是書院﹐尋著步玄掌門﹐"
			"鍵入 apprentice master 拜他為師。" :),
	}));
}

private void tell_langyi(object me)   // 小偷 瑯夷派
{
	do_chat(({
		(: command, "say 瑯夷派﹖噓 ... 那是小偷的勾當﹐堂主一手血魂匕法﹐"
			"匕首暗算、潛行取命﹐見不得光。" :),
		(: command, "say 那地方藏得隱密：從廣場中央 east（東）到廣場東邊﹐"
			"再 east（東）走進一條僻靜小巷﹐尋著巷裡破屋的地窖﹐"
			"再 down（下）便能潛入。" :),
		(: command, "say 到了地底密道﹐尋著瑯夷堂主﹐"
			"鍵入 apprentice master 拜他為師——前提是你心夠狠。" :),
	}));
}

private void tell_zhenwu(object me)   // 軍人 振武軍營
{
	do_chat(({
		(: command, "say 振武軍營﹗那是軍人的去處﹐統領人稱「鎮北將軍」﹐"
			"一桿龍神槍法縱橫沙場﹐威風凜凜。" :),
		(: command, "say 路是這麼走的：從廣場中央 west（西）到廣場西邊﹐"
			"再 northeast（東北）沿大道上去﹐便是振武軍營轅門。" :),
		(: command, "say 進轅門往北是校場﹐尋著振武統領﹐"
			"鍵入 apprentice master 投他麾下。" :),
	}));
}

private void tell_longtu(object me)   // 方士 龍圖丹派
{
	do_chat(({
		(: command, "say 龍圖丹派﹗那是方士一脈﹐掌門尊稱「杏林神醫」﹐"
			"煉丹施針、懸壺濟世﹐一手驚異二針出神入化。" :),
		(: command, "say 路是這麼走的：從廣場中央 east（東）到廣場東邊﹐"
			"再 southeast（東南）循著藥香上山﹐便是龍圖丹派山門。" :),
		(: command, "say 進門往北是丹院﹐尋著龍圖丹師﹐"
			"鍵入 apprentice master 拜他為師。" :),
	}));
}

int do_ask(string arg)
{
	object me = this_player();
	string topic;

	if( !arg || sscanf(arg, "guide about %s", topic) != 1 )
		return notify_fail(
			"你想問江湖嚮導甚麼﹖（試試 ask guide about 拜師）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("江湖嚮導正忙著﹐稍候再問罷。\n");

	// 總覽：拜師 / 門派 / 師父（及英文 sect/master/join）
	if( topic == "拜師" || topic == "門派" || topic == "師父"
	||  topic == "sect" || topic == "sects" || topic == "master"
	||  topic == "join" || topic == "apprentice" ) {
		tell_overview(me);
		return 1;
	}

	// 武者 冷梅莊
	if( topic == "武者" || topic == "冷梅莊" || topic == "冷梅"
	||  topic == "fighter" || topic == "hanmei" || topic == "lunmay" ) {
		tell_hanmei(me);
		return 1;
	}

	// 道士 天師派
	if( topic == "道士" || topic == "天師派" || topic == "天師"
	||  topic == "taoist" || topic == "tianshi" ) {
		tell_tianshi(me);
		return 1;
	}

	// 和尚 白象寺
	if( topic == "和尚" || topic == "白象寺" || topic == "白象"
	||  topic == "bonze" || topic == "monk" || topic == "baixiang" ) {
		tell_baixiang(me);
		return 1;
	}

	// 書生 步玄派
	if( topic == "書生" || topic == "步玄派" || topic == "步玄"
	||  topic == "scholar" || topic == "buxuan" ) {
		tell_buxuan(me);
		return 1;
	}

	// 小偷 瑯夷派
	if( topic == "小偷" || topic == "瑯夷派" || topic == "瑯夷"
	||  topic == "thief" || topic == "rogue" || topic == "langyi" ) {
		tell_langyi(me);
		return 1;
	}

	// 軍人 振武軍營
	if( topic == "軍人" || topic == "振武軍營" || topic == "振武"
	||  topic == "soldier" || topic == "zhenwu" ) {
		tell_zhenwu(me);
		return 1;
	}

	// 方士 龍圖丹派
	if( topic == "方士" || topic == "龍圖丹派" || topic == "龍圖"
	||  topic == "alchemist" || topic == "physician" || topic == "longtu" ) {
		tell_longtu(me);
		return 1;
	}

	return notify_fail(
		"江湖嚮導摸了摸鬍子﹕這個老朽就不甚清楚了。\n"
		"（試試 ask guide about 拜師﹐或 ask guide about 某一派的名字）\n");
}

int accept_fight()
{
	do_chat((: command, "say 哎﹐老朽只會帶路﹐打打殺殺的可不在行﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
