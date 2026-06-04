/*
 *  Package: Study
 *  Summary: Studying and learning from objects.
 */

#include <ansi.h>
#include <dbase.h>
#include <name.h>

int study_content(object me);
int halt_study(object me, object from, string how);
void enlighten_int(object me);

int study_ob(object me)
{
    mapping req, content;
    string t, msg;
    int min, max, to_learn = 0;

    if( this_player()->is_busy() )
	return notify_fail("你正忙著其他事呢！\n");
    if( this_player()->is_fighting() )
	return notify_fail("你還是先應付眼前的敵人吧！\n");
    req = query("required/attribute");
    if( mapp(req) ) {
	foreach(t, min in req)
	    if( this_player()->query_attr(t, 1) < min ) {
		write("你的" + to_chinese(t) + "不夠，所以對這上面記載的"
			"內容完全無法體會。\n");
		return 1;
	    }
    }
    req = query("required/skill");
    if( mapp(req) ) {
	foreach(t, min in req)
	    if( this_player()->query_skill(t, 1) < min ) {
		write("你在" + to_chinese(t) + "上的造詣還不夠理解這上面所記載的內容。\n");
		return 1;
	    }
    }


    content = query("content");
    if( !content )
	return notify_fail("這上面沒有記載什麼有用的內容。\n");

    foreach(t, max in content)
	if( this_player()->query_skill(t, 1) < max ) to_learn++;
    if( ! to_learn ) {
	write("這上面記載的內容對你而言都了無新意 ...。\n");
	return 1;
    }

    this_player()->start_busy((: study_content :), (: halt_study :));
    if( stringp(msg = query("study_msg")) )
	message_vision(msg, this_player());
    else
	message_vision("$N開始聚精會神地研讀" + name() + "上面的內容。\n",
		this_player());

    return 1;    
}

int study_content(object me)
{
    mapping content;
    int skill, archaism, cost, max, point, gain = 0;
    string t;

    if( ! mapp(content = query("content"))
    ||	! sizeof(content) ) return 0;


    skill = me->query_skill("literate");


    cost = 1 + (9 - me->query_attr("wis")/3);
    if( cost < 1 ) cost = 1;


    if( (archaism = query("required/skill/archaic attainment")) ) {
	skill = skill/10 + me->query_skill("archaic attainment");
	cost *= 2;
    }

    if( me->query_stat("sen") < cost
    ||	me->query_stat("gin") < cost
    ||	(me->query_stat_maximum("fatigue") > 0 && me->query_stat("fatigue") >= me->query_stat_maximum("fatigue")) ) {
	// 玩家角色的 fatigue 由 /adm/daemons/chard.c::setup_char 初始化(max 100、
	// current 0、TYPE_WASTING 隨時間遞減)，故此處 query_stat_maximum>0 為真、
	// 疲勞達上限即中斷研讀——符合 cmds/std/study.c help 所述機制。
	// 對未設 fatigue 的實體(NPC/測試物件) max 為 0，跳過此閘、改由 gin/sen 消耗節制，
	// 避免「max 恆 0 → 0>=0」在第一拍誤判精神不繼而永遠學不到。
	tell_object(me, "你覺得精神不繼，無法再繼續研讀了。\n");
	return 0;
    }

    me->consume_stat("gin", cost);
    me->consume_stat("sen", cost);

    point = me->query_attr("int") / sizeof(content);
    foreach(t, max in content) {
	if( max > skill ) max = skill;	
	if( me->query_skill(t, 1) < content[t]
	&&  random( point + skill ) >= max/2 ) {
	    me->improve_skill(t, 1 + random(point));
	    gain++;
	}
    }

    if( gain ) {
	me->improve_skill("literate", 1 + random(me->query_attr("int")));
	if( archaism )
	    me->improve_skill("archaic attainment",
		1 + random(me->query_attr("int")));
	me->supplement_stat("fatigue", gain);
	me->damage_stat("sen", gain);

	// 悟性書：blueprint 以 set("enlighten/int", 上限) 標示(鏡 content 的
	// skill→上限 範式、用 required/skill/... 同款巢狀路徑)。一般書無此欄、
	// query 回 0 → 整段跳過，不影響既有書本。docs 06「書本系統」L116-118:
	// 悟性書提升悟性(int)。每次成功研讀有機會 +1，越高越難、且不得超過書的上限。
	enlighten_int(me);
    }

    return 1;
}

// enlighten_int()
//
// 悟性書研讀時嘗試提升「悟性」(int) 屬性。
//   * 觸發條件：本拍 study 確實有 gain(學到東西)，純掛機不長悟性。
//   * 上限：min(書的 enlighten/int, ATTRVAL_MAX=50)。set_attr 對玩家本就拒絕
//     >50 的值(見 feature/attribute.c)，故雙重保險、絕不無限增長。
//   * 機率：越接近(或超過)上限越不易成長；每次至多 +1(鏡 humanoid.c
//     advance_level 升屬性的 +1 範式)，不會一次暴漲。
void enlighten_int(object me)
{
    int cap, cur;

    if( (cap = query("enlighten/int")) <= 0 ) return;	// 非悟性書
    if( cap > 50 ) cap = 50;				// 對齊 ATTRVAL_MAX

    cur = me->query_attr("int", 1);			// 取未受 apply 影響的本值
    if( cur >= cap ) return;				// 已達(或超過)此書能教的上限

    // 成功率隨悟性升高而下降：random(cur) < (cap-cur) 時成長。
    // 例：cur 低於 cap 越多越易成；cur 接近 cap 時機率趨近 0。
    if( random(cur + 1) < cap - cur ) {
	if( me->set_attr("int", cur + 1) ) {		// set_attr 回 0 代表被夾住/未初始化
	    tell_object(me, HIW "你福至心靈，似乎對許多事情的領悟又深了一層！\n" NOR);
	}
    }
}

int halt_study(object me, object from, string how)
{
	string msg;
	if( stringp( msg = query("halt_msg") ) ) 
		write( msg );
	else
		write("你停止研讀" + name() + "上面記載的內容。\n");
		return 1;
}

// vim: set ts=4 sw=4 syntax=lpc

