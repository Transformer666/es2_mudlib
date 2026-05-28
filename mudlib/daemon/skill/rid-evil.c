// 金剛伏魔杖法 rid-evil -- 白象寺羅漢弟子的入門杖法
//
// 這是一門杖(staff)武功招式﹐白象寺羅漢(攻)分支的根本攻擊杖法。本檔
// 比照武功招式 daemon (lunmay.c/taoism-fire.c) 的結構建立﹐使技能可被
// 指派與習練﹐並透過 map_skill("staff","rid-evil") 對應禪杖招式。
// 招式以禪杖($w)施展﹐借佛門金剛之力降魔伏邪。
// TODO: combat specifics -- dodge/damage 數值與招式平衡待實戰調校。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手中$w一橫﹐一式『金剛起手』當頭壓向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N沉腰運力﹐$w如怒龍出海橫掃$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N大喝一聲﹐一式『伏魔降世』狠狠搗向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N腳踏蓮花步﹐$w盤旋而下劈向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N雙手持杖﹐$w直挺挺點向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N默誦佛號﹐一式『普渡眾生』$w橫掃千軍捲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N後退半步﹐$w凝而後發猛擊$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N寶相莊嚴﹐一式『金剛伏魔』$w攜千鈞之勢轟向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
});

string *interattack = ({
  "$N雙手橫持禪杖﹐口誦佛號﹐寶相莊嚴﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("rid-evil");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (YEL + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "rid-evil", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
