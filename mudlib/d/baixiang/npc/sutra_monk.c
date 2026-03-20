// vim: syntax=lpc

#include <npc.h>

inherit F_SCHOLAR;

void create()
{
	set_name("知客僧", ({"zhike", "monk", "scholar"}));
	set_attr("int", 18);
	set_attr("wis", 20);
	set_race("human");
	set_class("commoner");
	set_level(15);
	set_skill("unarmed", 20);
	set_skill("dodge", 15);

	set("age", 45);
	set("gender", "male");
	set("attitude", "peaceful");
	set("long",
		"一位清瘦的中年僧人﹐身穿整潔的褐色僧袍﹐鼻樑上架著一\n"
		"副銅框眼鏡。他正聚精會神地翻閱著一卷泛黃的經書﹐不時提\n"
		"筆在旁邊的紙上寫下注解。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"知客僧翻過一頁經書﹐微微點頭﹐似有所悟。\n",
		"知客僧說道﹕「《金剛經》云﹕一切有為法﹐如夢幻泡影。」\n",
		"知客僧輕輕推了推鼻樑上的眼鏡﹐繼續抄寫經文。\n",
		"知客僧說道﹕「佛法浩瀚﹐窮畢生之力亦難盡讀﹐唯有精進不懈。」\n",
	}));
	set("refuse_fight", 1);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 30);
}
