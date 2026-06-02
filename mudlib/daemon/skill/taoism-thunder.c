// 天師道法【紫雷咒】 taoism-thunder -- 天師派紫衣弟子的入門雷術
//
// 這是一門法術(magic)技能﹐天師派紫衣(雷)分支的根本道法。本檔比照
// 玄衣風咒 daemon (taoism-wind.c) 的結構建立﹐使技能可被指派與習練。
// 實際的施法(cast)指令與咒術消耗(神)等機制屬未來工作。
// TODO: spell-cast wiring -- 接上 cast 指令、神(sen)消耗、法術判定。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖一道紫雷射向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N掐訣引雷﹐一道紫電轟向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N袖中紫符鼓盪﹐化作一片雷網罩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『紫府裂空』激射$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N揮手撒出一蓬雷珠﹐密密麻麻地轟向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐一道雷龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團紫雷轟向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『紫電引雷』霹靂暴鳴﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
});

string *interattack = ({
  "$N默運雷訣﹐指間隱隱透出一縷紫芒﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism-thunder");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIC + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "taoism-thunder", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "taoism-thunder"; }

mapping query_spells()
{
  return ([
    "紫雷" :     ([ "id":"zilei",   "sen":8,  "power":10, "type":"雷殛",
        "action":HIY "$N口誦真言﹐掐訣一引﹐一道紫雷脫手飛出﹐「霹」地轟向$n！" NOR ]),
    "紫府裂空" : ([ "id":"ziputie", "sen":16, "power":20, "type":"雷殛",
        "action":HIY "$N足踏罡步﹐袖中紫符鼓盪﹐一式『紫府裂空』化作雷網紫電﹐激射$n！" NOR ]),
    "紫電引雷" : ([ "id":"zidian",  "sen":30, "power":34, "type":"雷殛",
        "action":HIY "$N凝神運法﹐周身雷光暴漲﹐一式『紫電引雷』霹靂沖天暴鳴﹐當頭劈向$n！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
