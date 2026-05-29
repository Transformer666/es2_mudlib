// instructor.c -- 雪亭練武堂的武師(教頭)，指點新手如何練功（純教學對話，不開任何任務）
// do_ask 結構沿用 /d/fancheng/npc/boatman.c。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("練武教頭", ({ "instructor", "wushi", "teacher", "jiaotou", "drill instructor" }) );
	set("nickname", "武師");
	set_race("human");
	set_class("commoner");
	set_level(20);

	set_skill("unarmed", 70);
	set_skill("blade", 60);
	set_skill("dodge", 65);
	set_skill("parry", 65);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一位身形精壯的中年武師﹐鎮上人都喚他一聲教頭。他赤著膀子﹐\n"
		"一身腱子肉結實得像繃緊的弓弦﹐拳掌上滿是經年捶打標靶磨出的\n"
		"厚繭。他往場中一站﹐目光沉穩有神﹐瞧得出是個下過真功夫的人。\n"
		"練武堂的後生晚輩有不懂的﹐都愛來向他討教。你或許可以問問他﹕\n"
		"ask instructor about 練功。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"練武教頭負手而立﹐沉聲道﹕功夫是練出來的﹐不是站著看會的。\n",
		"練武教頭瞧著場中標靶﹐淡淡道﹕拳腳兵器﹐多打假人石柱﹐自然純熟。\n",
		"練武教頭道﹕想學閃躲﹐就去找比你能耐的人型對手挨打﹐挨多了身子自會躲。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 後生﹐想練功麼﹖有甚麼不懂的﹐儘管問（ask instructor about 練功）。" :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想向這位武師討教甚麼﹖（試試 ask instructor about 練功）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("練武教頭正忙著﹐沒空理你。\n");

	// 練功總綱：怎麼練各種功夫
	if( arg == "instructor about 練功"
	||  arg == "wushi about 練功"
	||  arg == "teacher about 練功"
	||  arg == "jiaotou about 練功"
	||  arg == "instructor about 練武"
	||  arg == "instructor about 武藝"
	||  arg == "wushi about 武藝"
	||  arg == "instructor about train"
	||  arg == "instructor about practice" ) {
		do_chat(({
			(: command, "say 練功之道﹐不外乎四門﹕兵器、拳腳、拆招、閃躲。內功則另靠吐納。" :),
			(: command, "say 兵器拳腳(unarmed與各般兵器)﹐功夫尚淺時﹐就打場中的假人、石獅、石柱——kill stake 便是﹐儘管捶打﹐熟能生巧。功夫深了﹐才去尋夜叉小孩那等硬手對打。" :),
			(: command, "say 拆招(parry)﹐要找動物型的對手練﹐野獸出招沒章法﹐最磨拆解的本事。" :),
			(: command, "say 閃躲(dodge)﹐須尋個比你能耐高的人型對手﹐收了兵器純挨打——挨得多了﹐身子自然會躲。" :),
			(: command, "say 內功(force)﹐則靠 exert 運氣吐納﹐既練門派內功﹐也固基礎內功。" :),
			(: command, "say 你想細問哪一門﹖兵器拳腳、拆招、閃躲、內功﹐還是天賦﹖" :),
		}));
		return 1;
	}

	// 兵器/拳腳：打標靶
	if( arg == "instructor about 兵器"
	||  arg == "wushi about 兵器"
	||  arg == "instructor about 拳腳"
	||  arg == "wushi about 拳腳"
	||  arg == "instructor about 標靶"
	||  arg == "instructor about unarmed"
	||  arg == "instructor about weapon" ) {
		do_chat(({
			(: command, "say 練兵器與拳腳﹐最簡便的就是捶打死靶。場中那木樁假人(stake)、石獅子(lion)、石柱(pillar)﹐都任你打。" :),
			(: command, "say 對著它下 kill stake﹐手上拿甚麼兵器﹐練的就是那門兵器；空著手打﹐練的便是拳腳(unarmed)。打得越勤﹐功夫長得越快。" :),
			(: command, "say 等你功夫純了、嫌假人不經打了﹐再去尋夜叉小孩那等活靶子對打罷。" :),
		}));
		return 1;
	}

	// 拆招 parry：找動物
	if( arg == "instructor about 拆招"
	||  arg == "wushi about 拆招"
	||  arg == "instructor about parry" ) {
		do_chat(({
			(: command, "say 拆招(parry)是化解敵招的本事。要練它﹐須找動物型的對手——野兔、田鼠那一類。" :),
			(: command, "say 野獸出招全無章法﹐忽快忽慢﹐最逼著你拆解應變。郊野(往西出練武堂、再往野地去)便有野兔田鼠可練。" :),
		}));
		return 1;
	}

	// 閃躲 dodge：找高階人型挨打
	if( arg == "instructor about 閃躲"
	||  arg == "wushi about 閃躲"
	||  arg == "instructor about dodge" ) {
		do_chat(({
			(: command, "say 閃躲(dodge)講究的是身法。要練它﹐得尋個比你能耐高些的人型對手。" :),
			(: command, "say 收了兵器、空著身子﹐純挨他的打——挨得越多﹐身子越懂得閃。死靶可不行﹐它根本不會出手。" :),
			(: command, "say 老練的法子是『跑練』﹕對他下了 kill 便走出房門﹐隔個兩三秒再回來。只是這般練法雖快﹐卻最耗氣力﹐當心疲乏。" :),
		}));
		return 1;
	}

	// 內功 force：exert
	if( arg == "instructor about 內功"
	||  arg == "wushi about 內功"
	||  arg == "instructor about force"
	||  arg == "instructor about 吐納" ) {
		do_chat(({
			(: command, "say 內功(force)不靠打殺﹐靠的是運氣吐納。尋個清靜處﹐下 exert 運轉真氣﹐便能同時長進門派內功與基礎內功。" :),
			(: command, "say 若你打標靶時 enable force﹐拳上帶勁固然狠﹐卻會震得自己內傷﹐新手切莫逞強。" :),
		}));
		return 1;
	}

	// 天賦：算命仙占算、封頂技能等級
	if( arg == "instructor about 天賦"
	||  arg == "wushi about 天賦"
	||  arg == "instructor about 潛能"
	||  arg == "instructor about talent" ) {
		do_chat(({
			(: command, "say 天賦麼……每個人練每門功夫﹐天生的悟性都有個頭﹐高的舉世無匹﹐低的也夠謀生。這頭﹐就封住你那門功夫練得到的最高境界。" :),
			(: command, "say 任你打再多假人、挨再多拳﹐功夫到了天賦的頂﹐便再難寸進。天意如此﹐強求不得。" :),
			(: command, "say 想知道自己某門功夫的天賦幾何﹖去尋個算命先生(找算命仙占算)﹐花些銀錢﹐他自會替你卜上一卦。" :),
		}));
		return 1;
	}

	return notify_fail("練武教頭搖搖頭﹕這個老夫可指點不來。（試試 ask instructor about 練功）\n");
}

// 武師雖懂武功，但對後生晚輩不動真格，純教學人物。
int accept_fight(object ob)
{
	do_chat((: command, "say 後生莫鬧﹐老夫是來教功夫的﹐可不跟你動真格。要練功﹐去打那邊的假人。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
