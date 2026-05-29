// 茅山咒術【幽冥三箭】 youmin -- 茅山派弟子的入門攻擊咒術
//
// 這是一門法術(magic)技能﹐茅山派召役幽冥之氣傷敵的根本咒術。本檔
// 比照天師派 daemon/skill/taoism-fire.c 的結構建立﹐使技能可被指派
// 與習練。實際的施法(cast)指令與咒術消耗(神)等機制屬未來工作。
// TODO: spell-cast wiring -- 接上 cast 指令、神(sen)消耗、法術判定。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖凝起一點幽光﹐化作一箭射向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"幽冥之氣"
  ]),
  ([
    "action":		"$N掐訣引魂﹐一道幽冥之箭破空射向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"幽冥之氣"
  ]),
  ([
    "action":		"$N袖中黃符燃起﹐化作三道幽箭齊射$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"幽冥之氣"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『幽冥三箭』連珠射向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"幽冥之氣"
  ]),
  ([
    "action":		"$N揮手撒出一蓬幽火﹐密密麻麻地射向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"幽冥之氣"
  ]),
  ([
    "action":		"$N足踏罡步﹐一道幽冥之氣盤旋著激射$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"幽冥之氣"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團幽光轟向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"幽冥之氣"
  ]),
  ([
    "action":		"$N雙指一彈﹐一式『九幽奪魄』三道幽箭破空攢射$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"幽冥之氣"
  ]),
});

string *interattack = ({
  "$N默運幽冥咒訣﹐指間隱隱透出一縷幽光﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("youmin");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (MAG + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "youmin", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
