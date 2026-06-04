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
private void give_reward2(object who);

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

		// 第一章已領賞者：依第二章「混沌珠」旗標(main_canon2)給對應招呼。
		// 招呼一律走單一 do_chat（is_chatting 期間 do_ask 早退、待招呼畢方應——
		// 鏡第一章 proven 之 is_chatting 把關）。
		if( this_player()->query("quest/main_canon1_done") ) {
			int q2 = this_player()->query("quest/main_canon2");
			if( this_player()->query("quest/main_canon2_done") )
				do_chat((: command,
					"say 少俠回來了。那混沌珠貧道已封鎮妥當——只是天靈絕巔那真兇一日尚在﹐這禍事便一日難了啊。" :));
			else if( q2 >= 3 )
				do_chat((: command,
					"say 少俠把那混沌珠奪回來了麼﹖那至邪之物萬不可久執在身﹐快給貧道瞧瞧——ask shoushan about 混沌珠。" :));
			else if( q2 == 1 || q2 == 2 )
				do_chat((: command,
					"say 少俠﹐那守珠的骨屍妖王與鬼王噬魂——這一身一魂的兩大守護﹐可曾破了﹖混沌珠的下落﹐就在那幽冥噬魂窟裡。" :));
			else
				do_chat((: command,
					"say 少俠來得正好——那混沌珠的下落﹐貧道已自骨符上參得透徹了。少俠可要聽貧道細說﹖ask shoushan about 混沌珠。" :));
			return;
		}

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

