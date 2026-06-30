// child.c

// 「阿寶的心願」(quest/snow_abao) 情感向支線——阿寶端：
//   瞎眼老太婆把貼身的青布手帕(abao_keepsake)託玩家帶上樹給阿寶（婆婆端見
//   d/snow/npc/gammer.c）。玩家 ask arbao about 婆婆 傾聽阿寶痴等爺爺的心事、
//   傳達婆婆「不尋仇、盼她回家」的話，再把手帕(give)交給阿寶，阿寶這才肯接受
//   爺爺已逝、願意下樹回家，支線收束（給聲望/見聞）。
//
//   設計守則：docs 只給「阿寶在榕樹上等誰」之疑團、未給解答，故做成情感向、
//   可完成的傳話支線（傳話＋信物＋旗標＋小獎勵），【不】把「殺柳東蘆復仇」硬綁
//   入本支線（柳東蘆是 d/fonxan boss，玩家去殺與否與本支線無涉，僅對白呼應）。
//   本支線 quest/snow_abao 旗標、ask-path 與信物 id 皆獨立，與既有 try/fon
//   封山入派鏈互不相干，不污染舊鏈、不動 hungry/try_fon 狀態。
//
//   鐵則遵循：#10 本檔信物收尾／設旗標／給賞逕在 accept_object handler 內
//   順序寫就，【不】destruct 阿寶（舊 try/fon 鏈仍倚賴她在場）；#11 本檔為
//   NPC（非房間）不涉 replace_program；#14 do_ask 開頭已守衛 is_fighting()/
//   is_chatting()，且本支線 accept_object 分支不夾延遲交付閉包。

#include <npc.h>

inherit F_VILLAGER;

void timeto_eat();
int do_ask(string arg);     // 主線伏筆 lore：侮天鬼/十三靈/三百年災變(純劇情，不給物)

void create()
{
	set_name("阿寶", ({ "arbao", "__ID_ARBAO__" }) );
	set_attr("spi", 18);
	set_attr("int", 19);
	set_attr("dex", 19);
	set_attr("con", 17);
	set_race("human");
	set_class("commoner");
	set_level(10);

	set_skill("stealing", 40);
	set_skill("dodge", 35);
	set_skill("lightswift", 45);
	set_skill("dagger", 40);
	set_skill("sword", 30);
	
	map_skill("dodge", "lightswift");

	set("age", 16);
	set("gender", "female");
	set("long",
		"這個十五、六歲的小姑娘就是「阿寶」了﹐她身上雖然穿著粗布\n"
		"衣服﹐但卻十足是個美人胚子﹐一雙水汪汪的大眼睛骨碌碌地轉\n"
		"著﹐還不時盯著你看﹐使你不禁覺得有些發窘。\n");

	// set arbao to consume food -dragoon
	set("schedule", ([
	    700: (: timeto_eat :),
	    1200: (: timeto_eat :),
	    1900: (: timeto_eat :),
	]));

	setup();
	carry_money("coin", 30);
	carry_object(__DIR__"obj/blue_cloth")->wear();
	carry_object("/obj/area/obj/dagger")->wield();
}

int hungry = 1;

void timeto_eat()
{
	this_object()->consume_stat("food", 
	    this_object()->query_stat("food")+1);
	return;
}

void init()
{
	::init();
	add_action("do_ask", "ask");        // 主線伏筆 lore；務必在下方早退之前註冊
	if( is_fighting() || is_chatting() ) return;
	
	if( this_player()->query_temp("try/fon")==10 ){
		do_chat("阿寶開心的向你搖搖手, 急問道: 見到柳大哥了嗎 ? 他好不好?\n");
		//this_player()->set_temp("try/fon",13);
	}

	// if trying fon, wont join thief
	if( this_player()->query_temp("try/fon") )
		return;

	if( hungry )
		do_chat((: command, "say 喂 ... 我肚子好餓﹐有沒有吃的﹖" :));
	else if( this_player()->query_class() == "thief" ) {
		do_chat(({
			"阿寶望著你，忽然說道：咦？你不是上次給我東西吃的那位 ...\n",
			"阿寶微笑說道：又在這裡遇到你，真巧。\n"
		}));
	}
	else
		do_chat((: command, "say 噓 ... 別讓婆婆知道我在這裡 ..." :));
}

