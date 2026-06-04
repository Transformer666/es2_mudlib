// atuo.c -- 釘靈古墓旁的老樵夫「阿拓」，docs 支線 item-giver。
//
// 來源(doc)：docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC」表 L107——
//   「阿拓 @ 釘靈古墓附近樵夫 → 給 girdle(腰帶)」。本檔即落實阿拓其人﹐並令其
//   贈玩家一條腰帶「縛柴麻絛帶」(d/capital/npc/obj/woodman_girdle)。
//
// 落點（room）：docs 載阿拓在「釘靈古墓附近樵夫」﹐然本 mudlib 現無釘靈古墓一域
//   (grep d/ 無此室)﹐依任務鐵則「無對應室則退而置於該域 main 門戶」——遂掛於京畿
//   南面城門 d/capital/gate.c：城外一條官道westward通往喬陰縣城、徑入山林古墓
//   一帶﹐正是樵夫挑柴入城、歇腳販薪的去處﹐安一個自城外林子裡來的老樵夫於城門
//   下﹐於情於理最是相宜。(待日後建出釘靈古墓一域﹐可再行遷置。)
//
// 給法（同步交付﹐承本專案頭號 bug class「同步交付」之教訓 — 鏡 d/capital/npc/
//   lizaiyan.c 之 give_robe﹐而「非」laojiugui.c 把 give 放進 do_chat closure 的
//   延遲寫法）：
//   * do_ask 之贈帶分支內﹐直接 give_girdle(who)：new() + if(!move(who)) move(env)﹐
//     並於設完成旗標『之前』同步呼叫——絕不放進延遲的 do_chat closure(玩家中途離場
//     會 soft-lock)﹔亦不用 `if(move)`(成功時反落地)。do_chat 只擺『say』氣氛。
//   * 防重領：以逐玩家旗標 quest/sq_atuo 為閘(已領者只給氣氛、不重發)﹐
//     give_girdle 內另以 present("woodman girdle", who) 作第二道防重給保險。
//   * 防遺失補發：若旗標已設、然帶已不在身(present 查無)﹐則同步補發一條——便於
//     「領了又弄丟」的玩家(及測試)再取一次﹐補發路徑亦同步、不延入 closure。
//
// 閘門可測性：docs 樵夫一列無載明硬性前置(書換/規費皆無)﹐故將「閒談相贈」純作
//   風味﹐閘門即「未領過 or 領了已遺失」——任何玩家(含 wizard)ask 一次即得帶﹐
//   便於驗收(UNGATED single-ask)。
//
// ⚠ 本 NPC 自訂 do_ask(add_action)﹐依 lesson『有自訂 add_action 之 NPC 斷不可
//   replace_program』— 本檔故「不」replace_program。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIY "阿拓" NOR, ({ "atuo", "a tuo", "woodcutter", "woodman" }) );
	set("nickname", "老樵夫");
	set("title", "釘靈古墓外的伐薪人");
	set("gender", "male");
	set("age", 66);
	set_attr("str", 22);
	set_attr("con", 24);
	set_race("human");
	set_class("commoner");
	set_level(14);
	set_skill("unarmed", 25);
	set_skill("dodge", 20);
	set_skill("force", 25);
	set_skill("axe", 40);

	set("long",
		"城門洞下歇腳的﹐是一個自城外林子裡來的老樵夫。他生得黧黑\n"
		"精瘦﹐一身打了補丁的粗布短褐﹐肩上橫著一根磨得發亮的扁擔﹐\n"
		"擔頭兩大捆新斫的柴薪還沁著松脂的清香。他腰間束著一條黝黑\n"
		"油亮的粗麻絛帶﹐想是縛柴縛慣了的舊物。雖上了年紀﹐那一身\n"
		"伐薪挑擔練出的筋骨卻結實得很﹐古銅色的臂膀虬筋盤結。聽他\n"
		"說﹐他終年在城西『釘靈古墓』外那片老樹林裡伐薪燒炭﹐今日\n"
		"挑了柴進城來販﹐正歇在這城門下乘涼﹐見人來便和氣地咧嘴一\n"
		"笑﹐露出一口被旱菸熏黃的牙。\n"
		"（你或許可以問問他這營生﹕ask atuo about 樵夫）\n");

	set("chat_chance", 5);
	set("chat_msg", ({
		"老樵夫阿拓拿旱菸桿在鞋底磕了磕菸灰﹐咧嘴笑道﹕後生﹐買捆柴罷﹖剛斫的﹐乾爽得很哩﹗\n",
		"老樵夫阿拓望著城西的方向﹐悠悠道﹕釘靈古墓外那片林子﹐邪門得緊﹐入夜可去不得喲……\n",
		"老樵夫阿拓拍了拍腰間那條黝黑的麻絛帶﹐自言自語﹕這條老絛子﹐縛了我三十年的柴嘍。\n",
		"老樵夫阿拓抹了把汗﹐嘆道﹕伐了大半輩子柴﹐膝下又沒個一兒半女﹐唉……\n",
	}));

	setup();
	carry_object("/d/capital/npc/obj/woodman_girdle")->wear();
	carry_money("coin", 12);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 把一條縛柴麻絛帶同步交到玩家手上（new + move﹔move 失敗才落地﹐鏡 lizaiyan.c）。
