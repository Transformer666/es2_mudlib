// temple_monk.c

#include <npc.h>

inherit F_SCHOLAR;

void create()
{
	set_name("廟中僧人", ({"temple_monk", "monk"}));
	set_attr("str", 18);
	set_attr("con", 20);
	set_attr("dex", 16);
	set_race("human");
	set_class("monk");
	set_level(15);

	set_skill("unarmed", 70);
	set_skill("dodge", 60);
	set_skill("internal", 50);

	set("age", 45);
	set("long",
		"一個身穿灰色僧袍的和尚﹐面容清瘦而平和。他盤坐在蒲團上\n"
		"閉目誦經﹐手中捻著一串念珠﹐偶爾敲一下木魚﹐發出清脆的聲響。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"僧人雙手合十﹐低聲念道﹕阿彌陀佛。\n",
		"僧人敲了一下木魚﹐殿中迴盪著清脆的聲響。\n",
		"僧人睜開眼看了你一眼﹐微微點頭﹐又閉上眼繼續誦經。\n",
	}));
	setup();
	carry_money("coin", 30);
}