// 第二章「混沌珠」領賞：第二章遠較序章兇險(下幽冥、破萬骨煉身之妖王與司魂之鬼
// 王)﹐故賞較序章更厚——銅錢 1000(序章 600)、金液丹一帖(序章為次一級的續命金丹)、
// 繞指柔劍一柄(unique 名劍﹐勝序章洗銀劍)﹐並授遠厚於序章的聲望/內丹(score)等閱
// 歷(reputation/emprise/survive/martial fame 皆顯著加碼)。同步交付——於 do_ask
// handler 內直接呼叫﹐玩家此刻必在場（環境校驗在前）。神兵頂裝仍由兩 boss 各以
// 機率掉落﹐此處不重複發頂裝(免架空 boss 掉落、破壞平衡)。
private void give_reward2(object who)
{
	object coin, pill, sword;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(1000);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/aquapill");
	if( !pill->move(who) ) pill->move(environment());

	sword = new("/d/snow/npc/obj/slasher_sword");
	if( !sword->move(who) ) sword->move(environment());

	// 聲望/內丹(score) boost：較序章 give_reward 顯著加碼（第二章難度更高）。
	who->gain_score("survive", 1800);
	who->gain_score("emprise", 600);
	who->gain_score("reputation", 350);
	who->gain_score("martial fame", 360);
	who->gain_score("explorer fame", 150);

	message_vision(
		HIY "守山道人將那顆翻滾著人面鬼影的混沌珠以聖木牌青芒重重裹住、"
		"收入袖中﹐神色凝重而欣慰。他長舒一口氣﹐自懷中取出一串沉甸甸的"
		"銅錢、一帖金液丹、並一柄劍刃微顫的名劍『繞指柔劍』﹐鄭重地交到"
		"$N手裡——又以指尖在$N眉心一點﹐傳了一縷溫養精氣的內丹真意。\n" NOR, who);
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
		&&   arg != "shoushan about 幽冥"
		&&   arg != "shoushan about 骨屍妖王"
		&&   arg != "shoushan about 鬼王噬魂"
		&&   arg != "shoushan daoist about 混沌珠"
		&&   arg != "shoushan daoist about 邪念"
		&&   arg != "shoushan daoist about 幽冥"
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

	// ============================================================
	// 正史第二章「混沌珠」：第一章領賞(main_canon1_done)後，本 NPC 即由序章領賞人
	// 轉為第二章的委託人與領賞人。第二章旗標 quest/main_canon2 (0→1→2→3) + 防重
	// 領旗標 quest/main_canon2_done。流程鏡第一章之 proven 機制：
	//   0          : 接任務 -> 道破混沌珠落於幽冥骨屍妖王手中、命少俠下幽冥奪珠，
	//                 旗標設為 1（並開 abyss.c 淵下骨階之門禁）
	//   1          : 已下幽冥，命破骨殿骨屍妖王 -> 由 skeleton_king.c::die() 推進為 2
	//   2          : 命再破噬魂窟鬼王噬魂 -> 由 soul_devourer.c::die() 推進為 3，
	//                 並自鬼王噬魂屍身掉落混沌珠
	//   3          : 持混沌珠回幽壑領賞 -> 同步交付 give_reward2()、記 main_canon2_done
	//   _done      : 只給朝向下一章(天靈絕巔真兇)的 oblique 伏筆，不重複給賞、不開新任務
	// 入門條件沿用上方序章兩道閘（main_omen8>=3、隨身淨邪聖木牌）——幽冥邪念尤熾，
	// 無聖物護持斷不可深入，與第一章一脈相承。
	// ============================================================
	if( me->query("quest/main_canon1_done") ) {
		int q2 = me->query("quest/main_canon2");

		// 已領過第二章之賞：只加深朝向下一章（天靈絕巔的真兇/動物war 終 boss）的
		// oblique 伏筆，不重複給賞、不開新任務。
		// LORE-FLAG: 此「天靈絕巔的真兇」即 docs 主線樹「天靈山悔天鬼/動物war 終
		//   boss」﹐然 docs 另有「侮天鬼(最終 boss)」「侮藥王鬼(混沌珠 group)」三個
		//   形近名諱﹐究係 1/2/3 個角色 identity 未明﹐待 user 裁定。故此處一概
		//   obliquely 指代﹐「不」落悔天鬼/侮天鬼/侮藥王鬼任一確切名諱。
		if( me->query("quest/main_canon2_done") ) {
			do_chat(({
				(: command, "say 混沌珠既已交在貧道手裡﹐這聚天下戾氣為一的至邪之物﹐貧道自會借京畿神社聖木餘力﹐尋一處清淨地將它封鎮起來——少俠了結了骨屍妖王與鬼王噬魂這守珠的一身一魂﹐已是大功一件了。" :),
				(: command, "say 只是 ... 那珠上殘留的氣息﹐與噬魂窟鬼壁所刻的鬼篆﹐都隱隱指向同一處——天靈山那雲遮霧繞的絕巔之上﹐分明還盤踞著一個驅策這一切的真兇。摩雲也好、骨屍妖王也罷﹐皆不過是牠手中的爪牙。那真兇的名諱﹐古籍語焉不詳、眾說紛紜﹐貧道一時也不敢妄斷。" :),
				(: command, "say 珠雖奪了﹐那盤踞天靈絕巔的真兇一日尚在﹐這天靈山的禍事便一日難言真個了結。少俠且先歇息將養﹐探明了上絕巔的門道、辨明了那真兇的來歷﹐貧道自會再來相告——這最後一程﹐怕才是真正的兇險。" :),
			}));
			return 1;
		}

		// 第二章已奪珠（旗標 3）：理應持混沌珠回來領賞
		if( q2 >= 3 ) {
			if( present("chaos pearl", me) ) {
				// 同步給賞、即記 _done（give_reward2 為直接 new+move﹐玩家此刻必在場）。
				// 不把給賞放進延遲 do_chat——免玩家於回呼前離場致賞沒領而卡關
				// （此乃第一章習得之教訓：延遲領賞會 soft-lock）。
				give_reward2(me);
				me->set("quest/main_canon2_done", 1);
				do_chat(({
					(: command, "say 少俠把那珠子給貧道 ... 唔﹗好一股徹骨的至邪之氣﹗這便是那『聚天下戾氣為一、至邪不祥』的混沌珠了——骨屍妖王與鬼王噬魂這守珠的一身一魂﹐少俠竟都破了﹐當真是天大的功德﹗" :),
					(: command, "say 這至邪之物﹐斷不可久執在凡人身上﹐貧道這便借京畿神社聖木餘力﹐將它封鎮起來。少俠深入幽冥、奪此邪珠﹐斷了那縷牽動滿山獸亂的邪念所依——這份功勞﹐貧道必稟明守木尊者﹐記在少俠名下。" :),
					(: command, "say 這一爐內丹、這帖丹藥、並這件護身之物﹐是貧道與尊者的一點心意﹐少俠萬莫推辭。只是 ... 珠雖奪了﹐那盤踞天靈絕巔、驅策這一切的真兇一日尚在﹐這禍事便一日未了。少俠且養精蓄銳﹐這最後一程﹐怕才是真正的硬仗。" :),
				}));
			}
			else
				do_chat((: command,
					"say 少俠不是說那鬼王噬魂的屍身裡墜下了混沌珠麼﹖那珠子至邪不祥﹐萬不可遺落在那幽冥之地——快回噬魂窟﹐自鬼王噬魂屍身中尋了那混沌珠來給貧道。" :));
			return 1;
		}

		// 第二章進行中（旗標 1 或 2）：提示去向
		if( q2 == 1 || q2 == 2 ) {
			do_chat((: command,
				"say 那混沌珠由骨屍妖王以萬骨煉身鎮其形、鬼王噬魂司魂魄佐其守﹐一身一魂、互為表裡。少俠且循那邪念淵下的骨階深入幽冥﹐先破了骨殿那以萬骨煉身的骨屍妖王﹐萬骨之鎖一開﹐再往北深入噬魂窟﹐斬了那司魂的鬼王噬魂——守珠的兩大守護盡除﹐那混沌珠方能到手。" :));
			return 1;
		}

		// 尚未接第二章（旗標 0）：道破混沌珠落於幽冥骨屍妖王手中，命少俠下幽冥奪珠，旗標設為 1
		me->set("quest/main_canon2", 1);
		do_chat(({
			(: command, "say 少俠來得正好﹗那片骨符﹐貧道已參詳得透徹——那驅策摩雲一脈的至邪之物『混沌珠』﹐如今正落在天靈山更深處幽冥之中﹐由一頭喚作『骨屍妖王』的邪物把持。牠以這滿山潰散的孽畜、與歷代葬身此山的枯骨煉成己身﹐萬骨為甲、千骸為軀﹐尋常刀兵難入其身。" :),
			(: command, "say 那骨屍妖王並非孤身守珠——另有一縷亙古的厲鬼『鬼王噬魂』與牠互為表裡﹕骨屍妖王煉其『身』、鬼王噬魂司其『魂』﹐一身一魂、共鎮那顆混沌珠於幽冥噬魂窟。混沌珠一日不毀﹐那縷牽動滿山獸亂的邪念便一日有所依憑——這顆至邪之珠﹐非奪回、毀去不可。" :),
			(: command, "say 貧道在這幽壑守候多時﹐已替少俠在那邪念淵下尋出了一道入幽冥的骨階。少俠且循那骨階深入幽冥——先過骨殿﹐破了那以萬骨煉身的骨屍妖王﹔再入噬魂窟﹐斬了那司魂的鬼王噬魂。守珠的一身一魂盡除﹐那混沌珠便可奪回。" :),
			(: command, "say 切記﹕幽冥深處的邪念﹐比這幽壑還要陰寒熾烈十倍﹐少俠那面淨邪聖木牌﹐萬萬不可離身﹗奪得了混沌珠﹐速速回這幽壑來尋貧道——此去兇險萬端﹐萬望珍重﹗" :),
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

// 領賞(序章與第二章)俱走 ask-path 為主（ask shoushan about 混沌珠）。玩家若改以
// give 交付骨符/混沌珠﹐道人皆不收下（回 0、信物留在玩家身上）﹐只提示改用 ask——
// 如此既不吞掉信物﹐領賞邏輯亦集中於 do_ask 一處（同步給賞、防重領）﹐免兩處重複。
int accept_object(object who, object ob)
{
	if( ob->id("bone talisman") ) {
		do_chat((: command, "say 這骨符乾係重大﹐少俠且收好﹐口頭問我便是——ask shoushan about 混沌珠﹐貧道自當為少俠參詳。" :));
		return 0;
	}
	if( ob->id("chaos pearl") ) {
		do_chat((: command, "say 這混沌珠至邪不祥﹐少俠且先收好、莫遞來遞去——口頭與我說一聲便是﹕ask shoushan about 混沌珠﹐貧道自當為少俠定奪這至邪之物的處置。" :));
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
