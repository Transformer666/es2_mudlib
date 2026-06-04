// 重擊術 powerblow -- 虎刀門「太守」進階(二轉)的高階刀法 sr(基礎技能 blade)
//
// 太守一脈的重擊絕學﹐docs 載「多 sr 系列重擊術(powerblow)﹐根據 sk 高低決定
// 機率﹐可直接爆 hp」(見 docs/03-門派與武功/01-武者-五大門派.md §5 虎刀門-太守﹐
// 評分 攻擊 S / 防禦 C+ / 續戰 C+ / 靈活 D)。中文名「重擊術」於 data/chinese.o
// 已有對應 key "powerblow":"重擊術"﹐故本檔沿用該 romanization "powerblow"﹐
// add_translate 僅作備援(字典已有則覆寫同值﹐無害)。
//
// 比照 daemon/skill/bawang_blade.c、daemon/skill/tiger-blade.c 之 actions 招式表
// 模型建立。重擊術剛猛沉重、一擊裂石(評分 攻擊 S)﹐故本表 damage 為虎刀諸刀法
// 之最、dodge 多大負(全力搶攻、破綻極大)﹐並帶高 "force" 係數(吃虎刀心法 hudao
// force 的內力﹐見 combatd.c::fight() force_bonus 公式)。基礎技能為 blade(刀法)。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 16~24(虎刀諸刀法之最)﹐高階式帶 attack 8~14 與 force 10~18。
//
// TODO(太守完整化)：docs 載重擊術為「sr 系列、根據 sk 高低決定機率、可直接爆
//   hp」﹐其「依技能機率觸發的爆擊(直接爆 hp)」屬 combat/perform / 特殊招(sr)
//   系統(非招式表)﹐標記為待辦。本檔先把帶「重擊裂石」氣象的普攻招式做實﹐
//   與虎刀 tiger-blade 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N雙手握刀運足全力﹐$w一式『泰山壓頂』當頭猛劈$n的$l",
    "dodge":		-15,
    "attack":		8,
    "force":		10,
    "damage":		16,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N沉肩墜肘灌勁於刀﹐$w一式『力斷崩石』狠狠劈砸$n的$l",
    "dodge":		-18,
    "attack":		10,
    "force":		12,
    "damage":		18,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N一聲虎吼勁貫刀身﹐$w化作一道沉雷重壓$n的$l",
    "dodge":		-16,
    "attack":		10,
    "force":		12,
    "damage":		18,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N踏前一步全力下劈﹐一式『裂地驚虎』$w沉沉砸向$n的$l",
    "dodge":		-20,
    "attack":		12,
    "force":		14,
    "damage":		20,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N雙臂青筋暴起﹐$w一式『開碑裂石』雷霆萬鈞劈向$n的$l",
    "dodge":		-18,
    "attack":		11,
    "force":		13,
    "damage":		19,
    "damage_type":	"瘀傷"
  ]),
  // —— 蓄力式﹕重擊術沉腰蓄勁、後發制人(略守﹐正 dodge) ——
  ([
    "action":		"$N橫刀沉腰蓄勁如滿弓﹐隨$n勢老驟然爆發重劈$n的$l",
    "dodge":		5,
    "attack":		10,
    "force":		14,
    "damage":		18,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N凝刀屏息蓄勢待發﹐借勢一記沉雷重壓$n的$l",
    "dodge":		3,
    "attack":		9,
    "force":		12,
    "damage":		17,
    "damage_type":	"瘀傷"
  ]),
  // —— 殺著﹕重擊術全力一擊﹐勁透刀背、裂石碎金 ——
  ([
    "action":		"$N周身真氣盡灌刀背﹐一式『嘯林裂虎』$w攜山崩之勢儘數轟向$n的$l",
    "dodge":		-22,
    "attack":		14,
    "force":		18,
    "damage":		24,
    "damage_type":	"砍傷"
  ]),
});

string *interattack = ({
  "$N雙手握刀沉腰蓄勁﹐刀身微顫真氣鼓盪﹐殺氣如山雨欲來﹐只待一擊裂石。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("powerblow");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示(字典已有則覆寫同值)。
  CHINESE_D->add_translate("powerblow", "重擊術");
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

  damage = COMBAT_D->fight(me, opponent, "powerblow", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
