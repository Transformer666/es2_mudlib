// tea_guest.c -- 聽濤茶樓裡候缺的選官（純氣氛，茶客閒談京中風向，隱隱透出朝廷耳目之嚴）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("候缺選官", ({ "tea guest", "guest", "xuanguan" }) );
	set_race("human");
	set_class("scholar");
	set_level(6);

	set("age", 44);
	set("gender", "male");
	set("long",
		"一位候缺謁選的外省官員﹐頭戴方巾﹐身著半舊的綢衫﹐獨\n"
		"坐窗邊﹐對著一盞早已涼透的茶出神。他來京裡候了大半年的\n"
		"缺﹐宦囊漸澀﹐眉宇間鬱結著一股鬱鬱不得志的悒悶﹐偶爾聽\n"
		"得鄰座官人低語﹐便不自覺地側耳留神。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"候缺選官對著那盞涼透的冷茶出神﹐長長地嘆了口氣。\n",
		"候缺選官苦笑道﹕在京裡候缺﹐候的是時運﹐也是門路。似我這般無依無傍的﹐怕是要候到鬍子白了。\n",
		"候缺選官壓低聲音道﹕兄台慎言。這羅城裡耳目最是繁密﹐隔牆便有耳﹐妄議朝政是要吃掛落的。\n",
		"候缺選官望著相府的方向﹐低聲道﹕聽聞相爺近來常為著些古怪的舊案召人入府密議﹐究竟是甚麼事﹐外頭誰也說不真切 ...\n",
	}));
	setup();
	carry_money("coin", 80);
}

int accept_fight(object ob)
{
	do_chat("候缺選官駭得連連擺手﹕使不得﹗光天化日﹐茶樓裡眾目睽睽﹐你莫要害我﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
