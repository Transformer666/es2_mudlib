// songanjiang.c -- 漕幫禮堂的分舵主「宋安江」。純氣氛閒談 NPC：
//                  不接任務、不交物、不動旗標。
//
// 【設定 / canon】依 ES2 設定﹐宋安江是漕幫禮堂的分舵主﹐掌京畿一處幫務﹔
//   canon 中他會授予玩家「旋芒」（一門漕幫武學 / 信物）。
//
// 【A-gated TODO】授「旋芒」與其後續﹐與漕幫「四鬼問環」同繫於一樁尚未拍板的主線抉擇(決策 A)﹐
//   故本檔【不】實作任何授藝 / 授物任務﹕宋安江只是個爽利仗義、替玩家介紹漕幫、引玩家
//   去尋江隕的氣氛分舵主﹐嘴上點到「旋芒」canon 為止。
//   == 待決策 A 拍板後再補（此處一律不做、不設旗標）==
//     - 宋安江授玩家「旋芒」(武學 / 信物)
//   本檔絕不讀寫任何 旋芒 / 四鬼 / main_omen / 主線 旗標﹔對白裡的「旋芒」純為 canon 氣氛。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("宋安江", ({ "songanjiang", "deputy songanjiang", "song anjiang" }) );
	set("nickname", "宋安江");
	set_race("human");
	set_class("commoner");
	set_level(18);

	set("age", 41);
	set("gender", "male");
	set("long",
		"這位是漕幫禮堂的分舵主宋安江﹐掌著京畿這一處的幫務。他\n"
		"生得方面闊口﹐三綹墨髯﹐穿一身利落的玄色勁裝﹐腰束革帶﹐行\n"
		"止間自有一股當家理事的精悍幹練。漕幫號稱數十萬眾﹐能在天子\n"
		"腳下替漕幫坐鎮一方分舵的﹐自非泛泛之輩。他待人爽利仗義﹐一\n"
		"雙眼睛卻精光內斂﹐顯是個外圓內方、心裡極有成算的人物。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"宋安江立在烏木長案後﹐執筆在一函漕運帳冊上勾畫﹐神色專注。\n",
		"宋安江抱拳和進出禮堂的幫眾一一招呼﹐三言兩語便把幾樁幫務分派停當。\n",
		"宋安江抬眼瞧了瞧「漕」字大旗﹐又朝江隕那頭恭敬地一拱手﹐方低頭理事。\n",
	}));
	setup();
	carry_money("silver", 8);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想向這位分舵主打聽甚麼﹖（試試 ask songanjiang about 漕幫）\n");

	// 漕幫 / 入幫：宋安江介紹漕幫幫風、引玩家去尋江隕
	if( arg == "songanjiang about 漕幫"
	||  arg == "songanjiang about 禮堂"
	||  arg == "songanjiang about 入幫"
	||  arg == "songanjiang about 加入"
	||  arg == "songanjiang about caobang"
	||  arg == "deputy songanjiang about 漕幫" ) {
		do_chat(({
			(: command, "say 客官光臨敝幫禮堂﹐失敬。在下宋安江﹐忝為這禮堂的分舵主﹐京畿一處的幫務﹐都歸在下打理。客官面生﹐想必是頭一回到咱漕幫罷？" :),
			(: command, "say 咱漕幫執掌天下漕運﹐幫眾數十萬﹐沿大運河南北分舵林立﹐勢力不可謂不大。可咱這幫子有條老規矩﹕從不與江湖中人結仇怨。跑船的求的是四海通達、和氣生財﹐這份『不結仇』的家風﹐百十年來未曾變過。" :),
			(: command, "say 客官若是有心在漕幫討個出身﹐這是好事﹐在下歡迎得很。只是 ... 幫裡眼下有幾樁大關節﹐還繫在那位老前輩江隕江爺身上。客官得空﹐不妨先去拜會江爺（ask jiangyun about 漕幫），聽聽他老人家的意思。" :),
		}));
		return 1;
	}

	// 旋芒：canon 引子——只給氣氛﹐絕不授藝授物、不接任務、不設旗標
	if( arg == "songanjiang about 旋芒"
	||  arg == "songanjiang about 武學"
	||  arg == "songanjiang about 武功"
	||  arg == "songanjiang about 絕學"
	||  arg == "songanjiang about 四鬼"
	||  arg == "songanjiang about 江隕"
	||  arg == "songanjiang about jiangyun" ) {
		do_chat(({
			(: command, "say 客官也聽過咱漕幫的『旋芒』？（宋安江眼中精光一閃﹐隨即笑了笑）那是咱漕幫壓箱底的一門功夫﹐脫胎自跑船的撐篙、收纜、破浪的勁路﹐使將開來如水上旋芒﹐端的不凡。" :),
			(: command, "say 不瞞客官﹐這門功夫﹐連同江爺手裡那樁『四鬼』的舊因果﹐眼下都還動不得——幫裡有一樁更大的關節未曾分曉﹐時機未到。待來日塵埃落定﹐客官果真與咱漕幫有緣﹐這旋芒的傳授﹐自有水到渠成的一日。" :),
			(: command, "say 客官且記在心上。這些事﹐還得江爺點頭﹔在下一個分舵主﹐也做不得主。" :),
		}));
		// TODO(decision-A)：授「旋芒」與漕幫四鬼支線同繫於主線抉擇 A。
		//   抉擇拍板前﹐本處【不】授任何武學 / 信物、【不】接任務、【不】設 旋芒/四鬼/主線 旗標﹔
		//   僅以上列對白作 canon 氣氛鋪墊。待 A 拍板後﹐再於此實作授藝流程。
		return 1;
	}

	return notify_fail("宋安江拱手一笑﹕客官若是來見識見識咱漕幫的氣派﹐只管隨意﹔旁的﹐恕在下一時也說不周全。（試試 ask songanjiang about 漕幫）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say （宋安江不慌不忙地一拱手）客官說笑了。這是漕幫議事的禮堂﹐又有江爺在座﹐動手是萬萬使不得的。客官有甚麼話﹐好好說便是。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
