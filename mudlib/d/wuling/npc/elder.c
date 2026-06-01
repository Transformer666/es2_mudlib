// elder.c -- 桃花林裡的釣叟老者（純氣氛閒談﹐一段桃花源式的自足引子﹐
//            不接任務、不設任何旗標、不與任何門派或任務掛鉤）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老者", ({ "elder", "old man", "diaosou" }) );
	set("nickname", "老者");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 71);
	set("gender", "male");
	set("long",
		"桃林深處坐著一位白髮老者﹐鶴髮童顏﹐一部長鬚垂到胸\n"
		"前﹐手裡執著一竿釣絲﹐卻不見鉤上有餌——竟是在學那姜尚渭水\n"
		"垂釣的閒趣。他背倚桃樹﹐閉目養神﹐落英紛紛揚揚地灑了他一\n"
		"身﹐也渾不在意﹐通身透著一股遺世獨立的恬淡之氣。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"老者執著那無餌的釣竿﹐半瞇著眼﹐任憑桃花落了滿肩﹐恍如老僧入定。\n",
		"老者拈鬚微微一笑﹐望著漫天飛舞的落英﹐似有無限感慨。\n",
		"老者悠悠吟道﹕『忽逢桃花林﹐夾岸數百步』 ... 客官可知這武陵﹐便是當年漁人問津的所在麼﹖\n",
	}));
	setup();
	carry_money("coin", 5);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想向這老者請教甚麼﹖（試試 ask elder about 桃花源）\n");

	if( arg == "elder about 桃花林"
	||  arg == "elder about 桃花"
	||  arg == "elder about 桃花源"
	||  arg == "elder about 武陵"
	||  arg == "elder about peach" ) {
		do_chat(({
			(: command, "say 後生坐罷。老朽在這桃林裡釣了二十年的閒﹐鉤上從不掛餌——所釣者﹐非魚也﹐是這一份清靜罷了。" :),
			(: command, "say 古人說武陵漁人﹐緣溪而行﹐忽逢桃花林﹐落英繽紛﹐豁然開朗﹐遂入了那不知有漢、無論魏晉的桃花源。老朽看哪﹐這水嵐武陵﹐約莫便是那傳說裡桃花源的影子了。" :),
			(: command, "say 山外的江湖﹐刀光劍影﹐爭個沒完﹔山裡這方天地﹐卻只有溪聲、花影與一壺濁酒。後生若是倦了那打打殺殺﹐不妨在這桃林裡多坐些時候。" :),
		}));
		return 1;
	}

	return notify_fail("老者執著釣竿﹐恍若未聞﹐只管望著那滿溪的落花出神。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 後生何苦動氣﹖老朽一把朽骨﹐連魚都懶得釣了﹐哪還禁得起你這般折騰。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
