// 虛空斬 vacancy-ax -- 步玄派「逍遙居士」進階(二轉)的最上乘劍法(基礎技能 sword)
//
// 步玄派居士武學的極致﹐由入門「小步玄劍 buxuan-sword」歷奇門劍訣再進
// 一階而成的殺著(見 docs/03-門派與武功/04-書生-步玄玄天.md §步玄派-核心
// 技能「虛空斬 ── vacancy ax」)。虛空斬以劍意斬空、無中生有﹐劍氣縱橫
// 如裂虛空﹐配合逍遙遊(xiaoyao-steps)身法與乾坤三轉心法(qiankun-force)
// 內力施展﹐乃步玄居士登峰造極的一脈劍法。
//
// 玩家透過 map_skill("sword","vacancy-ax") 將劍法對應到本招式後﹐戰鬥時
// COMBAT_D->fight() 即依本表施展。本檔比照 daemon/skill/aomei-sword.c /
// dual-dragon-sword.c 的招式表模型建立﹐並因是步玄居士最上乘劍法﹐damage
// 與 force 係數再較奇門劍訣高一階(設計值)。docs 英文 key 為「vacancy ax」﹐
// 本招式 daemon 註冊名取連字號的 "vacancy-ax"﹐另以 CHINESE_D->add_translate()
// 自行登錄中文名「虛空斬」﹐使 skills / score 等指令工整顯示中文。
//
// 數值為本次設計值(docs 只給技能名非確切數字)﹐供日後平衡微調﹕damage
//   18~26、高階另帶 attack 10~14 與 force 14~22(較奇門劍訣再高一階)。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N腳踏玄步﹐$w斜斜一引劍意斬空削向$n的$l",
    "dodge":		-5,
    "attack":		8,
    "force":		12,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『無中生有』﹐$w化作一道虛芒憑空掠向$n的$l",
    "dodge":		-10,
    "attack":		10,
    "force":		14,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍隨意走﹐一招『裂空』劍氣縱橫直貫$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		16,
    "damage":		22,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N斂息凝劍﹐$w如行雲流水後發先至直點$n的$l",
    "dodge":		-15,
    "attack":		12,
    "force":		18,
    "damage":		22,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N側身遊走如逍遙遊步﹐$w斜挑而上劃向$n的$l",
    "dodge":		-10,
    "attack":		10,
    "force":		14,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  // —— 攻防一體﹕正 dodge﹐劍意斬空、先守後發之勢 ——
  ([
    "action":		"$N斂劍半步如入虛空﹐待$n勢老即還﹐一式『空明反照』斬向$n的$l",
    "dodge":		10,
    "attack":		12,
    "force":		18,
    "damage":		22,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍凝如淵﹐隨$n破綻一現﹐$w憑空一斬直透$n的$l",
    "dodge":		12,
    "attack":		10,
    "force":		16,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕虛空斬最盛一式﹐劍裂虛空、玄之又玄 ——
  ([
    "action":		"$N足尖一點凌空而起﹐一式『虛空斬』劍氣裂空儘數攢向$n的$l",
    "dodge":		-15,
    "attack":		14,
    "force":		22,
    "damage":		26,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐劍意斂於虛空﹐一身玄機如行雲流水﹐靜待出手的時機。\n",
  "$N斂劍而立﹐劍意內蘊如裂空之兆﹐殺機暗藏於波瀾不興之中。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("vacancy-ax");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("vacancy-ax", "虛空斬");
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

  damage = COMBAT_D->fight(me, opponent, "vacancy-ax", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