// 第二道防重給：玩家身上已有則不再給。
private void give_girdle(object who)
{
	object girdle;

	if( !who || environment(who) != environment() )
		return;
	if( present("woodman girdle", who) )
		return;

	girdle = new(__DIR__"obj/woodman_girdle");
	if( !girdle->move(who) )
		girdle->move(environment());
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg )
		return notify_fail("你想問這位老樵夫甚麼﹖（試試 ask atuo about 樵夫）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("阿拓正埋頭整理擔上的柴捆﹐沒空理你。\n");

	// 贈帶分支：樵夫 / 古墓 / 腰帶 / 麻絛帶 / 柴 / girdle
	if( arg == "atuo about 樵夫"
	||  arg == "atuo about 古墓"
	||  arg == "atuo about 釘靈古墓"
	||  arg == "atuo about 腰帶"
	||  arg == "atuo about 麻絛帶"
	||  arg == "atuo about 絛帶"
	||  arg == "atuo about 柴"
	||  arg == "atuo about 伐薪"
	||  arg == "atuo about girdle"
	||  arg == "atuo about woodcutter"
	||  arg == "a tuo about 樵夫"
	||  arg == "a tuo about girdle"
	||  arg == "woodcutter about 樵夫"
	||  arg == "woodman about girdle" ) {

		// 已領過：若帶已不在身(弄丟了)﹐同步補發一條﹔否則只給氣氛、不重發。
		if( me->query("quest/sq_atuo") >= 1 ) {
			if( !present("woodman girdle", me) ) {
				give_girdle(me);
				do_chat(({
					(: command, "say 咦﹖前番贈你的那條麻絛帶﹐怎的不見了﹖年輕人就是毛躁。" :),
					(: command, "say 罷罷罷﹐老漢這擔上還有一條﹐再與你一條便是——這回可得束牢嘍﹗" :),
				}));
				return 1;
			}
			do_chat(({
				(: command, "say （阿拓咧嘴一笑，露出一口熏黃的牙）那條麻絛帶老漢既已贈了你﹐便是你的了。" :),
				(: command, "say 好生束著罷——別小看這條粗絛子﹐縛了我三十年的柴﹐比那綢緞帶子還禁得住勒哩﹗" :),
			}));
			return 1;
		}

		// 未領：同步授帶（先給物、後設旗標）﹐再播氣氛對白。
		give_girdle(me);
		me->set("quest/sq_atuo", 1);
		do_chat(({
			"阿拓把旱菸桿往鞋底一磕﹐上下打量了你一番﹐和氣地咧嘴笑了。\n",
			(: command, "say 後生肯跟老漢這伐柴的糟老頭子說話﹐難得喲。老漢終年在城西釘靈古墓外那片林子裡伐薪燒炭﹐一個人﹐慣了。" :),
			(: command, "say 那古墓邪門得很﹐入夜林子裡陰風颼颼的﹐尋常樵子早不敢去嘍﹐就剩老漢一個傻子﹐一伐便是三十年。" :),
			(: command, "say 老漢膝下沒個一兒半女﹐這條縛柴的麻絛帶束慣了腰桿﹐倒捨不得。也罷——看你投緣﹐這條老絛子便贈與你罷﹗" :),
			"阿拓伸手解下腰間那條黝黑油亮的麻絛帶﹐在掌心抖了抖塵土﹐鄭重塞進你手中。\n",
			(: command, "say 這絛子韌得很﹐束在腰上勒緊了﹐挑擔、趕路、動手腳﹐都比尋常皮帶禁使。拿去罷﹐莫嫌它土。" :),
		}));
		return 1;
	}

	return notify_fail("阿拓憨憨一笑﹐撓了撓頭﹕老漢一個伐柴的﹐曉得的不多。（試試 ask atuo about 樵夫）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗後生莫動手﹗老漢一個伐柴的糟老頭子﹐當不起少俠動怒。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
