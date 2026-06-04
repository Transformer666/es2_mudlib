// 狂擊亂鬥之法 berserk -- 振武軍營「軍隊統領」進階(二轉)的核心槍法(基礎技能 pike)
//
// 振武軍營暴力路線的招牌絕學﹐docs 載「狂擊亂鬥之法 berserk：消精氣上限百分比現值﹐
// 可怕攻擊力對單目標 1-4 次或多目標 4-11 次。lv70+ 每級 +1 gin +2 kee；lv140 起每
// 10 級 +1 膂力膽識根骨」(見 docs/03-門派與武功/06-軍人-振武大內.md §1 振武軍營-核心
// 技能 / 進階-軍隊統領)。中文名「狂擊亂鬥之法」於 data/chinese.o 已有對應 key
// "berserk":"狂擊亂鬥之法"﹐故本檔沿用該 romanization "berserk"﹐add_translate 僅作
// 備援(字典已有則覆寫同值﹐無害)。
//
// 比照 daemon/skill/dragon_god.c(入門龍神槍法)、daemon/skill/powerblow.c 之 actions
// 招式表模型建立。狂擊亂鬥剛猛狂暴、全力搶攻(評分 攻擊極高、破綻極大)﹐故本表 damage
// 為振武諸槍法之最、dodge 多大負(狂攻不守)﹐並帶高 "force" 係數(吃瘋虎功 tiger force
// 的內力﹐見 combatd.c::fight() force_bonus 公式)。基礎技能為 pike(槍法)。
//
// 數值為本次設計值(docs 只給定性描述非確切數字)﹐供日後平衡微調﹕
//   damage 14~22(振武諸槍法之最)﹐高階式帶 attack 8~14 與 force 8~16。
//
// TODO(統領完整化)：docs 載 berserk「消精氣上限百分比現值﹐對單目標 1-4 次或多目標
//   4-11 次」﹐其「消耗精氣換取的多段連擊/群攻」屬 combat/perform(特殊招)系統(非招式
//   表)﹐標記為待辦。本檔先把帶「狂擊亂鬥」氣象的普攻招式做實﹐與虎刀 powerblow
//   同一範圍。lv70+/lv140+ 的屬性成長亦屬等級成長引擎之 TODO。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N雙目赤紅﹐$w平端狂搶﹐一式『亂鬥開疆』連環疾搠$n的$l",
    "dodge":		-14,
    "attack":		8,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N怒吼一聲全力前衝﹐$w化作一片槍影狂掃$n的$l",
    "dodge":		-16,
    "attack":		10,
    "force":		10,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N步步進逼槍槍搶攻﹐$w一式『狂濤亂卷』翻江倒海般砸向$n的$l",
    "dodge":		-18,
    "attack":		10,
    "force":		12,
    "damage":		17,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N殺性大發﹐$w如疾風驟雨﹐一式『亂鬥十三槍』瘋狂攢刺$n的$l",
    "dodge":		-20,
    "attack":		12,
    "force":		12,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N槍尖抖出漫天槍花﹐不留半分餘地儘數罩向$n的$l",
    "dodge":		-16,
    "attack":		11,
    "force":		11,
    "damage":		17,
    "damage_type":	"刺傷"
  ]),
  // —— 借勢式﹕狂擊中偶有沉腰借力的緩著(略守﹐正 dodge) ——
  ([
    "action":		"$N沉腰一頓蓄起狂勁﹐隨即爆喝著反挑$n的$l",
    "dodge":		4,
    "attack":		10,
    "force":		12,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N槍勢一收旋即暴漲﹐借勢一記橫掃反掄向$n的$l",
    "dodge":		2,
    "attack":		9,
    "force":		10,
    "damage":		15,
    "damage_type":	"挫傷"
  ]),
  // —— 殺著﹕狂擊亂鬥傾盡狂勁的一槍﹐勢若奔雷、勇不可當 ——
  ([
    "action":		"$N血貫雙瞳渾身狂勁盡灌槍尖﹐一式『振武狂濤』攜雷霆萬鈞之勢儘數轟向$n的$l",
    "dodge":		-22,
    "attack":		14,
    "force":		16,
    "damage":		22,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙目赤紅、殺氣狂湧﹐長槍斜指微微發顫﹐渾身狂勁鼓盪﹐只待一槍狂搶。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("berserk");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示(字典已有則覆寫同值)。
  CHINESE_D->add_translate("berserk", "狂擊亂鬥之法");
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

  damage = COMBAT_D->fight(me, opponent, "berserk", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