// 把紅木梳子交到玩家手上（先複製到自己身上，再 give 出去）。
// 回傳 1 表示梳子確實落在玩家身上，0 表示沒交成（玩家離場/負荷過重）。
// 採同步交付（直接呼叫，非延遲 do_chat）——梳子是入盜賊一行的唯一鑰匙，
// 若放進延遲回呼又逢玩家於梳子交出前離場，便會「hungry 已清、梳子沒給、
// 玩家再也餵不了食物討不到梳子」而永久卡死（與 keeper/boatman 一致的修法）。
private int give_comb(object player)
{
	object comb;

	if( !player || environment(player)!=environment() ) {
		command("say 咦 ... 人呢﹖");
		return 0;
	}
	comb = new(__DIR__"obj/comb");
	comb->move(this_object());
	command("give comb to " + player->query("id"));
	// 確認梳子真的到了玩家身上（give 失敗則梳子仍在阿寶身上，視為沒交成）
	return present("annatto comb", player) ? 1 : 0;
}

// 吃下玩家給的食物（純氣氛＋扣食量）。梳子的交付不在此處，改由 accept_object
// 同步處理，確保交不成時不會把 hungry 清掉。
private void eat_food(string food_name, object player)
{
	set_stat_current("food", 0);
	command("eat " + food_name);
	if( !player || environment(player) != environment() ) return;

	command("say 對了 ... 不該白吃你的東西﹐這個送給你吧﹗");
}

private void do_follow(object me,object ob)
{
	if( !ob->move(me) )	ob->move(environment(me));
	message_vision("阿寶把一件物品遞給了$N.\n",me);
	command("follow "+me->query("id"));
	me->set_temp("try/fon",43);
}

// 「阿寶的心願」支線給賞：一點市井聲望、一點行旅見聞——情感向小獎勵，
//   不臆造大件戰利品，呼應 keeper/biaotou 之 gain_score 範式。
private void abao_reward(object who)
{
	if( !who || environment(who) != environment() ) return;
	who->gain_score("reputation", 15);
	who->gain_score("explorer fame", 20);
}

int accept_object(object me, object ob)
{
	// ── 「阿寶的心願」支線：玩家把婆婆的青布手帕(give)交給阿寶 ──────────
	//   置於 accept_object 最前，獨立於下方 try/fon 鏈，互不干擾。
	if( ob->id("abao keepsake") ) {
		// 非進行中本支線的玩家（沒接過、或已完成）：仍收下避免手帕卡在玩家身上，
		//   但不重複給賞、不重複推進旗標。
		if( me->query("quest/snow_abao") != 1 ) {
			do_chat((: command, "say 這手帕 ... 是婆婆的呀。多謝你了。" :));
			return 1;
		}

		// 進行中（旗標 1）：阿寶認出手帕，情感收束。
		//   同步給賞、即記旗標（abao_reward 直接 gain_score，玩家此刻必在場），
		//   不把給賞放進延遲 do_chat——免玩家於回呼前離場致賞沒領、旗標卻記完成。
		abao_reward(me);
		me->set("quest/snow_abao", 2);
		do_chat(({
			"阿寶接過那方青布手帕﹐指尖撫過角上那個歪歪扭扭的「寶」字﹐怔怔地出了神。\n",
			(: command, "say 這 ... 這是奶奶替我縫的手帕呀 ... 她、她怎麼把這個給了你 ...？" :),
			"你把婆婆的話一五一十地說與阿寶聽——婆婆不再尋仇了﹐只盼她下樹回家。\n",
			(: command, "say 奶奶說 ... 爺爺他 ... 真的回不來了麼 ...？" :),
			"阿寶抱著那方手帕﹐眼淚一顆顆滾落下來﹐哭了好一陣子。\n",
			(: command, "say 我都曉得的 ... 我只是 ... 只是不肯信罷了。爺爺最疼我﹐他答應過要回來教我輕功的 ..." :),
			(: command, "say 你說得對 ... 奶奶一個人在底下﹐才是真孤單。我這就 ... 這就下樹去陪她。多謝你﹐多謝你替奶奶傳話。" :),
			(: command, "smile" :),
		}));
		return 1;
	}

	if(me->query_temp("try/fon")!=40){
		if( !hungry || !inherits(F_FOOD, ob) ) {
			do_chat((: command, "say 給我這個幹嘛﹖" :));
			return 0;
		}

		command("smile");
		command("say 啊 .. 太好了﹗真謝謝你﹗ ...");
		// 同步吃下食物並當場把梳子交給玩家（玩家此刻正在給食，必在場）。
		// 只有梳子確實交出後，才清掉 hungry——否則保留 hungry 讓玩家能再餵
		// 食物重試討梳子，杜絕「梳子沒到手卻再也討不到」的軟鎖。
		eat_food(ob->query("id"), me);
		if( give_comb(me) )
			hungry = 0;
		// do_chat 僅作收尾氣氛對白，不再夾帶交付梳子的閉包。
		do_chat((: command, "say 噓 ... 別讓婆婆知道我在這裡 ..." :));
		return 1;
	}
	if(ob->id("__ID_CHALLIE__")){
		do_chat(({
			"阿寶仔細看了看破布.\n",
			"阿寶說道: 這....嗚..我就知道跟柳家無關..嗚...爺爺..\n",
			"阿寶傷心的哭了起來.\n",
			"阿寶哭了好一陣子, 才又對你說道: 謝謝你, 我們這就去見奶奶吧.\n",
			(: do_follow,me,ob :),
		}));
		hungry=0;		// stop talking about another quest by init
		return 1;
	}
}

