// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "spells"; }

int valid_learn(object me)
{
    if( (int)me->query_skill("taoism") < (int)me->query_skill("necromancy") / 2 )
        return notify_fail("你的天師正道修為不夠，無法領悟更高深的茅山道術。\n");
    return 1;
}

string cast_spell_file(string spell)
{
    return CLASS_D("taoist") + "/necromancy/" + spell;
}

string scribe_spell_file(string spell)
{
    return CLASS_D("taoist") + "/necromancy/" + spell;
}

int practice_skill(object me)
{
    object bug;

    if( bug = me->query_temp("mind_bug") )
        return notify_fail("你的魂魄還沒有全部收回，趕快殺死你的"
            + bug->name() + "吧！\n");

    if( (int)me->query("mana") < 10 )
        return notify_fail("你的法力不夠。\n");

    if( (int)me->query("sen") < 30 )
        return notify_fail("你的精神無法集中。\n");

    me->add("mana", -10);
    me->receive_damage("sen", 30);

    write("你閉目凝神，神遊物外，開始修習茅山道術中的法術....\n");
    if( random((int)me->query("sen")) < 5 ) {
        int rnd;

        rnd = random(me->query_skill("spells", 1));
        if( rnd < 10 ) bug = new("/obj/npc/mind_bug");
        else           bug = new("/obj/npc/mind_beast");

        write("可是你心思一亂，變出了一隻面目猙獰的" + bug->name() + "！\n");
        bug->move(environment(me));
        bug->kill_ob(me);
        me->fight(bug);
        me->set_temp("mind_bug", bug);
        bug->set("owner", me->query("id"));
        return notify_fail("你的魂魄正被" + bug->name() + "纏住，快把它除掉吧！\n");
    }
    else return 1;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("necromancy", 1);
    learn = me->query_learn("necromancy");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺自己對茅山道術的領悟更深了一層﹗\n" NOR);
            me->advance_skill("necromancy", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("necromancy", 1);
        me->gain_score("martial art", (skill+1) * 10);
        if( skill >= 50 )
            me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("wis") < level / 3 ) {
        tell_object(me, HIW "由於你茅山道術的修練有成﹐你的悟性提高了。\n" NOR);
        me->add("wis", 1);
    }
}

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("necromancy");
    setup();
}
