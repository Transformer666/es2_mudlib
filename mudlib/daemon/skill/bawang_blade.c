// 霸王刀招 bawang blade -- 虎刀門護衛的入門刀法
//
// 虎刀一脈以快、狠、決為宗(門主講究刀要快、人要狠)﹐故本刀法招式
// 偏重剛猛搶攻與一往無前的撲殺﹐dodge 值多為負(破綻較大但刀勢凌
// 厲難擋)﹐damage 沉重。注冊名 bawang blade 與 data/chinese.o 中
// "bawang blade":"霸王刀招" 一致﹔基礎技能為 blade(刀法)。
//
// 本檔比照封山劍法(fonxansword.c)、大內劍法(danei_sword.c)樣板撰寫﹐
// 只是基礎兵器由 sword 改為 blade(虎刀門慣用厚背快刀﹐見
// obj/area/obj/blade.c 單刀)﹐damage_type 多取砍傷/割傷以合刀法。
//
// TODO: 招式攻防數值待平衡(dodge / damage / damage_type)﹐目前比照
//       fonxansword / danei_sword 模板。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N大喝一聲﹐手中$w當頭一刀﹐勢若虎撲般狠劈$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N腳下一個箭步﹐一式『猛虎出柙』﹐$w橫掃$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N沉腕翻刀﹐$w化作一片血光﹐連環疾斬$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N一招『霸王卸甲』﹐$w自下撩起﹐狠狠豁向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N欺身搶進﹐$w以雷霆萬鈞之勢力劈$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N刀走偏鋒﹐一式『嘯林斷木』斜削$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N橫刀一引﹐借勢一招『力拔山兮』﹐$w反撩$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N縱身而起﹐一式『餓虎攫食』﹐$w凌空猛劈$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
});

string *interattack = ({
  "$N橫刀於胸﹐刀尖斜指﹐殺氣如猛虎蓄勢﹐只待破綻一現便要撲殺。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("bawang blade");
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

  damage = COMBAT_D->fight(me, opponent, "bawang blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
