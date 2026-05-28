// 龍神槍法 dragon god -- 振武軍營軍隊統領的入門槍法（基礎技能 pike）

#include <ansi.h>

inherit SKILL;

// TODO: 招式攻防數值待平衡（dodge / damage / damage_type），目前比照 lunmay 模板。
mapping *actions = ({
  ([
    "action":		"$N沉腰坐馬﹐手中$w平端而出﹐一式『神龍出海』直搠$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N大喝一聲﹐$w化作一道寒芒﹐當頭橫掃$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N雙臂一振﹐一招『龍翔九天』﹐$w自下而上挑向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N前腳一蹬﹐$w如怒龍翻江﹐連環疾刺$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N槍尖一抖﹐幻出點點槍花﹐儘數罩向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『神龍擺尾』﹐$w橫掃千軍﹐反掄向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N斜跨一步﹐$w凝而後發﹐一槍貫向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足下生風﹐一式『龍神問天』縱身刺向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N長槍斜指﹐槍尖微沉﹐如蟄龍待動﹐凝神靜待破綻。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("dragon god");
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

  damage = COMBAT_D->fight(me, opponent, "dragon god", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
