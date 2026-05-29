// 封山劍法 fonxansword -- 封山派劍客的入門劍法
//
// 封山一脈以守為先、以正禦邪(掌門講究守山、守正、守心)﹐故本劍法
// 招式偏重沉穩封守與後發制人﹐dodge 值多為正(易被閃避但自身破綻亦
// 小)﹐damage 平實而綿密。注冊名 fonxansword 與 data/chinese.o 中
// "fonxansword":"封山劍法" 一致﹔基礎技能為 sword(劍法)。
//
// 本檔比照冷梅劍法(lunmay.c)、青邪杖法(chin_staff.c)樣板撰寫。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉腕端劍﹐$w如山勢般穩穩封向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腳下生根﹐一式『青嶂橫雲』橫掃$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N凝劍不動﹐待$n稍露破綻﹐$w後發先至直刺$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一招『封山鎖嶺』﹐$w層層遞進逼向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形微沉﹐$w如松針吐翠點向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N退步穩樁﹐借勢一式『靜水深流』斜削$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一招『以正禦邪』﹐$w堂堂正正當頭壓向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N足尖一點﹐凌空一式『嶽峙淵渟』斬向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐沉腰落樁﹐穩如青嶂﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("fonxansword");
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

  damage = COMBAT_D->fight(me, opponent, "fonxansword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