void relay_say(object ob,string msg)
{
	int tmp = ob->query_temp("try/fon");

	// communicate with gammer
	if( !userp(ob) ){
		if( ob->id("__ID_GAMMER__") ){
			if( strsrch(msg,"不會再去找他尋仇")>= 0 ) {
				do_chat(
(:command("say 真的! 那太好了!"):));
				return;
			}
			if( strsrch(msg,"喜歡上柳淳風")>= 0 ) {
				do_chat(({
"阿寶臉紅了一下.\n",
(:command("say 是."):),
				}));
				return;
			}
			if( strsrch(msg,"幫你爺爺報了仇")>= 0 ) {
				all_inventory(environment())->set_fon_temp(this_player());
				call_out((:do_chat(
"阿寶說道: 奶奶心情不好, 我要去陪陪她, 請你幫忙我去告訴柳大哥這個好消息, 
多謝你了.\n"):),4);
				call_out((:do_chat(
"阿寶說完, 也急急忙忙追著瞎眼老太婆離去.\n"):),5);
				call_out((:destruct(this_object()):),8);
			}
		}
		return;
	}
	// communicate with user
	switch(tmp){
		case 0:
		case 1:
			if( (strsrch(msg, "柳大哥今年中秋會回來") >= 0) ) {
				do_chat(({
"阿寶臉一紅﹐說道：你 .. 你說的是封山派的柳淳風柳大哥嗎﹖\n",
"阿寶說道：這可糟了﹐他這時候回來﹐婆婆定要殺了他的 ... 怎麼辦呢﹖\n",
"阿寶說道: 這位"+ob->rank("respectful")+"可否幫小女子一個忙?\n",
				}));
				ob->set_temp("try/fon",3);
			}
			break;
		case 3:
			if( strsrch(msg,"可")>=0 || strsrch(msg,"好")>=0 ){
				do_chat(({
"阿寶道: 如果你能遇上柳大哥的話, 請你告訴他暫時還是別來雪亭鎮, 不然, 要是他
和婆婆起了衝突,我會很為難的.還有.....\n",
"阿寶紅著臉, 囁聲道: ...請你告訴他阿寶很想他....\n",
				}));
				ob->set_temp("try/fon",5);
			}
			break;
		case 10:
			if( strsrch(msg,"見到")>=0 || strsrch(msg,"好")>=0 ) {
				do_chat(
"阿寶臉上泛起陣陣紅暈, 喃喃唸著柳大哥, 而後問道: 路上有甚麼問題嗎?\n"
				);
				ob->set_temp("try/fon",13);
			}
			break;
		case 13:
			if( strsrch(msg,"死鬼")>=0 ) {
				do_chat(({
"阿寶道: 喔, 柳大哥跟你提了這件事喔, 奶奶最討厭了, 怎麼都講不聽, 人家都不要
理她了.\n",
"阿寶道: 我爺爺叫趙丰, 江湖上的好友稱他丰爺, 一身輕功 <冷燕飄> 絕步江湖, 奶
奶雖然叫他死鬼, 可是他倆感情很好, 大家都知道呢.\n",
"阿寶突然眼睛紅了起來, 道: 可是三年多前爺爺不知被誰暗算, 死在天邪國外郊...\n",
"阿寶接著道: 人家不知道了, 嗚..  柳大哥年紀比較大, 一定記得我爺爺趙丰的事.\n",
				}));
				ob->set_temp("try/fon",15);
			}
			break;
		default:	break;
	}
}

void set_fon_temp(object me)
{
	if( me->query_temp("try/fon")!=48 )	return;
	me->set_temp("try/fon",50);
}

// 主線伏筆 lore(純劇情，不給物)：阿寶是個耳朵尖的市井小姑娘，平日蹲在老榕樹上，
//   聽過往的客商、說書的、還有她那瞎眼婆婆嘴裡漏出的種種怪談——侮天鬼破封、
//   十三靈護世、三百年前那場災變。她說得半懂不懂，卻替主線埋下一串伏筆。
//   採 do_ask(ask arbao about <topic>)，與既有 relay_say(try/fon 任務鏈)互不相干。
//   handler 守衛 is_fighting()/is_chatting()，不擾既有對話動畫。
int do_ask(string arg)
{
	if( !arg ) return notify_fail("你想問阿寶甚麼？(試試 ask arbao about 侮天鬼)\n");
	if( is_fighting() || is_chatting() )
		return notify_fail("阿寶正忙著，沒空理你。\n");

	if( arg == "arbao about 侮天鬼" || arg == "arbao about 鬼"
	 || arg == "arbao about wutiangui" ) {
		do_chat(({
			(: command, "say 噓——你怎麼也問這個？說書的先生講過，三百年前皇城裡有一株頂頂老的聖木被人砍斷了，封在地底下的「侮天鬼」就那麼鑽了出來 ..." :),
			(: command, "say 阿寶我聽了直起雞皮疙瘩呢！聽說那惡鬼把咱們人當成 ... 當成吃食的！壞人裡頭最壞的那個，背後說不定就是牠 ..." :),
		}));
		return 1;
	}
	if( arg == "arbao about 十三靈" || arg == "arbao about 靈"
	 || arg == "arbao about shisanling" ) {
		do_chat(({
			(: command, "say 十三靈呀？婆婆喝多了會念叨——好久好久以前，有位大英雄砍了那惡鬼的頭，天上就生出十三位靈來，把人間的髒東西都掃乾淨了，這才有了如今的好山好水。" :),
			(: command, "say 婆婆說那十三靈百年就要重生一回呢 ... 阿寶聽不大懂，只覺得這故事怪嚇人的。" :),
		}));
		return 1;
	}
	if( arg == "arbao about 災變" || arg == "arbao about 三百年"
	 || arg == "arbao about 大火" || arg == "arbao about 災難" ) {
		do_chat(({
			(: command, "say 三百年前那場大災變？嗯 ... 客商們閒磕牙說，就是打那聖木斷了、惡鬼出世起，這天朝便一年不如一年，江湖上也愈發不太平了。" :),
			(: command, "say 連咱們雪亭鎮西頭那座鬧鬼的破宅子，聽說也是好些年前一把無名大火燒的 ... 阿寶我才不敢晚上往那邊去呢！" :),
		}));
		return 1;
	}

	// ── 「阿寶的心願」情感支線 ask-path ──────────────────────────────
	// 問婆婆／心願／爺爺／回家：傾聽阿寶痴等爺爺的心事，並由玩家代婆婆傳話。
	//   此為「傳話」一步——傾聽＋對白，真正的收束在玩家 give 手帕(accept_object)。
	if( arg == "arbao about 婆婆" || arg == "arbao about 奶奶"
	 || arg == "arbao about 心願" || arg == "arbao about 爺爺"
	 || arg == "arbao about 趙丰" || arg == "arbao about 回家"
	 || arg == "arbao about granny" ) {
		object me = this_player();
		int q;

		if( !me || !interactive(me) )
			return notify_fail("這裡沒人問你的話。\n");
		q = me->query("quest/snow_abao");

		// 已圓滿（旗標 2）：阿寶已釋懷
		if( q >= 2 ) {
			do_chat((: command,
				"say 奶奶的手帕我收好了。等會兒我便下樹去陪她——這些日子﹐倒是我不懂事﹐讓她一個人擔著心。多謝你呀。" :));
			return 1;
		}

		// 進行中（旗標 1）：傾聽心事，催玩家把手帕交給她
		if( q == 1 ) {
			if( present("abao keepsake", me) )
				do_chat(({
					(: command, "say 你說 ... 奶奶託你帶了話給我﹖" :),
					"阿寶望著你手上那方青布手帕﹐眼神一下子怔住了。\n",
					(: command, "say 那 ... 那手帕 ...你快把它(give)交給我瞧瞧 ... 那真是奶奶的麼 ...？" :),
				}));
			else
				do_chat(({
					(: command, "say 奶奶要你帶話給我﹖她 ... 她還好麼﹖" :),
					(: command, "say 你說奶奶給了你一方手帕﹖怎麼沒見著呀﹖你可別是哄我的 ...（ask gammer about 信物 向婆婆討回那方手帕罷）" :),
				}));
			return 1;
		}

		// q==0：尚未自婆婆處接下此心願——阿寶只痴痴吐露等爺爺的心事，
		//   指引玩家先去問廣場上的瞎眼老太婆（她的奶奶）。
		do_chat(({
			(: command, "say 我在等我爺爺呀。爺爺說過要回來教我輕功的﹐他答應過的﹐他一定會回來 ..." :),
			"阿寶說著﹐眼圈忽地紅了﹐卻又倔強地仰起臉。\n",
			(: command, "say 你 ... 你若是見著我奶奶﹐廣場上那個瞎眼的老婆婆﹐替我問問她﹐爺爺到底甚麼時候回來呀﹖（ask gammer about 阿寶）" :),
		}));
		return 1;
	}

	return notify_fail("阿寶眨眨眼：這個阿寶可不曉得 ... 你問問侮天鬼、十三靈、三百年前那場災變，或是 ... 婆婆的事？\n");
}

// vim: set ts=4 sw=4 syntax=lpc
