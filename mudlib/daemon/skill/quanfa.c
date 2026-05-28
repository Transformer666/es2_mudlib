#pragma save_binary

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉腰坐馬﹐一記直拳搶攻$n的$l",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N欺身上前﹐雙掌齊出推向$n的$l",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N腳下一錯﹐一記橫肘掃向$n的$l",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N身形一矮﹐一拳由下而上撩向$n的$l",
    "dodge":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N大喝一聲﹐右掌如風般劈向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N凌空躍起﹐一記旋踢橫掃$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N虛晃一招﹐忽然一肘頂向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N佯作後退﹐隨即一掌反撩$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N擺開拳架﹐凝神注視著$n的動靜。\n",
  "$N雙拳緩緩游走﹐尋找著進招的空隙。\n",
  "$N腳步輕移﹐拳勢蓄而不發。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("quanfa");
  setup();
}

void
attack_using (object me, object opponent, string skill)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (CYN + interattack[random(sizeof(interattack))] + NOR, me, opponent);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "quanfa", actions[random(sizeof(actions))]);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
