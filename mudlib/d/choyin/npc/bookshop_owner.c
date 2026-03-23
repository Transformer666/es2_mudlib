// bookshop_owner.c
// Quest: 失竊的古卷 (bookshop_manuscript)
// Flow: ask about 古卷/失竊 -> quest starts -> search east_lane -> find manuscript
//       -> give manuscript to owner -> reward

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void give_manuscript_reward(object me);

void create()
{
	set_name("書肆掌櫃", ({"bookshop_owner", "owner", "shopkeeper"}));
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個文質彬彬的中年人﹐身穿灰色長袍﹐鼻樑上架著一副銅框\n"
		"眼鏡﹐手中總是捧著一卷書。他說話慢條斯理﹐一看便知是個飽讀\n"
		"詩書的人。你可以用 list 看看書目﹐用 buy 購買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"掌櫃翻了翻書頁﹐搖頭嘆道﹕如今讀書的人越來越少了。\n",
		"掌櫃推了推眼鏡﹐說道﹕本店書籍﹐童叟無欺。\n",
		"掌櫃小心翼翼地擦拭著一冊古書﹐神情專注。\n",
		"掌櫃嘆了口氣﹕那卷「劍意殘篇」被偷走後﹐我一直悶悶不樂。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/book_erta" : 30,
		__DIR__"obj/book_erta2" : 30,
	]));

	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("掌櫃連忙擺手道﹕客倌﹐小店是做學問的地方﹐可不興動武﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say 好的﹐" + item->name() + "﹐請拿好。");
	::deliver_merchandise(customer, item);
}

int accept_object(string me_id, object ob)
{
	object giver;

	giver = this_player();
	if( !giver ) return 0;

	if( base_name(ob) == __DIR__"obj/ancient_manuscript" ) {
		if( giver->query("quest/bookshop_manuscript_done") ) {
			do_chat("掌櫃推了推眼鏡﹐說道﹕古卷已經找回來了﹐多謝你。\n");
			return 0;
		}

		if( !giver->query_temp("pending/bookshop_manuscript") ) {
			do_chat("掌櫃疑惑地看了看古卷﹐說道﹕這是 ... 你從哪裡得來的﹖\n");
			return 0;
		}

		do_chat(({
			"掌櫃顫抖著接過古卷﹐仔細端詳了一番。\n",
			"掌櫃激動地說道﹕就是這卷﹗就是這卷「劍意殘篇」﹗\n",
			"掌櫃說道﹕你看﹐這上面的劍招圖解﹐全是前人心血﹐千金難換啊。\n",
			"掌櫃將古卷小心翼翼地收好﹐對你深深一揖。\n",
			"掌櫃說道﹕大恩不言謝﹐這些銀兩和一本拙作﹐聊表心意。\n",
			(: give_manuscript_reward, giver :),
		}));
		return 1;
	}

	return 0;
}

void give_manuscript_reward(object me)
{
	object money;

	if( !me || environment(me) != environment() ) return;
	if( me->query("quest/bookshop_manuscript_done") ) return;

	me->set("quest/bookshop_manuscript_done", 1);
	me->delete_temp("pending/bookshop_manuscript");
	me->gain_score("quest", 80);

	money = new("/obj/money/silver");
	money->set_amount(3);
	if( money->move(me) )
		money->move(environment());

	me->improve_skill("literate", random(3) + 1);

	do_chat("掌櫃將幾錠碎銀和一本書塞進了" + me->name() + "手裡。\n");
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "古卷") >= 0 || strsrch(msg, "失竊") >= 0
	||  strsrch(msg, "偷") >= 0 || strsrch(msg, "劍意") >= 0
	||  strsrch(msg, "manuscript") >= 0 ) {
		if( ob->query("quest/bookshop_manuscript_done") ) {
			do_chat("掌櫃微微一笑﹐說道﹕多虧你幫忙﹐那卷古書總算物歸原主了。\n");
			return;
		}

		if( ob->query_temp("pending/bookshop_manuscript") ) {
			do_chat(({
				"掌櫃推了推眼鏡﹐焦急地說道﹕你找到古卷了嗎﹖\n",
				"掌櫃說道﹕書肆東邊的巷子裡﹐那賊應該是從那邊跑掉的。\n",
			}));
			return;
		}

		do_chat(({
			"掌櫃嘆了口氣﹐放下手中的書卷。\n",
			"掌櫃說道﹕唉﹐別提了。前幾日店裡遭了賊﹐偷走了一卷珍貴的古籍。\n",
			"掌櫃說道﹕那是一卷手抄的「劍意殘篇」﹐記載著上古劍術的心法和圖解﹐\n",
			"掌櫃說道﹕是我花了半輩子積蓄才從一個遊方道士手中購得的。\n",
			"掌櫃說道﹕那賊偷了東西往東邊的巷子跑﹐也許慌亂中掉落在那裡。\n",
			"掌櫃說道﹕我報了衙門﹐可衙門的人敷衍了事﹐根本不管。\n",
			"掌櫃用懇求的目光看著你﹐說道﹕小友﹐你若能幫我找回來﹐我必有重謝。\n",
			(: $1->set_temp("pending/bookshop_manuscript", 1) :),
		}));
		return;
	}

	if( strsrch(msg, "書") >= 0 || strsrch(msg, "book") >= 0 ) {
		do_chat("掌櫃說道﹕本店有各類書籍﹐用 list 看看吧。\n");
		return;
	}
}
