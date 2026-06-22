// jiangyun.c -- 漕幫禮堂的耆宿「江隕」(uid: jiangyun)。
//
// 【設定 / canon】依 ES2 設定﹐江隕是漕幫在京畿的老前輩、漕幫「四鬼問環」支線的關鍵人﹕
//   他授予玩家「四鬼招喚環」﹐玩家持環往卯天樹下開封、誅赤魈／青蛛／濁魚／旱魃 四鬼。
//   本幫亦以江隕為名義上的創幫者——漕幫禮堂（/d/caobang/hall）於 create() 內即以 uid
//   "jiangyun" 向 CLAN_D 登錄漕幫(register_clan)。
//
// 【漕幫支線「四鬼問環」終點 quest-giver】（旗標自成 quest/caobang_*﹐與下方正史主線
//   main_canon* 旗標完全獨立、互不讀寫）：
//   這是序章漕幫這條道上、正史第五章四鬼任務【之前】的一段「問環」支線。玩家先向漕運
//   碼頭周老大領漕幫竹籌(quest/caobang_start)﹐持籌循渡口船工阿邦→阿義→酒館外老乞丐
//   三步 ask-path 問出四鬼舊環的源流(quest/caobang_clue_a/b/c)﹐再回禮堂向江隕覆命﹕
//     * topic「問環」(及 四鬼問環／舊環／古篆拓／拓本／sigui token)：見 siguihuan_quest()。
//     * 須持竹籌(caobang tally)且三段線索齊全(caobang_clue_a/b/c 皆 >=1)﹐方授「四鬼古篆拓」
//       (d/caobang/npc/obj/sigui_token)+ set quest/caobang_done = 1（同步授物：handler 內直接
//       new+move﹐在設旗標之前——承同步交付教訓）。完成後純氣氛、防重領；拓本遺失補發、不重置。
//   本支線終獎「四鬼古篆拓」是一幅四鬼古篆的拓本【信物】﹐刻意與正史那枚開封用的「四鬼招喚
//   環」(ghost ring)分作不同物件、不同 id、不同階段——拓本是漕幫認下玩家「問環之功」的記認、
//   兼正史授環的敘事引子﹐而非開封聖物。topic「問環」與下方正史「四鬼」topic(關鍵字 四鬼／環／
//   招喚環／封印／卯天樹／星光環…)【無任何重疊】﹐二線並行不悖。
//
// 【正史主線第五章「四鬼任務」quest-giver】（決策 A 已拍板、序章直通 canon﹐本檔遂實作
//   授環/交差）﹕
//   * 接任務：玩家須先了結第四章蜈蚣之患(quest/main_canon4_done >= 1)。江隕授「四鬼招喚
//     環」(d/chimei/npc/obj/ghost_ring) 並 set quest/main_canon5 = 1。同步授環(handler 內
//     直接 new+move﹐非延遲 do_chat——承同步交付之教訓)。
//   * 進行中：提醒往卯天樹下『用 環』開封、誅四鬼。
//   * 交差：四鬼盡誅(main_canon5 == 2、四鬼之 die() 計數達 4 時推進)且持「星光環」
//     (starlight_ring)歸來→同步發獎 give_reward5 + set quest/main_canon5_done = 1﹐並導入
//     第六章四神 lead。
//   * 未達門檻(main_canon4_done < 1)：僅給「時機未到」氣氛對白(原 A-gated 鋪墊)。
//
// 【正史主線第六章「四神任務」quest-giver】（sishen_quest）：須先了結第五章四鬼之患
//   (main_canon5_done >= 1)。開四神之約(main_canon6=1)、四印嵌齊星光環歸來交差(main_
//   canon6==2)→發獎 give_reward6 + main_canon6_done=1，導入第七章渾沌獸 lead。
//
// 【正史主線第七章「渾沌獸任務」quest-giver】（hundun_quest）：須先了結第六章四神之患
//   (main_canon6_done >= 1)。江隕以那湊齊的五片『破碎的印記』(其一即玩家自蜈蚣之患聖木
//   殘根所得)合『神之心』，於禮堂中熔煉成『渾沌印記』(d/longdao/npc/obj/chaos_seal)、同
//   步授予玩家並 set main_canon7=1，指引往天龍島七彩石(d/longdao/colorstone)『insert
//   chaos seal』招出渾沌獸(d/longdao/npc/chaosbeast)。降渾沌獸得『渾沌之心』(完整印記，
//   d/longdao/npc/obj/chaos_heart)、main_canon7=2；持心歸來交差(main_canon7==2)→同步發獎
//   give_reward7 + main_canon7_done=1，開天靈/地靈兩條 arc lead（赤魈村許願池 天命刃+eye
//   ／地氣塔頂 悍地斧+heart）。授印/發獎同步綁定（承同步交付教訓）。
//
// 【正史主線第八章「天靈/地靈任務」quest-giver】（tianling_quest）：須先了結第七章渾沌獸
//   之患(main_canon7_done >= 1)。天靈、地靈兩條 sibling sub-quest 共此狀態機，開約後 set
//   main_canon8=1：天靈在赤魈村許願池(d/chimei/wishpool，自村 west)、地靈在京畿地氣塔頂
//   (d/dipa/tower_top，自皇城廣場 down→塔基→up→塔頂)。降天靈(d/chimei/npc/tianling_spirit)
//   得天命刃(d/chimei/npc/obj/fate_dagger)+天靈之眼(d/chimei/npc/obj/sky_eye)、main_canon8
//   =2；降地靈(d/dipa/npc/diling_spirit)得悍地斧(d/dipa/npc/obj/quake_axe)+地靈之心(d/dipa/
//   npc/obj/earth_heart)、main_canon8=3。本章主獎皆由二靈逐玩家 die() 掉落，江隕只開約、
//   交差發謝禮。持眼+心歸來交差(main_canon8==3)→同步發獎 give_reward8 + main_canon8_done=1，
//   導入第九章日月神薛(京畿神社 donate eye+heart+星光環 ring)。docs 列的火雷風雨四神武器/
//   聖木殘根→炎日箭→太陽槍 物鏈乃敘事鋪陳，已抽象入接任務對白，不另造 sub-chain。

#include <npc.h>
#include <ansi.h>

int do_ask(string arg);
private int siguihuan_quest(object me);
private int sigui_quest(object me);
private int sishen_quest(object me);
private int hundun_quest(object me);
private int tianling_quest(object me);
private void give_sigui_token(object who);
private void give_ghost_ring(object who);
private void give_chaos_seal(object who);
private void give_reward5(object who);
private void give_reward6(object who);
private void give_reward7(object who);
private void give_reward8(object who);

