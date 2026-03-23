// student.c
// Quest: 學童丟書 (student_lost_book)
// Flow: talk about 書/丟 -> quest starts -> search lake -> find book
//       -> give book to student -> reward

#include <npc.h>

inherit F_VILLAGER;

void give_book_reward(object me);

void create()
{
	set_name("小學童", ({"student", "child"}));
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 8);
	set("gender", "male");
	set("long",
		"一個穿著藍布小褂的孩子﹐搖頭晃腦地背誦著什麼。看到有人\n"
		"走過便抬起頭來﹐露出天真無邪的笑容。他的眼眶有些紅﹐似乎\n"
		"剛哭過。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"小學童搖頭晃腦地背誦道﹕人之初﹐性本善……\n",
		"小學童好奇地看著你﹐問道﹕你認得字嗎﹖\n",
		"小學童蹲在地上用樹枝寫字﹐一筆一劃十分認真。\n",
		"小學童嘟著嘴﹐嘀咕道﹕先生要是知道書丟了﹐一定會打我手心的 ...\n",
	}));
	setup();
}

int accept_object(string me_id, object ob)
{
	object giver;

	giver = this_player();
	if( !giver ) return 0;

	if( base_name(ob) == __DIR__"obj/student_book" ) {
		if( giver->query("quest/student_lost_book_done") ) {
			do_chat("小學童笑道﹕書已經找回來啦﹐謝謝大哥哥﹗\n");
			return 0;
		}

		if( !giver->query_temp("pending/student_lost_book") ) {
			do_chat("小學童歪著頭﹐說道﹕這是 ... 我的書﹗你怎麼有的﹖\n");
			giver->set_temp("pending/student_lost_book", 1);
		}

		do_chat(({
			"小學童接過書冊﹐眼睛一亮﹐高興得蹦了起來。\n",
			"小學童叫道﹕我的千字文﹗找到了找到了﹗\n",
			"小學童連忙把書擦了擦﹐小心翼翼地抱在懷裡。\n",
			"小學童仰著頭對你說道﹕謝謝大哥哥﹗這個送你﹗\n",
			(: give_book_reward, giver :),
		}));
		return 1;
	}

	return 0;
}

void give_book_reward(object me)
{
	object bookmark;

	if( !me || environment(me) != environment() ) return;
	if( me->query("quest/student_lost_book_done") ) return;

	me->set("quest/student_lost_book_done", 1);
	me->delete_temp("pending/student_lost_book");
	me->gain_score("quest", 60);

	me->improve_skill("literate", random(2) + 1);

	bookmark = new(__DIR__"obj/pressed_flower_bookmark");
	if( bookmark ) {
		if( bookmark->move(me) )
			bookmark->move(environment());
	}

	do_chat("小學童從口袋裡掏出一枚壓花書籤﹐塞進了" + me->name() + "手裡。\n");
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "書") >= 0 || strsrch(msg, "丟") >= 0
	||  strsrch(msg, "哭") >= 0 || strsrch(msg, "怎麼了") >= 0
	||  strsrch(msg, "book") >= 0 ) {
		if( ob->query("quest/student_lost_book_done") ) {
			do_chat("小學童得意地舉起書﹐說道﹕書找回來啦﹐嘿嘿。\n");
			return;
		}

		if( ob->query_temp("pending/student_lost_book") ) {
			do_chat(({
				"小學童著急地說道﹕你找到我的書了嗎﹖\n",
				"小學童說道﹕就在湖邊﹐我追蝴蝶的時候掉的 ...\n",
			}));
			return;
		}

		do_chat(({
			"小學童的眼眶一紅﹐癟了癟嘴。\n",
			"小學童說道﹕大哥哥﹐我 ... 我把先生借我的書弄丟了。\n",
			"小學童說道﹕就是那本千字文﹐先生說要好好愛惜的 ...\n",
			"小學童說道﹕我在湖邊追蝴蝶的時候﹐書從懷裡掉出來了。\n",
			"小學童說道﹕等我回去找的時候﹐怎麼找都找不到。\n",
			"小學童抽了抽鼻子﹐可憐兮兮地說道﹕你能幫我去湖邊找找嗎﹖\n",
			(: $1->set_temp("pending/student_lost_book", 1) :),
		}));
		return;
	}
}
