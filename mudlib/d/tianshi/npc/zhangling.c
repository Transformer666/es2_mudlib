// zhangling.c -- 天師派駕雲使者 張齡（素雲書傳人）
//
// 張齡執掌天師派的駕雲道法【素雲書】(taoism-cloud)——一門 magic 槽的傳送
// 法術(走 conjure 指令﹐見 daemon/skill/taoism-cloud.c)。本派弟子年滿 10 級
// 後﹐可向她打聽「素雲書」習得入門口訣﹕
//     ask 張齡 about 素雲書
// 習得後玩家須 `enable magic with taoism-cloud`﹐再 `conjure <地點代號>` 駕雲。
//
// 授技 idiom 比照 d/tianshi/npc/master.c::init_apprentice 的 set_skill；
// 對話打聽 idiom 比照 d/snow/npc/swordsmith.c::accept_inquiry。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("張齡", ({ "zhang ling", "zhangling", "zhang" }));
	set("nickname", "素雲真人");
	set_race("human");
	set_class("taoist");
	set("sect", "天師派");
	set("rank", "駕雲使者");
	set("title", "天師派素雲真人");

	set_attr("str", 16);
	set_attr("dex", 22);
	set_attr("int", 25);
	set_attr("wis", 24);
	set_attr("spi", 26);
	set_attr("con", 20);
	set_attr("cor", 20);
	set_attr("cps", 22);

	set_level(30);

	set_skill("unarmed", 50);
	set_skill("dodge", 80);
	set_skill("parry", 60);
	set_skill("force", 100);
	set_skill("magic", 150);
	set_skill("taoism-cloud", 180);
	map_skill("magic", "taoism-cloud");

	advance_stat("gin", 180);
	advance_stat("kee", 180);
	advance_stat("sen", 240);

	set("age", 48);
	set("gender", "female");
	set("long",
		"這位身形清臒的女冠便是天師派的駕雲使者張齡﹐道號素雲真人。\n"
		"她一襲素白道袍﹐外罩一領雲紋鶴氅﹐立在庭中時衣袂無風自動﹐周\n"
		"身隱隱浮著一層淡淡的白氣﹐宛若踏雲而來。素雲書是天師派祕傳的\n"
		"駕雲道法﹐能瞬息馳越千里﹐張齡浸淫此術數十年﹐縱橫四海如履平\n"
		"地。本派弟子年資稍長﹐便可向她打聽素雲書的口訣——你可以用\n"
		"  ask 張齡 about 素雲書\n"
		"向她請教這門駕雲之術。\n");

	set("chat_chance", 5);
	set("chat_msg", ({
		"張齡負手而立﹐衣袂無風自動﹐周身白氣繚繞。\n",
		"張齡淡淡說道﹕千里之遙﹐素雲書一念可至。\n",
		"張齡說道﹕本派弟子滿了十級﹐便可來問我素雲書的口訣。\n",
		"張齡說道﹕駕雲一回耗神五十﹐神識不足﹐切莫強運。\n",
	}));

	setup();
}

// 不與人動手。
int accept_fight()
{
	do_chat("張齡微微一笑﹐說道﹕貧道只管駕雲趕路﹐不耐與人動手。\n");
	return 0;
}

int accept_kill()
{
	return 0;
}

// ask 張齡 about 素雲書 / taoism-cloud / 雲遊 / 傳送
void accept_inquiry(object who, string topic)
{
	if( !objectp(who) ) return;

	switch( topic ) {
	case "素雲書":
	case "taoism-cloud":
	case "雲遊":
	case "傳送":
	case "駕雲":
		// 非道門中人﹐不傳。
		if( who->query_class() != "taoist" || who->query("sect") != "天師派" ) {
			command("say 素雲書乃我天師派祕傳的駕雲道法﹐非本派弟子﹐恕難相授。");
			return;
		}

		// 已習得者﹐再提點用法。
		if( who->query_skill("taoism-cloud", 1) > 0 || who->query_learn("taoism-cloud") ) {
			command("say 你既已習得素雲書﹐只消 enable magic with taoism-cloud﹐"
				"再 conjure 地點代號﹐便可駕雲飛去。");
			command("say 你素雲書的火候越深﹐能去的地方便越多﹐莫要荒廢了。");
			return;
		}

		// 火候(等級)未足。
		if( who->query_level() < 10 ) {
			command("say 你道行尚淺﹐心神難凝﹐駕雲一道急不得。"
				"且去歷練到十級﹐再來尋我罷。");
			return;
		}

		// 授技：set_skill 給 0 級﹐並 set_learn 開啟學習旗標﹐
		// 否則 enable magic with taoism-cloud 會因 query_skill/query_learn 皆 0 而擋下。
		seteuid(getuid());
		who->set_skill("taoism-cloud", 0);
		who->set_learn("taoism-cloud", 1);

		message_vision(
			"$N取過一卷素白雲箋﹐將天師道法【素雲書】的駕雲口訣緩緩傳授給$n。\n",
			this_object(), who);
		command("say 我已將素雲書的入門口訣傳了給你。");
		command("say 你先 enable magic with taoism-cloud﹐再 conjure snow﹐"
			"便可駕雲飛往飲風客棧。");
		command("say 駕雲一回耗神五十﹐火候越深﹐能去的地方越多。去罷。");
		return;

	default:
		command("say 這個貧道便不甚清楚了。");
		return;
	}
}

// vim: set ts=4 sw=4 syntax=lpc
