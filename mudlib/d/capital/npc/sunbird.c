// sunbird.c -- 京畿神社神龕上日神化身的太陽鳥﹐地靈任務鏈的丹引受獻者。
//
// 來歷（承 docs 05 L62 地靈任務鏈「聖木殘根→京畿神社→金屋內丹→炎日箭→太陽
//   槍→地氣塔頂」﹔docs 重要任務 NPC 表 L121「太陽鳥｜京畿神社｜donate 大環丹
//   → 金屋內丹」）：
//   太陽鳥棲在京畿神社神龕之上﹐相傳是司掌日月的日神化身。少俠走那地靈一路﹐
//   須將承先啟後的丹引『大環丹』捐(donate)與這尊太陽鳥——太陽鳥納了這味丹引、
//   振翅引下一縷澄澈日華﹐將那丹引溫養、熔鑄成那地靈鏈承先的中繼聖物『金屋內
//   丹』(npc/obj/jinwu_pill)相贈﹐少俠方能持它連同聖木殘根﹐去煉就炎日箭、太陽
//   槍﹐循四神之力層層引動﹐登臨地氣塔頂。
//
// 機制（donate 服務型 NPC﹔旗標存玩家身上：quest/sunbird_done）。兩條捐獻途徑﹐
//   皆同步交付（直接 new+move﹐玩家此刻必在場﹔絕不放進延遲 do_chat closure——
//   免玩家於回呼前離場致賞沒領而卡關﹐承 sanctifier.c 同步交付教訓）：
//     * ask  : ask sunbird about 大環丹／金屋內丹／捐獻／donate -- 持大環丹即同步換丹
//     * give : give 大環丹 to sunbird            -- accept_object 直接同步換丹
//   double-grant 防呆：quest/sunbird_done >= 1 即不再收丹/重發﹔回贈前另以
//     present("jinwu pill", who) 防同一回合重發。遺失同步補贈：旗標雖已 done﹐
//     若玩家身上已無金屋內丹﹐ask 時再溫養補贈一枚（仍防重發）。
//
// runtime 鐵則：
//   #10：本檔無 ::die()/destruct()——換丹時先記旗標/回贈金屋內丹、收走(destruct)
//        大環丹殿後（destruct-LAST﹔destruct 後同函式其後碼不保證續行）。
//   #11：本檔為 NPC（非 ROOM）﹐不涉 replace_program﹔有 init/do_ask 的本物件絕
//        不 replace_program。do_ask 開頭即 is_fighting()/is_chatting() 守衛。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void grant_jinwu(object who);
private void do_donate(object who);

void create()
{
	set_name("太陽鳥", ({ "sunbird", "sun bird", "bird" }) );
	set("nickname", "太陽鳥");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 0);
	set("gender", "無性");
	set("long",
		"這是棲在京畿神社神龕上的太陽鳥﹐相傳是日神的化身。牠生\n"
		"著三足金喙﹐一身火紅的羽翼上嵌著細碎的金芒﹐振翅之際彷彿\n"
		"有暖融融的日光自羽間流瀉而出﹐叫人望之而生敬畏之心。相傳\n"
		"牠能納人間至誠的丹引﹐以日華溫養熔鑄成更精純的內丹。\n"
		"你或許可以問問牠﹕ask sunbird about 大環丹。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"太陽鳥輕輕舒展火紅的羽翼﹐一層暖融融的金芒在殿中流轉。\n",
		"太陽鳥昂首發出一聲清越的長鳴﹐殿內的香煙竟隨之裊裊盤旋而上。\n",
		"太陽鳥金喙微啟﹐一雙眼睛靜靜地凝視著前來上香的香客﹐似有所悟。\n",
	}));
	set("no_get", 1);
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 同步回贈一枚金屋內丹（地靈鏈中繼物）。who=捐獻的玩家﹔於 do_donate 內、收走大環
// 丹之前直接 new+move（玩家此刻必在場﹔絕不放進延遲 do_chat）。防重發：玩家身上已
// 有金屋內丹則不重發。
private void grant_jinwu(object who)
{
	object pill;

	if( !who || environment(who) != environment() ) return;

	// 防同一回合／遺失補贈時的重發。
	if( present("jinwu pill", who) ) return;

	pill = new(__DIR__"obj/jinwu_pill");
	if( !objectp(pill) ) return;
	if( !pill->move(who) ) pill->move(environment());
}

