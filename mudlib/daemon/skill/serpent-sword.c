// 金蛇劍法 serpent sword -- 瑯夷派「金蛇門人」進階(二轉)的主武功劍法(基礎技能 sword)
//
// 金蛇門人俗稱「戰鬥賊」﹐捨瑯夷暗算之匕、改以右手持劍快攻(見 docs/03-門派與武功/
// 05-盜賊-瑯夷隱教.md §進階分支-金蛇門人﹕「右手持劍、左手搭配槍法」、「戰鬥中靠
// 快速背刺有驚人破壞力」)。金蛇劍法劍走輕靈、招式刁鑽如金蛇吐信﹐是金蛇門人持劍
// 搶攻、背刺暴擊的根本殺招﹐瑯夷派證入「金蛇門人」一階方得傳授。比照天邪虎嘯
// daemon/skill/tianxie-roar.c 之 actions 招式表模型建立﹐基礎技能為 sword(劍法)。
//
// 因基礎技能為 sword﹐金蛇門人捨匕習劍﹐進階時師父自動掛上 map_skill("sword",
// "serpent sword")。中文字典查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 「金蛇劍法」。
//
// 數值為本次設計值(docs 只給評分非確切數字﹐攻評 S)﹐供日後平衡微調﹕招式 damage
//   15~23﹐傷害型別「割傷/刺傷」﹐多式帶 "force" 吃金蛇罡氣(serpent-force)的力道加成。
//
// TODO(金蛇門人完整化)：docs「快速背刺暴擊」、「蛇感提升警覺」屬 backstab/警覺/
//   perform 系統(非招式表)﹐標記為待辦。本檔先把金蛇持劍快攻的普攻招式做實。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N$w一抖﹐劍尖如金蛇吐信疾點$n的$l",
    "dodge":		-8,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足下一錯欺身搶進﹐一式『金蛇出洞』$w斜削$n的$l",
    "dodge":		-12,
    "attack":		8,
    "force":		10,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N手腕翻轉﹐$w如靈蛇盤曲詭異地繞向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		9,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身形飄忽繞至側後﹐$w貼著$n的$l陰狠抹過",
    "dodge":		-12,
    "attack":		9,
    "force":		11,
    "damage":		19,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式『金蛇噬心』﹐$w自死角刁鑽地刺向$n的$l",
    "dodge":		-10,
    "attack":		8,
    "force":		10,
    "damage":		17,
    "damage_type":	"刺傷"
  ]),
  // —— 守勢式﹕金蛇劍法少數退而後發之招﹐借勢回刺(正 dodge) ——
  ([
    "action":		"$N退步藏鋒卸去來勢﹐隨即凝而後發疾撩$n的$l",
    "dodge":		7,
    "attack":		8,
    "force":		9,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N佯作收劍矮身一沉﹐$w自下而上挑向$n的$l",
    "dodge":		8,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕金蛇劍法最盛一式﹐快攻暴起、一劍封喉 ——
  ([
    "action":		"$N殺機陡盛欺身直進﹐一式『金蛇封喉』$w攜凜冽劍光直透$n的$l",
    "dodge":		-16,
    "attack":		13,
    "force":		14,
    "damage":		23,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N$n斜引劍尖內斂﹐如金蛇蟄伏﹐殺機暗藏只待暴起噬人的時機。\n",
  "$N足尖無聲游走尋著死角﹐$n貼身覷著破綻﹐只待一劍封喉。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("serpent sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("serpent sword", "金蛇劍法");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIY + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "serpent sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
