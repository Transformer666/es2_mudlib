// shoushan.c -- 守山道人，京畿神社守木尊者座下的雲遊行者，
//              正史序章「逐念入山」(canon 第一章)的委託人與領賞人
//
// 故事背景（承接前傳主線八「天靈降魔」beat 8 摩雲伏誅）：
//   獸王摩雲——那懾服天靈山百獸、興起這場動物war的獸王總頭目——已伏誅於魔
//   窟(d/tianling/den.c)。然摩雲身死之際﹐周身那團青黑戾氣並未消散﹐反凝
//   成一縷濃黑的邪念﹐穿窟破霧﹐徑往天靈山更深、更幽暗的方向遁去（見
//   moyun.c::die() 之高潮敘事）。京畿神社那位溫養出淨邪聖木牌的守木尊者﹐
//   早料到摩雲不過是受人驅策的爪牙﹐遂遣這位座下的雲遊行者「守山道人」先
//   一步循著地脈上得天靈山﹐守在魔窟之後那道幽壑(youhe.c)裡﹐靜候那持聖物
//   破障、了結摩雲的少俠。摩雲既死﹐道人便將那縷邪念遁去的去向、與更深一
//   層的禍患﹐和盤托出——這便是正史主線自前傳接續而下的序章。
//
// 序章定位（前傳→正史的接縫）：
//   前傳 main_omen 八個 beat 是這場動物war的序幕﹐beat 8(摩雲)是動物war的
//   高潮與第一場決戰。摩雲既為獸王總頭目﹐牠一死﹐那群龍無首、卻仍受邪念
//   驅策的殘部(canon 動物war 群獸：白猴/老虎/魔象/猴王/大鱷/母豬/吞風獅/老
//   龍 之屬)便潰散於天靈山深處的幽壑獸塚之間。守山道人託少俠先掃平這潰散
//   殘部中為首的兩頭孽畜——老龍與吞風獅——再循那縷邪念深入﹐探明那驅策摩雲
//   一脈的至邪之物「混沌珠」今時的下落。
//
// 任務流程（旗標存在玩家身上：quest/main_canon1﹔另以 quest/main_canon1_done 防重領）：
//   入門條件     : 須先完成前傳主線八（quest/main_omen8 >= 3﹐摩雲已伏誅）﹐
//                  且隨身仍攜淨邪聖木牌(holy relic)——深處邪念更熾﹐無聖物護
//                  持近不得﹔不合則只示警、不開任務
//   未開始 (0)   : 玩家 ask shoushan about 混沌珠（亦收 邪念/正史/主線/任務 等）
//                  -> 道人道破摩雲死後邪念遁向深處﹐託少俠掃平殘部為首的老龍
//                  與吞風獅、循邪念探混沌珠下落﹐旗標設為 1
//   進行中 (1)   : 玩家往北深入獸塚﹐擊殺老龍 -> 旗標於 laolong.c::die() 推進為 2
//   進行中 (2)   : 玩家再往北入吞風獅穴﹐擊殺吞風獅 -> 旗標於 windlion.c::die()
//                  推進為 3﹐並自吞風獅屍身掉落「骨符殘片」(混沌珠下落線索)
//   已探明 (3)   : 玩家持骨符殘片回幽壑﹐ask shoushan about 混沌珠 -> 道人參
//                  詳骨符﹐道破混沌珠由天靈山更深處的骨屍妖王把持﹐領賞
//                  (give_reward)﹐並以 quest/main_canon1_done 記已領、防重複
//   已領賞       : main_canon1_done 為真者﹐只給朝向下一章(骨屍妖王/鬼王噬魂)
//                  的純劇情伏筆﹐不再重複給賞﹐亦不開下一章任務
//
// 注意：本 NPC 不主動攻擊、不可結仇（accept_fight 回 0）﹔給賞為同步交付（在
//       do_ask handler 內 give_reward() 直接 new+move﹐且在記 _done 旗標之前）﹐
//       絕不放進延遲的 do_chat closure——免玩家於回呼前離場致賞沒領而卡關。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("守山道人", ({ "shoushan daoist", "mountain warden", "shoushan", "daoist" }) );
	set("nickname", "守山道人");
	set_attr("str", 22);
	set_attr("con", 24);
	set_attr("dex", 22);
	set_attr("int", 26);
	set_attr("wis", 28);
	set_attr("spi", 26);
	set_race("human");
	set_class("commoner");
	set_level(20);
	set_skill("unarmed", 40);
	set_skill("dodge", 45);
	set_skill("force", 50);
	set_skill("literate", 45);

	set("gender", "male");
	set("age", 58);
	set("long",
		"一位身披洗得發白的青布道袍、盤膝坐在幽壑石上的老道人。他\n"
		"鬚眉霜白﹐面容清癯﹐一雙眼睛卻沉靜如古井﹐自有一股閱盡世\n"
		"情的澄明。胸前掛著一面與你那塊一般無二的淨邪聖木牌﹐牌上\n"
		"青芒幽幽流轉﹐在這滿是青黑戾氣的幽壑裡﹐替他撐開一方清明\n"
		"的天地。他是京畿神社那位守木尊者座下的雲遊行者﹐早一步循\n"
		"著地脈上得這天靈山深處﹐守在摩雲魔窟之後﹐靜候那了結了獸\n"
		"王、又循著那縷遁去邪念追下來的少俠。\n"
		"你或許可以問問他﹕ask shoushan about 混沌珠。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"守山道人指尖掐算著甚麼﹐眉頭微蹙﹐喃喃道﹕那縷邪念 ... 果然是往更深處去了。\n",
		"守山道人撫著胸前那面淨邪聖木牌﹐輕嘆一聲﹕摩雲一死﹐這滿山的孽畜倒愈發躁動了。\n",
	}));
	setup();
	carry_object("/obj/area/obj/robe")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_canon1");
		if( this_player()->query("quest/main_canon1_done") )
			return;
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 少俠﹐那兩頭潰散殘部為首的孽畜——老龍與吞風獅——可曾掃平﹖那縷邪念的去向﹐還得從牠們身上尋。" :));
		else if( q >= 3 )
			do_chat((: command,
				"say 少俠回來了﹗那混沌珠的下落﹐可從那骨符上參出甚麼端倪了麼﹖" :));
		else if( !q && this_player()->query("quest/main_omen8") >= 3 )
			do_chat((: command,
				"say 少俠便是了結了獸王摩雲的那位罷﹖貧道在此恭候多時了。" :));
	}
}

