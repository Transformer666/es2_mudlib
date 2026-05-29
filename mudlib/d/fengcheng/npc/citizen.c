// citizen.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("城民", ({ "citizen", "townman" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 37);
	set("gender", "male");
	set("long",
		"一個尋常的風城百姓﹐裹著件厚實的棉袍﹐臉膛被朔風颳得\n"
		"黝黑粗糙﹐袖著手不慌不忙地走著﹐一臉北地人家飽經風霜的\n"
		"硬朗。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :),
		"城民朝你拱了拱手﹐算是打了個招呼。\n",
		"城民得意地說道﹕咱們風城好歹是北地第一大城﹐這市集馬市的熱鬧﹐尋常州縣可比不了。\n",
		"城民裹緊了棉袍﹐嘟囔道﹕這朔風一年到頭颳個不停﹐你們南邊來的怕是住不慣哩。\n",
		"城民壓低聲音道﹕近來塞外的馬賊又不安分了﹐城頭那烽火臺﹐可有些日子沒這麼緊著了。\n",
	}));
	setup();
	carry_money("coin", 30);
}

int accept_fight()
{
	do_chat("城民慌忙擺手道﹕使不得使不得﹗光天化日﹐城門差役就在眼前哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
