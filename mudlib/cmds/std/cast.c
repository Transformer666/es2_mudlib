

#include <skill.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string spells, spl, trg;
    object target;
        
    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() ) return notify_fail("你現在沒有空！\n");

    if( !arg ) return notify_fail("指令格式﹕cast <咒文名稱> [on <施咒對象>]\n");

    if( sscanf(arg, "%s on %s", spl, trg)==2 ) {
	target = present(trg, environment(me));
	if( !target ) target = present(trg, me);
	if( !target ) return notify_fail("這裡沒有 " + trg + "。\n");

	// add by dragoon, modified by annihilator
	if( userp(target) && !interactive(target) ) {
	     write("你不能對斷線中的人施法。\n");
	     return 1;
	}
    } else {
	spl = arg;
	target = 0;
    }

    // BUG-fix(2026-06-02 adversarial review)：原 `!target->query(...)` 在無對象
    // (cast 不帶 on)時 target==0 → 對 0 呼叫方法、一旦有 no_magic 房即 crash。
    // 加 (target && ...) 防呆；訊息亦改為 no_magic 語意。
    if( environment(me)->query("no_magic")
    && !me->is_fighting(target)
    && !(target && target->query("unprotect_mark")) ) {
	    tell_object(me, "這裡法力受制，不能施展法術。\n");
	    return 1;
    }

    spl = replace_string( spl, " ", "_");

    // BUG-fix：未 enable 時 skill_mapped("spells") 回傳原字串 "spells"，
    // SKILL_D("spells") 因無 /daemon/skill/spells.c 而 fallback 成 DAEMON_D 本體。
    // 加 `!= "spells"` 確保真已指派咒文系才派發(否則落到下方 notify_fail 提示)。
    notify_fail("你請先用 enable 指令選擇你要使用的咒文系。\n");
    if( stringp(spells = me->skill_mapped("spells")) && spells != "spells" )
	return (int)SKILL_D(spells)->cast_spell(me, spl, target);

    return 0;
}

int help (object me)
{
    write(@HELP
指令格式﹕cast <咒文名稱> [on <施咒對象>]

施展法術，你必需要指定<咒文名稱>，<施咒對象>若已處於戰門狀態則可省略。

在你使用某一個咒文之前，你必須先用 enable 指令來指定你要使用的咒文系，並
使用的該咒文系中的咒文，咒文名稱可參考 help taoism。

大多數的法術從你開始吟誦咒文，到完成法術會需要一段時間。這段時間施法者會
無法移動或攻擊。
HELP
    );
    return 1;
}

