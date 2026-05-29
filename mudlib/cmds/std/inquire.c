// inquire.c -- 向喬陰縣前廣場的算命先生「占算」某技能的天賦(潛能)
//
// 指令格式﹕inquire <技能英文代號>      （中文別名﹕占算）
//
// 設計與來源：docs/02-遊戲系統與機制/03-升級與天賦.md「算命仙天賦對照表」。
//   每個技能在玩家身上有 140~200 的天賦(潛能)上限(首次習得時隨機決定，存於
//   "talent/<skill>")。算命先生收卦金後，揭示該技能的天賦數值對應的斷語。
//
// 流程（比照 cmds/std/enchant.c 的尋人＋收費模式）：
//   1. 須站在算命先生(NPC 以 set("fortune_teller",1) 標記)面前，否則拒絕。
//   2. 須指定一個技能英文代號(物件/技能由英文 id 比對，見 feature/name.c)。
//   3. 玩家須已習得該技能（query_talent>0 或 query_skill 原始值>0），否則先生
//      看不出名堂。
//   4. 收卦金五兩黃金(= 5 萬文，黃金 base_value 10000 文/兩，見 obj/money/gold.c)；
//      以 me->can_afford / me->pay_money 結帳(見 feature/char/finance.c)。錢不夠或
//      湊不出整數則拒絕、不收費、不洩天機。
//   5. 成功：扣費，讀 me->query_talent(skill) → 對照表斷語，由先生說出(技能名以
//      to_chinese 轉中文以利閱讀)。
//
// 安全性：本指令只「讀」天賦 + 收費，絕不更動任何技能等級／天賦。

#include <ansi.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

// 一卦卦金：五兩黃金。黃金 base_value 為 10000 文/兩(obj/money/gold.c)，
// 故 5 兩 = 50000 文。finance.c 的 can_afford/pay_money 一律以「文」計價。
#define FEE_GOLD	5
#define FEE_COIN	(FEE_GOLD * 10000)

// 找出此房間裡的算命先生（NPC 以 set("fortune_teller", 1) 標記）。
private object find_teller(object me)
{
	object ob;

	foreach(ob in all_inventory(environment(me)))
		if( ob != me && living(ob) && ob->query("fortune_teller") )
			return ob;
	return 0;
}

// 依天賦數值(140~200)取對照表斷語。天賦範圍本就 140~200，
// 用區間 >=200/>=190/.../>=150/else 對應，最低檔涵蓋 140。
private string talent_desc(int talent)
{
	if( talent >= 200 ) return "此乃天縱之才﹗他日在這門技藝上的發展可說是無可限量﹐舉世無匹﹗";
	if( talent >= 190 ) return "好根骨﹗委實是非同凡響﹗";
	if( talent >= 180 ) return "嗯﹐這份根骨非常不一般呀﹗";
	if( talent >= 170 ) return "這根骨相當不錯呀﹗";
	if( talent >= 160 ) return "根骨發展不錯﹐若是棄而不練﹐真是可惜啊。";
	if( talent >= 150 ) return "還算不錯﹐只要肯下苦功﹐他日當有一番成就。";
	return "發展一般﹐雖不能成名﹐但也可憑此謀生。";
}

int main(object me, string arg)
{
	object teller;
	int talent;

	if( me->is_busy() ) return notify_fail("你現在沒有空﹗\n");

	teller = find_teller(me);
	if( !teller )
		return notify_fail("這裡沒有算命先生。\n");

	if( teller->is_fighting() )
		return notify_fail(teller->name() + "正忙著﹐沒空理你。\n");

	if( !arg || arg == "" )
		return notify_fail("你要請先生占算哪一門技藝﹖（格式﹕inquire <技藝英文代號>﹐如 inquire sword）\n");

	arg = lower_case(arg);

	// 須已習得此技藝：天賦於首次習得時才隨機決定(見 feature/char/skill.c)；
	// 連原始等級都沒有、也沒天賦的，先生看不出名堂。
	talent = me->query_talent(arg);
	if( talent <= 0 && me->query_skill(arg, 1) <= 0 ) {
		message_vision(
			"$N端詳了$n半晌﹐搖頭道﹕你連這門功夫的皮毛都未沾過﹐老朽便是鐵口﹐也算不出個名堂來。\n",
			teller, me);
		return 1;
	}

	// 已有等級、但天賦尚未顯現（例如純由師父 set_skill 點授、自己還沒下過苦功
	// 練習，故 improve_skill 尚未替此技隨機定下 talent）。此時根骨未定，難測。
	if( talent <= 0 ) {
		message_vision(
			"$N端詳了$n半晌﹐搖頭道﹕你這門功夫是旁人硬塞給你的﹐自個兒還沒下過苦功﹐根骨深淺尚未顯現﹐待你親身練上一練﹐老朽再替你卜算罷。\n",
			teller, me);
		return 1;
	}

	// 收卦金五兩黃金。比照 enchant.c：can_afford 回 0=錢不夠、2=湊不出零錢。
	switch( me->can_afford(FEE_COIN) ) {
	case 0:
		message_vision(
			"$N把玩著手中的銅錢﹐淡淡道﹕老朽不做白工﹐這一卦的卦金是五兩黃金﹐客官先備妥了再來罷。\n",
			teller, me);
		return 1;
	case 2:
		message_vision(
			"$N搖頭道﹕客官身上的金銀零碎﹐湊不齊這五兩黃金的整數卦金﹐老朽可找不開。\n",
			teller, me);
		return 1;
	}
	me->pay_money(FEE_COIN);

	// 揭示天賦（只讀不改）。技能名轉中文以利閱讀；查不到中文則沿用英文代號。
	// 比照 enchant.c：以 message_vision 讓算命先生($N)當眾道出斷語，
	// 不用 ob->command("say")（driver 的 command 第二參數通常不開放，見 command.md）。
	message_vision(
		"$N接過$n奉上的五兩黃金﹐收入袖中﹐這才捻起三枚銅錢往桌上一擲﹐"
		"又掐指端詳了$n的骨相良久。\n", teller, me);
	message_vision(
		"$N捋鬚道﹕客官這身「" + to_chinese(arg) + "」的根骨麼 ... "
		+ talent_desc(talent) + "\n", teller, me);

	return 1;
}

int help(object me)
{
	write(@HELP
指令格式﹕inquire <技藝英文代號>      （中文﹕占算）

當你站在算命先生面前﹐可用此指令請他占算你在某門技藝上的「天賦(根骨)」。
每門技藝的天賦在你首次習得時便已隨機定下(140~200)﹐天賦越高﹐這門功夫
日後能練到的境界便越高。先生會依你的天賦深淺﹐道出一句吉凶斷語。

須指定技藝的英文代號﹐例如﹕
    inquire sword        占算劍法天賦
    inquire unarmed      占算拳腳天賦
    inquire force        占算內功天賦

你須已習得該門技藝﹐先生方占算得出。每占一卦﹐須奉卦金五兩黃金。
（可先 ask teller about 算命 聽先生細說。）
HELP
	);
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
