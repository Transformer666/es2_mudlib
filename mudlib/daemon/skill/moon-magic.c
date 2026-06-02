// 太陰秘法 moon magic -- 天月庵神尼門下的入門法術
//
// 這是一門法術(magic)技能﹐天月庵以太陰(月)之力濟世度人、治療控制的
// 根本道法。本檔比照天師派【紫雷咒】daemon (daemon/skill/taoism-thunder.c)
// 與【玄風咒】(taoism-wind.c) 的結構建立﹐使技能可被指派與習練﹐並透過
// map_skill("magic","moon magic") 對應月法施展。
//
// 玩家透過 map_skill("magic","moon magic") 將法術對應到本秘法後﹐戰鬥時
// 即以太陰秘法的招式出手﹐由 COMBAT_D->fight() 結算傷害。
//
// 太陰秘法本以治療(heal)與控制(沉睡、冰封)為主旨（見 docs/03-門派與武功/
// 03-和尚-寶蓮天月白象.md §天月庵﹕治療/控制玩法）﹐然此類 cast 特殊功能
// （群補 link/link2、坐禪 zazengo、conjure 等）尚未接線﹐故本 daemon 暫
// 比照天師道法 daemon﹐先以攻擊招式表(actions)提供基本戰鬥能力。
//
// TODO: spell-cast wiring -- 接上 cast 指令、神(sen)消耗與法術判定。
// TODO: heal/control specials -- 太陰秘法的療傷、群補(link/link2)、控制
//       (沉睡/冰封)等核心特殊功能待日後設計平衡並接線。
// TODO: 月法理應另登錄中文名「太陰秘法」﹐惟字典 key 是否已收錄待查﹔
//       若 to_chinese("moon magic") 無詞條﹐可比照 baolian_force.c 以
//       CHINESE_D->add_translate("moon magic", "太陰秘法") 自行登錄。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N纖手結印﹐一縷清冷的太陰真氣如月華般漫向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N口誦月華真言﹐一道銀芒悄無聲息地點向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N素手輕揚﹐一片清寒月光如水般籠罩$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『太陰寒月』森森地激射$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N掐訣引月﹐一團清冷的太陰之氣盤旋著撲向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N默運秘法﹐指尖月華流轉﹐化作千點寒星灑向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一輪清冷的虛月緩緩壓向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N雙掌一合﹐一式『太陰七損』月華暴湧﹐森寒地席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
});

string *interattack = ({
  "$N默運太陰秘法﹐指間隱隱透出一縷清冷的銀芒﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("moon magic");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIW + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "moon magic", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "moon magic"; }

mapping query_spells()
{
  return ([
    "月華" :     ([ "id":"yuehua",  "sen":8,  "power":10, "type":"陰寒",
        "action":HIW "$N纖手結印﹐口誦月華真言﹐一道清冷銀芒悄無聲息地點向$n！" NOR ]),
    "太陰寒月" : ([ "id":"taiyin",  "sen":16, "power":20, "type":"陰寒",
        "action":HIW "$N凝神運法﹐素手輕揚﹐一式『太陰寒月』化作森森月華寒光﹐如水籠罩$n！" NOR ]),
    "太陰七損" : ([ "id":"qisun",   "sen":30, "power":34, "type":"陰寒",
        "action":HIW "$N雙掌一合﹐周身月華暴湧﹐一式『太陰七損』清輝沖天暴漲﹐森寒地席捲$n！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
