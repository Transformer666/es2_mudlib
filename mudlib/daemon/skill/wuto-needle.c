// 武陀灸術【五敗針法】 wuto-needle -- 武陀灸堂香主弟子的入門針法
//
// 這是一門針法(needle)技能﹐武陀灸堂一脈的根本針術。本檔比照龍圖丹派
// 的針法 daemon (amazing-needle.c) 的結構建立﹐使技能可被指派與習練。
// 基礎技能型別為 needle (針術)﹐見 feature/weapon/needle.c。中文字典已收
// 「武陀灸術【五敗針法】」一條(見 data/chinese.o)﹐故不需 add_translate。
// TODO: combat specifics -- 五敗封脈、針到病除之治療輔助、神(sen)消耗等機制。

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
    "action":		"$N欺身近前﹐一式『五敗截脈』連刺$n的$l",
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
    "action":		"$N一式『敗血封經』﹐$w自死角扎向$n的$l",
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
    "action":		"$N雙指夾針﹐一式『五敗摧心』連環點向$n的$l",
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
  DAEMON_D->register_skill_daemon("wuto-needle");
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

  damage = COMBAT_D->fight(me, opponent, "wuto-needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
