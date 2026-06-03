// 傲梅暗劍訣 aomei-sword -- 冷梅莊「劍士」進階(二轉)的高階劍法(基礎技能 sword)
//
// 劍士由入門「冷梅劍法 lunmay」精進而成的殺著。比照 daemon/skill/lunmay.c
// 之 actions 招式表模型建立﹐但更強﹕招式 damage 係數更高、另帶 "attack"
// (命中加成)與 "force"(內力加成係數﹐見 combatd.c::fight() 之 force_bonus
// 公式)﹐並有兩式高階「攻防一體」絕招(帶正 dodge﹐防守反擊之意)。
//
// 玩家透過 map_skill("sword","aomei-sword") 將劍法對應到本招式後﹐戰鬥時
// COMBAT_D->fight() 即依本表施展招式。傲梅暗劍訣「提升攻擊能力、攻勢等級和
// 傷害﹐攻防一體﹐既有爆發力也有防禦力(parry 後反擊)」(見 docs/03-門派與武
// 功/01-武者-五大門派.md §2 冷梅莊-劍士﹐評分 攻擊 A / 防禦 A)。
//
// 傲梅暗劍訣最致命的設計缺點是「精消耗極大」﹕本表的 "force" 係數偏高﹐使
// combatd 依公式扣去較多精(gin)。此處以招式數值體現該特性﹐符合 docs。
//
// 中文字典(data/chinese.o)裡傲梅暗劍訣對應 key 為 advance_lunmay(見
// memory/patterns/authoring-class-sect.md 技能名 manifest)﹐惟本招式 daemon
// 註冊名取直觀的 "aomei-sword"﹐另以 CHINESE_D->add_translate() 自行登錄
// 中文名「傲梅暗劍訣」﹐使 skills / score 等指令能工整顯示中文。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 15~22(入門 lunmay 為 5~10)﹐高階兩式另帶 attack 8~12 與
//   force 10~18(入門無 force 係數﹐即沿用基準 ratio 75)。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手腕一翻﹐$w化作一朵寒梅暗刺﹐悄無聲息地點向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腳踏梅花亂步﹐$w疾斬而出﹐一式『暗香疏影』撩向$n的$l",
    "dodge":		-10,
    "attack":		6,
    "force":		8,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N長劍輕顫﹐劍尖暴吐三點寒星﹐連環疾刺$n的$l",
    "dodge":		-12,
    "attack":		8,
    "force":		10,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身形微側﹐一式『冷蕊侵霜』﹐$w如寒梅吐蕊直貫$n的$l",
    "dodge":		-15,
    "attack":		8,
    "force":		12,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N劍走偏鋒﹐$w斜斜挑起一蓬劍雨﹐儘數罩向$n的$l",
    "dodge":		-10,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
  // —— 攻防一體﹕正 dodge﹐先守後發、parry 後反擊之勢 ——
  ([
    "action":		"$N斂劍半步﹐待$n勢老即還﹐一式『傲雪反梅』後發制人斬向$n的$l",
    "dodge":		8,
    "attack":		10,
    "force":		14,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N凝劍如淵﹐隨$n破綻一現﹐$w凝而後發直透$n的$l",
    "dodge":		10,
    "attack":		8,
    "force":		12,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕傲梅暗劍訣最盛一式﹐爆發力與精耗俱極大 ——
  ([
    "action":		"$N足尖一點凌空而起﹐一式『傲梅暗劍』漫天寒芒儘數攢向$n的$l",
    "dodge":		-15,
    "attack":		12,
    "force":		18,
    "damage":		22,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐劍尖凝霜﹐一身傲骨清冷如寒梅破雪﹐靜待出手的時機。\n",
  "$N斂劍而立﹐劍意內蘊﹐宛如止水明鏡﹐殺機暗藏於波瀾不興之中。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("aomei-sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("aomei-sword", "傲梅暗劍訣");
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

  damage = COMBAT_D->fight(me, opponent, "aomei-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
