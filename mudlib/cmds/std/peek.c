// peek.c
//
// 盜賊「窺視」指令：偷偷觀看目標身上的物品欄，而不取走任何東西。
// 鏡 steal.c 的開場守則與能力/警覺對峙公式，但屬非戰鬥行為：
//   成功 → 看清對方身上帶著什麼（隨技巧高低看見的多寡不同）。
//   失敗 → 可能被對方察覺，但不直接進入戰鬥（比 steal 溫和）。
//
// 警覺公式（docs/03-門派與武功/05-盜賊-瑯夷隱教.md）：
//   警覺 = 靈性 × 定力 / 10 + gin / 16
//        = query_attr("spi") * query_attr("cps") / 10 + query_stat("gin") / 16

#include <ansi.h>
#include <login.h>

inherit F_CLEAN_UP;

void create() {seteuid(getuid());}

int main(object me, string arg)
{
    object victim;
    int sp, dp, skill, forcesk, alert;
    string peeker_race;

    peeker_race = me->query_race();
    forcesk = (me->query_skill("force", 1)/25) + 4;

    if( me->is_busy() ) return notify_fail("你現在沒有空﹗\n");

    if( me->query("life_form") == "ghost" )
	return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( environment(me)->query("no_fight")
    || environment(me)->query("no_steal") )
	return notify_fail("這裡不適合鬼鬼祟祟。\n");

    if( me->skill_mapped("stealing")==0 )
	return notify_fail("你必須使用 (enable) 妙手空空之技!\n");

    if( me->query_temp("peeking") || me->query_temp("stealing") )
	return notify_fail("你已經在找機會下手了﹗\n");

    if( !arg )
	return notify_fail("指令格式﹕peek <人物>\n");

    victim = present(arg, environment(me));
    if( !victim || victim==me || !victim->is_character() )
	return notify_fail("你想窺視的對象不在這裡。\n");
    if( !wizardp(me) && wizardp(victim) )
	return notify_fail("玩家不能窺視巫師身上的東西。\n");

    // add by dragoon (mirror steal.c)
    if( userp(victim) && !interactive(victim) )
	return notify_fail("這人現在不在線上。\n");

    // Don't let NPC peek NPC.
    if( !userp(me) && !userp(victim) )
	return 0;

    // 窺視的能力 sp：以妙手空空(stealing)為主，輔以機敏(dex)與定力(cps)。
    // 鏡 steal.c 的 sp 建構，但因窺視只看不取，能力門檻較低。
    skill = me->query_skill("stealing");
    if( me->query_stat("gin") < skill/4 )
	skill /= 2;
    me->consume_stat("gin", skill/4);

    sp = skill*5 + (int)me->query_attr("dex")*5 + (int)me->query_attr("cps")*5;

    // 盜賊職業天生窺探能力更強。
    if( me->query("class") == "thief" )
	sp += skill*5 + (int)me->query_attr("dex")*5;

    // 精(gin)越高，窺探越精準（二次級數，鏡 steal.c）。
    sp += 1 + (int)me->query_stat("gin")*(int)me->query_stat("gin")/600;

    if( sp < 1 ) sp = 1;

    // 焦僥(jiaojao)一族天生敏銳，窺探能力與 force 相關（鏡 steal.c）。
    if( peeker_race == "jiaojao" )
	sp += (skill + (int)me->query_attr("dex")) * forcesk;

    // 戰鬥中分心，窺探能力減半。
    if( me->is_fighting() && peeker_race != "jiaojao" ) sp /= 2;

    // 對方警覺力 dp（docs 警覺公式）：靈性 × 定力 / 10 + gin / 16。
    alert = (int)victim->query_attr("spi") * (int)victim->query_attr("cps") / 10
	  + (int)victim->query_stat("gin") / 16;
    dp = alert;

    // 焦僥目標額外警覺（docs：焦僥 警覺 +100 被動）。
    if( victim->query_race() == "jiaojao" ) dp += 100;
    // 對方也是盜賊時更難得手（鏡 steal.c 的盜賊互防精神）。
    if( victim->query("class") == "thief" ) dp += skill;
    if( victim->is_fighting() ) dp /= 2;     // 對方戰鬥中疏於防範，較易偷看
    if( dp < 1 ) dp = 1;

    write("你不動聲色地慢慢靠近" + victim->name() + "﹐想看清楚他身上帶著什麼 ...\n\n");

    me->set_temp("peeking", 1);
    me->delete_temp("pending/hidden");
    call_out("complete_peek", 2, me, victim, sp, dp);

    return 1;
}