void create()
{
	set_name("江隕", ({ "jiangyun", "elder jiangyun", "jiang yun" }) );
	set("nickname", "江隕");
	set_race("human");
	set_class("commoner");
	set_level(20);

	set("age", 71);
	set("gender", "male");
	set("long",
		"這位是漕幫在京畿輩分最高的老前輩﹐江隕。他生得清癯﹐一\n"
		"頭花白的長髮在腦後束成一個髻﹐穿一件洗得發舊的玄青長袍﹐袍\n"
		"角還沾著經年的河水氣。他不像個跑船的﹐倒像個飽歷風霜的隱\n"
		"者——一雙眼睛深得很﹐望著「漕」字大旗出神時﹐眉宇間似壓著\n"
		"一樁說不出口的舊事。漕幫上下﹐連分舵主見了他都要執晚輩禮。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"江隕負手立在「漕」字大旗下﹐仰望著歷代總舵主的牌位﹐久久不語。\n",
		"江隕枯瘦的手指輕輕撫過供案上那具鏽蝕的鐵錨﹐眼神悠遠﹐似在追憶甚麼。\n",
		"江隕端起一盞涼透了的茶﹐卻並不喝﹐只望著窗外東去的河水﹐輕輕嘆了口氣。\n",
		"江隕低聲自語﹕四鬼散於四方 ... 這一樁因果﹐到底何時方了 ...\n",
	}));
	setup();
	carry_money("silver", 5);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想向這位老前輩請教甚麼﹖（試試 ask jiangyun about 漕幫／四鬼）\n");

	// 漕幫：江隕道出漕幫的源流與不結仇的幫風
	if( arg == "jiangyun about 漕幫"
	||  arg == "jiangyun about 禮堂"
	||  arg == "jiangyun about 漕運"
	||  arg == "jiangyun about caobang"
	||  arg == "elder jiangyun about 漕幫" ) {
		do_chat(({
			(: command, "say 客官遠來。這裡是漕幫的禮堂﹐老朽江隕﹐在這幫裡叨陪末座﹐忝為幾分薄面。漕幫執掌天下漕運﹐自前朝開鑿這條大運河、設下漕運糧道時便已立幫﹐傳到如今﹐也有百十年的光景了。" :),
			(: command, "say 咱漕幫幫眾數十萬﹐沿運河南北分舵林立﹐看著聲勢浩大﹔可這幫子自立幫起﹐便守著一條不成文的規矩——不與江湖中人結仇怨。跑船的人﹐求的是四海通達、與人方便﹐結那些刀頭舔血的梁子﹐做甚﹖" :),
			(: command, "say 客官若有心入夥﹐這禮堂的分舵主宋安江﹐人最爽利﹐入幫的章程﹐尋他問便是。老朽老了﹐如今只在這禮堂裡看看舊旗、守守舊事罷了。" :),
		}));
		return 1;
	}

	// 四鬼問環：漕幫支線終點——驗三段線索齊全、授「四鬼古篆拓」+ set caobang_done。
	// topic 與下方正史「四鬼」topic 無重疊（不含 四鬼／環／招喚環…等正史關鍵字）。
	if( arg == "jiangyun about 問環"
	||  arg == "jiangyun about 四鬼問環"
	||  arg == "jiangyun about 舊環"
	||  arg == "jiangyun about 古篆拓"
	||  arg == "jiangyun about 拓本"
	||  arg == "jiangyun about sigui token"
	||  arg == "elder jiangyun about 問環" ) {
		return siguihuan_quest(this_player());
	}

	// 四鬼：正史主線第五章 quest-giver——接任務／進行中／交差／門檻未達 四態
	if( arg == "jiangyun about 四鬼"
	||  arg == "jiangyun about 環"
	||  arg == "jiangyun about 招喚環"
	||  arg == "jiangyun about 指環"
	||  arg == "jiangyun about 封印"
	||  arg == "jiangyun about 卯天樹"
	||  arg == "jiangyun about 星光環"
	||  arg == "jiangyun about 赤魈"
	||  arg == "jiangyun about 青蛛"
	||  arg == "jiangyun about 濁魚"
	||  arg == "jiangyun about 旱魃"
	||  arg == "jiangyun about quest"
	||  arg == "elder jiangyun about 四鬼" ) {
		return sigui_quest(this_player());
	}

	// 四神：正史主線第六章 quest-giver——接任務／進行中／交差／門檻未達 四態。
	// 門檻：須先了結第五章四鬼之患(quest/main_canon5_done >= 1)。
	if( arg == "jiangyun about 四神"
	||  arg == "jiangyun about 神印"
	||  arg == "jiangyun about 天龍島"
	||  arg == "jiangyun about 火神"
	||  arg == "jiangyun about 天龍"
	||  arg == "jiangyun about 雷神"
	||  arg == "jiangyun about 風神"
	||  arg == "elder jiangyun about 四神" ) {
		return sishen_quest(this_player());
	}

	// 渾沌獸：正史主線第七章 quest-giver——接任務(授渾沌印記)／進行中／交差／門檻未達
	// 四態。門檻：須先了結第六章四神之患(quest/main_canon6_done >= 1)。
	if( arg == "jiangyun about 渾沌"
	||  arg == "jiangyun about 渾沌獸"
	||  arg == "jiangyun about 渾沌印記"
	||  arg == "jiangyun about 七彩石"
	||  arg == "jiangyun about 神之心"
	||  arg == "jiangyun about 破碎的印記"
	||  arg == "jiangyun about chaos"
	||  arg == "elder jiangyun about 渾沌獸" ) {
		return hundun_quest(this_player());
	}

	// 天靈/地靈：正史主線第八章 quest-giver——接任務／進行中／交差／門檻未達 四態。
	// 門檻：須先了結第七章渾沌獸之患(quest/main_canon7_done >= 1)。天靈(赤魈村許願池→
	// 天命刃+天靈之眼)與地靈(地氣塔頂→悍地斧+地靈之心)兩條 sibling sub-quest 共此狀態機。
	if( arg == "jiangyun about 天靈"
	||  arg == "jiangyun about 地靈"
	||  arg == "jiangyun about 天命刃"
	||  arg == "jiangyun about 悍地斧"
	||  arg == "jiangyun about 天靈之眼"
	||  arg == "jiangyun about 地靈之心"
	||  arg == "jiangyun about 許願池"
	||  arg == "jiangyun about 地氣塔"
	||  arg == "jiangyun about 日月神薛"
	||  arg == "jiangyun about spirit"
	||  arg == "elder jiangyun about 天靈"
	||  arg == "elder jiangyun about 地靈" ) {
		return tianling_quest(this_player());
	}

	return notify_fail("江隕望著東去的河水﹐淡淡道﹕有些事﹐時候未到﹐多問無益。客官且自便罷。（試試 ask jiangyun about 漕幫／問環／四鬼／四神／渾沌獸／天靈／地靈）\n");
}

