// 穹劍訣 sky-sword -- 大內巡院「大內都統」進階(二轉)的最高劍法絕學(基礎技能 sword)
//
// 大內都統為軍人最高一階(設計(docs未明定分支名):承大內高手以重擊精傷證道之最高一階)。
// docs 大內巡院進階明列「穹槍訣 sky_pike：神威下攻擊對目標精傷﹐按陰陽五行技能」(見
// docs/03-門派與武功/06-軍人-振武大內.md §2 大內巡院 soldier.royal)。data/chinese.o 已
// 有 key "sky_pike":"穹槍訣"﹐惟其為槍法(pike)﹔本門統領以大內劍法(sword)入門﹐故承穹槍
// 訣「神威精傷」之意改以劍訣承之﹐命名「穹劍訣 sky-sword」﹐基礎技能由 pike 改 sword﹐
// 以免映射落到玩家未習的 pike 槽。字典查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「穹劍訣」。
//
// 比照 daemon/skill/royal-sword.c(神威劍訣)、daemon/skill/powerblow.c(重擊術)之 actions
// 招式表模型建立。穹劍訣乃大內諸劍法之最﹐剛猛沉重、一劍貫頂(承穹槍訣精傷之意)﹐故本表
// damage 為大內諸劍法之最、dodge 多大負(全力搶攻、破綻較大)﹐並帶高 "force" 係數吃大內
// 心法(royal force)的內力(見 combatd.c::fight() force_bonus 公式)。基礎技能為 sword(劍法)。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 16~24(大內諸劍法之最)﹐高階式帶 attack 8~14 與 force 10~18。
//
// TODO(大內都統完整化)：docs 載穹槍訣「神威狀態下攻擊對目標精傷、按陰陽五行技能」。
//   神威狀態(royal)、精氣傷害(非血傷)與按五行技能加成屬 combat/perform 系統(非招式表)﹐
//   標記為待辦。本檔先把帶「神威貫頂、一劍裂雲」氣象的高階劍招做實﹐與虎刀 powerblow
//   同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N雙手持劍運足全力﹐$w一式『穹頂裂雲』當頭猛刺$n的$l",
    "dodge":		-15,
    "attack":		8,
    "force":		10,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N沉肩墜肘灌勁於劍﹐$w一式『神威貫日』狠狠貫向$n的$l",
    "dodge":		-18,
    "attack":		10,
    "force":		12,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一聲清嘯勁貫劍身﹐$w化作一道沉雷直劈$n的$l",
    "dodge":		-16,
    "attack":		10,
    "force":		12,
    "damage":		18,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N踏前一步全力下刺﹐一式『穹蒼覆地』$w沉沉貫向$n的$l",
    "dodge":		-20,
    "attack":		12,
    "force":		14,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙臂青筋暴起﹐$w一式『裂雲驚虹』雷霆萬鈞刺向$n的$l",
    "dodge":		-18,
    "attack":		11,
    "force":		13,
    "damage":		19,
    "damage_type":	"刺傷"
  ]),
  // —— 蓄力式﹕穹劍訣神威蓄勁、後發制人(略守﹐正 dodge) ——
  ([
    "action":		"$N橫劍沉腰蓄勁如滿弓﹐神威真氣鼓盪﹐隨$n勢老驟然爆發重刺$n的$l",
    "dodge":		5,
    "attack":		10,
    "force":		14,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝劍屏息蓄勢待發﹐借勢一記沉雷貫向$n的$l",
    "dodge":		3,
    "attack":		9,
    "force":		12,
    "damage":		17,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕穹劍訣神威盡灌、一劍貫頂裂雲 ——
  ([
    "action":		"$N周身神威真氣盡灌劍身﹐一式『穹頂貫頂』$w攜山崩之勢儘數貫向$n的$l",
    "dodge":		-22,
    "attack":		14,
    "force":		18,
    "damage":		24,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙手持劍沉腰蓄勁﹐劍身微顫神威真氣鼓盪﹐殺氣如山雨欲來﹐只待一劍裂雲。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("sky-sword");
  // 字典查無此 key﹐自行登錄中文名「穹劍訣」(承穹槍訣 sky_pike 之意﹐惟以劍代槍)。
  CHINESE_D->add_translate("sky-sword", "穹劍訣");
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

  damage = COMBAT_D->fight(me, opponent, "sky-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
