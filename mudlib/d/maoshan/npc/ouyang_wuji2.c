// ouyang_wuji2.c - 歐陽無寂 茅山奇術師父

#include <npc.h>

inherit F_SCHOLAR;

void create()
{
	set_name("歐陽無寂", ({"ouyang wuji2", "ouyang wuji", "wuji2"}));
	set("nickname", "茅山奇術宗師");
	set_attr("str", 16);
	set_attr("dex", 18);
	set_attr("con", 18);
	set_attr("int", 28);
	set_attr("wis", 26);
	set_attr("spi", 24);
	set_attr("cps", 20);
	set_race("human");
	set_class("taoist");
	set_level(55);

	set_skill("sword", 60);
	set_skill("maoshan sword", 70);
	set_skill("maoshan neigong", 85);
	set_skill("dodge", 60);
	set_skill("parry", 55);

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 250);

	set("age", 58);
	set("gender", "male");
	set("attitude", "peaceful");
	set("long",
		"歐陽無寂是茅山派精通奇術的道長﹐他是掌門歐陽無極的師弟。\n"
		"他身穿一件灰色道袍﹐面容和善﹐眼中時常閃爍著智慧的光芒。\n"
		"他精研茅山奇術與遁甲之書﹐能觀天象﹐知吉凶﹐是茅山派中\n"
		"最博學的道士。幻霧觀終年籠罩的迷霧便是他的傑作。\n");

	set("chat_chance", 2);
	set("chat_msg", ({
		"歐陽無寂翻閱著一卷泛黃的遁甲書﹐口中唸唸有詞。\n",
		"歐陽無寂抬頭望了望迷霧﹐微微一笑﹐說道﹕虛虛實實﹐方為道也。\n",
		"歐陽無寂閉目掐算了一番﹐緩緩睜開眼睛。\n",
	}));

	setup();
	carry_object(STOCK_WEAPON("staff"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 300);
}

int acquire_skill(object ob, string skill)
{
	if( is_chatting() )
		return notify_fail("你最好等道長的話說完再插嘴。\n");
	if( !ob->is_apprentice_of(this_object())
	&&	ob->query_class() != "taoist" ) {
		do_chat("歐陽無寂搖了搖頭﹐說道﹕你非茅山弟子﹐貧道不便傳授。\n");
		return 0;
	}

	switch(skill) {
	case "maoshan neigong":
		if( !ob->query_learn(skill)
		&&	ob->query_skill("maoshan sword") >= 50 ) {
			say("歐陽無寂點了點頭﹐說道﹕你劍法根基穩固﹐可修內功了。\n");
			message_vision("$N將茅山內功的進階心法傳授給$n。\n", this_object(), ob);
			ob->improve_skill(skill, random(ob->query_attr("int")) + 1);
		}
		break;
	default:
		return 0;
	}

	do_chat(({
		"歐陽無寂說道﹕奇術之道﹐在於洞察天機﹐明辨虛實。\n",
		"歐陽無寂說道﹕你且去修煉﹐日後若有所悟﹐再來找貧道。\n",
	}));

	return 1;
}
