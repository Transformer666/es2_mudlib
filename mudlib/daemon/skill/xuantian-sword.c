// 玄天劍法 xuantian-sword -- 玄天教散人的入門劍法
//
// 玄天教書生一脈外託遊學論道、內操四廠諜報﹐這套玄天劍法乃散人入門的
// 根本劍術﹐講究觀星布陣、料敵機先﹐劍走輕靈而暗藏殺機﹐配合玄天心法
// (xuantian force)的吐納施展。本檔比照 buxuan-sword.c/lunmay.c 的結構建立﹐
// 使技能可被指派與習練。
//
// 玄天劍法在中文字典尚無詞條﹐故於 create() 時以 CHINESE_D->add_translate()
// 自行登錄中文名「玄天劍法」﹐使 skills / score 顯示工整。
// TODO: combat specifics -- 與身法、內功(xuantian force)聯動的料敵/暗襲
//       效果﹐及進階招式判定。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N足踏星位﹐$w斜斜一引刺向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身形一晃﹐$w化作一道寒芒掠向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式『玄鳥振翅』﹐$w盤旋而出撩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍隨星轉﹐手中$w如周天運行直點$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N側身遊走﹐$w斜挑而上劃向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一招『機先暗藏』﹐$w忽地繞向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N斂息蓄勢﹐$w凝而後發直刺$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足尖輕點﹐一式『星河倒懸』連環斬向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐步法暗轉﹐神色不動如觀星問道﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("xuantian-sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("xuantian-sword", "玄天劍法");
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

  damage = COMBAT_D->fight(me, opponent, "xuantian-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
