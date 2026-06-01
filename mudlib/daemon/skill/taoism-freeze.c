// 天師道法【冰咒】 taoism-freeze -- 天師派素衣弟子的入門冰術
//
// 這是一門法術(magic)技能﹐天師派素衣(冰)分支的根本道法。本檔比照
// 朱衣火術 daemon (taoism-fire.c) 的結構建立﹐使技能可被指派與習練。
// 實際的施法(cast)指令與咒術消耗(神)等機制屬未來工作。
// TODO: spell-cast wiring -- 接上 cast 指令、神(sen)消耗、法術判定。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖一點寒星射向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N掐訣引冰﹐一道寒流捲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N袖中素符凝霜﹐化作一片冰晶罩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『玄冰封脈』激射$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N揮手撒出一蓬冰屑﹐密密麻麻地落向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐一道冰龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團寒珠轟向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『玄武凝寒』霜華暴卷﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
});

string *interattack = ({
  "$N默運冰訣﹐指間隱隱透出一縷寒芒﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism-freeze");
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

  damage = COMBAT_D->fight(me, opponent, "taoism-freeze", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