// 漕幫支線「四鬼問環」終點狀態機。who=this_player()。同步授「四鬼古篆拓」(信物)、旗標
// 與授受綁定（承同步交付教訓）。本支線旗標自成 quest/caobang_*﹐與正史 main_canon* 完全
// 獨立、互不讀寫。
private int siguihuan_quest(object me)
{
	if( !me ) return 0;

	if( is_fighting() || is_chatting() )
		return notify_fail("江隕正凝望著「漕」字大旗出神﹐一時無暇答話。\n");

	// 已完成：純氣氛、防重領（拓本遺失則補發、不重置進度）。
	if( me->query("quest/caobang_done") >= 1 ) {
		if( !present("sigui token", me) ) {
			// 同步補發：give_sigui_token 直接 new+move（玩家此刻必在場）；do_chat 只留氣氛。
			give_sigui_token(me);
			do_chat((: command, "say 少俠那幅四鬼古篆拓怎不見了？那是老朽認下少俠問環之功的記認﹐丟不得。罷了﹐老朽再拓一幅與你——這回好生收著。" :));
			return 1;
		}
		do_chat(({
			(: command, "say 少俠循著竹籌﹐一路從渡口的阿邦、阿義﹐問到那落魄的漕幫舊人﹐又把這四鬼舊環的源流問了個齊全——老朽守了幾十年的這樁心事﹐今日總算遇著個肯為它奔走的後生了。" :),
			(: command, "say 少俠手中那幅四鬼古篆拓﹐好生收著。他日京畿那株聖木之節若當真為甚麼變故所斷、卯天樹下鎮鬼的封印一鬆——少俠再來尋老朽（ask jiangyun about 四鬼），老朽自會把那枚真能開封誅鬼的舊環﹐正式交在少俠手裡。" :),
		}));
		return 1;
	}

	// 未持籌 / 未起差事：指去碼頭尋周老大領籌（不記旗標）。
	if( me->query("quest/caobang_start") < 1 || !present("caobang tally", me) ) {
		do_chat((: command, "say （江隕淡淡看你一眼）客官連咱漕幫的竹籌都不曾揣著﹐這四鬼問環的舊事﹐老朽便是說了﹐客官也接不住。客官若有心入夥﹐先往渡口東頭的漕運碼頭﹐尋那攬頭周老大領一枚竹籌罷。(ask zhoulaoda about 差事)" :));
		return 1;
	}

	// 持籌、線索未齊：指去循阿邦→阿義→老乞丐把四鬼源流問齊（不記旗標）。
	if( me->query("quest/caobang_clue_c") < 1 ) {
		do_chat(({
			(: command, "say （江隕的目光在少俠腰間那枚竹籌上一掠﹐微微頷首）少俠是揣著籌子來的——是咱漕幫的人了。只是這四鬼舊環的因由﹐千頭萬緒﹐老朽不好沒頭沒腦地說與你。" :),
			(: command, "say 少俠且去渡口走一遭﹕先尋那老船工阿邦﹐再循他的話頭問年輕的阿義﹐末了去酒館外尋那討飯的老乞丐——那老叫花子是漕幫的舊人﹐這四鬼舊環的根底﹐就數他曉得得最透。少俠把這一路的源流問齊了﹐再回來尋老朽覆命。(ask abang about 四鬼)" :),
		}));
		return 1;
	}

	// 線索齊全(clue_c 在)﹐首次覆命：同步授「四鬼古篆拓」、即記 caobang_done。
	// 先給物、後記旗標——免於回呼前離場致拓本沒領、旗標卻記完成而卡關（#同步交付）。
	give_sigui_token(me);
	me->set("quest/caobang_done", 1);
	do_chat(({
		(: command, "say （江隕定定地看了少俠半晌﹐渾濁的老眼裡迸出久違的精光）少俠竟揣著竹籌﹐一路從阿邦、阿義﹐問到那落魄的老乞丐﹐把老朽這四鬼舊環的源流﹐問了個齊全——肯為這檔子與己無干的舊事如此奔走的後生﹐老朽等了幾十年了。" :),
		(: command, "say 不瞞少俠﹕老朽手裡確有一枚當年布鎮卯天樹下封印之人所遺的舊銅環﹐環身刻著赤魈、青蛛、濁魚、旱魃四鬼的古篆。只是那環真能開封誅鬼——這樁干係太大﹐繫於京畿那株聖木的氣數﹐時候未到﹐老朽還交付不得。" :),
		(: command, "say （江隕取過那枚舊環﹐在一方素絹上以濃墨將環身四道古篆細細拓下﹐又補了一行小楷﹐雙手疊好奉與少俠）這幅四鬼古篆拓﹐少俠收著——是老朽認下少俠這份問環之功的記認。他日聖木之節若有變故、鬼封一鬆﹐少俠再來尋老朽（ask jiangyun about 四鬼）﹐老朽自會把那枚開封的舊環﹐正式交在少俠手裡。去罷﹐少俠﹐好生留著這幅拓本。" :),
	}));
	return 1;
}

// 同步授「四鬼古篆拓」(支線信物)。who=玩家。防重複授物（身上已有則不重授）。
// 先試 move 到玩家身上﹐不成（負重等）則落在環境地上——絕不靜默丟失。
private void give_sigui_token(object who)
{
	object token;

	if( !who || environment(who) != environment() ) return;
	if( present("sigui token", who) ) return;

	token = new("/d/caobang/npc/obj/sigui_token");
	if( !objectp(token) ) return;
	if( !token->move(who) ) token->move(environment());

	who->gain_score("emprise", 120);
	who->gain_score("reputation", 80);
	who->gain_score("explorer fame", 60);

	message_vision(
		HIY "江隕鄭重自懷中取出一枚古樸厚重的青銅舊環﹐又取一方素絹、一錠濃墨﹐"
		"將那環身四道詰屈如蟲的古篆細細拓下﹐補了一行小楷﹐疊得方正﹐雙手交到"
		"$N手裡——這幅四鬼古篆拓﹐是漕幫認下$N問環之功的記認。\n" NOR,
		who);
}

