// jiangyun.c -- 漕幫禮堂的耆宿「江隕」(uid: jiangyun)。
//
// 【設定 / canon】依 ES2 設定﹐江隕是漕幫在京畿的老前輩、漕幫「四鬼問環」支線的關鍵人﹕
//   他授予玩家「四鬼招喚環」﹐玩家持環往卯天樹下開封、誅赤魈／青蛛／濁魚／旱魃 四鬼。
//   本幫亦以江隕為名義上的創幫者——漕幫禮堂（/d/caobang/hall）於 create() 內即以 uid
//   "jiangyun" 向 CLAN_D 登錄漕幫(register_clan)。
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

#include <npc.h>
#include <ansi.h>

int do_ask(string arg);
private int sigui_quest(object me);
private int sishen_quest(object me);
private void give_ghost_ring(object who);
private void give_reward5(object who);
private void give_reward6(object who);

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
	||  arg == "jiangyun about 星光環"
	||  arg == "jiangyun about 天龍島"
	||  arg == "jiangyun about 火神"
	||  arg == "jiangyun about 天龍"
	||  arg == "jiangyun about 雷神"
	||  arg == "jiangyun about 風神"
	||  arg == "jiangyun about 渾沌獸"
	||  arg == "elder jiangyun about 四神" ) {
		return sishen_quest(this_player());
	}

	return notify_fail("江隕望著東去的河水﹐淡淡道﹕有些事﹐時候未到﹐多問無益。客官且自便罷。（試試 ask jiangyun about 漕幫／四鬼／四神）\n");
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

int accept_fight(object ob)
{
	do_chat((: command, "say （江隕並不動怒﹐只淡淡看你一眼）客官﹐這是漕幫議事的清淨禮堂﹐動手的事﹐犯不著。老朽一把年紀﹐也奉陪不起。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
