// fisherman.c
// Quest: 鯉君渡金鯉傳說 (golden_carp)
// Flow: ask fisherman about carp -> fish at riverbank with bamboo_pole -> catch golden carp

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("釣叟", ({"fisherman", "old_fisherman"}));
	set_attr("str", 12);
	set_attr("con", 16);
	set_attr("dex", 14);
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 65);
	set("long",
		"一個瘦削的老翁﹐頭戴斗笠﹐身披蓑衣﹐盤腿坐在河邊的大\n"
		"石頭上。他手持一根竹製釣竿﹐目不轉睛地盯著水面上的浮標﹐看\n"
		"起來已經在這裡坐了很久。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"釣叟輕聲說道﹕噓﹐小聲點﹐別嚇跑了魚。\n",
		"釣叟自言自語道﹕今天的魚兒不太上鉤啊。\n",
		"釣叟嘆了口氣﹕以前這裡的鯉魚又大又肥﹐現在越來越少了。\n",
		"釣叟忽然說道﹕聽說羿水深處有一條金色的大鯉魚﹐怕是成了精吧。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/golden_carp_done") )
		return;

	if( this_player()->query_temp("pending/golden_carp") )
		do_chat("釣叟看了你一眼﹕怎麼﹖還沒釣到那條金鯉﹖得有耐心啊。\n");
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "鯉魚") >= 0 || strsrch(msg, "金鯉") >= 0
	||  strsrch(msg, "金色") >= 0 || strsrch(msg, "釣魚") >= 0
	||  strsrch(msg, "成精") >= 0 ) {
		if( ob->query("quest/golden_carp_done") ) {
			do_chat("釣叟讚嘆道﹕你竟然真的釣到了金鯉﹗了不起﹐了不起﹗\n");
			return;
		}
		if( ob->query_temp("pending/golden_carp") ) {
			do_chat("釣叟說道﹕去河灘那邊試試吧﹐記得帶根竹竿﹐用 fish 就能釣了。\n");
			return;
		}
		do_chat(({
			"釣叟壓低聲音﹐神秘兮兮地說道﹕你也聽說了﹖\n",
			"釣叟說道﹕這鯉君渡的名字﹐就是因為古時候有鯉魚精在此渡河而得名。\n",
			"釣叟說道﹕老夫在這裡釣了大半輩子的魚﹐有一回月圓之夜﹐親眼看見水裡有金光閃過。\n",
			"釣叟說道﹕那金光有碗口粗﹐從水底一竄而過﹐快得不得了﹐肯定就是那條金鯉。\n",
			"釣叟嘆道﹕老夫年紀大了﹐手腳不俐落﹐怕是沒本事釣上來。\n",
			"釣叟看了看你﹐說道﹕你若有興趣﹐去碼頭南邊的河灘試試看﹐帶一根竹竿就行了。\n",
		}));
		ob->set_temp("pending/golden_carp", 1);
		return;
	}

	if( strsrch(msg, "竹竿") >= 0 || strsrch(msg, "釣竿") >= 0 ) {
		do_chat("釣叟說道﹕碼頭那邊的行商有賣竹竿﹐買一根就能當釣竿用。\n");
		return;
	}

	if( strsrch(msg, "河灘") >= 0 ) {
		do_chat("釣叟往南一指﹕河灘就在碼頭南邊﹐沿著河走就到了。\n");
		return;
	}
}
