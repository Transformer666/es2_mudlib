// vim: syntax=lpc

inherit F_CLEAN_UP;

void setup()
{
    seteuid(getuid());
}

string type()
{
    return "martial";
}

// Default stubs for skill daemon interface.
// Subclasses can override these to provide custom behavior.

void skill_improved(object me, string sk)
{
    // Called when a character's skill learning progress increases.
    // Override in subclass to handle level-up logic.
}

void skill_advanced(object me, string sk)
{
    // Called when a character's skill level increases.
    // Override in subclass to grant stat bonuses.
}

// Default dodge interface — returns bonus to defense counter_ability.
varargs int
dodge_using(object me, int ability, int strength, object from)
{
    return me->query_skill("dodge") / 2;
}

// Default parry interface — returns amount of strength absorbed.
varargs int
parry_using(object me, int ability, int strength, object from)
{
    int parry_skill, absorbed;

    parry_skill = me->query_skill("parry");
    absorbed = strength * parry_skill / (parry_skill + ability + 1);
    return absorbed;
}
