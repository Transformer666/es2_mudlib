// 天師道法【火術】 taoism-fire -- 天師派朱衣弟子的入門火術
//
// 這是一門法術(magic)技能﹐天師派朱衣(火)分支的根本道法。本檔目前
// 比照武功招式 daemon (sword.c/lunmay.c) 的結構建立﹐使技能可被指派
// 與習練。實際的施法(cast)指令與咒術消耗(神)等機制屬未來工作。
// TODO: spell-cast wiring -- 接上 cast 指令、神(sen)消耗、法術判定。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖一點火星撲向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N掐訣引火﹐一道火舌捲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N袖中朱符燃起﹐化作一團赤焰罩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『離火燎原』噴向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N揮手撒出一蓬火星﹐密密麻麻地落向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐一道火龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團火球轟向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『朱雀焚天』烈焰沖天而起﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
});

string *interattack = ({
  "$N默運火訣﹐指間隱隱透出一縷赤芒﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism-fire");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (RED + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "taoism-fire", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "taoism-fire"; }

mapping query_spells()
{
  return ([
    "火球" :     ([ "id":"huoqiu", "sen":8,  "power":10, "type":"灼傷",
        "action":HIR "$N口誦真言﹐掐訣一引﹐一團赤紅的火球脫手飛出﹐「轟」地罩向$n！" NOR ]),
    "離火" :     ([ "id":"lihuo",  "sen":16, "power":20, "type":"灼傷",
        "action":HIR "$N足踏罡步﹐袖中朱符燃起﹐一式『離火燎原』化作火舌烈焰﹐席捲$n！" NOR ]),
    "朱雀焚天" : ([ "id":"zhuque", "sen":30, "power":34, "type":"灼傷",
        "action":HIR "$N凝神運法﹐周身真火暴漲﹐一式『朱雀焚天』赤焰沖天而起﹐當頭澆向$n！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
