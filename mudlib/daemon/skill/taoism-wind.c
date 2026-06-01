// 天師道法【罡風咒】 taoism-wind -- 天師派玄衣弟子的入門風術
//
// 這是一門法術(magic)技能﹐天師派玄衣(風)分支的根本道法。本檔比照
// 素衣冰咒 daemon (taoism-freeze.c) 的結構建立﹐使技能可被指派與習練。
// 實際的施法(cast)指令與咒術消耗(神)等機制屬未來工作。
// TODO: spell-cast wiring -- 接上 cast 指令、神(sen)消耗、法術判定。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖一捲罡風射向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N掐訣引風﹐一道罡氣捲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N袖中玄符鼓盪﹐化作一片風刃罩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『玄風裂脈』激射$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N揮手撒出一蓬風絮﹐密密麻麻地捲向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐一道風龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團罡風轟向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『青龍御風』狂飆暴卷﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
});

string *interattack = ({
  "$N默運風訣﹐指間隱隱透出一縷罡芒﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism-wind");
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

  damage = COMBAT_D->fight(me, opponent, "taoism-wind", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