// 第五章四鬼任務狀態機。who=this_player()。同步授環/發獎、旗標與授受綁定（承同步交付教訓）。
private int sigui_quest(object me)
{
	if( !me ) return 0;

	// 已完成：四神 lead 尾聲（不重複發獎）。
	if( me->query("quest/main_canon5_done") >= 1 ) {
		do_chat(({
			(: command, "say 少俠誅盡了卯天樹下的山林川原四鬼、得了那枚星光環﹐這壓在老朽心頭數十年的舊因果﹐總算了結了大半。" :),
			(: command, "say 那枚星光環﹐少俠須好生收著——環身那四道古篆所鎮的﹐原與火、天龍、雷、風四方神祇之力同源。他日少俠若集得火神、雷神、風神、天龍四神的完整封印﹐以四片神印嵌入這星光環﹐另有一番驚天動地的造化。四神之事﹐凶險更勝四鬼﹐少俠好自為之。" :),
		}));
		return 1;
	}

	// 交差：四鬼盡誅(main_canon5 == 2)且持星光環歸來→同步發獎、記 _done。
	if( me->query("quest/main_canon5") == 2 && present("starlight ring", me) ) {
		give_reward5(me);
		me->set("quest/main_canon5_done", 1);
		do_chat(({
			(: command, "say （江隕的目光落在少俠手中那枚流轉著星河微芒的奇環上﹐渾濁的老眼霎時迸出一線精光﹐枯瘦的手微微一顫）這 ... 這是星光環﹗少俠當真把那山林川原四鬼盡數誅了﹖﹗" :),
			(: command, "say 好﹗好﹗好﹗三百年的鎮鬼封印、數十年壓在老朽心頭的舊因果﹐今日總算是了了﹗少俠這份膽識與功業﹐老朽這把老骨頭﹐生受了﹗這點薄禮並些須歷練﹐萬莫推辭。" :),
		}));
		return 1;
	}

	// 進行中：已接環、未誅盡——提醒往卯天樹下開封誅鬼。
	if( me->query("quest/main_canon5") >= 1 ) {
		do_chat(({
			(: command, "say 少俠既已接了這枚四鬼招喚環﹐便往那卯天樹下封印之地去罷——於卯天樹下『用 環』(use ring)﹐催動環上四道古篆﹐便能開那鎮鬼的封印﹐將山林川原四鬼盡數引出。" :),
			(: command, "say 赤魈、青蛛、濁魚、旱魃﹐這四鬼皆是長生不滅的元神之鬼﹐凶厲非常﹐尤以那原鬼旱魃為最。少俠須將四鬼盡數誅了﹐方得那枚了結因果的星光環。卯天樹在赤魈村深處的赤魈森林盡頭——自漕幫碼頭循水路乘船﹐可往赤魈村去。" :),
		}));
		return 1;
	}

	// 接任務：須先了結蜈蚣之患(main_canon4_done)。同步授環 + 旗標 1。
	if( me->query("quest/main_canon4_done") >= 1 ) {
		give_ghost_ring(me);
		me->set("quest/main_canon5", 1);
		do_chat(({
			(: command, "say （江隕定定地看了少俠半晌﹐忽地長身而起﹐渾濁的老眼裡迸出久違的精光）少俠便是了結了京畿那蜈蚣之患的那位罷﹖守木尊者的訊息﹐已隨水路傳到老朽耳中了。" :),
			(: command, "say 京畿聖木之節既為巨蜈蝕斷﹐鎮在卯天樹下那座三百年的鬼封﹐便也跟著鬆了——山林川原四鬼﹐怕是要應劫而出了。老朽等的這個有膽識的後生﹐看來便是少俠你了。" :),
			(: command, "say （江隕自懷中鄭重取出一枚古樸厚重的青銅指環﹐雙手奉上）這枚四鬼招喚環﹐是當年布鎮卯天樹下封印之人所遺﹐環身刻著赤魈、青蛛、濁魚、旱魃四鬼的古篆。少俠持此環往卯天樹下﹐『用 環』開那封印﹐將四鬼引出而一一誅之﹐斷這四方厲鬼之患罷﹗卯天樹在赤魈村深處——自漕幫碼頭乘船﹐可往赤魈村去。" :),
		}));
		return 1;
	}

	// 門檻未達(尚未了結蜈蚣之患)：時機未到的氣氛鋪墊兼伏筆。
	do_chat(({
		(: command, "say （江隕的神色倏地凝重起來﹐枯瘦的手在那具鐵錨上停了一停）客官 ... 也聽說了『四鬼』麼﹖" :),
		(: command, "say 唉。那是一樁壓在老朽心頭數十年的舊因果了。當年那布鎮卯天樹下的山林川原四鬼——赤魈、青蛛、濁魚、旱魃——皆是長生不滅的元神之鬼。老朽手裡﹐還留著一枚當年鎮鬼的舊環﹐本該交付一個有緣、有膽識的後生﹐持環去開那封印、了結這段因果。" :),
		(: command, "say 只是 ...（江隕搖了搖頭﹐長嘆一聲）這環何時能交﹐繫於京畿那株聖木的氣數。聖木之節一日不斷﹐卯天樹下的鬼封便一日穩固﹐四鬼沉睡不出﹐這環便交不得。客官且記下這四個名字﹐待京畿聖木有變之日﹐再來尋老朽罷。" :),
	}));
	return 1;
}

// 同步授「四鬼招喚環」。who=玩家。防重複授環。
private void give_ghost_ring(object who)
{
	object ring;
	if( !who ) return;
	if( present("ghost ring", who) ) return;
	ring = new("/d/chimei/npc/obj/ghost_ring");
	if( !objectp(ring) ) return;
	if( !ring->move(who) ) ring->move(environment());
}

// 第五章交差獎賞（同步發放﹐較第四章再加碼——四鬼為迄今最難之 arc）。星光環為主獎、
// 已由四鬼末一頭掉落﹔此處乃漕幫的謝禮與江湖歷練。
private void give_reward5(object who)
{
	object coin, pill;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(2800);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/major_heal_pill");
	if( !pill->move(who) ) pill->move(environment());

	who->gain_score("survive", 2800);
	who->gain_score("emprise", 900);
	who->gain_score("reputation", 500);
	who->gain_score("martial fame", 540);
	who->gain_score("explorer fame", 200);

	message_vision(
		HIY "江隕鄭重自懷中取出一串沉甸甸的銅錢、一帖上好的療傷丹藥﹐雙手交"
		"到$N手裡﹔又顫巍巍地朝$N深深一揖——這一揖﹐是替那困守卯天樹下封印三"
		"百年的天下蒼生﹐謝過少俠的。\n" NOR, who);
}

