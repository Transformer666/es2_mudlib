// 大邪七損刀訣 seven_blade -- 哭笑門「使者」進階(二轉)的高階刀法(基礎技能 blade)
//
// 哭笑門使者(七損刀)一脈的上乘刀法(見 docs/03-門派與武功/01-武者-五大門派.md §3
// 哭笑門-使者(七損刀))。docs 載使者「難練自損(attr-2)﹐手動 perform、無視防禦、外加
// 定人﹐威力看攻擊能力值﹐parry 成功時注入破體刀氣﹐對付一群敵人麻煩﹐適合單打獨鬥」
// (評分 攻擊 A / 防禦 B- / 續戰 B- / 靈活 A)。中文名「大邪七損刀訣」於 data/chinese.o
// 已有對應 key "seven_blade":"大邪七損刀訣"﹐故本檔沿用該 romanization "seven_blade"﹐
// add_translate 僅作備援(字典已有則覆寫同值﹐無害)。
//
// 比照虎刀門鬼才瘋虎刀法 daemon/skill/tiger-blade.c 之 actions 招式表模型建立(同為
// 搶攻爆發、攻擊 A/S 評級)﹐招式 damage 係數高、dodge 多負(破綻大但刀勢凌厲)﹐另帶
// "attack"(命中加成)與 "force"(吃大邪心經 danei-sutra 的內力加成係數﹐見 combatd.c
// ::fight() 之 force_bonus 公式)。基礎技能為 blade(刀法)﹐使者捨杖習刀、使快刀。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕damage 15~22
//   (入門 chin_staff 為 5~10)﹐高階式帶 attack 6~12 與 force 8~16。
//
// TODO(使者完整化)：docs 載使者「自損 attr-2、手動 perform 無視防禦、定人、parry 成功
//   注破體刀氣」等絕招﹐其「無視防禦/定人/parry 觸發/屬性自損」屬 combat/perform 系統
//   (非招式表)﹐標記為待辦。本檔先把帶「七損刀」氣象的普攻刀招做實﹐與虎刀 tiger-blade、
//   冷梅 hanshuang 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N陰惻惻一笑﹐$w一式『一損天靈』挾邪氣當頭劈向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N腳下一個鬼魅般的滑步搶進﹐$w化作一片血光斜削$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		10,
    "damage":		17,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N沉腕翻刀﹐一式『三損形神』$w凌空猛豁$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N怪笑連連﹐$w一式『五損精氣』直透防禦狠捅$n的$l",
    "dodge":		-14,
    "attack":		8,
    "force":		12,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N欺身搶進忽哭忽笑﹐$w以雷霆萬鈞之勢力斬$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"砍傷"
  ]),
  // —— 守勢式﹕七損刀少數收勢之招﹐借勢回斬(正 dodge) ——
  ([
    "action":		"$N橫刀一引借勢卸力﹐隨即一式『回鋒索命』反撩$n的$l",
    "dodge":		6,
    "attack":		7,
    "force":		10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N佯作退步避其鋒銳﹐刀走偏鋒陰冷地削向$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  // —— 殺著﹕七損刀最毒一式﹐七損俱發、無視防禦、刀勢暴漲 ——
  ([
    "action":		"$N周身邪氣暴漲哭笑癲狂﹐一式『七損俱滅』快刀如鬼嘯般無視防禦攢向$n的$l",
    "dodge":		-16,
    "attack":		12,
    "force":		16,
    "damage":		22,
    "damage_type":	"砍傷"
  ]),
});

string *interattack = ({
  "$N橫刀於胸陰惻惻一笑﹐刀尖滴血﹐邪氣蓄而不發﹐只待破綻一現便要索命。\n",
  "$N雙目時哭時笑﹐快刀斜引刀勢蓄勢﹐尋找著進招的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("seven_blade");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示(字典已有則覆寫同值)。
  CHINESE_D->add_translate("seven_blade", "大邪七損刀訣");
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

  damage = COMBAT_D->fight(me, opponent, "seven_blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
