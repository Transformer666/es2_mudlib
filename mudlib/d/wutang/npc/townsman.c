// townsman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("鎮民", ({ "townsman", "townman" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 44);
	set("gender", "male");
	set("long",
		"一個尋常的五堂鎮居民﹐穿著洗得發白的粗布短褂﹐手裡提著剛從\n"
		"鋪子裡買來的油鹽﹐看樣子正要回家。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :),
		"鎮民朝你點了點頭﹐算是打了個招呼。\n",
		"鎮民說道﹕咱們五堂鎮雖小﹐有鏢局的爺們鎮著﹐倒也太平。\n",
		"鎮民嘆道﹕這年頭物價漲得兇﹐油鹽都貴了不少。\n",
		"鎮民說道﹕往東過了松林便是雪亭鎮了﹐腳程快的半日就到。\n",
		// 郭布要收的徒弟疑團(docs 05:29)之指引伏筆：郭布(朱衣真人)在天師派
		// 三清殿(d/tianshi)收朱衣弟子。本鎮只留口耳相傳之指引，不動 tianshi。
		"鎮民壓低聲音道﹕聽說天師派的朱衣真人郭布﹐近來正四處尋訪與火有緣的後輩收作門徒﹐你若靈性不俗﹐不妨往天師派三清殿走一遭。\n",
	}));
	setup();
	carry_money("coin", 15);
}

int accept_fight()
{
	do_chat("鎮民慌忙擺手道﹕使不得使不得﹗我一個本分人﹐跟你動什麼手﹖\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
