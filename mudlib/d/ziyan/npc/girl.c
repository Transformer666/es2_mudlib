// girl.c -- 紫煙溫泉下游浣巾的鎮女（純氣氛閒談﹐不接任務、不動旗標）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("浣巾女", ({ "girl", "village girl", "huanjinnu" }) );
	set("nickname", "浣巾女");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 18);
	set("gender", "female");
	set("long",
		"一個荊釵布裙的紫煙鎮女﹐挽著袖子蹲在溫泉下游的暖石\n"
		"上浣著巾帕﹐烏黑的辮子垂在肩頭﹐手腕隨著捶巾的木杵一起一\n"
		"落﹐溫熱的泉水在她指間漾開一圈圈帶著白汽的漣漪。她生得眉\n"
		"清目秀﹐臉上是溫泉鄉女兒特有的那份紅潤清澈﹐見了生客﹐只\n"
		"是靦腆地一笑。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"浣巾女舉起木杵﹐輕輕捶著暖石上的巾帕﹐溫泉漾開帶著白汽的細波。\n",
		"浣巾女把浣好的巾帕擰乾了﹐搭在泉畔的竹竿上晾著﹐口中低低地哼著溫泉鄉的小調。\n",
		"浣巾女抬手撩了撩垂下的鬢髮﹐衝你抿嘴一笑﹐又低頭浣她的巾帕去了。\n",
	}));
	setup();
	carry_money("coin", 6);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這浣巾女甚麼﹖（試試 ask girl about 溫泉）\n");

	if( arg == "girl about 溫泉"
	||  arg == "girl about 泉"
	||  arg == "girl about 紫煙"
	||  arg == "girl about 鎮"
	||  arg == "girl about spring" ) {
		do_chat(({
			(: command, "say 客官是外鄉來的罷﹖咱這紫煙溫泉啊﹐冬暖夏溫﹐一年到頭都是熱的。我們鎮上的姑娘都愛來這下游浣巾洗衫﹐水暖手不凍﹐舒坦得很哩。" :),
			(: command, "say 泉上的湯氣一到晨昏就泛出淡淡的紫煙﹐好看得很。客官沿著北邊石階上去﹐就回鎮心了﹔要泡湯﹐尋池邊那位燒湯老叟看著水溫便是。" :),
		}));
		return 1;
	}

	return notify_fail("浣巾女低頭浣著巾帕﹐衝你靦腆地笑了笑﹐似是不慣與生人多話。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗這位客官好沒道理﹗光天化日的﹐欺負我一個浣巾的姑娘家做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