private void complete_peek(object me, object victim, int sp, int dp)
{
    object *inv, *visible, ob;
    int show, i;
    string list;

    if( !me ) return;

    me->delete_temp("peeking");

    if( !victim || environment(victim) != environment(me) ) {
	tell_object(me, "太可惜了﹐你想窺視的目標已經走了。\n");
	return;
    }

    // 沿用 steal 的察覺機制：給目標一次反窺視的機會。
    if( victim->detect_steal(me, 0, sp) ) return;

    // 對峙判定（鏡 steal.c 的 random(sp+dp) > dp）。
    if( random(sp+dp) <= dp ) {
	// 失手被察覺，但窺視較溫和，不直接開戰。
	if( random(sp) > dp/2 ) {
	    tell_object(me, victim->name() + "不經意地一轉頭﹐你急忙裝作若無其事﹗\n"
			"還好﹐沒有被發現。\n");
	    me->improve_skill("stealing", random(me->query_attr("int")));
	    return;
	}
	tell_object(me, HIR "糟糕﹗你的舉動被發現了﹗\n\n" NOR);
	message_vision("$N狐疑地看著$n﹕「你鬼鬼祟祟地盯著我幹什麼﹖」\n\n",
		victim, me);
	me->improve_skill("stealing", random(me->query_attr("int")));
	me->gain_score("thievery", 1);
	return;
    }

    // 得手：看清對方身上的物品欄。
    inv = all_inventory(victim);
    inv -= ({ 0 });
    // 只列出有 short() 描述的物品（鏡 look.c 的 inventory_look 慣例）。
    visible = filter_array(inv, (: $1 && stringp($1->short()) :));
    if( !sizeof(visible) ) {
	tell_object(me, "你仔細打量了一番﹐" + victim->name()
		+ "身上似乎沒帶什麼東西。\n");
	me->improve_skill("stealing", me->query_attr("int"));
	return;
    }

    // 技巧越高，看得越清楚（看得到的件數越多）。技巧不足時只瞥見部分。
    show = sizeof(visible);
    if( sp < dp*2 ) {
	show = 1 + me->query_skill("stealing") * sizeof(visible) / 200;
	if( show < 1 ) show = 1;
	if( show > sizeof(visible) ) show = sizeof(visible);
    }

    list = "";
    for( i = 0; i < show; i++ ) {
	ob = visible[i];
	list += "    " + ob->short();
	if( ob->query("equipped") ) list += HIY "（隨身）" NOR;
	list += "\n";
    }

    tell_object(me, HIW "你瞄了一眼 ...\n\n" NOR);
    tell_object(me, "你窺見" + victim->name() + "身上帶著﹕\n" + list
	+ ((show < sizeof(visible)) ?
	    "（你的眼力還不夠﹐只看清了一部分。）\n" : ""));

    me->improve_skill("stealing", me->query_attr("int"));
    me->gain_score("thievery", 1);

    // 若手腳不夠俐落，可能被旁人撞見你的窺視行徑。
    if( random(sp) < dp/2 )
	message("vision", "你看到" + me->name() + "鬼鬼祟祟地打量著"
	    + victim->name() + "。\n", environment(me), ({ me, victim }) );
}

int help(object me)
{
    write(@HELP
指令格式 : peek <某人>

這個指令讓盜賊有機會偷偷窺看他人身上帶著什麼東西，而不取走任何
物品。窺視成功時，你能看清對方的物品欄（眼力越高看得越清楚）；
若失手被發覺，對方雖會起疑，但通常不至於當場翻臉動手。

窺視的成敗取決於你的妙手空空之技、機敏、定力，以及對方的警覺力
（靈性、定力與精）。盜賊職業與焦僥一族在這方面有天生優勢；想窺
視另一名盜賊時，就看誰的功力更高了。

HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
