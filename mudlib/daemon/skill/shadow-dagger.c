// 奪命血魂匕 shadow dagger -- 瑯夷派「黑龍左使」進階(二轉)的高階匕法(基礎技能 dagger)
//
// 瑯夷派黑龍左使一脈最狠辣的暗算殺招(見 docs/03-門派與武功/05-盜賊-瑯夷隱教.md
// §進階分支-黑龍左使﹕「攻擊狀態脫離有機會造成一擊必殺技」、偷襲/暗算/殺手本能)。
// 由入門血魂匕法(blood dagger)精進而成﹐專走死角、見血追命﹐是瑯夷派證入「黑龍
// 左使」一階方得傳授的殺著。比照白象寺達摩烈焰刀 daemon/skill/damo-blade.c 之
// actions 招式表模型建立﹐基礎技能為 dagger(匕法/錐法)﹐反手持匕施展﹐attack_using
// 第三參數為兵器物件(weapon)。
//
// 因基礎技能為 dagger(匕法)﹐玩家透過 map_skill("dagger","shadow dagger") 對應後即可
// 持匕施展(黑龍左使進階時師父自動掛上此映射)。中文字典(data/chinese.o)查無此 key﹐
// 以 CHINESE_D->add_translate() 自行登錄。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹐供日後平衡微調﹕招式 damage 14~22
//   (高於入門 blood dagger 5~10)﹐死角偷襲式帶 "attack"(命中加成﹐應暗算之利)與
//   "force"(吃瑯夷派內功 longyeforce 的內力加成係數)﹐殺著一式為見血追命之最盛一擊。
//
// TODO(黑龍左使完整化)：docs 載黑龍左使「攻擊狀態脫離有機會造成一擊必殺技(打 hp)」、
//   「消除疲勞內功」﹐其「脫戰必殺 / 疲勞清除」屬 perform/combat 系統(非招式表)﹐標記
//   為待辦。本檔先把帶「奪命血魂」氣象的普攻匕招做實﹐與白象 damo-blade、虎刀 tiger-blade
//   同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N壓低身形貼地搶進﹐$w自下而上一式『血魂索命』挑向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腕底一抖殺機暴起﹐$w如毒蛇吐信疾刺$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		10,
    "damage":		17,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足尖一錯欺身近前﹐一式『黑龍出洞』狠割$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形飄忽繞至側後﹐$w貼著$n的$l陰狠抹過",
    "dodge":		-12,
    "attack":		8,
    "force":		11,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N手腕翻轉﹐$w如黑龍纏絲詭異地繞向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  // —— 守勢式﹕奪命血魂匕少數退而後發之招﹐借勢回刺(正 dodge) ——
  ([
    "action":		"$N退步藏鋒卸去來勢﹐隨即凝而後發疾撩$n的$l",
    "dodge":		7,
    "attack":		7,
    "force":		9,
    "damage":		14,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N佯作收手矮身一沉﹐$w自死角斜斜挑向$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕奪命血魂匕最狠一式﹐見血追命、一擊索魂 ——
  ([
    "action":		"$N殺氣陡盛踏死角而進﹐一式『赤魂奪命』$w攜噬人血光直透$n的$l",
    "dodge":		-16,
    "attack":		12,
    "force":		15,
    "damage":		22,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N反手握著$n刃光內斂﹐如毒蛇蟄伏﹐殺機暗藏只待噬人的時機。\n",
  "$N足尖無聲游走尋著死角﹐$n貼身斜引﹐凝而不發地覷著破綻。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("shadow dagger");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("shadow dagger", "奪命血魂匕");
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

  damage = COMBAT_D->fight(me, opponent, "shadow dagger", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
