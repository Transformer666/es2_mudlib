// 金蛇槍法 serpent pike -- 瑯夷派「金蛇門人」進階(二轉)的副武功槍法(基礎技能 pike)
//
// 金蛇門人「右手持劍、左手搭配槍法」(見 docs/03-門派與武功/05-盜賊-瑯夷隱教.md
// §進階分支-金蛇門人)﹐金蛇槍法即其左手所配的副武功﹐與右手金蛇劍法(serpent
// sword)相輔相成﹕劍走刁鑽快攻、槍走長距牽制﹐攻評達 S。金蛇槍法槍勢綿密、
// 戳挑點刺如金蛇纏身﹐瑯夷派證入「金蛇門人」一階方得連同金蛇劍法一併傳授。
// 比照 daemon/skill/serpent-sword.c 之 actions 招式表模型建立﹐基礎技能為
// pike(槍法)﹐見 feature/weapon/pike.c。
//
// 因基礎技能為 pike﹐進階時師父 set_skill 授此招式並掛 unmap/留待玩家
// map_skill("pike","serpent pike") 切換(金蛇門人以 sword 為主映射﹐pike 為副)。
// 中文字典查無此 key﹐以 CHINESE_D->add_translate() 自行登錄「金蛇槍法」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕招式 damage 14~21﹐
//   傷害型別「刺傷」呼應槍法﹐多式帶 "force" 吃金蛇罡氣(serpent-force)的力道加成。
//
// TODO(金蛇門人完整化)：docs 雙持劍槍協同、快速背刺暴擊屬 combat/perform 系統
//   (非招式表)﹐標記為待辦。本檔先把金蛇槍法的普攻招式做實。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N$w平端﹐槍尖如金蛇吐信疾戳$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足下一頓﹐一式『金蛇纏身』$w盤旋著挑向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N$w一抖﹐槍花亂顫如靈蛇盤曲詭異地點向$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		10,
    "damage":		17,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N長身搶進﹐$w借勢前送狠戳$n的$l",
    "dodge":		-10,
    "attack":		8,
    "force":		11,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『金蛇盤柱』﹐$w自死角刁鑽地撩向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		9,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  // —— 守勢式﹕金蛇槍法借長距退而後發、凝而後刺(正 dodge) ——
  ([
    "action":		"$N回槍卸去來勢﹐隨即凝而後發疾戳$n的$l",
    "dodge":		8,
    "attack":		7,
    "force":		9,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N槍尖一沉佯作收勢﹐$w自下而上挑向$n的$l",
    "dodge":		7,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕金蛇槍法最盛一式﹐長驅直入、一槍穿心 ——
  ([
    "action":		"$N槍勢陡盛長身直進﹐一式『金蛇穿心』$w攜凜冽槍風直透$n的$l",
    "dodge":		-16,
    "attack":		11,
    "force":		14,
    "damage":		21,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N$n斜引槍尖內斂﹐如金蛇蟄伏﹐殺機暗藏只待暴起穿心的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("serpent pike");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("serpent pike", "金蛇槍法");
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

  damage = COMBAT_D->fight(me, opponent, "serpent pike", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
