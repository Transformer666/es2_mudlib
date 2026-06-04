// 瘋虎刀法 tiger blade -- 虎刀門「鬼才」進階(二轉)的高階刀法(基礎技能 blade)
//
// 鬼才一脈由入門「霸王刀招 bawang blade」精進而成的殺著﹐docs 載鬼才「兩手
// 持刀皆可使用瘋虎刀法」(見 docs/03-門派與武功/01-武者-五大門派.md §5 虎刀門-
// 鬼才)。中文名「瘋虎刀法」於 data/chinese.o 已有對應 key "tiger blade":
// "瘋虎刀法"﹐故本檔沿用該 romanization "tiger blade"﹐add_translate 僅作備援
// (字典已有則覆寫為同值﹐無害)。
//
// 比照 daemon/skill/bawang_blade.c(入門霸王刀招)、daemon/skill/hanshuang.c
// (冷梅虎督劍法)之 actions 招式表模型建立﹐但更強﹕招式 damage 係數更高、
// 另帶 "attack"(命中加成)與 "force"(吃虎刀心法 hudao force 的內力加成係數﹐
// 見 combatd.c::fight() 之 force_bonus 公式)。鬼才是江湖中最具爆發力的二轉
// (評分 攻擊 S / 防禦 D / 續戰 B+ / 靈活 D)﹐故本表招式剛猛搶攻、dodge 多負
// (破綻大但刀勢凌厲)、damage 沉重。基礎技能為 blade(刀法)﹐使用厚背快刀。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 15~22(入門 bawang blade 為 5~10)﹐高階式帶 attack 6~12 與
//   force 8~16。
//
// TODO(鬼才完整化)：docs 載鬼才有「overpower(消 250 氣、十五成功力)」、「第一追
//   後保證第二追與反手拔刀(無視防禦)、兩手最多 10 刀連擊」等絕招﹐其「無視防禦」
//   與「連擊段數 / 追擊」屬 combat/perform 系統(非招式表)﹐標記為待辦。本檔先把
//   帶「瘋虎搶攻」氣象的普攻招式做實﹐與冷梅 hanshuang、封山 jianling-sword 同
//   一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N雙目赤紅一聲虎吼﹐$w當頭一式『瘋虎撲山』狠劈$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N腳下一個箭步搶進﹐$w化作一片血光連環疾斬$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		10,
    "damage":		17,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N沉腕翻刀﹐一式『餓虎攫食』$w凌空猛劈$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N雙刀齊出﹐一式『雙虎奪命』左右交斬狠豁$n的$l",
    "dodge":		-14,
    "attack":		8,
    "force":		12,
    "damage":		18,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N欺身搶進﹐$w以雷霆萬鈞之勢力劈$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"砍傷"
  ]),
  // —— 守勢式﹕瘋虎刀法少數收勢之招﹐借勢回斬(正 dodge) ——
  ([
    "action":		"$N橫刀一引借勢卸力﹐隨即一式『虎尾反鉤』反撩$n的$l",
    "dodge":		6,
    "attack":		7,
    "force":		10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N佯作退步避其鋒銳﹐刀走偏鋒斜削$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  // —— 殺著﹕瘋虎刀法最盛一式﹐兩手連環、刀勢暴漲 ——
  ([
    "action":		"$N周身殺氣暴漲﹐一式『瘋虎噬魂』兩手快刀如暴雨般攢向$n的$l",
    "dodge":		-16,
    "attack":		12,
    "force":		16,
    "damage":		22,
    "damage_type":	"砍傷"
  ]),
});

string *interattack = ({
  "$N雙刀斜引刀尖滴血﹐殺氣如瘋虎蓄勢﹐只待破綻一現便要撲殺。\n",
  "$N橫刀於胸雙目赤紅﹐刀勢蓄而不發﹐尋找著進招的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("tiger blade");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示(字典已有則覆寫同值)。
  CHINESE_D->add_translate("tiger blade", "瘋虎刀法");
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

  damage = COMBAT_D->fight(me, opponent, "tiger blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
