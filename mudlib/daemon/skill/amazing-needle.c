// 武陀灸術【驚異二針】 amazing-needle -- 龍圖丹派醫師的入門針法
//
// 這是一門針法(needle)技能﹐龍圖丹派醫師一脈的根本針術。本檔比照
// 武功招式 daemon (lunmay.c/blood_dagger.c) 的結構建立﹐使技能可被指派
// 與習練。基礎技能型別為 needle (針術)﹐見 feature/weapon/needle.c。
// TODO: combat specifics -- 點穴封脈、針到病除之治療輔助、神(sen)消耗等機制。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手腕一沉﹐$w疾點$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N指尖一彈﹐$w如銀蛇吐信扎入$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N欺身近前﹐一式『驚異二針』連刺$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝神辨穴﹐$w精準地點向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N手腕翻轉﹐$w詭異地繞向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『封脈截經』﹐$w自死角扎向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N退步藏針﹐$w凝而後發疾刺$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指夾針﹐一式『驚鴻照影』連環點向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙指夾著$w﹐針尖微顫﹐凝神辨認著$n身上的穴位﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("amazing-needle");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "amazing-needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
