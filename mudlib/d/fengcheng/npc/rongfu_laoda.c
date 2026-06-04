// rongfu_laoda.c -- 榮府老大（Master of the Rong Mansion），風城榮府的當家。
//
// docs（docs/01-世界觀與劇情/05-主線任務與NPC.md，「結仇陣營 → 官兵化解」段）：
//   仇恨深者 → 風城某客棧二樓 oldman 查 → 實戰經驗換【海大富】信任
//        → 海大富告知去尋【榮府老大】幫忙（500 gold）化解官兵仇恨。
//   故本 NPC 是「解官兵仇恨」鏈的最末一環：玩家須先得海大富信任
//        （quest/haidafu_trust >= 1），再備上 500 兩黃金交與榮府老大，
//        由他出面斡旋，【實際化解】官兵陣營（soldier / garrison / scout / guard）
//        對玩家的仇恨，並 set quest/rongfu_done = 1 記下此事。
//
// 故事背景：
//   榮府是風城裡數一數二的高門大戶，當家的榮老大年輕時也是刀頭舔血闖過來的
//   人物，如今金盆洗手、坐鎮一方，與官面上、綠林裡都還留著三分薄面。城裡江
//   湖人與官兵結下的死仇，旁人解不開的，他往官府衙門遞句話、擺桌酒、塞錠
//   金，多半也就化干戈為玉帛了——只是這人情往來的銀錢，少說也得 500 兩黃金。
//
// 機制（service / item-giver 收費型 NPC；旗標存玩家身上：quest/rongfu_done）：
//   收費走 give：玩家 `give 500 gold to laoda`（或 give <N> gold to laoda，
//   N >= 500），於 accept_object() 內處理——
//     - 已斡旋過（quest/rongfu_done >= 1）：double-grant 防呆，不重收錢、
//       不重複斡旋，改述「早為你了結了」之言，退還金錢（return 0）。
//     - 未得海大富信任（quest/haidafu_trust < 1）：婉拒收錢，指點先去尋海大富
//       驗本事得信任（return 0，金錢退還）。
//     - 信任已得、黃金恰為 500 兩：收下這 500 兩（return 1；give 指令於本函回 1
//       且 item->value() 非零時，會自行 destruct 這足額的 500 兩黃金——銀貨兩
//       訖），同步【實際化解官兵仇恨】並 set quest/rongfu_done = 1。
//     - 信任已得、黃金多於 500 兩：只扣其中 500 兩（ob->add_amount(-500)，餘額
//       留在玩家身上不找零誤吞），同步化解＋設旗標，return 0（餘額之錢不被
//       destruct，留還玩家）。
//     - 信任已得、黃金不足 500 兩：婉拒收錢（return 0，退還），說明須備 500 兩。
//   `say` / `ask laoda about ...` 僅作氣氛與指路提示，不經手錢與旗標。
//
// 「實際化解官兵仇恨」的機制（先 grep 既有機制，未臆造 efun）：
//   ES2 的仇恨儲存在「每個 NPC 自身」的 killer mapping（以玩家 id 字串為鍵）
//   ——見 /feature/char/attack.c：kill_ob() 寫入 killer[ob->query("id")]，
//   is_killing(who) 查玩家是否在某 NPC 的 killer 名單，remove_killer(who) 刪除
//   該鍵並一併移出 enemy 名單。並無「玩家身上的集中仇恨旗標」。
//   故化解之法即：掃出當前載入、仍記恨此玩家、且屬官兵陣營（class 為
//   soldier / garrison / scout / guard）的 NPC，逐一令其 remove_killer(who)，
//   並令玩家對其亦 remove_killer（雙向解仇，鏡 /d/snow/npc/girl.c 的
//   remove_killer(who); who->remove_killer(this_object());）。
//   再 set quest/rongfu_done = 1 將此斡旋永久記在玩家身上。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()——旗標／訊息逕在 handler 內順序寫就。
//   #11：本檔為 NPC（非房間），不涉 replace_program。
//   同步交付：收錢（give→accept_object 內 destruct 或 add_amount）、化解仇恨、
//             設旗標、tell_object 全在 accept_object 內「直接」完成，
//             不丟進延遲的 do_chat closure 陣列（純氣氛對白才走 do_chat）。
//   handler 守衛：accept_object / relay_say 開頭即 is_fighting()/is_chatting()/
//             !userp() 守衛，戰鬥或閒談動畫中不誤觸。
//   範式來源（先 grep 既有檔模仿，未臆造 efun）：
//     - give 收錢（money_id / value() / add_amount / accept_object 回 1 由 give
//       指令 destruct 足額錢）：/d/maoshan/npc/laodao.c、/cmds/std/give.c
//     - 雙向解仇 remove_killer：/d/snow/npc/girl.c
//     - 以 livings() + 屬性過濾掃載入中之 NPC：/cmds/arch/overview.c
//       （livings() / is_killing() / clonep() / userp()）
//     - is_killing(who)→player id 解析、remove_killer、enemy/killer 語意：
//       /feature/char/attack.c（僅讀以對齊語意，未改動該檔）
//     - relay_say / is_fighting()/is_chatting() 守衛、quest 旗標、double-grant
//       防呆：/d/fengcheng/npc/haidafu.c（同鏈上一環）

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

