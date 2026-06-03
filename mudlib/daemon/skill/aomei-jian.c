// 傲梅劍 aomei-jian -- 冷梅莊「古劍門傳人」進階(二轉)的左手劍法(基礎技能 sword)
//
// 古劍門傳人雙劍合璧的另一半﹕右手「傲劍絕 aojian-jue」、左手「傲梅劍」
// (見 docs/03-門派與武功/01-武者-五大門派.md §2 冷梅莊-古劍門傳人)。
// 本檔比照 daemon/skill/lunmay.c 之 actions 招式表模型建立﹐路數承自冷梅
// 一脈、招式較傲劍絕輕靈﹐damage 中庸而 dodge 偏守﹐合於古劍門「打不死、
// 重續戰」的定位(評分 防禦 A+ / 續戰 A+)。
//
// 玩家透過 map_skill("sword","aomei-jian") 對應後﹐戰鬥時 COMBAT_D->fight()
// 即依本表施展招式。雙劍流的左右手 perform 絕招與 parry 回 kee 屬 combat/
// perform 機制﹐為未來工作。
//
// 中文字典查無此 key﹐以 CHINESE_D->add_translate() 自行登錄「傲梅劍」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 12~16﹐承冷梅一脈以刺、割為主﹐多式帶守勢正 dodge。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N左手$w一抖﹐一式『梅蕊輕揚』斜斜撩向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		12,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N左腕翻飛﹐$w化作一片落梅﹐紛紛點向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『暗香盈袖』﹐左手$w繞了個圈悄刺$n的$l",
    "dodge":		0,
    "attack":		5,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N左手劍勢忽快忽慢﹐$w如疏影橫斜般掠向$n的$l",
    "dodge":		-5,
    "attack":		6,
    "damage":		14,
    "damage_type":	"割傷"
  ]),
  // —— 守勢﹕承古劍門續戰之長 ——
  ([
    "action":		"$N斂左手劍於肘後﹐一式『寒梅斂雪』凝守待機﹐劍鋒虛引$n的$l",
    "dodge":		12,
    "attack":		4,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N左手劍圓轉相隨﹐先化後刺﹐$w隨$n勢盡回撩$n的$l",
    "dodge":		10,
    "attack":		6,
    "damage":		13,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式『冷蕊纏枝』﹐左手$w綿密不絕地黏向$n的$l",
    "dodge":		8,
    "attack":		5,
    "damage":		12,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N左手劍光一斂復吐﹐一式『傲梅吐蕊』寒芒森森貫向$n的$l",
    "dodge":		-10,
    "attack":		8,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N左手梅劍斜引﹐劍尖凝著一縷寒意﹐恰似寒梅凝霜﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("aomei-jian");
  CHINESE_D->add_translate("aomei-jian", "傲梅劍");
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

  damage = COMBAT_D->fight(me, opponent, "aomei-jian", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