// 第六章四神任務狀態機。who=this_player()。承第五章交差所伏「集四神完整封印嵌入星
// 光環」之 lead——接任務／進行中／交差／門檻未達 四態。同步發獎、旗標與星光環嵌印機
// 制（do_insert）綁定（承同步交付教訓）。
private int sishen_quest(object me)
{
	if( !me ) return 0;

	// 已完成：渾沌獸 lead 尾聲（不重複發獎）。
	if( me->query("quest/main_canon6_done") >= 1 ) {
		do_chat(({
			(: command, "say 少俠降盡了天龍島上火、天龍、雷、風四神，將四片完整神印嵌入了星光環——這四方神祇之力齊備的星光環，已是了結十三靈的終局之鑰了。" :),
			(: command, "say 只是那侮天鬼的因果，遠未到了結之時。少俠須知，這世間另有五片『破碎的印記』與一枚『神之心』散落四方；湊齊那五片破碎印記、合以神之心，可煉成一方『渾沌印記』。持那渾沌印記，往那七彩石處『insert chaos seal』，便能招出那頭隨地流竄的『渾沌獸』——降了渾沌獸，必得一片完整印記。四神已了，渾沌獸之事，便是少俠下一步的去處了。" :),
		}));
		return 1;
	}

	// 交差：四神盡降、四印盡嵌(main_canon6 == 2、do_insert 第四片嵌入時推進)且持四印
	// 齊備的星光環歸來→同步發獎、記 _done。
	if( me->query("quest/main_canon6") == 2 && present("starlight ring", me) ) {
		give_reward6(me);
		me->set("quest/main_canon6_done", 1);
		do_chat(({
			(: command, "say （江隕的目光落在少俠手中那枚四色神光齊綻的星光環上，渾濁的老眼霎時迸出滔天的精光，枯瘦的雙手抖得幾乎握不住）這 ... 這是四神之力盡數嵌齊的星光環！少俠當真把那天龍島上火、天龍、雷、風四神盡數降了？！" :),
			(: command, "say 好！好！好！三百年了——自那布鎮卯天樹下封印之人遺下這一樁因果，歷四鬼、歷四神，今日總算在少俠手中見了曙光！這四神之力齊備的星光環，便是他日了結十三靈、再戰那侮天鬼的終局之鑰了。這點薄禮並些須歷練，少俠萬莫推辭。" :),
			(: command, "say 少俠且聽老朽一言：這因果尚未了結。世間另有五片『破碎的印記』與一枚『神之心』散落四方——湊齊那五片破碎印記、合以神之心，可煉成一方『渾沌印記』；持那渾沌印記往七彩石處招出那頭隨地流竄的『渾沌獸』，降之必得一片完整印記。四神既了，這渾沌獸，便是少俠下一步的去處了。" :),
		}));
		return 1;
	}

	// 進行中：已接約、四印未嵌齊——提醒往天龍島降四神、取印嵌環。
	if( me->query("quest/main_canon6") >= 1 ) {
		do_chat(({
			(: command, "say 少俠既已接了這四神之約，便往那海外天龍島去罷——自西方檒城的望安港、那舊船屋的棧橋登舟(往西渡海)，循星光環四道古篆之引，可渡海登那天龍島。" :),
			(: command, "say 天龍島上鎮著火神(鳳凰)、天龍(島主)、雷神(澤獸)、風神(大鵬)四方神祇，凶險遠勝四鬼，尤以那雷神、風神為最。少俠須將四神一一降伏，自其屍身取下『火神之印』、『天龍之印』、『雷神之印』、『風神之印』四片完整神印，再於身上將四印逐一嵌入星光環(insert seal of fire／insert seal of dragon／insert seal of thunder／insert seal of wind)。四印盡嵌，星光環四色神光齊綻之時，再持環回來尋老朽覆命。" :),
		}));
		return 1;
	}

	// 接任務：須先了結第五章四鬼之患(main_canon5_done >= 1)。同步啟旗標 1。星光環玩
	// 家手中已有（第五章主獎），此處不另授物，只開四神之約。
	if( me->query("quest/main_canon5_done") >= 1 ) {
		me->set("quest/main_canon6", 1);
		do_chat(({
			(: command, "say （江隕定定地看了少俠半晌，渾濁的老眼裡那一線精光久久不散）少俠既誅盡了卯天樹下的山林川原四鬼、得了那枚星光環，老朽便把這壓在心頭最深的一樁因果，也一併託付了罷。" :),
			(: command, "say 少俠手中那枚星光環，環身四道古篆所鎮的，原與火、天龍、雷、風四方神祇之力同源。海外有一座天龍島，鎮著火神(鳳凰)、天龍(島主)、雷神(澤獸)、風神(大鵬)四方神祇——三百年前山林川原四鬼既封於卯天樹下，這四神之力便分鎮那島。少俠若能將這四神一一降伏，取其完整神印嵌入星光環，這枚環，便成了了結十三靈、再戰侮天鬼的終局之鑰了。" :),
			(: command, "say 往那西方檒城的望安港去罷——港邊舊船屋的棧橋上有位識得水路的老船家，少俠奉了老朽之命、持星光環登舟往西渡海，便能登那天龍島。四神凶險遠勝四鬼，少俠須得有備而往、好自為之。降了四神、取了火、天龍、雷、風四印嵌入星光環(insert seal of …)，再回來尋老朽。" :),
		}));
		return 1;
	}

	// 門檻未達(尚未了結四鬼之患)：時機未到的氣氛鋪墊兼伏筆。
	do_chat(({
		(: command, "say （江隕搖了搖頭，長嘆一聲）少俠也聽說了那海外天龍島上的『四神』麼？火、天龍、雷、風四方神祇，凶險遠非那山林川原四鬼可比。" :),
		(: command, "say 只是 ... 那是後話了。少俠手裡若無那枚誅盡四鬼方得的星光環，這四神之事，老朽便是說了，也是枉然。客官且先去了結那卯天樹下的四鬼之患、得了星光環，再來尋老朽問這四神罷。" :),
	}));
	return 1;
}