#define GOLD_COST   500     // 斡旋所需黃金（兩）
#define SOLDIER_FACTIONS ({ "soldier", "garrison", "scout", "guard" })

// 化解官兵仇恨：掃出當前載入、仍記恨 who、且屬官兵陣營的 NPC，逐一雙向解仇。
// 回傳實際化解的官兵數目（供回報訊息參考）。
private int mediate_soldier_enmity(object who)
{
	object *foes;
	int n;

	if( !who ) return 0;

	// livings() 取所有載入中的生物；過濾出 clone 的、非玩家的、仍記恨此玩家、
	// 且 class 屬官兵陣營者。（鏡 /cmds/arch/overview.c 的 livings()+屬性過濾。）
	foes = filter_array(livings(), (:
		objectp($1)
		&& clonep($1)
		&& !userp($1)
		&& $1->is_killing($(who))
		&& member_array($1->query_class(), SOLDIER_FACTIONS) >= 0
	:));

	n = sizeof(foes);
	foreach(object foe in foes) {
		// 雙向解仇（鏡 /d/snow/npc/girl.c）：官兵忘卻此仇、玩家亦不再與之為敵。
		foe->remove_killer(who);
		who->remove_killer(foe);
	}
	return n;
}

void create()
{
	set_name(HIY "榮老大" NOR, ({ "rongfu laoda", "laoda", "rong laoda", "rongfu master", "master rong" }) );
	set("nickname", "榮府當家");
	set_attr("str", 22);
	set_attr("con", 21);
	set_attr("dex", 20);
	set_attr("int", 23);
	set_race("human");
	set_class("commoner");      // 已金盆洗手的當家，不結官兵之仇，故設 commoner
	set_level(30);
	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_skill("force", 50);

	set("gender", "male");
	set("age", 58);
	set("long",
		"這是榮府的當家——人稱榮老大。一張保養得宜的方臉，三縷花白\n"
		"長鬚，穿一襲簇新的寶藍緞袍，腰束玉帶，端坐在太師椅上自有一股\n"
		"不怒而威的氣派。聽說他年輕時也是刀頭舔血、在綠林裡闖過名號的\n"
		"人物，如今金盆洗手、坐鎮這風城榮府，往來盡是官紳商賈，與官面\n"
		"上、綠林裡都還留著三分薄面。城裡江湖人與官兵結下的死仇，旁人\n"
		"解不開的，他遞句話、擺桌酒、塞錠金，多半也就化干戈為玉帛了。\n"
		"你若是與官兵結了仇怨想托他斡旋，得先得了海大富的信任，再備上\n"
		"五百兩黃金的人情——give 500 gold to laoda 便是。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"榮老大端著茶盞，慢條斯理地吹著浮沫，眼皮也不抬地聽底下管事回話。\n",
		"榮老大撚著花白的長鬚，淡淡道：這風城裡的恩恩怨怨，銀錢能了的，都不算事。\n",
		"榮老大瞇起眼，似笑非笑：官面上的人情，比金子還金貴，不到火候，使不得。\n",
	}));
	setup();
}

// 已得海大富信任後、指點來給錢斡旋的固定說辭（含 double-grant 防呆共用）。
private void tell_how_to_pay(object ob)
{
	if( !ob || environment(ob) != environment() ) return;

	tell_object(ob,
		HIY "榮老大撚著長鬚，淡淡道：海大富既肯為你引見，這事便好說。你備上 "
		+ GOLD_COST + " 兩黃金的人情，交與老夫——give " + GOLD_COST
		+ " gold to laoda——老夫往衙門裡走動走動，這官兵的仇怨，自為你了結。\n" NOR);
}

