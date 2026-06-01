// fish.c -- 「釣魚」：在臨水的房間垂釣，是一條不靠打鬥的江湖歷練門路。
//
// 設計與來源：
//   docs/02-遊戲系統與機制/04-業力與聲望.md、docs/04-玩家社群與文化/01——
//   釣魚被列為一條「江湖歷練」的非戰鬥成長／營生途徑。戰鬥平衡尚是未定之
//   數，故玩家需要一條不打架也能慢慢成長的路子。檒城望安港的漁婦目前只是
//   純氣氛 NPC，這裡把垂釣做成可實際進行的動作。
//
// 機制全部比照現有、已讀過原始碼確認的做法（gather.c / refine.c）：
//   * 指令查找：檔名 == 動詞（adm/daemons/cmd_d.c 用 get_dir + verb+".c"）。
//     放在 /cmds/std/ 所有人都搜得到，故在此用「房間旗標」鎖死可釣之處。
//   * 場地判定：須在 set("fishable", 1) 的臨水房間（比照 refine.c 之 danfang）。
//     初版只在 /d/fancheng/pier.c（舊船屋木棧橋）開放，日後可在更多水邊房間
//     加 set("fishable",1) 擴點。
//   * 冷卻：set_temp("fish_cooldown", time()+N)，以 time() 判定（同 gather.c）。
//     垂釣需靜候魚汛，不能連點刷分——這是「慢慢攢」而非速成的關鍵。
//   * 硬直：start_busy（拋竿垂釣得花點時間，同 gather.c）。
//   * 經驗：me->gain_score("survive", N)。survive 即「江湖歷練」升級經驗軸
//     （見 feature/char/score.c：set_level_target 以 target_score/survive 為門檻；
//     任務 NPC 如 d/snow/npc/diviner.c 領賞亦 gain_score("survive", ...)）。
//     任務一次給 120~500，這裡每次只給一丁點（FISH_XP_MIN~MAX），刻意做成
//     涓滴細流，避免變成無限刷級的破口。
//   * 漁獲：偶爾釣上一尾小魚（/obj/food/fish.c，可吃可賣），偶爾空竿（氣氛）。
//
// 平衡（皆為初版、可調，集中在下面 #define）：
//   冷卻 45 秒、每次 survive 8~18、約七成上鉤。以一級門檻 = 100*lvl*lvl 估算，
//   一級玩家升 2 級約需 400 點 survive，純靠釣魚約需數十竿、十餘分鐘以上，
//   是明確的慢速途徑而非速成外掛。數字要調動只改下面常數即可。

#include <ansi.h>

inherit F_CLEAN_UP;

#define FISH_OBJ        "/obj/food/fish"

// --- 平衡參數（初版、可調）-------------------------------------------------
#define FISH_COOLDOWN   45      // 兩次垂釣之間的冷卻秒數（魚汛間隔）
#define FISH_BUSY       2       // 垂釣後的硬直（heart beat 數）
#define FISH_XP_MIN     8       // 每次有所收穫時，最少獲得的江湖歷練 (survive)
#define FISH_XP_RANGE   11      // 經驗浮動範圍：實得 = MIN + random(RANGE) → 8~18
#define FISH_CATCH_PCT  70      // 上鉤機率（百分比）；其餘為空竿
// ---------------------------------------------------------------------------

void do_fish(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	int left;

	if( me->query("life_form") == "ghost" )
		return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

	if( me->is_busy() )
		return notify_fail("請先用 halt 停止你正在做的事。\n");

	// 與人交手之際手忙腳亂，沒法靜心垂釣。
	if( me->is_fighting() )
		return notify_fail("你正與人交手，哪有閒情垂釣﹖\n");

	// 場地判定：須在臨水、可垂釣的房間（房間 set("fishable", 1)）。
	if( !environment(me) || !environment(me)->query("fishable") )
		return notify_fail("這裡沒有可供垂釣的水域。\n");

	// 冷卻檢查：set_temp 存下次可用的時間戳（同 gather.c）。
	left = me->query_temp("fish_cooldown") - time();
	if( left > 0 )
		return notify_fail("方纔驚動了魚群，且待 " + left + " 秒﹐魚汛回轉了再下竿罷。\n");

	do_fish(me);
	return 1;
}

void do_fish(object me)
{
	object fish;
	int xp;

	// do_fish 與 main 之間若狀態有變，再確認一次。
	if( !me ) return;

	// 先設冷卻、進入硬直——無論這一竿有無收穫，都要靜候下一次魚汛。
	me->set_temp("fish_cooldown", time() + FISH_COOLDOWN);
	me->start_busy(FISH_BUSY);

	message_vision(HIC "\n$N尋了個臨水的去處﹐放長絲線﹐靜靜垂下一竿。\n" NOR, me);

	// 空竿（氣氛）：不給漁獲、不給經驗，但冷卻照算。
	if( random(100) >= FISH_CATCH_PCT ) {
		tell_object(me,
			"你屏息凝神等了半晌﹐浮標卻紋風不動﹐到頭來空歡喜一場。\n");
		return;
	}

	// 上鉤：給一尾小魚，並授一丁點江湖歷練 (survive)。
	xp = FISH_XP_MIN + random(FISH_XP_RANGE);

	fish = new(FISH_OBJ);
	if( !fish->move(me) ) fish->move(environment(me));

	message_vision(HIC "$N手腕一抖﹐絲線繃緊﹐一尾小魚破水而出﹐在空中甩著尾巴﹗\n" NOR, me);
	tell_object(me,
		"你將這尾魚收進簍裡﹐這一番垂釣的工夫﹐倒也長了些行走江湖的見識。\n");

	me->gain_score("survive", xp);
}

int help(object me)
{
	write(@HELP
指令格式﹕fish     （中文﹕釣魚）

在臨水的去處（如檒城望安港的舊船屋木棧橋）放竿垂釣。這是一條不靠打鬥的
江湖歷練門路﹕運氣好時釣上一尾小魚（可吃可賣）﹐並長進一丁點江湖歷練﹔
運氣差時則空竿而回。

垂釣須靜候魚汛﹐拋竿之後得歇上一陣方能再下竿﹐連點是釣不著魚的﹔與人
交手之際亦無法垂釣。這是慢慢攢經驗的路子﹐圖的是個細水長流。
HELP
	);
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
