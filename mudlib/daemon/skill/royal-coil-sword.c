// 盤龍劍訣 royal-coil-sword -- 大內巡院「大內供奉」進階(二轉)的高階劍法(基礎技能 sword)
//
// 設計(docs未明定招式名)：大內供奉為承大內高手之上、兼修大內心法(royal force)的神威
// 內功一脈(見 docs/03-門派與武功/06-軍人-振武大內.md §2 大內巡院 soldier.royal﹐核心
// 技能列「大內心法 royal force：神威狀態提升護甲傷害」)。docs 未替供奉一脈命名一套新
// 劍法﹐其特色為神威護體、綿密續戰﹐故本招式名「盤龍劍訣 royal-coil-sword」為本次設計
// 值﹐用以承載供奉「綿密纏鬥、長於續戰」的招式氣象﹔字典 data/chinese.o 查無此 key﹐
// 以 CHINESE_D->add_translate() 自行登錄中文名「盤龍劍訣」。
//
// 比照 daemon/skill/royal-sword.c(神威劍訣)、daemon/skill/guardtiger-blade.c 之 actions
// 招式表模型建立﹐damage 中庸、守勢招(正 dodge)較多以體現供奉「神威護體、續戰綿密」
// 的定位﹐並帶較高 "force" 係數吃大內心法(royal force)的內力(見 combatd.c::fight()
// force_bonus 公式)。基礎技能為 sword(劍法)。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 13~18﹐高階式帶 attack 6~10 與 force 8~14。
//
// TODO(大內供奉完整化)：docs 載大內心法有「royal 神威狀態提升護甲傷害」。神威狀態下
//   的護甲/傷害加成屬 combat/perform 系統(非招式表)﹐由 daemon/skill/royal_force.c
//   與戰鬥層配合﹐標記為待辦。本檔先把帶神威護體氣象的劍招做實。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N$w一式『盤龍探爪』纏身遞進﹐劍走偏鋒削向$n的$l",
    "dodge":		-5,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腕底翻轉﹐$w如盤龍纏柱﹐連綿不絕地刺向$n的$l",
    "dodge":		-8,
    "attack":		7,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N沉身進步﹐一式『神龍擺尾』$w橫掃$n的$l",
    "dodge":		-10,
    "attack":		8,
    "force":		10,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  // —— 守勢式﹕盤龍綿密護體、後發制人(正 dodge﹐供奉續戰之本﹐較多) ——
  ([
    "action":		"$N橫劍盤旋於身前一式『神威護體』凝守待機﹐借勢回刺$n的$l",
    "dodge":		12,
    "attack":		7,
    "force":		10,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N斂劍蓄勢真氣護體﹐隨$n勢老沉穩後發削向$n的$l",
    "dodge":		10,
    "attack":		7,
    "force":		10,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N佯作退步避其鋒銳﹐隨即一式『盤龍回身』反撩$n的$l",
    "dodge":		10,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N$w盤旋如龍蟠﹐一招一式綿密纏住$n﹐順勢貫向$n的$l",
    "dodge":		8,
    "attack":		8,
    "force":		12,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕盤龍劍訣真氣盡灌、神龍出淵 ——
  ([
    "action":		"$N周身神威真氣盡灌劍身﹐一式『神龍出淵』$w攜萬鈞之勢貫向$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		14,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N橫劍盤旋於胸前﹐周身神威真氣護體流轉如龍蟠﹐凝神靜候$n的破綻。\n",
  "$N按劍沉腰守勢綿密﹐神威內蘊、攻守蓄而不發﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("royal-coil-sword");
  // 字典查無此 key﹐自行登錄中文名「盤龍劍訣」。
  CHINESE_D->add_translate("royal-coil-sword", "盤龍劍訣");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIY + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "royal-coil-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
