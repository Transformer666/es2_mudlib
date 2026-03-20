// vim: syntax=lpc
#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("廚子", ({"cook", "chuzi"}));
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 40);
	set("gender", "male");
	set("long",
		"一個壯實的中年漢子，是封山派的廚子。他挽起袖子，正在灶台\n"
		"前忙碌著，翻炒山中採來的野菜和菌菇，鍋裡冒出陣陣香氣。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"廚子往鍋裡撒了一把山鹽，嘟囔道：今天的菌菇真新鮮。\n",
		"廚子擦了擦額頭的汗，端起一大盆野菜湯放到桌上。\n",
		"廚子一邊切菜一邊說道：山上的野菜雖然簡樸，但勝在天然。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 15);
}

int accept_fight(object ob)
{
	do_chat("廚子連忙擺手道：別、別動手！我就是個做飯的！\n");
	return 0;
}
