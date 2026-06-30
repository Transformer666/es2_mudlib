// greyape.c -- 老灰猿，盤踞文國古藤岩窟、毛色蒼白的西山猿群老祖，群猿之首。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 28 一線——文國山林獵場的最強對手、上段把關，
// 通臂猿臂、力大機變，是頗硬的對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老灰猿", ({ "grey ape", "greyape", "old ape", "ape", "laohuiyuan" }) );
	// 根骨 44 → 形體上限約 220 點；另以 advance_stat 加厚氣血﹐通臂力大、極耐戰。
	set_attr("con", 44);
	set_attr("str", 40);
	set_attr("dex", 30);
	set_race("human");
	set_class("commoner");
	set_level(28);

	// 通臂猿臂、拳腳剛猛、騰挪閃躲俱精、內力深厚（閱盡西山歲月的猿群老祖）。
	set_skill("unarmed", 52);
	set_skill("dodge", 36);
	set_skill("parry", 34);
	set_skill("force", 30);

	// 厚其氣血﹐使之耐打、有來有往（量近黑風蒼狼一線）。
	advance_stat("kee", 48);

	set("age", 12);
	set("gender", "male");
	set("long",
		"一頭毛色蒼白如雪的老灰猿﹐盤膝蹲坐在岩窟深處﹐通臂猿臂垂及\n"
		"於地﹐一身的筋肉虬結如鐵。牠是這群灰猿的老祖﹐一雙眼睛精厲\n"
		"沉靜得不似走獸﹐閱盡了西山的寒暑歲月。牠攀藤盪躍快如鬼魅﹐\n"
		"一雙長臂的力氣大得驚人﹐能扯斷兒臂粗的古藤、掀起磨盤大的山\n"
		"石。見了犯境的生人﹐牠厲聲長嘯﹐群猿隨之齊聲呼應﹐聲勢駭人。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 440,
		"unarmed mastery" : 108,
		"martial art"     : 70,
		"martial mastery" : 36,
		"combat"          : 38,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；厲嘯反撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 老灰猿厲聲長嘯﹐群猿齊聲呼應﹐牠舒展通臂、攀藤縱躍﹐挾著一身蠻力撲將下來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
