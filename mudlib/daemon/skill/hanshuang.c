// 寒霜三千 hanshuang -- 冷梅莊「虎督」進階(二轉)的劍法之一(基礎技能 sword)
//
// 虎督﹕拜入天邪﹐有「天邪神功 tianxie-force」輔助、超高 kee 與 attr﹐
// 可使用「寒霜三千」跟「天邪虎嘯」﹐冷梅系最具控場(定人)(見
// docs/03-門派與武功/01-武者-五大門派.md §2 冷梅莊-虎督﹐評分 攻擊 B /
// 防禦 B / 續戰 B / 靈活 A)。
//
// ⚠️ 交替使用﹕docs 明載「寒霜三千」與「天邪虎嘯」**只能交替使用**。本檔
//    與 daemon/skill/tianxie-roar.c(天邪虎嘯)實作為兩門獨立 sword 招式
//    技能﹔「交替」是戰鬥層的細節(理想上由 perform/combat 邏輯強制兩者
//    不可連續施展)﹐尚未在招式 daemon 層強制﹐標記為待辦。
//
// 比照 daemon/skill/lunmay.c 之 actions 招式表模型建立。虎督少了劍客
// 爆發力、多了持久續戰與控場﹐故本表 damage 中庸、帶 "force" 係數吃天邪
// 神功的超高 kee(力道公式見 combatd.c::fight() force_bonus)﹐並以寒霜「凝
// 凍/牽制」的招式敘述體現控場風味(定人之實際 hold 機制屬 combat/perform﹐
// 為未來工作)。
//
// 中文字典查無此 key﹐以 CHINESE_D->add_translate() 自行登錄「寒霜三千」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 14~18﹐多式帶 force 8~16 吃天邪神功的高 kee。
//
// TODO(虎督完整化)：①「寒霜三千 / 天邪虎嘯」交替使用的強制邏輯；②定人
//   (控場 hold)的實際機制。二者皆屬 combat/perform 系統﹐非招式表。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N$w一引﹐一式『寒霜初凝』化作漫天霜花撲向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"冰傷"
  ]),
  ([
    "action":		"$N足下生寒﹐$w捲起一片霜風﹐颯然斬向$n的$l",
    "dodge":		-10,
    "attack":		6,
    "force":		10,
    "damage":		15,
    "damage_type":	"冰傷"
  ]),
  ([
    "action":		"$N一式『霜封千里』﹐$w所指處寒氣森森凍向$n的$l",
    "dodge":		-12,
    "attack":		8,
    "force":		12,
    "damage":		16,
    "damage_type":	"冰傷"
  ]),
  ([
    "action":		"$N$w疾轉如輪﹐捲起千重霜刃﹐儘數絞向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"冰傷"
  ]),
  // —— 控場式﹕寒霜凝凍、牽制之意(正 dodge﹐穩守控場) ——
  ([
    "action":		"$N$w橫掃出一道霜牆﹐寒氣瀰漫欲封$n手腳﹐順勢削向$n的$l",
    "dodge":		5,
    "attack":		6,
    "force":		10,
    "damage":		14,
    "damage_type":	"冰傷"
  ]),
  ([
    "action":		"$N凝劍蓄勢﹐一式『冰封三尺』寒霜層層鎖向$n的$l",
    "dodge":		8,
    "attack":		7,
    "force":		12,
    "damage":		15,
    "damage_type":	"冰傷"
  ]),
  ([
    "action":		"$N$w所過之處滴水成冰﹐一式『霜寒徹骨』直透$n的$l",
    "dodge":		-5,
    "attack":		7,
    "force":		12,
    "damage":		16,
    "damage_type":	"冰傷"
  ]),
  ([
    "action":		"$N周身寒氣暴漲﹐一式『寒霜三千』三千霜刃天羅地網般攢向$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		16,
    "damage":		18,
    "damage_type":	"冰傷"
  ]),
});

string *interattack = ({
  "$N$w斜引﹐劍身凝著一層薄霜﹐周身寒氣森森﹐殺機暗藏於凜冽之中。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("hanshuang");
  CHINESE_D->add_translate("hanshuang", "寒霜三千");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIC + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "hanshuang", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