// say-handler / ask 指路：僅作氣氛與指路提示，不經手錢與旗標。
void relay_say(object ob, string arg)
{
	// handler 守衛：戰鬥中／閒談動畫中／非玩家所言，一律不理。
	if( is_fighting() || is_chatting() ) return;
	if( !ob || !userp(ob) ) return;
	if( !arg ) return;

	if( strsrch(arg, "官兵") < 0 && strsrch(arg, "斡旋")  < 0
	 && strsrch(arg, "仇") < 0   && strsrch(arg, "化解") < 0 )
		return;

	if( ob->query("quest/rongfu_done") >= 1 ) {
		command("say 你與官兵那段仇怨，老夫早為你斡旋了結了，安心便是。");
		return;
	}
	if( ob->query("quest/haidafu_trust") < 1 ) {
		command("say 你與官兵的過節老夫不是不能管，只是無憑無據，老夫憑甚麼為你出這個面？");
		tell_object(ob,
			HIR "榮老大擺了擺手：你先去尋四廠的海大富，叫他驗過你的本事、肯為你引見了，"
			"老夫自有道理。\n" NOR);
		return;
	}
	command("say 海大富既肯為你引見，這事便好說。");
	tell_how_to_pay(ob);
}

// 收費走 give：玩家 give <N> gold to laoda 觸發此函。
// who 為給予者；ob 為交來之物（足額時 give 指令會在本函回 1 後自行 destruct）。
int accept_object(object who, object ob)
{
	int amount, freed;

	// handler 守衛：戰鬥／閒談動畫中、非玩家給予，一律不收。
	if( is_fighting() || is_chatting() ) return 0;
	if( !who || !userp(who) ) return 0;

	// 只認黃金；其餘物事一律婉拒，不吞玩家物品。
	if( ob->query("money_id") != "gold" ) {
		command("say 老夫甚麼沒見過？你這點東西，老夫看不上眼，拿回去罷。");
		return 0;
	}

	amount = (int)ob->query_amount();   // 黃金兩數

	// double-grant 防呆：已斡旋過者，不重收錢、不重複斡旋，退還金錢。
	if( who->query("quest/rongfu_done") >= 1 ) {
		command("say 你與官兵那段仇怨，老夫早為你斡旋了結了，這金子且收回去罷。");
		return 0;       // 退還，不收
	}

	// 未得海大富信任：婉拒收錢，指點先去尋海大富。
	if( who->query("quest/haidafu_trust") < 1 ) {
		command("say 慢著。你與官兵的過節，老夫憑甚麼信你？這金子老夫不能收。");
		tell_object(who,
			HIR "榮老大將金子推了回來：你且先去尋四廠的海大富，叫他驗過你的本事、肯為你"
			"引見了，再來尋老夫不遲。\n" NOR);
		return 0;       // 退還，不收
	}

	// 信任已得，但黃金不足 500 兩：婉拒收錢。
	if( amount < GOLD_COST ) {
		command("say 就這點金子？官面上的人情，可比這金貴得多。");
		tell_object(who,
			HIR "榮老大將金子推了回來：斡旋這場仇怨的人情，少說也得 " + GOLD_COST
			+ " 兩黃金，你這還不夠，湊足了再來。\n" NOR);
		return 0;       // 退還，不收
	}

	// 信任已得、黃金足額：恰 500 兩則收下整錠（return 1，give 指令自行 destruct）；
	// 多於 500 兩則只扣 500、餘額留還玩家（add_amount(-500)，本函 return 0 不被 destruct）。
	if( amount > GOLD_COST ) {
		ob->add_amount(-GOLD_COST);     // 只取 500 兩，餘額留在玩家手裡
		freed = 0;
	} else {
		freed = 1;      // 恰 500 兩，整錠收下（return 1 由 give 指令 destruct）
	}

	// ── 同步交付（全在 handler 內直接完成，不走延遲 do_chat）──
	// 1. 設永久旗標（先設，鐵則 #10 精神：關鍵狀態先落地）
	who->set("quest/rongfu_done", 1);
	// 2. 實際化解官兵仇恨（雙向解仇當前載入之官兵 NPC）
	{
		int cleared = mediate_soldier_enmity(who);

		command("say 好說好說。這 " + GOLD_COST + " 兩，老夫笑納了——這官兵的仇怨，包在老夫身上。");
		tell_object(who,
			HIY "榮老大將那 " + GOLD_COST + " 兩黃金不動聲色地收入袖中，提筆寫了張帖子喚管事"
			"送往衙門。不過片刻，便聽他撚鬚笑道：成了。自今往後，官面上那些人，再不會"
			"尋你的晦氣了。\n" NOR);
		if( cleared > 0 )
			tell_object(who,
				HIG "你只覺方才還對你橫眉立目、必欲除之而後快的官兵，竟似一夕之間"
				"忘了你這號人物，眼前 " + cleared + " 名與你結仇的官兵，恩怨盡釋。\n" NOR);
		else
			tell_object(who,
				HIG "你心頭一鬆——往後與官兵打照面，再不必擔心他們認出舊仇、拔刀相向了。\n" NOR);
	}

	return freed;       // 1：整錠 500 兩由 give 指令 destruct；0：已扣 500、餘額退還
}

int accept_fight(object ob)
{
	command("say 放肆！光天化日竟敢在榮府撒野，是不要命了麼？來人哪！");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
