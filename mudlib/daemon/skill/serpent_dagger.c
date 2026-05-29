// 金蛇匕法 serpent dagger -- 隱教聖女門下的入門匕法
//
// 這是一門匕法(dagger)技能﹐隱教金蛇門人一脈見血封喉的根本殺招。本檔
// 比照瑯夷派血魂匕法 daemon (blood_dagger.c) 的結構建立﹐使技能可被指派
// 與習練。基礎技能型別為 dagger (錐法)﹐見 feature/weapon/dagger.c。
// 金蛇匕法在中文字典尚無詞條﹐故於 create() 時以 CHINESE_D->add_translate()
// 自行登錄中文名「金蛇匕法」（比照 danei_force.c 的作法）。
// TODO: combat specifics -- 暗算/背刺加成、見血追擊、用毒、精/警覺消耗等機制。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N壓低身形﹐手中$w自下而上挑向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腕底一抖﹐$w如金蛇吐信疾刺$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足尖一錯﹐欺身近前﹐一式『毒蛇出洞』割向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形飄忽﹐$w貼著$n的$l斜斜抹過",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N手腕翻轉﹐$w如蛇盤曲詭異地繞向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一招『金蛇噬心』﹐$w自死角刺向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N退步藏鋒﹐$w凝而後發疾撩$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形一矮﹐反手一式『蛇信封喉』刺入$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N反手握著$n﹐刃光內斂﹐如金蛇蟄伏﹐靜待噬人的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("serpent dagger");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("serpent dagger", "金蛇匕法");
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

  damage = COMBAT_D->fight(me, opponent, "serpent dagger", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