// 序章領賞：給銅錢、丹藥、與洗銀劍各一﹐並授存活、俠義之舉、聲望、武名等大筆閱歷。
// 同步交付——於 do_ask handler 內直接呼叫﹐玩家此刻必在場（環境校驗在前）。
private void give_reward(object who)
{
	object coin, pill, sword;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(600);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/major_heal_pill");
	if( !pill->move(who) ) pill->move(environment());

	sword = new("/d/snow/npc/obj/silversword");
	if( !sword->move(who) ) sword->move(environment());

	who->gain_score("survive", 900);
	who->gain_score("emprise", 300);
	who->gain_score("reputation", 150);
	who->gain_score("martial fame", 180);
	who->gain_score("explorer fame", 80);

	message_vision(
		HIY "守山道人將那片骨符就著聖木牌的青芒反覆參詳﹐神色愈發凝重﹐"
		"末了長嘆一聲﹐自袖中取出一串銅錢、一帖丹藥與一柄佩劍﹐鄭重地交"
		"到$N手裡。\n" NOR, who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "shoushan about 混沌珠"
		&&   arg != "shoushan about 邪念"
		&&   arg != "shoushan about 正史"
		&&   arg != "shoushan about 主線"
		&&   arg != "shoushan about 任務"
		&&   arg != "shoushan about 摩雲"
		&&   arg != "shoushan daoist about 混沌珠"
		&&   arg != "shoushan daoist about 邪念"
		&&   arg != "mountain warden about 混沌珠"
		&&   arg != "shoushan about quest"
		&&   arg != "shoushan about task") )
		return notify_fail("你想問這位守山道人甚麼﹖（試試 ask shoushan about 混沌珠）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("守山道人正闔目掐算著甚麼﹐沒空理你。\n");

	// 入門條件一：須先了結獸王摩雲（前傳主線八完成）
	if( me->query("quest/main_omen8") < 3 ) {
		do_chat(({
			(: command, "say 少俠面生﹐周身又無半分降伏獸王的氣象 ... 這天靈山深處的禍事﹐豈是未經摩雲一戰的人所能與聞的。" :),
			(: command, "say 少俠若真有心究這滿山戾氣的根底﹐且先下山去﹐求那制邪的聖物、破那邪障的門道﹐先了結了那頭懾服百獸的獸王摩雲﹐再來尋貧道不遲。" :),
		}));
		return 1;
	}

	// 入門條件二：深處邪念更熾，須隨身攜淨邪聖木牌方護持得心神
	if( !present("holy relic", me) ) {
		do_chat((: command,
			"say 少俠雖已了結摩雲﹐可這幽壑深處的邪念﹐比那魔窟還要熾烈十倍——少俠那面淨邪聖木牌呢﹖無聖物護持心神﹐再往深處去﹐怕是未及交手便要先亂了方寸。且回身將那聖物帶在身邊﹐再來尋貧道。" :));
		return 1;
	}

	q = me->query("quest/main_canon1");

	// 已領過序章之賞：只加深朝向下一章（骨屍妖王/鬼王噬魂/混沌珠）的伏筆，不重複給賞、不開新任務。
	if( me->query("quest/main_canon1_done") ) {
		do_chat(({
			(: command, "say 那片骨符﹐貧道已參詳明白——混沌珠如今正落在天靈山更深處那頭『骨屍妖王』的手裡。那妖王以無數枯骨煉成己身﹐又有『鬼王噬魂』與牠互為表裡﹐層層守著那顆至邪之珠。" :),
			(: command, "say 少俠掃平了摩雲的潰散殘部﹐這場動物war的第一鏈算是斷了。然混沌珠一日不毀﹐那縷邪念便一日有所依憑——往後深入幽冥、奪那混沌珠、會一會骨屍妖王﹐還得靠少俠這身本事。貧道且在這幽壑替少俠守著前路﹐探明了下一程的門道﹐自會相告。" :),
		}));
		return 1;
	}

	// 任務已探明（旗標 >=3）：理應持骨符回來領賞
	if( q >= 3 ) {
		if( present("bone talisman", me) ) {
			// 同步給賞、即記 _done（give_reward 為直接 new+move﹐玩家此刻必在場）。
			// 不把給賞放進延遲 do_chat——免玩家於回呼前離場致賞沒領而卡關。
			give_reward(me);
			me->set("quest/main_canon1_done", 1);
			do_chat(({
				(: command, "say 少俠把那骨符給貧道瞧瞧 ... 嘶﹗這骨符上刻的﹐是『噬魂』一脈的鬼篆﹐其上殘留的這縷陰識﹐分明在指引著一條入幽冥的路。" :),
				(: command, "say 貧道參出來了——那驅策摩雲一脈的至邪之物『混沌珠』﹐如今正落在天靈山更深處『骨屍妖王』的手裡﹐另有『鬼王噬魂』與牠互為表裡。混沌珠的下落﹐總算是有了眉目。" :),
				(: command, "say 這點銅錢丹藥﹐少俠收著防身。少俠了結摩雲、又掃平了牠的殘部﹐功在天下蒼生——只是這追兇之路才剛起頭﹐往後深入幽冥奪那混沌珠﹐還有得拼啊。" :),
			}));
		}
		else
			do_chat((: command,
				"say 少俠不是說那吞風獅屍身裡有片骨符麼﹖那骨符上刻著混沌珠的下落線索﹐快回獸塚北邊的吞風獅穴﹐自牠屍身中尋了來給貧道參詳。" :));
		return 1;
	}

	// 任務進行中（旗標 1 或 2）：提示去向
	if( q == 1 || q == 2 ) {
		do_chat((: command,
			"say 摩雲既為這場獸亂的總頭目﹐牠一死﹐那群龍無首的孽畜便潰散在這幽壑獸塚之間。少俠且往北深入獸塚﹐先除了那為首的老龍﹐再往北的吞風獅穴﹐斬了那頭吞風獅——那縷邪念的去向、混沌珠的線索﹐都得從牠們身上尋。" :));
		return 1;
	}

	// 尚未接序章：道破摩雲死後邪念遁向深處，託少俠掃平殘部、探混沌珠下落，旗標設為 1
	me->set("quest/main_canon1", 1);
	do_chat(({
		(: command, "say 少俠便是持淨邪聖木牌、了結了獸王摩雲的那位了——貧道是京畿神社守木尊者座下的雲遊行者﹐尊者早料到摩雲不過是頭被驅策的爪牙﹐遣貧道先一步上山﹐守在這魔窟之後﹐恭候少俠多時了。" :),
		(: command, "say 少俠可曾留意﹖摩雲氣絕之際﹐周身那團戾氣並未消散﹐反凝成一縷濃黑的邪念﹐穿窟破霧﹐徑往這天靈山更深的幽壑遁去了。那縷邪念﹐分明指向天靈山深處那頭悔天鬼﹐與那顆喚作『混沌珠』的至邪之物——摩雲一脈的兇性﹐皆源出於此。" :),
		(: command, "say 摩雲既為這場動物war的獸王總頭目﹐牠一死﹐那群龍無首、卻仍受邪念驅策的孽畜便潰散在這幽壑獸塚之間。其中為首的兩頭——一頭蟄伏獸塚的老龍﹐一頭盤踞穴中的吞風獅——最是兇悍。少俠且為天下蒼生﹐往北深入獸塚﹐先除了這兩頭孽畜。" :),
		(: command, "say 斬了那兩頭為首的孽畜﹐循著那縷邪念的去向﹐自能探明混沌珠今時的下落。少俠身懷聖物護持心神﹐這一程﹐便交託與少俠了——萬望謹慎﹗" :),
	}));
	return 1;
}

// 序章領賞走 ask-path 為主（ask shoushan about 混沌珠）。玩家若改以 give 交付
// 骨符﹐道人不收下（回 0、骨符留在玩家身上）﹐只提示改用 ask——如此既不吞掉
// 線索信物﹐領賞邏輯亦集中於 do_ask 一處（同步給賞、防重領）﹐免兩處重複。
int accept_object(object who, object ob)
{
	if( ob->id("bone talisman") ) {
		do_chat((: command, "say 這骨符乾係重大﹐少俠且收好﹐口頭問我便是——ask shoushan about 混沌珠﹐貧道自當為少俠參詳。" :));
		return 0;
	}
	do_chat((: command, "say 貧道一個守山的出家人﹐了無長物﹐這個受不起﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠息怒﹗貧道一個守山的出家人﹐與少俠同是為著這天下的禍患而來﹐何苦自相殘殺。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