// 第六章交差獎賞（同步發放﹐較第五章再加碼——四神為迄今最難之 arc）。星光環為信物
// （玩家自始持有、四印已嵌）﹐此處乃漕幫的謝禮與江湖歷練﹐不取走星光環（終局之鑰，
// 玩家須續持往渾沌獸/十三靈 arc）。
private void give_reward6(object who)
{
	object coin, pill;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(5000);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/major_heal_pill");
	if( !pill->move(who) ) pill->move(environment());

	who->gain_score("survive", 5000);
	who->gain_score("emprise", 1600);
	who->gain_score("reputation", 900);
	who->gain_score("martial fame", 950);
	who->gain_score("explorer fame", 400);

	message_vision(
		HIY "江隕鄭重自懷中取出一串更為沉甸甸的銅錢、一帖上好的療傷丹藥﹐雙手交"
		"到$N手裡﹔復又顫巍巍地離座而起﹐朝$N深深一揖到地——這一揖﹐是替那盼了三"
		"百年、終得四神之力齊備之星光環的天下蒼生﹐謝過少俠的。\n" NOR, who);
}

// 第七章渾沌獸任務狀態機。who=this_player()。承第六章交差所伏「五片破碎印記＋神之心煉
// 渾沌印記、往七彩石招渾沌獸、降之必得完整印記」之 lead——接任務(授渾沌印記)／進行中／
// 交差／門檻未達 四態。同步授印/發獎、旗標與授受綁定（承同步交付教訓）。
private int hundun_quest(object me)
{
	if( !me ) return 0;

	// 已完成：天靈/地靈 arc lead 尾聲（不重複發獎）。
	if( me->query("quest/main_canon7_done") >= 1 ) {
		do_chat(({
			(: command, "say 少俠以渾沌印記自七彩石招出了那頭隨地流竄的渾沌獸、又將牠降伏，得了那枚渾沌之心、一片完整印記——這壓在老朽心頭最後一樁因果，總算也了結了。" :),
			(: command, "say 少俠且記下這往後兩樁去處：其一，天靈之事——往那赤魈村的許願池去，可解得『天命刃』(dagger of fate)與一枚『眼』；其二，地靈之事——須登那地氣塔頂，可得『悍地斧』(twohanded axe)與一枚『心』。集齊那心、眼，並這枚渾沌之心、那枚星光環，往京畿神社獻與日月神薛，再戰那侮天鬼的終局之路，便豁然在望了。這天、地二靈之事，少俠細問老朽便是(ask jiangyun about 天靈／地靈)。去罷，少俠。" :),
		}));
		return 1;
	}

	// 交差：渾沌獸已降(main_canon7 == 2、chaosbeast die() 推進)且持渾沌之心歸來→同步發
	// 獎、記 _done。
	if( me->query("quest/main_canon7") == 2 && present("chaos heart", me) ) {
		give_reward7(me);
		me->set("quest/main_canon7_done", 1);
		do_chat(({
			(: command, "say （江隕的目光落在少俠手中那枚七彩流轉、混沌未分的完整印記上，渾濁的老眼霎時迸出畢生最盛的精光，枯瘦的雙手抖得幾乎握不住）這 ... 這是渾沌之心！少俠當真以那渾沌印記自七彩石招出了那頭隨地流竄的渾沌獸、又把牠降了？！" :),
			(: command, "say 好！好！好！自蜈蚣之患所留那枚破碎的印記、歷四鬼、歷四神、終又降了這天地初開的渾沌獸——三百年的因果，今日總算在少俠手中見了終局的曙光！這點薄禮並些須歷練，少俠萬莫推辭，老朽這把老骨頭，生受了！" :),
			(: command, "say 少俠且聽老朽道明往後兩樁去處：其一，天靈之事——往那赤魈村的許願池去，可解得『天命刃』(dagger of fate)與一枚『眼』；其二，地靈之事——須登那地氣塔頂，可得『悍地斧』(twohanded axe)與一枚『心』。集齊那心、眼，並這枚渾沌之心、那枚星光環，往京畿神社獻與日月神薛，再戰侮天鬼的終局之路，便豁然在望了。這天、地二靈之事，少俠細問老朽便是(ask jiangyun about 天靈／地靈)。" :),
		}));
		return 1;
	}

	// 進行中：已授渾沌印記、渾沌獸未降——提醒往七彩石招喚誅之。
	if( me->query("quest/main_canon7") >= 1 ) {
		do_chat(({
			(: command, "say 少俠既已得了老朽所煉的這方渾沌印記，便往那海外天龍島去罷——自西方檒城的望安港登舟渡海登島，循島心鎮島神域旁那一道盤旋的玄石階向上(up)攀去，便登臨那矗著七彩石的石臺。" :),
			(: command, "say 立於那七彩石前，於身上『insert chaos seal』(亦可『用 渾沌印記』)，便能將那石中所封、隨地流竄的渾沌獸重新招出。那渾沌獸是天地初開、清濁未判時所遺的太古之獸，烙人猛砍、凶險更勝那天龍島四神，少俠須得有備而往、好自為之。降了渾沌獸，必得一枚渾沌之心、一片完整印記，再持心回來尋老朽覆命。" :),
		}));
		return 1;
	}

	// 接任務：須先了結第六章四神之患(main_canon6_done >= 1)。同步以破碎印記＋神之心熔煉
	// 授「渾沌印記」+ 啟旗標 1。
	if( me->query("quest/main_canon6_done") >= 1 ) {
		give_chaos_seal(me);
		me->set("quest/main_canon7", 1);
		do_chat(({
			(: command, "say （江隕定定地看了少俠半晌，渾濁的老眼裡那一線精光久久不散）少俠既降盡了天龍島火、天龍、雷、風四神、嵌齊了星光環，老朽便把這壓在心頭最後一樁因果，也一併託付了罷。" :),
			(: command, "say 少俠須知，這世間另有五片『破碎的印記』與一枚『神之心』散落四方——其中一片破碎印記，正是少俠當年斫斷京畿聖木之節、自那聖木殘根中所得、一路帶在身邊的。老朽這些年，已暗中湊齊了其餘四片，又得了那一枚散落人間的神之心；如今少俠既至，這最後一道熔煉的火候，便齊了。" :),
			(: command, "say （江隕鄭重自懷中取出那湊齊的破碎印記與神之心，於掌心以秘法一引，那數片殘印與神之心霎時熔作一團七彩流轉的混沌元氣、凝成一方奇異的印記，雙手奉上）這便是『渾沌印記』了。少俠持此印往那海外天龍島，自島心鎮島神域旁的玄石階向上(up)攀去，便登臨那七彩石——立於石前，於身上『insert chaos seal』(亦可『用 渾沌印記』)，便能將那石中所封、隨地流竄的渾沌獸招出。降了渾沌獸，必得一枚渾沌之心、一片完整印記。那渾沌獸凶險更勝四神，少俠好自為之。" :),
		}));
		return 1;
	}

	// 門檻未達(尚未了結四神之患)：時機未到的氣氛鋪墊兼伏筆。
	do_chat(({
		(: command, "say （江隕搖了搖頭，長嘆一聲）少俠也聽說了那隨地流竄、混沌未分的『渾沌獸』麼？那是天地初開、清濁未判時所遺的一頭太古之獸，凶險遠非那天龍島四神可比。" :),
		(: command, "say 只是 ... 那是後話了。少俠手裡若無那枚四神之力齊備的星光環，這渾沌獸之事，老朽便是說了，也是枉然。客官且先去了結那天龍島的四神之患、嵌齊星光環，再來尋老朽問這渾沌獸罷。" :),
	}));
	return 1;
}

