// heipao.c -- 黑袍怪人：亙古守在地獄地氣塔頂的形蹤詭秘之人。
//             docs 支線「塔頂贈寶」的贈物人——將其看守的兩件上古奇珍（封神寶鏡、
//             離玄光熾）一併相贈能登臨地氣絕頂、心志不撼的少俠。
//             (canon：docs 01-世界觀與劇情/05 L122「黑袍怪人 @ 地獄地氣塔頂 →
//             封神寶鏡 + 離玄光熾」)
//
// 故事背景：
//   京畿地脈所鍾、地氣磅礡之處那座上古地氣塔的塔頂，除卻那司一方地氣的地靈，尚有
//   一道形蹤詭秘的黑袍怪人，亙古守在這地氣最盛之巔。怪人通體罩在一襲洗得發舊的玄
//   黑袍中，不見面目，亦不言來歷，只道自己看守著上古封神一役所遺的兩件奇珍——一面
//   封神寶鏡、一道離玄光熾，靜候一位心志能不為塔頂磅礡地氣所撼的有緣人。他見少俠
//   能登臨這地氣絕頂，便將這兩件相生相濟的奇珍一併相贈，了一段塔頂之緣。
//
// 支線流程（旗標存玩家身上：quest/sq_heipao）：
//   未領 (0)  : 玩家 ask heipao about 寶（或 封神寶鏡/光熾/奇珍/heipao about treasure …）
//               -> 怪人一句 ask 即將「封神寶鏡」與「離玄光熾」兩件奇珍『一併』同步交付、
//               即記旗標為 1（UNGATED 單問雙贈：任何 docs 條件只作對白風味，wizard 一步可測）。
//   已領 (1)  : 不再重複贈寶（防重領）；ask 只給一段純劇情對白。
//   穩健性    : 若旗標已記為 1 但某件奇珍不在玩家身上（中途遺失/賣掉），逐件同步補贈、
//               不重置進度（step-flag 在、物不在則補；鏡在身則不重發）。
//
// 同步交付（本專案頭號 bug class 之防範）：贈寶一律在 do_ask handler 內直接 new()+move()
//   給玩家、且在設完成旗標之前——絕不放進延遲的 do_chat/closure（玩家中途離場會「物沒了、
//   旗標卻記完成」soft-lock）。do_chat 只擺氣氛對白。
//
// 注意：本 NPC 有 do_ask，**不** replace_program。is_chatting/is_fighting guard 於 do_ask。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIK "黑袍怪人" NOR,
		({ "heipao", "black robe", "stranger", "黑袍怪人", "黑袍" }) );
	set("nickname", HIK "黑袍怪人" NOR);
	set_attr("int", 25);
	set_attr("wis", 30);
	set_attr("con", 28);
	set_race("human");
	set_class("commoner");
	set_level(25);
	set_skill("unarmed", 40);
	set_skill("dodge", 40);
	set_skill("force", 50);
	set_skill("literate", 40);

	set("gender", "male");
	set("age", 0);
	set("long",
		"一道形蹤詭秘的人影，亙古守在這地氣最盛的塔頂。他通體罩在一\n"
		"襲洗得發舊、卻不染塵土的玄黑長袍裡，袍角無風自動，連面目都隱\n"
		"在那一片化不開的暗影之下，教人看不真切。他既不似那盤踞臺心的\n"
		"地靈應地氣而生，也不似尋常登塔的客旅——只是靜靜地立在這磅礡地\n"
		"氣的絕頂，彷彿與這座上古地氣塔一同矗立了亙古的歲月。他周身透\n"
		"著一股說不出的幽冷與沉寂，懷中似護著甚麼亙古的奇珍，靜候著一\n"
		"位心志不為這塔頂地氣所撼的有緣人。\n"
		"你或許可以問問他：ask heipao about 寶。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"黑袍怪人靜立於磅礡地氣之中，玄黑的袍角無風自動，似在掂量你的心志。\n",
		"黑袍怪人幽幽道：能登臨這地氣絕頂而心志不撼者，亙古以來，也沒有幾個。\n",
		"黑袍怪人望著臺心那將凝未凝的黃濛土光，沉聲道：我所守的兩件奇珍，本是一對……\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !this_player()->query("quest/sq_heipao") )
			do_chat((: command,
				"say 你竟能登臨這地氣絕頂、心志不為這磅礡地氣所撼……有意思。我看守的兩件奇珍，或許正等著你來。(ask heipao about 寶)" :));
	}
}

