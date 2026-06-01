// elder.c -- 康平村心曬場上的村正老丈（純氣氛閒談）。
//            管著合村大小事的老village-head﹐閒話些村裡的年成桑麻。不接任務、不動旗標。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("村正老丈", ({ "elder", "village head", "cunzhenglaozhang" }) );
	set("nickname", "村正老丈");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 66);
	set("gender", "male");
	set("long",
		"一位管著康平村大小事的村正老丈﹐生得清癯矍鑠﹐留著一\n"
		"把花白的山羊鬍﹐拄著根油亮的棗木拐杖﹐成日價在曬場上踱來踱\n"
		"去﹐看著翻穀的、碾米的村人﹐東家長西家短地照應著。他在康平\n"
		"村住了一輩子﹐村裡的人情世故、田畝節氣﹐沒有他不曉得的。得\n"
		"閒也可問問他﹕ask elder about 康平村。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"村正老丈拄著拐杖在曬場上踱著﹐彎腰捻起一把曬穀﹐看了看成色﹐滿意地點點頭。\n",
		"村正老丈瞇眼望著滿場金黃的新穀﹐捋著鬍子緩緩道﹕今年這年成﹐是十來年裡頭一份的好哇。\n",
		"村正老丈和翻穀的村婦招呼道﹕穀子曬透了趁早入倉﹐莫教半夜的露水返了潮。\n",
	}));
	setup();
	carry_money("coin", 50);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這村正老丈打聽甚麼﹖（試試 ask elder about 康平村）\n");

	if( arg == "elder about 康平村"
	||  arg == "elder about 康平"
	||  arg == "elder about 村"
	||  arg == "elder about 曬場"
	||  arg == "elder about 謝場"
	||  arg == "elder about kangping" ) {
		do_chat(({
			(: command, "say 客官是頭一回到咱康平村罷﹖咱這小村偏在斐縣城西﹐出村往東過田壟便是縣裡的土地祠了。合村百十戶人家﹐都靠著村外那一片田過活﹐取名『康平』﹐圖的就是個身康家平、年年有個好收成。" :),
			(: command, "say 今年雨水勻、年成好﹐新穀剛登場﹐合村正忙著曬穀碾米。過幾日穀子入了倉﹐村裡要在這曬場上擺一場秋收謝天的酒飯﹐熱鬧熱鬧。客官若不趕路﹐留下吃碗咱康平的新米飯﹐也圖個豐年的喜氣。" :),
		}));
		return 1;
	}

	if( arg == "elder about 謝天"
	||  arg == "elder about 秋收"
	||  arg == "elder about 新米" ) {
		do_chat((: command,
			"say 秋收謝場的事﹐村裡的康平小店店家正張羅著哩——頭一籠待客的新米飯糰﹐便指著他去備。客官若得閒﹐不妨去小店問問店家（ask keeper about 新米），搭把手﹐也是一樁善緣。" :));
		return 1;
	}

	return notify_fail("村正老丈捋著鬍子和氣一笑﹕客官問這個做甚﹖難得到咱村裡﹐隨意逛逛﹐吃碗新米飯罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗光天化日的﹐客官這是做甚﹖老朽一個管村事的莊稼老兒﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