// 捐獻核心（ask-path 與 give-path 共用）：收走大環丹、同步回贈金屋內丹、記 quest/
// sunbird_done=1。⚠ 旗標/回贈全置於收走(destruct)大環丹「之前」﹔大環丹 destruct 殿
// 後（destruct-LAST﹐承 lesson #10：destruct 後同函式其後碼不保證續行）。
// 進入本函式前﹐呼叫端須已確認 who 持大環丹且 quest/sunbird_done < 1。
private void do_donate(object who)
{
	object dahuan;

	if( !who || environment(who) != environment() ) return;

	dahuan = present("dahuan pill", who);
	if( !dahuan ) return;

	// 先記旗標（於 destruct 之前）。
	who->set("quest/sunbird_done", 1);

	// 同步回贈金屋內丹（直接 new+move﹔絕不放進延遲 do_chat）。
	grant_jinwu(who);

	message_vision(
		HIY "太陽鳥金喙一啟﹐自$N掌心輕輕銜過那枚赭紅的大環丹﹐昂首一聲清越長"
		"鳴﹐火紅的羽翼霍然大張——一縷澄澈的日華自牠羽間流瀉而下﹐將那枚丹引溫"
		"養、熔鑄。但見金芒繚繞間﹐丹引漸漸斂去赭紅、化作一枚通體流轉著暖芒的內"
		"丹。太陽鳥振翅一送﹐那枚『金屋內丹』便穩穩落入了$N手中。\n" NOR, who);

	do_chat((: command,
		"say 太陽鳥昂首長鳴﹐殿中金芒流轉——這枚金屋內丹既成﹐少俠便持它連同那聖木殘根﹐去煉就那炎日箭、太陽槍罷﹔循四神之力層層引動﹐方能登臨那地氣塔頂。" :));

	// ⚠ 大環丹既化入內丹﹐destruct 殿後（必置於上方旗標/回贈/message 之後——
	// destruct-LAST﹐承 lesson #10）。
	destruct(dahuan);
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg || (arg != "sunbird about 大環丹"
		&&   arg != "sunbird about 金屋內丹"
		&&   arg != "sunbird about 金屋"
		&&   arg != "sunbird about 內丹"
		&&   arg != "sunbird about 捐獻"
		&&   arg != "sunbird about 獻"
		&&   arg != "sunbird about 地靈"
		&&   arg != "sunbird about donate"
		&&   arg != "sunbird about pill"
		&&   arg != "sun bird about 大環丹"
		&&   arg != "sun bird about 金屋內丹"
		&&   arg != "sun bird about 捐獻"
		&&   arg != "sun bird about donate"
		&&   arg != "bird about 大環丹"
		&&   arg != "bird about 金屋內丹"
		&&   arg != "bird about 捐獻"
		&&   arg != "bird about 獻"
		&&   arg != "bird about donate"
		&&   arg != "bird about pill") )
		return notify_fail("你想問這尊太陽鳥甚麼﹖（試試 ask sunbird about 大環丹）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("太陽鳥正闔目斂翅、靜納日華﹐沒空理你。\n");

	// 已捐獻畢（quest/sunbird_done）：double-grant 防呆——不重複收丹、不重複給賞。
	// 遺失同步補贈：旗標雖 done﹐若玩家身上已無金屋內丹﹐再溫養補贈一枚（grant_jinwu
	// 內另防重發﹔已有則不發）。
	if( me->query("quest/sunbird_done") >= 1 ) {
		if( !present("jinwu pill", me) ) {
			grant_jinwu(me);
			do_chat((: command,
				"say 少俠那枚金屋內丹竟不見了麼﹖罷了——念在這丹引干係少俠地靈一路的成敗﹐太陽鳥再引一縷日華﹐為少俠溫養補上一枚。這回可要妥善收著了。" :));
		}
		else
			do_chat((: command,
				"say 少俠所獻的大環丹﹐太陽鳥早已為少俠溫養熔鑄成金屋內丹了。少俠且持它連同聖木殘根﹐去煉那炎日箭、太陽槍罷。" :));
		return 1;
	}

	// 未捐獻：持大環丹即同步換丹﹔未持則指點。
	if( present("dahuan pill", me) ) {
		do_donate(me);
		return 1;
	}

	do_chat((: command,
		"say 少俠走那地靈一路麼﹖那聖木殘根、金屋內丹、炎日箭、太陽槍直至地氣塔頂的一路﹐承先啟後的便是這枚『金屋內丹』。少俠且尋一枚『大環丹』來﹐捐(donate)與太陽鳥——太陽鳥自引一縷日華﹐為少俠將那丹引溫養、熔鑄成金屋內丹。（持大環丹來﹕ask sunbird about 捐獻﹐或 give 大環丹 to sunbird）" :));
	return 1;
}

// 收下信物：
//   大環丹(dahuan pill) -- 地靈鏈丹引﹐donate 換金屋內丹﹐旗標 quest/sunbird_done=1
// give-path：玩家以 give 大環丹 to sunbird 交付﹐accept_object 直接同步換丹（與 ask-
// path 共用 do_donate）。double-grant 防呆：已 done 則不重複收丹、回 1 避免卡物但不
// 重發。其餘物事一律婉拒（回 0、不吞玩家物品）。
int accept_object(object who, object ob)
{
	if( ob->id("dahuan pill") ) {
		// 已捐獻畢：double-grant 防呆——不重複收丹、不重複給賞﹔大環丹留玩家身上。
		if( who->query("quest/sunbird_done") >= 1 ) {
			do_chat((: command, "say 少俠先前已獻過大環丹、得了金屋內丹了﹐這枚少俠且自留著罷。" :));
			return 0;
		}

		// 同步換丹（收走大環丹、回贈金屋內丹、記旗標﹔do_donate 內 destruct-LAST）。
		do_donate(who);
		return 1;
	}

	// 其餘物事：婉拒、不收下（避免吞掉玩家的尋常物品）。
	do_chat((: command, "say 此乃清淨神龕﹐太陽鳥只納那承先啟後的大環丹丹引﹐這個受不起﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat("太陽鳥振翅騰起﹐周身金芒大盛﹐一股莊嚴之氣令人不敢造次。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
