// 紫薇心經 chivi sutra -- 振武軍營「軍師」進階(二轉)所授的內功(基底 FORCE)
//
// docs 載振武軍營軍師一脈「天風道長任務可學紫薇心經與法術」(見 docs/03-門派與武功/
// 06-軍人-振武大內.md §進階-軍師)。本檔將紫薇心經實作為一門內功心法(force)﹐使軍師
// 施法/施術時力道與法力能隨內功成長﹐並借 FORCE(/std/force.c)提供的打坐修煉 +
// valid_enable 共用機制﹔本檔只註冊心法名、登錄中文名、並 override cultivate_msg()
// 提供軍師自家的打坐氣象。
//
// 中文名「紫薇心經」於 data/chinese.o 已有對應 key "chivi sutra":"紫薇心經"﹐故本檔
// 沿用該 romanization "chivi sutra"(含空白﹐故檔名以連字號代之 chivi-sutra.c﹐
// register/translate 用的 key 仍為含空白原名)﹐add_translate 僅作備援(字典已有則覆寫
// 同值﹐無害)。
//
// 設計(docs 原值)：docs 軍師習紫薇心經之條件為「天風道長任務」﹐屬尚未接的任務門檻﹔
//   為與本批進階一致(只 gate level/skill/attr)﹐其達標查驗由 master.c::do_advance 以
//   入門火候 + 屬性門檻替代﹐天風道長任務標記為待接的故事門檻 TODO。
//
// === 元素防禦 + 解效果(docs/03-門派與武功/02-道士-天師與茅山.md L41-45) ===
// docs 紫薇心經載：lv 15、`fire/storm/freeze/thunder defence` 短時提防、`dispel` 強解。
// 派發走 exert(本檔為 force-slot 內功﹐cmds/std/exert.c 以 skill_mapped("force") 派
// 至本門 exert_function)。玩家鍵入：
//   exert fire     -> 火防 ﹔ exert storm -> 風防(docs 用 storm 表風) ﹔
//   exert freeze   -> 冰防 ﹔ exert thunder -> 雷防 ﹔ exert dispel -> 解元素效果。
// 提防實作：暫時 add_temp("apply/<elem>_def", N)(/std/magic.c::magic_element_resist 讀
//   apply/<elem>_def 折算元素魔法傷害)﹐call_out 到期以 add_temp(-N) 抵銷復原(鏡
//   strategy.c::do_wis/end_wis、royal_force.c::rf_end_royal﹐**不可 delete_temp**﹐
//   以保住其他來源同鍵增減)。dispel：把本門「正在生效」的四防一次抵銷清掉。
// 元素鍵 fire/freeze/wind/thunder 對齊 /std/magic.c 引擎標頭(L35)﹔docs 的 storm 對應
//   引擎 wind 鍵(故 apply/wind_def)。本檔 inherit FORCE﹐不便繼承 magic 引擎﹐故元素防
//   buff 以本門自有 add_temp + call_out 自足實作(與引擎同鍵 apply/<elem>_def﹐可被
//   /std/magic.c::magic_element_damage 讀到)﹐不臆造跨繼承呼叫。

#include <ansi.h>

inherit FORCE;

// === 元素防禦/解效果參數(docs：lv 15、短時提防)。集中於此便於調校。===
#define CS_MIN_LEVEL    15      // 提防門檻：等級下限(docs L43 lv 15)。
#define CS_DEF_SEN      20      // 每式提防耗神(sen)。
#define CS_DEF_BUFF     30      // 提防加成：apply/<elem>_def 百分點。
#define CS_DEF_DURATION 30      // 提防持續秒數(call_out 以秒計)。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯 Undefined
//   function﹐進而 daemon lazy-load 靜默失敗、exert 指令靜默回 0)。
varargs int exert_function(object me, string func, object target);
private int  cs_gate(object me);
private int  cs_defence(object me, string elem, string cname);
int          cs_dispel(object me);
void         cs_defence_end(object me, string elem, int amt);

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("chivi sutra");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示(字典已有則覆寫同值)。
	CHINESE_D->add_translate("chivi sutra", "紫薇心經");
	setup();
}

// 振武軍師打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIM "$N斂神靜坐﹐緩緩運轉紫薇心經﹐周身似有一股紫氣自百會垂落、繞身周流﹐"
	           "如帝星臨頂、星河環身﹐心神為之清明﹐法力亦隨之溫養綿長。\n" NOR;
}

// 提防/解效果共用門檻：須等級達標(docs L43 lv 15)。
private int
cs_gate(object me)
{
	if( me->query_level() < CS_MIN_LEVEL )
		return notify_fail(sprintf(
			"你紫薇心經火候未到(需等級 %d)﹐運不起這護身的元素法門。\n",
			CS_MIN_LEVEL));
	return 1;
}