// 同步贈寶：一句 ask 直接 new()+move() 將「封神寶鏡」「離玄光熾」兩件一併給玩家。
// 逐件先試 move 到玩家身上，不成（負重等）則落在環境地上——絕不靜默丟失。
// 已在身者不重發（補贈時亦走此函式，故逐件 present()-check）。
private void give_treasures(object who)
{
	object ob;

	if( !who || environment(who) != environment() ) return;

	if( !present("fengshen mirror", who) ) {
		ob = new("/d/dipa/npc/obj/fengshen_mirror");
		if( !ob->move(who) ) ob->move(environment());
	}
	if( !present("lixuan radiance", who) ) {
		ob = new("/d/dipa/npc/obj/lixuan_radiance");
		if( !ob->move(who) ) ob->move(environment());
	}

	message_vision(
		HIK "黑袍怪人自玄黑的袍中取出一面青冥流光的封神寶鏡、一道赤金燃焰的離玄光熾，"
		"鏡光與火芒交映，一陰一陽。他將這兩件相生相濟的上古奇珍鄭重交到$N手中，"
		"袍角一拂，沉聲道：去罷。\n" NOR,
		who);

	who->gain_score("emprise", 200);
	who->gain_score("reputation", 100);
	who->gain_score("explorer fame", 80);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "heipao about 寶"
		&&   arg != "heipao about 寶鏡"
		&&   arg != "heipao about 封神寶鏡"
		&&   arg != "heipao about 光熾"
		&&   arg != "heipao about 離玄光熾"
		&&   arg != "heipao about 奇珍"
		&&   arg != "heipao about 黑袍"
		&&   arg != "black robe about 寶"
		&&   arg != "stranger about 寶"
		&&   arg != "heipao about treasure"
		&&   arg != "heipao about mirror"
		&&   arg != "heipao about radiance"
		&&   arg != "heipao about light") )
		return notify_fail("你想問這位黑袍怪人甚麼？（試試 ask heipao about 寶）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("黑袍怪人靜立於磅礡地氣之中，恍若未聞，沒空理你。\n");

	q = me->query("quest/sq_heipao");

	// 已領過兩寶：純劇情對白，不重發（防重領）。
	if( q >= 1 ) {
		// 穩健性：旗標在、某件奇珍卻不在身上（遺失/賣掉）-> 逐件同步補贈，不重置進度。
		if( !present("fengshen mirror", me) || !present("lixuan radiance", me) ) {
			// 同步補贈：give_treasures 內逐件 present()-check 後直接 new+move（玩家此刻必在場）；
			// do_chat 只留氣氛對白。不可把 give_treasures 塞進 do_chat 陣列——那會延後數心跳
			// 異步執行，違同步交付契約（本專案頭號 bug class）。
			give_treasures(me);
			do_chat((: command, "say 你那奇珍怎不見了？罷了，我這裡尚守著一份，再付與你便是——這回可要收好，亙古之物，丟不得。" :));
			return 1;
		}
		do_chat(({
			(: command, "say 那封神寶鏡與離玄光熾可還在你身上？好。一鏡一光，一陰一陽，相生相濟——你好生用著，莫教這亙古的奇珍失了輝。" :),
			(: command, "say 我守這塔頂亙古，所候的，不過是一個心志不撼、堪託奇珍的有緣人罷了。如今寶已付你，去罷——這磅礡地氣之巔，不是久留之地。" :),
		}));
		return 1;
	}

	// 首次：同步『一併』贈兩寶、即記旗標（give_treasures 為直接 new+move，玩家此刻必在場）。
	// 先給物、後記旗標——免於回呼前離場致寶沒領、旗標卻記完成而卡關。
	give_treasures(me);
	me->set("quest/sq_heipao", 1);
	do_chat(({
		(: command, "say 你既能登臨這地氣絕頂、心志不為這磅礡地氣所撼，便是與這塔頂、與我所守之物有緣。" :),
		(: command, "say 我守著上古封神一役所遺的兩件奇珍：一面封神寶鏡，鏡主映照、護心映本相；一道離玄光熾，光主光明、破盡幽冥晦昧。一陰一陽，本是一對，相生相濟。" :),
		(: command, "say 這兩件奇珍，我亙古守候，便是要付與你這般的有緣人——如今一併贈了你。持之在身，但教這鏡光火芒護住你的本心、照亮你前路的幽冥。去罷，珍重。" :),
	}));
	return 1;
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品（尤不收回封神寶鏡/離玄光熾）。
int accept_object(object who, object ob)
{
	if( ob->id("fengshen mirror") || ob->id("lixuan radiance") ) {
		do_chat((: command,
			"say 收回去——這奇珍既已付你，便是你的了，我怎能再收？持在身上護心照路便是。" :));
		return 0;
	}
	do_chat((: command,
		"say 我守的是這塔頂的奇珍，這個受不起，你還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 你我無冤無仇，何苦在這地氣絕頂動這刀兵？我守的不過是兩件亙古的奇珍罷了。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
