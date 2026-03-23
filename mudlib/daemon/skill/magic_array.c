// vim: syntax=lpc
// magic_array.c - 奇門遁甲

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("magic array");
    setup();
}

int valid_enable(string usage)
{
    return usage == "spells";
}

int valid_learn(object me)
{
    if( (int)me->query_skill("tao mystery") <= (int)me->query_skill("magic array") )
        return notify_fail("你的小天魔道修為不夠，無法領悟更高深的奇門遁甲之術。\n");
    return 1;
}

string cast_spell_file(string spell)
{
    return CLASS_D("juechen") + "/magic-array/" + spell;
}

int practice_skill(object me)
{
    return notify_fail("法術類技能必須用學的或是從實戰中獲取經驗。\n");
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("magic array", 1);
    learn = me->query_learn("magic array");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺自己對奇門遁甲的領悟更深了一層﹗\n" NOR);
            me->advance_skill("magic array", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("magic array", 1);
        me->gain_score("martial art", (skill+1) * 10);
        if( skill >= 50 )
            me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("int") < level / 3 ) {
        tell_object(me, HIW "由於你奇門遁甲的修練有成﹐你的悟性提高了。\n" NOR);
        me->add("int", 1);
    }
}