// 同步授「渾沌印記」。who=玩家。防重複授印（身上已有則不重授）。
private void give_chaos_seal(object who)
{
	object seal;
	if( !who ) return;
	if( present("chaos seal", who) ) return;
	seal = new("/d/longdao/npc/obj/chaos_seal");
	if( !objectp(seal) ) return;
	if( !seal->move(who) ) seal->move(environment());
}

// 第七章交差獎賞（同步發放﹐較第六章再加碼——渾沌獸為迄今最難之 arc）。渾沌之心為信物
// （玩家須續持往天靈/地靈/日月神薛 arc）﹐此處乃漕幫的謝禮與江湖歷練﹐不取走渾沌之心。
private void give_reward7(object who)
{
	object coin, pill;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(8000);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/major_heal_pill");
	if( !pill->move(who) ) pill->move(environment());

	who->gain_score("survive", 8000);
	who->gain_score("emprise", 2600);
	who->gain_score("reputation", 1400);
	who->gain_score("martial fame", 1500);
	who->gain_score("explorer fame", 600);

	message_vision(
		HIY "江隕鄭重自懷中取出一串迄今最為沉甸甸的銅錢、一帖上好的療傷丹藥﹐雙手"
		"交到$N手裡﹔復又顫巍巍地離座而起﹐朝$N深深一揖到地、久久不起——這一揖﹐是"
		"替那困於這三百年因果、終盼得渾沌獸伏誅的天下蒼生﹐謝過少俠的。\n" NOR, who);
}

