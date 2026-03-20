// agui.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("阿桂", ({"agui", "kid"}));
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 10);
	set("gender", "male");
	set("long",
		"一個虎頭虎腦的小男孩﹐穿著一件打了補丁的粗布短衫﹐光著\n"
		"兩隻小腳丫。他手裡拿著一根樹枝當刀使﹐正一個人比劃著﹐嘴\n"
		"裡唸唸有詞﹐似乎在模仿什麼武林高手。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"阿桂揮舞著樹枝﹐嘴裡喊道﹕看我的降龍十八掌﹗\n",
		"阿桂歪著腦袋好奇地看著你﹐問道﹕你是哪裡來的大俠啊﹖\n",
		"阿桂說道﹕我長大了也要學武功﹐打壞人﹗\n",
		"阿桂指著東邊的草堂﹐說道﹕那個老道士可厲害了﹐我看到他飛過牆呢﹗\n",
	}));
	setup();
}
