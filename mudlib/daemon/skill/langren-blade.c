// 浪人刀法 langren-blade -- 雪吟莊「浪人」進階(二轉)的強化刀法(基礎技能 blade)
//
// 浪人一脈由入門「數字刀 deepblade」精進而成的高階刀法(見 docs/03-門派與
// 武功/01-武者-五大門派.md §4 雪吟莊-浪人﹕「強化數字刀﹐攻勢可破千﹐三不
// 五時無視防禦必殺招」)。比照入門 daemon/skill/deepblade.c 之 actions 招式表
// 模型建立﹐但更強﹕招式 damage 係數更高、另帶 "attack"(命中加成)與 "force"
// (吃天邪神功 tianxie-force 的內力加成係數﹐見 combatd.c::fight() 之
// force_bonus 公式)﹐以體現浪人「攻勢凌厲、可破千」的剛猛綿密。
//
// 因基礎技能為 blade(刀法)﹐玩家透過 map_skill("blade","langren-blade")
// 對應後即可施展(同入門 deepblade 的刀法掛法)。weapon 物件由 attack_using
// 一路傳入 COMBAT_D->fight()﹐與 deepblade.c / bawang_blade.c 一致。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「浪人刀法」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 12~18(入門 deepblade 為 5~10)﹐高階式帶 attack 5~10 與 force 6~14。
//
// TODO(浪人完整化)：docs 載浪人「攻勢可破千、三不五時無視防禦必殺招」﹐
//   無視防禦之必殺判定屬 combat/perform 系統(非招式表)﹐標記為待辦。本檔
//   先把普攻刀招做實﹐與封山/虎刀諸進階招式同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉腕橫刀﹐一式『浪卷千堆』$w自下而上撩向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		12,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N腳下進步﹐$w挾天邪煞氣當頭直劈$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N一式『數窮勢盡』﹐$w層層遞進、勢若奔濤逼向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N刀走偏鋒﹐$w化作一片寒光連環疾斬$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式『天傾地裂』﹐$w平掃而出橫斬$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  // —— 守勢式﹕浪人攻守相續、刀光凝而後發(正 dodge) ——
  ([
    "action":		"$N側身一錯卸開來勢﹐$w凝而後發直劈$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		8,
    "damage":		13,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N佯作回刀避其鋒銳﹐隨即一式『回浪逐月』反撩$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"割傷"
  ]),
  // —— 殺著﹕浪人刀法最盛一式﹐刀數無窮、攻勢可破千 ——
  ([
    "action":		"$N長身而起﹐周身天邪真氣鼓盪﹐一式『刀數無窮』縱身狂斬$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		14,
    "damage":		18,
    "damage_type":	"砍傷"
  ]),
});

string *interattack = ({
  "$N橫刀於胸﹐刀光微沉﹐天邪煞氣隱隱流轉﹐凝神靜候出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("langren-blade");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("langren-blade", "浪人刀法");
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

  damage = COMBAT_D->fight(me, opponent, "langren-blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
