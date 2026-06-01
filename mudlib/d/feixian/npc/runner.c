// runner.c -- 斐縣縣衙前當值的差役（非戰鬥﹐純氣氛）。
//             兼帶一句自成一格的本地閒談 foreshadow：南邊山中武陀灸堂
//             鬼華陀的傳聞——僅止於氣氛點染﹐不設、不動任何任務旗標﹐
//             與既有的拜師 / 主線各任務毫無瓜葛。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("差役", ({ "runner", "yamen runner", "chaiyi" }) );
	set("nickname", "差役");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 36);
	set("gender", "male");
	set("long",
		"一個斐縣縣衙的老差役﹐穿著件半舊的青色號褂﹐頭戴一頂\n"
		"褪了色的紅纓帽﹐腰間斜插一根烏木水火棍。這太平小縣難得有\n"
		"甚麼大案﹐他當差多年﹐臉上早磨出一副閒散又自得的神氣﹐倚\n"
		"著衙門前的石獅子有一搭沒一搭地打著呵欠。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"差役按著水火棍﹐不緊不慢地在衙門前踱了個來回。\n",
		"差役打了個長長的呵欠﹐嘟囔道﹕這太平日子﹐閒得人骨頭都鬆了。\n",
		"差役瞧了你一眼﹐慢悠悠地道﹕生面孔啊﹖到斐縣來﹐安分些便是了。\n",
	}));
	setup();
	carry_money("coin", 60);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這差役甚麼﹖（試試 ask runner about 斐縣）\n");

	// 本地風土：斐縣概況，純氣氛
	if( arg == "runner about 斐縣"
	||  arg == "runner about 縣衙"
	||  arg == "runner about 縣城"
	||  arg == "runner about feixian"
	||  arg == "runner about county" ) {
		do_chat(({
			(: command, "say 斐縣地處喬陰與群山之間﹐是進山的頭一道關口。地方雖小﹐倒也太平﹐一年到頭沒幾樁官司﹐縣太爺清閒﹐咱當差的也樂得自在。" :),
			(: command, "say 客官若是過路歇腳﹐悅客來客棧、錢記酒樓盡可去得。只是往南那片山裡頭﹐近來不大安生﹐進山可得留神著些。" :),
		}));
		return 1;
	}

	// 武陀灸堂 / 鬼華陀：自成一格的本地傳聞 foreshadow（不設任何旗標）
	if( arg == "runner about 武陀灸堂"
	||  arg == "runner about 武陀"
	||  arg == "runner about 灸堂"
	||  arg == "runner about 鬼華陀"
	||  arg == "runner about 武道通"
	||  arg == "runner about wuto"
	||  arg == "runner about 山" ) {
		do_chat(({
			(: command, "say 噓——客官這話可別亂打聽。打斐縣往喬陰那頭去﹐市集南邊巷子裡有座武陀灸堂﹐堂主是位人稱『鬼華陀』的武道通老先生﹐一手針灸艾灸的本事﹐當真能起死回生。" :),
			(: command, "say 只是那位老先生性子古怪﹐救人也挑緣分。聽說他這一身通神的醫術﹐另有一段不為人知的來歷——咱當差的也只是道聽塗說﹐究竟如何﹐客官有膽量﹐自個兒去尋他討教罷。" :),
		}));
		return 1;
	}

	return notify_fail("差役斜睨著你﹐懶懶地道﹕問這許多做甚﹖無事莫在衙門前逗留。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 大膽﹗竟敢在縣衙門前撒野﹖也不怕驚動了堂上的縣太爺﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
