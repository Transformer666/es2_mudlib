// qiyong.c - 杞庸 傳授武學的神秘少年

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("杞庸", ({"qiyong", "qi yong"}));
	set_attr("str", 22);
	set_attr("dex", 26);
	set_attr("con", 20);
	set_attr("int", 24);
	set_attr("wis", 28);
	set_attr("spi", 25);
	set_attr("cps", 24);
	set_race("human");
	set_class("commoner");
	set_level(50);

	set_skill("sword", 100);
	set_skill("unarmed", 100);
	set_skill("dodge", 90);
	set_skill("parry", 85);
	set_skill("force", 90);

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 200);

	set("age", 16);
	set("gender", "male");
	set("attitude", "peaceful");
	set("long",
		"一個看起來不過十五六歲的少年﹐身穿一件樸素的青衫﹐面容清\n"
		"秀﹐嘴角帶著淡淡的微笑。他的眼神卻深邃得不像這個年紀的人﹐\n"
		"彷彿看透了世間萬物。他獨自坐在潭邊﹐手中輕撫著一片落葉﹐\n"
		"渾身散發著一股難以言喻的氣質。據傳二百多年前﹐曾有一名少\n"
		"年以同樣的容貌現身﹐傳授武學予有緣之人。\n");

	set("chat_chance", 3);
	set("chat_msg", ({
		"杞庸望著水面﹐輕聲道﹕天地之間﹐萬物皆有其道。\n",
		"杞庸拾起一片落葉﹐隨手一揮﹐那落葉竟如飛刀般射入對面的樹幹。\n",
		"杞庸微微一笑﹐說道﹕有緣人﹐自會在此相逢。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	set_temp("apply/vision_of_ghost", 1);
}

void do_hydra_reward(object player);

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "鮫蛟") >= 0 || strsrch(msg, "水") >= 0
	||  strsrch(msg, "潭") >= 0 || strsrch(msg, "鱗片") >= 0
	||  strsrch(msg, "hydra") >= 0 || strsrch(msg, "異常") >= 0
	||  strsrch(msg, "水紋") >= 0 ) {
		if( ob->query("quest/manglin_hydra_done") ) {
			do_chat("杞庸微笑道﹕鮫蛟既除﹐這潭水又歸於清澈了。\n");
			return;
		}
		if( ob->query_temp("pending/manglin_hydra") == 2 ) {
			do_chat(({
				"杞庸點了點頭﹐說道﹕好﹐你果然不負所望。\n",
				"杞庸說道﹕這鮫蛟鱗甲堅硬無比﹐我替你取幾片下來 ...\n",
				(: do_hydra_reward, ob :),
			}));
			return;
		}
		if( ob->query_temp("pending/manglin_hydra") ) {
			do_chat("杞庸說道﹕你到潭邊仔細搜尋便是﹐那畜生就藏在水底。\n");
			return;
		}
		do_chat(({
			"杞庸望著水面﹐若有所思地說道﹕\n",
			"杞庸說道﹕這潭底近來不太平靜﹐有一條上古鮫蛟潛伏其中。\n",
			"杞庸說道﹕那畜生已有千年道行﹐生有十二爪﹐兇悍異常。\n",
			"杞庸說道﹕牠若不除﹐遲早要禍害這片林子裡的生靈。\n",
			"杞庸看了看你﹐說道﹕你若有心﹐不妨到潭邊搜尋牠的蹤跡。\n",
		}));
		ob->set_temp("pending/manglin_hydra", 1);
		return;
	}
}

void do_hydra_reward(object player)
{
	object reward;

	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/manglin_hydra_done") ) return;

	player->set("quest/manglin_hydra_done", 1);
	player->delete_temp("pending/manglin_hydra");
	player->gain_score("quest", 120);

	reward = new(__DIR__"obj/hydra_scale");
	reward->move(player);
	message_vision("杞庸取出幾片蛟鱗﹐三兩下便編成一件鱗甲﹐遞給$N。\n", player);
	tell_object(player, "( 你獲得了一件蛟鱗甲 )\n");
}

int acquire_skill(object ob, string skill)
{
	if( is_chatting() )
		return notify_fail("少年正在說話﹐你不好意思打斷。\n");

	switch(skill) {
	case "sword":
		if( ob->query_skill("sword") < 50 ) {
			say("杞庸看了看你﹐微笑道﹕你的劍法根基不錯﹐我指點你幾招。\n");
			message_vision("$N隨手折了一根樹枝﹐向$n演示了幾式精妙的劍招。\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("wis")) + 1);
		} else {
			do_chat("杞庸微笑道﹕你的劍法已有所成﹐餘下的要靠自己領悟了。\n");
		}
		break;
	case "unarmed":
		if( ob->query_skill("unarmed") < 50 ) {
			say("杞庸點了點頭﹐說道﹕拳腳功夫﹐講究以柔克剛。\n");
			message_vision("$N輕描淡寫地比劃了幾個動作﹐向$n指點了拳法要訣。\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("dex")) + 1);
		} else {
			do_chat("杞庸微笑道﹕你的拳腳功夫已到了瓶頸﹐需自行突破。\n");
		}
		break;
	default:
		do_chat("杞庸搖了搖頭﹐說道﹕這門功夫﹐我也不太精通。\n");
		return 0;
	}

	do_chat(({
		"杞庸說道﹕武學之道﹐無窮無盡﹐你且好好修煉。\n",
		"杞庸說道﹕記住﹐武功再高﹐也不過是入道的途徑罷了。\n",
	}));

	return 1;
}
