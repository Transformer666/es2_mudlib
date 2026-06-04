// 噬魂毒匕 venom dagger -- 瑯夷派「黑龍右使」進階(二轉)的高階毒匕(基礎技能 dagger)
//
// 黑龍右使一脈以毒證道的殺著(見 docs/03-門派與武功/05-盜賊-瑯夷隱教.md §進階分支-
// 黑龍右使﹕「將身上的毒傳遞給敵人」、「適合暗殺掌門級 NPC」)。由入門血魂匕法
// (blood dagger)轉走用毒一路﹐刃淬奇毒、見血封喉﹐是瑯夷派證入「黑龍右使」一階
// 方得傳授的毒匕。比照奪命血魂匕 daemon/skill/shadow-dagger.c 之 actions 招式表
// 模型建立﹐基礎技能為 dagger(匕法/錐法)﹐反手持匕施展﹐attack_using 第三參數為
// 兵器物件(weapon)。
//
// 因基礎技能為 dagger﹐玩家透過 map_skill("dagger","venom dagger") 對應後即可持匕
// 施展(黑龍右使進階時師父自動掛上此映射)。中文字典(data/chinese.o)查無此 key﹐
// 以 CHINESE_D->add_translate() 自行登錄「噬魂毒匕」。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹐供日後平衡微調﹕招式 damage 13~20﹐
//   傷害型別取「毒傷」呼應用毒一脈﹐死角偷襲式帶 "attack"(命中加成)與 "force"(吃
//   龍涎毒功 venom-force 的內力加成係數)﹐殺著一式為見血淬毒之最盛一擊。
//
// TODO(黑龍右使完整化)：docs 載黑龍右使「隔空遞毒、不進戰鬥即毒殺」﹐其「遞毒/
//   毒殺」屬 perform/poison 系統(非招式表)﹐標記為待辦。本檔先把帶「噬魂毒匕」
//   氣象的普攻毒匕做實﹐與瑯夷 shadow-dagger 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N壓低身形貼地搶進﹐$w淬著奇毒自下而上挑向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"毒傷"
  ]),
  ([
    "action":		"$N腕底一抖殺機暴起﹐$w如毒蛇吐信疾刺$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"毒傷"
  ]),
  ([
    "action":		"$N足尖一錯欺身近前﹐一式『龍涎噬骨』狠割$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		15,
    "damage_type":	"毒傷"
  ]),
  ([
    "action":		"$N身形飄忽繞至側後﹐$w攜幽碧毒華貼著$n的$l陰狠抹過",
    "dodge":		-12,
    "attack":		8,
    "force":		11,
    "damage":		17,
    "damage_type":	"毒傷"
  ]),
  ([
    "action":		"$N手腕翻轉﹐$w如毒龍纏絲詭異地繞向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"毒傷"
  ]),
  // —— 守勢式﹕噬魂毒匕少數退而後發之招﹐借勢回刺淬毒(正 dodge) ——
  ([
    "action":		"$N退步藏鋒卸去來勢﹐隨即凝而後發疾撩$n的$l",
    "dodge":		7,
    "attack":		7,
    "force":		9,
    "damage":		13,
    "damage_type":	"毒傷"
  ]),
  ([
    "action":		"$N佯作收手矮身一沉﹐$w自死角斜斜挑向$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"毒傷"
  ]),
  // —— 殺著﹕噬魂毒匕最狠一式﹐見血淬毒、封喉索魂 ——
  ([
    "action":		"$N殺氣陡盛踏死角而進﹐一式『噬魂封喉』$w攜劇毒血光直透$n的$l",
    "dodge":		-16,
    "attack":		12,
    "force":		15,
    "damage":		20,
    "damage_type":	"毒傷"
  ]),
});

string *interattack = ({
  "$N反手握著$n刃上毒華隱隱﹐如毒蛇蟄伏﹐殺機暗藏只待噬人的時機。\n",
  "$N足尖無聲游走尋著死角﹐$n貼身斜引﹐凝而不發地覷著下毒的破綻。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("venom dagger");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("venom dagger", "噬魂毒匕");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (GRN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "venom dagger", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