// 短時提某元素之防：暫時 add_temp("apply/<elem>_def", N)﹐到期 add_temp(-N) 復原。
// elem 為引擎鍵(fire/freeze/wind/thunder)﹐cname 為顯示中文(火/冰/風/雷)。
private int
cs_defence(object me, string elem, string cname)
{
	if( !cs_gate(me) ) return 0;

	// 同一元素之本門提防尚在身上時不重複疊加(避免無限延長)。
	if( me->query_temp("chivi_def_" + elem) )
		return notify_fail(sprintf("你周身那層紫薇%s防護之氣尚未消退。\n", cname));

	if( me->query_stat_current("sen") < CS_DEF_SEN )
		return notify_fail("你神識不足﹐運不起這護身的元素法門。\n");

	me->consume_stat("sen", CS_DEF_SEN, me);

	me->set_temp("chivi_def_" + elem, CS_DEF_BUFF);
	me->add_temp("apply/" + elem + "_def", CS_DEF_BUFF);
	me->set_temp("chivi_def_callout_" + elem,
		call_out("cs_defence_end", CS_DEF_DURATION, me, elem, CS_DEF_BUFF));

	message_vision(HIM
		"$N斂神誦經﹐周身紫氣垂落凝成一層瑩瑩光暈﹐隱隱透出護身的氣機。\n" NOR, me);
	tell_object(me, sprintf(HIM
		"你運轉紫薇心經﹐周身%s防之氣大盛。(消 sen %d﹐持續 %d 秒)\n" NOR,
		cname, CS_DEF_SEN, CS_DEF_DURATION));
	me->start_busy(1);
	return 1;
}

// 提防到期：把先前加的量「減回去」並清旗標。用 add_temp(-amt)﹐不可 delete_temp。
void
cs_defence_end(object me, string elem, int amt)
{
	if( !objectp(me) || !stringp(elem) ) return;
	me->add_temp("apply/" + elem + "_def", -amt);
	me->delete_temp("chivi_def_" + elem);
	me->delete_temp("chivi_def_callout_" + elem);
	tell_object(me, NOR "你周身那層紫薇護身的元素之氣漸漸消退了。\n");
}

// dispel 強解：把本門四元素提防一次抵銷清掉(docs L45 `dispel` 強解)。
// 僅清本門以 chivi_def_<elem> 標記的增減﹐並以「本玩家專屬的 call_out handle」取消
// 未到期回呼(remove_call_out_by_handle﹐見 neolith call_out.c:316)﹐避免用
// remove_call_out("cs_defence_end") 誤刪本 daemon(singleton)替其他玩家排的同名回呼。
// 取消回呼後手動 add_temp(-amt) 抵銷﹐不動其他來源(雨師妾被動、桃山密籙 debuff)同鍵增減。
int
cs_dispel(object me)
{
	int amt, n, h;
	string elem;

	if( !cs_gate(me) ) return 0;

	foreach( elem in ({ "fire", "freeze", "wind", "thunder" }) ) {
		amt = me->query_temp("chivi_def_" + elem);
		if( amt <= 0 ) continue;
		h = me->query_temp("chivi_def_callout_" + elem);
		if( h > 0 ) remove_call_out(h);   // 依 handle 取消本玩家專屬回呼
		me->add_temp("apply/" + elem + "_def", -amt);
		me->delete_temp("chivi_def_" + elem);
		me->delete_temp("chivi_def_callout_" + elem);
		n++;
	}

	if( !n )
		return notify_fail("你周身並沒有正在運轉的紫薇元素護身之氣可解。\n");

	message_vision(HIM
		"$N掐訣輕喝﹐周身那層瑩瑩紫氣應聲潰散﹐護身的元素法門盡數收去。\n" NOR, me);
	tell_object(me, sprintf(HIM "你以紫薇心經強解了 %d 道元素護身之氣。\n" NOR, n));
	me->start_busy(1);
	return 1;
}

// exert fire/storm/freeze/thunder/dispel -- 紫薇心經元素防 + 強解(docs L41-45)。
// 其餘 func(含 "chivi sutra" 本身)落回 FORCE 基底(打坐修煉 / notify_fail)。
varargs int exert_function(object me, string func, object target)
{
	if( !objectp(me) ) me = this_player();
	if( !objectp(me) ) return 0;

	switch( func ) {
	case "fire":    return cs_defence(me, "fire",    "火");
	case "storm":   return cs_defence(me, "wind",    "風");  // docs 以 storm 表風
	case "freeze":  return cs_defence(me, "freeze",  "冰");
	case "thunder": return cs_defence(me, "thunder", "雷");
	case "dispel":  return cs_dispel(me);
	}

	return ::exert_function(me, func, target);
}

// vim: set ts=4 sw=4 syntax=lpc