// 第八章天靈/地靈任務狀態機。who=this_player()。承第七章交差所伏「天靈(赤魈村許願池→
// 天命刃+眼)／地靈(地氣塔頂→悍地斧+心)」兩條 sibling sub-quest 之 lead——接任務／進行
// 中／交差／門檻未達 四態。本章主獎(天命刃/天靈之眼/悍地斧/地靈之心)皆由二靈 die() 逐
// 玩家掉落，江隕此處只開約、交差發謝禮(同步發獎，承同步交付教訓)。旗標 main_canon8：
//   0(未接)→1(已接)→2(天靈已斃、得眼+刃)→3(地靈已斃、得心+斧)→_done(交差)。
private int tianling_quest(object me)
{
	if( !me ) return 0;

	// 已完成：日月神薛 lead 尾聲（不重複發獎）。
	if( me->query("quest/main_canon8_done") >= 1 ) {
		do_chat(({
			(: command, "say 少俠降了赤魈村許願池的天靈、得了天命刃與天靈之眼，又登地氣塔頂降了地靈、得了悍地斧與地靈之心——這天、地二靈的因果，總算也了結了。" :),
			(: command, "say 如今少俠手中，心、眼、那枚四神之力齊備的星光環俱已齊備。再無別話了，少俠——便往京畿神社去罷，將這天靈之眼、地靈之心，連同那枚星光環，一併獻與神社中那位日月神薛(donate eye／donate heart／donate ring)。心、眼、環三者既獻，那再戰侮天鬼、了結十三靈的終局之路，便豁然在望了。去罷，少俠，天下蒼生，都在等著少俠這最後一程。" :),
		}));
		return 1;
	}

	// 交差：天、地二靈盡誅(main_canon8 == 3、二靈 die() 推進)且持眼+心歸來→同步發謝禮、
	// 記 _done。眼/心/天命刃/悍地斧皆玩家自二靈屍身所得、續持往日月神薛 arc，此處不取走。
	if( me->query("quest/main_canon8") == 3
	&&  present("sky eye", me)
	&&  present("earth heart", me) ) {
		give_reward8(me);
		me->set("quest/main_canon8_done", 1);
		do_chat(({
			(: command, "say （江隕的目光落在少俠手中那枚流轉著澄澈天光的天靈之眼、與那枚流轉著沉雄土光的地靈之心上，渾濁的老眼霎時迸出畢生未有的精光，枯瘦的雙手抖得幾乎握不住）這 ... 這是天靈之眼，與地靈之心！少俠當真把赤魈村許願池的天靈、地氣塔頂的地靈，盡數降了？！" :),
			(: command, "say 好！好！好！自蜈蚣之患、歷四鬼、歷四神、降渾沌獸，又了結了這天、地二靈——三百年的因果，今日總算在少俠手中走到了終局的門前！這點薄禮並些須歷練，少俠萬莫推辭，老朽這把老骨頭，生受了！" :),
			(: command, "say 少俠且聽老朽道明這最後一程的去處：如今心、眼，並那枚四神之力齊備的星光環俱已齊備——少俠須往京畿神社去，將這天靈之眼、地靈之心，連同那枚星光環，一併獻與神社中那位日月神薛(donate eye／donate heart／donate ring)。心、眼、環三者既獻，那再戰侮天鬼、了結十三靈的終局之路，便豁然在望了。" :),
		}));
		return 1;
	}

	// 進行中（天靈已斃、地靈未斃）：提醒登地氣塔頂降地靈。
	if( me->query("quest/main_canon8") == 2 ) {
		do_chat(({
			(: command, "say 少俠既已降了赤魈村許願池的天靈、得了那柄天命刃與一枚天靈之眼，便只剩那地靈一樁了。" :),
			(: command, "say 那地靈，盤踞在京畿地氣塔的塔頂——自皇城廣場一隅那道深嵌地底的石階下行(down)，便至那矗於京畿地脈之上的地氣塔塔基；循塔心那道黃石旋梯盤旋而上(up)，便登臨那地氣磅礡的塔頂。那地靈是司一方地氣的厚土之靈，沉雄磅礡，凶險更勝那天靈，少俠須得有備而往、好自為之。降了地靈，必得一枚地靈之心、一柄悍地斧(twohanded axe)，再持那心、眼回來尋老朽覆命。" :),
		}));
		return 1;
	}

	// 進行中（天、地二靈俱未斃）：提醒往二地降二靈。
	if( me->query("quest/main_canon8") >= 1 ) {
		do_chat(({
			(: command, "say 少俠既已接了這天、地二靈之事，便往那二處去罷。其一，天靈——往那赤魈村去，自村中循西邊那道少有人行的小徑(west)下山腳，便至那終年不涸的許願池。許願池上應天地靈氣所鍾的天靈之所，少俠持渾沌之心、星光環引動池水，那司一方天命的天靈便會應引而現。降之，必得一柄天命刃(dagger of fate)與一枚天靈之眼。" :),
			(: command, "say 其二，地靈——須登那京畿地氣塔的塔頂。自皇城廣場一隅那道深嵌地底的石階下行(down)，至那矗於京畿地脈之上的地氣塔塔基，再循塔心黃石旋梯盤旋而上(up)，便登臨地氣磅礡的塔頂。那司一方地氣的地靈應引而現，降之，必得一柄悍地斧(twohanded axe)與一枚地靈之心。天、地二靈俱降、心眼俱得，再持回來尋老朽覆命。" :),
		}));
		return 1;
	}

	// 接任務：須先了結第七章渾沌獸之患(main_canon7_done >= 1)。同步啟旗標 1。
	// 本章主獎皆由二靈掉落，此處不另授物，只開天、地二靈之約。
	if( me->query("quest/main_canon7_done") >= 1 ) {
		me->set("quest/main_canon8", 1);
		do_chat(({
			(: command, "say （江隕定定地看了少俠半晌，渾濁的老眼裡那一線精光久久不散）少俠既以渾沌印記自七彩石招出了渾沌獸、又把牠降伏、得了那枚渾沌之心，老朽便把這最後兩樁去處，也一併託付了罷。" :),
			(: command, "say 少俠須知：這世間有天、地二靈，分司一方天命與地氣。其一，天靈——盤踞在赤魈村後那一泓終年不涸、天地靈氣所鍾的許願池上。自赤魈村循西邊那道少有人行的小徑(west)下山腳，便至那許願池；少俠持渾沌之心、星光環引動池水，那司一方天命的天靈便會應引而現——降之，必得一柄天命刃(dagger of fate)與一枚天靈之眼。" :),
			(: command, "say 其二，地靈——盤踞在京畿地氣塔的塔頂。古來相傳，須以聖木殘根、金屋內丹煉就炎日箭、太陽槍，循四神之力層層引動，方能登臨那地氣磅礡的塔頂；如今少俠既已降了渾沌獸、嵌齊了星光環，這層層的引動，老朽已替少俠暗中疏通——少俠但自皇城廣場一隅那道深嵌地底的石階下行(down)，至那地氣塔塔基，再循塔心黃石旋梯盤旋而上(up)，便能登臨塔頂。那司一方地氣的地靈應引而現，降之，必得一柄悍地斧(twohanded axe)與一枚地靈之心。" :),
			(: command, "say 天、地二靈俱降、那心、眼俱得，少俠再持回來尋老朽覆命。集齊那心、眼，並這枚四神之力齊備的星光環，便可往京畿神社獻與日月神薛，再戰侮天鬼的終局之路，便在眼前了。二靈凶險不在渾沌獸之下，少俠好自為之。" :),
		}));
		return 1;
	}

	// 門檻未達(尚未了結渾沌獸之患)：時機未到的氣氛鋪墊兼伏筆。
	do_chat(({
		(: command, "say （江隕搖了搖頭，長嘆一聲）少俠也聽說了那分司天命、地氣的『天靈』與『地靈』麼？一在赤魈村那終年不涸的許願池上，一在京畿地氣塔的塔頂，皆是凶險不下於那渾沌獸的厲靈。" :),
		(: command, "say 只是 ... 那是後話了。少俠手裡若無那降了渾沌獸方得的渾沌之心，這天、地二靈之事，老朽便是說了，也是枉然。客官且先去了結那渾沌獸之患、得了渾沌之心，再來尋老朽問這天靈、地靈罷。" :),
	}));
	return 1;
}

// 第八章交差謝禮（同步發放﹐較第七章再加碼——天、地二靈為迄今最末、亦最險之 arc）。本
// 章主獎(天命刃/天靈之眼/悍地斧/地靈之心)皆由二靈逐玩家掉落、玩家自始持有並續持往日月
// 神薛 arc﹐此處乃漕幫的謝禮與江湖歷練﹐不取走任何信物。
private void give_reward8(object who)
{
	object coin, pill;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(12000);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/major_heal_pill");
	if( !pill->move(who) ) pill->move(environment());

	who->gain_score("survive", 12000);
	who->gain_score("emprise", 4000);
	who->gain_score("reputation", 2000);
	who->gain_score("martial fame", 2200);
	who->gain_score("explorer fame", 900);

	message_vision(
		HIY "江隕鄭重自懷中取出一串迄今最為沉甸甸的銅錢、一帖上好的療傷丹藥﹐雙手"
		"交到$N手裡﹔復又顫巍巍地離座而起﹐朝$N深深一揖到地、久久不起——這一揖﹐是"
		"替那困於這三百年因果、終盼得天、地二靈伏誅、終局在望的天下蒼生﹐謝過少俠的。\n"
		NOR, who);
}

// 收物防呆：本支線純 ask-path、不收物（無 give-turn-in）。婉拒玩家遞來的物事、不吞玩家
// 物品（尤不收回那幅四鬼古篆拓信物）。回 0＝give 命令不轉移、物事留在玩家身上。
int accept_object(object who, object ob)
{
	if( ob && ob->id("sigui token") ) {
		do_chat((: command,
			"say 這拓本既拓與了少俠﹐便是少俠問環之功的記認﹐收回去——他日鬼封一鬆﹐少俠憑它來尋老朽便是。" :));
		return 0;
	}
	do_chat((: command,
		"say 老朽一個守舊事的閒人﹐受不起少俠的東西﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say （江隕並不動怒﹐只淡淡看你一眼）客官﹐這是漕幫議事的清淨禮堂﹐動手的事﹐犯不著。老朽一把年紀﹐也奉陪不起。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
