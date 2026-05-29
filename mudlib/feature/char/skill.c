

#include <ansi.h>
#include <dbase.h>
#include <skill.h>

mapping skills          = ([]);         // The level of skills.
mapping learned         = ([]);         // The learning progress of skills.
mapping skill_map       = ([]);         // The links of mapped skill.
mapping skill_flag      = ([]);         // Ultra skill flags.

string best_skill = "";

// implementations

string query_best_skill()
{
    return best_skill;
}

mapping query_skills()
{
    if( previous_object() && geteuid(previous_object()) != ROOT_UID )
	return copy(skills);
    return skills;
}

mapping query_skill_flags()
{
    if( previous_object() && geteuid(previous_object()) != ROOT_UID )
	return copy(skill_flag);
    return skill_flag;
}

mapping query_learned()
{
    if( previous_object() && geteuid(previous_object()) != ROOT_UID )
	return copy(learned);
    return learned;
}

mapping query_skill_map()
{
    if( previous_object() && geteuid(previous_object()) != ROOT_UID )
	return copy(skill_map);
    return skill_map;
}

// set_skill()
//
// Sets the level of specific skill.
// Note that currently this function doesnot do any security check.
// Security check could be added in the future.

void set_skill(string skill, int val)
{
    if( val > 200 ) val = 200;
    skills[skill] = val;
}

int set_learn(string skill, int lrn)
{
    return learned[skill] = lrn;
}

// delete_skill()
//
// This function deletes a skill completely, including its learning progress
// and mapped reference.

int delete_skill(string skill)
{
    string s1, s2;

    map_delete(skills, skill);
    map_delete(learned, skill);
    foreach(s1, s2 in skill_map)
	if( s2==skill ) map_delete(skill_map, s1);

    return 1;
}

// map_skill()
//
// This function maps a skill to another. If no mapped_to specificed, or
// map one skill to itself, the skill is unmapped. If mapped_to is "none",
// the skill is 'disabled' that query_skill() always return 0 upon querying
// this skill.

varargs void map_skill(string skill, string mapped_to)
{
    if( !mapped_to ) {
	map_delete(skill_map, skill);
	return;
    }

    if( mapped_to=="none" ) skill_map[skill] = 0;
    else if( mapped_to==skill ) map_delete(skill_map, skill);
    else skill_map[skill] = mapped_to;
}

// skill_mapped()
//
// Return the skill name which the specific skill is mapped to. If the
// skill is not mapped, the name of the skill is returned.

string skill_mapped(string skill)
{
    return !undefinedp(skill_map[skill]) ? skill_map[skill] : skill;
}

// query_skill()
//
// Return the level of a skill. If the skill is mapped, the AVERAGE of
// original skill and mapped skill is return. If the skill is mapped to
// 0, (i.e. the skill is disabled, see map_skill()), 0 is returned.
varargs int query_skill(string skill, int raw)
{
    int s;

    if( raw ) return skills[skill];

    s = query_temp("apply/" + skill);
    if( undefinedp(skill_map[skill]) ) s += skills[skill];
    else {
	if( skill_map[skill]==0 ) return 0;
	s += (skills[skill] + query_skill(skill_map[skill]) ) / 2;
    }
    return (s > 200) ? 200 : s;
}

int query_learn(string skill)
{
    return learned[skill];
}

// skill gain:
//
// This mapping registers every improve_skill from last reset_skill_gain()
// till now.
static mapping skill_gain = ([]);

mapping query_skill_gain() { return skill_gain; }
void reset_skill_gain() { skill_gain = ([]); }

// improve_skill()
//
// This function improves the skill by adding specific amount to its
// learning progress.

varargs void
improve_skill(string skill, int amount)
{
    if( skill_flag[skill] & SKILL_FLAG_ABANDONED ) return;

    if( !amount ) amount = 1;

    // Level bonus for skill improvement.
    amount += amount * random(this_object()->query_level() / 8);

    if( undefinedp(learned[skill]) ) learned[skill] = amount;
    else learned[skill] += amount;

    if( undefinedp(skill_gain[skill]) ) skill_gain[skill] = amount;
    else skill_gain[skill] += amount;

    if( undefinedp(skills[skill]) ) skills[skill] = 0;

    SKILL_D(skill)->skill_improved(this_object(), skill);

    // --- 學習進度(learned) → 技能等級(skills) 轉換（依 docs/02-03 重建）---
    // 原開源 mudlib 缺此轉換：base /std/skill 無 skill_improved、亦無練功指令，
    // 故 study/戰鬥只會累積 learned[]，技能等級永不上升。依「技能天賦」設計補上：
    //   * 每個技能有 140~200 的天賦(潛能)上限，首次習得時隨機決定（算命仙可揭示）。
    //   * learned 為累積值；跨過門檻 (等級+1)^2 即升一級，封頂於天賦。
    //   * 拜師 set_skill 直接給的高等級不受影響（只 ++、不 --；要再自習超越得大量 learned）。
    {
        int talent, lvl;

        talent = query("talent/" + skill);
        if( !talent ) {
            talent = 140 + random(61);              // 140 ~ 200
            set("talent/" + skill, talent);
        }

        lvl = skills[skill];
        while( lvl < talent && learned[skill] >= (lvl+1)*(lvl+1) )
            lvl++;
        if( lvl > skills[skill] ) {
            skills[skill] = lvl;                    // 直接升等（advance_skill 在本檔後段定義，避免前向參考）
            if( skills[skill] > skills[best_skill] ) best_skill = skill;
        }
    }
}

// 查詢某技能的天賦(潛能)上限（140~200；尚未習得回 0）。供算命等用。
int query_talent(string skill)
{
    return query("talent/" + skill);
}

// advance_skill()
//
// This function advances the level of a skill by adding specific amount
// to the skill level.

varargs void advance_skill(string skill, int amount)
{
    if( !amount ) amount = 1;

    if( undefinedp(skills[skill]) )
	skills[skill] = amount;
    else
	skills[skill] += amount;

    if( skills[skill] > 200 ) skills[skill] = 200;

    SKILL_D(skill)->skill_advanced(this_object(), skill);

    if( skills[skill] > skills[best_skill] ) best_skill = skill;
}

// abandon_skill()
//
// This function toggles abandon flag of specific skill.

varargs void abandon_skill(string skill, int restore)
{
    if( undefinedp(learned[skill]) ) return;

    if( restore ) skill_flag[skill] &= (~SKILL_FLAG_ABANDONED);
    else	  skill_flag[skill] |= SKILL_FLAG_ABANDONED;

    if( !skill_flag[skill] ) map_delete(skill_flag, skill);
}

int query_skill_map_num()
{
    mapping my_skill_map;
    mixed *levels;

    my_skill_map = this_object()->query_skill_map();
    if( !mapp(my_skill_map) ) return 0;
    levels = values(my_skill_map);
    levels -= ({ 0 });
    return sizeof(levels);
}

