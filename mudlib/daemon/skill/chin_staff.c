// 青邪杖法 chin_staff -- 哭笑門護法的入門杖法
//
// 哭笑門護法一脈以守為攻、以久制勝(社群評分 D攻/S防/S續戰)﹐故本杖
// 法招式偏重沉穩格擋與纏鬥消耗﹐dodge 值多為正(易被閃避但自身破綻
// 亦小)﹐damage 平實而綿密。注冊名 chin_staff 與 data/chinese.o 中
// "chin_staff":"青邪杖法" 一致﹔基礎技能為 staff(杖法)。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N雙手持$w沉腰一掃﹐杖頭如鬼嘯般橫掃$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N一式『判官勾魂』﹐$w自下而上猛挑$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N腳下生根﹐$w凝而後發直搗$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N杖走中宮﹐一式『哭喪當頭』狠劈$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N身形微沉﹐$w如毒蛇吐信點向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一招『笑面索命』﹐$w盤旋著纏向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N退步穩樁﹐$w借勢一頓重砸$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N怪笑一聲﹐凌空一式『青邪伏魔』當頭壓向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
});

string *interattack = ({
  "$N雙手橫杖當胸﹐沉腰落樁﹐似哭似笑地靜待著破綻。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("chin_staff");
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

  damage = COMBAT_D->fight(me, opponent, "chin_staff", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
