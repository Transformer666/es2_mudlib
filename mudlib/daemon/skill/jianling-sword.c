// 凰翔三疊劍 jianling-sword -- 封山派「劍靈」進階(二轉)的高階劍法(基礎技能 sword)
//
// 劍靈由入門「封山劍法 fonxansword」精進而成的殺著﹐承自封山舊版強化「九天
// 鳳翔」一脈(見 docs/03-門派與武功/01-武者-五大門派.md §1 封山派-劍靈﹕
// 「舊版封山強化(九天鳳翔那版)」)。比照 daemon/skill/fonxansword.c 之 actions
// 招式表模型建立﹐但更強﹕招式 damage 係數更高、另帶 "attack"(命中加成)與
// "force"(內力加成係數﹐見 combatd.c::fight() 之 force_bonus 公式)﹐並有體現
// 「劍招提升攻勢、守勢、護甲」的攻守兼備招式(帶正 dodge﹐守勢之意)。
//
// 玩家透過 map_skill("sword","jianling-sword") 將劍法對應到本招式後﹐戰鬥時
// COMBAT_D->fight() 即依本表施展招式。劍靈「以劍招提升攻勢、守勢、護甲﹐可
// 彌補不足 attr」(評分 攻擊 B+ / 防禦 B / 續戰 C+ / 靈活 D)。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「凰翔三疊劍」﹐使 skills / score 等指令能工整顯示中文。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 14~21(入門 fonxansword 為 5~10)﹐高階式另帶 attack 6~12 與
//   force 8~16(入門無 force 係數﹐即沿用基準 ratio 75)。
//
// TODO(劍靈完整化)：docs 載劍靈有「無視防禦三連擊」絕招﹐其「無視防禦」與
//   「連擊段數」屬 combat/perform 系統(非招式表)﹐標記為待辦。本檔先把帶
//   「三疊連環」氣象的普攻招式做實﹐與冷梅 aomei-sword 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉腕一引﹐$w如鳳起青嶂﹐第一疊劍勢平平刺向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腳踏山步﹐一式『鳳翔初疊』﹐$w層層遞進撩向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍勢一緊﹐第二疊劍光緊隨而至﹐連環疾點$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		17,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『青嶂展翼』﹐$w如鳳舒雙翼斜斜掠向$n的$l",
    "dodge":		-12,
    "attack":		8,
    "force":		12,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍走山勢﹐$w大開大闔當頭壓向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
  // —— 攻守兼備﹕劍靈「以劍招提升守勢、護甲」之意﹐正 dodge、守勢沉穩 ——
  ([
    "action":		"$N斂劍半步﹐一式『守山如嶽』凝守待機﹐借勢回刺$n的$l",
    "dodge":		8,
    "attack":		8,
    "force":		12,
    "damage":		17,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝劍如淵﹐隨$n勢老﹐$w沉穩後發直透$n的$l",
    "dodge":		10,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕凰翔三疊劍最盛一式﹐三疊劍勢層層暴漲、攻勢凌厲 ——
  ([
    "action":		"$N足尖一點凌空而起﹐一式『九天鳳翔』三疊劍光層層暴漲儘數攢向$n的$l",
    "dodge":		-15,
    "attack":		12,
    "force":		16,
    "damage":		21,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐劍身一線寒芒不滅﹐沉腰落樁穩如青嶂﹐靜待出手的時機。\n",
  "$N斂劍而立﹐劍意內蘊如鳳棲山巔﹐攻守之勢蓄而不發。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("jianling-sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("jianling-sword", "凰翔三疊劍");
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

  damage = COMBAT_D->fight(me, opponent, "jianling-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
