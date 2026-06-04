// 玄天劍訣 xuantian-jue -- 玄天教散人(二轉)的進階劍法(基礎技能 sword)
//
// 玄天教書生一脈以文心參武道、料敵機先﹐玄天劍訣乃散人進階所授的上乘劍術
// (見 docs/03-門派與武功/04-書生-步玄玄天.md §玄天教-核心技能﹕「玄天劍訣 ──
// 能打擊對手精、氣、神、定單一敵人」)。由入門玄天劍法(xuantian-sword)精進而
// 成﹐配合玄天心法(xuantian force)的吐納施展﹐劍走輕靈、暗藏控場殺機。
//
// 本檔比照 daemon/skill/xuantian-sword.c / buxuan-sword.c 的結構建立﹐使技能
// 可被指派與習練﹐並因是上乘劍訣較入門劍法略予加成(設計值)。玄天劍訣在中文
// 字典尚無詞條﹐故於 create() 時以 CHINESE_D->add_translate() 自行登錄中文名
// 「玄天劍訣」﹐使 skills / score 顯示工整。
//
// 設計(docs未明定確切數值)﹕招式傷害較入門玄天劍法略高﹐供日後平衡微調。
// TODO(控場完整化)：docs 載玄天劍訣可「打擊對手精、氣、神、定單一敵人」﹐
//   屬 perform/控場系統(困天、定人)﹐標記為待辦。本檔先接通基本攻擊判定。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N足踏天罡星位﹐$w斜斜一引直刺$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『料敵機先』﹐$w化作一道寒芒搶先掠向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍隨星轉﹐一招『玄鳥九變』盤旋而出撩向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N斂息凝神﹐$w如周天運行﹐後發先至直點$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N側身遊走如觀星布陣﹐$w斜挑而上劃向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『機鋒暗藏』﹐$w忽地繞向$n的$l要害",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N長劍斜引蓄勢﹐$w凝而後發直刺$n的$l",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足尖輕點﹐一式『星河倒懸』連環斬向$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐步法暗轉﹐神色不動如觀星問道﹐料敵機先﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("xuantian-jue");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("xuantian-jue", "玄天劍訣");
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

  damage = COMBAT_D->fight(me, opponent, "xuantian-jue", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
