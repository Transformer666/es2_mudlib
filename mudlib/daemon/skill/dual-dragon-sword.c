// 步玄雙龍劍氣 dual-dragon-sword -- 步玄派「居士」進階(二轉)的高階雙劍劍法(基礎技能 sword)
//
// 居士由入門「小步玄劍 buxuan-sword」精進而成的殺著。步玄派以雙劍佐控場
// (見 docs/03-門派與武功/04-書生-步玄玄天.md §步玄派-核心技能「小步玄劍 ──
// 雙劍」)﹐居士主修的步玄雙龍劍氣乃雙劍合璧、雙龍出海的上乘劍訣﹔docs
// §9/2 平衡明載「步玄雙龍劍氣 必兩次命中」﹐故本表招式以雙劍連環、一招
// 兩擊的氣象呈現﹐並較入門小步玄劍 damage 高一階、另帶 attack(命中)與
// force(內力)係數(見 combatd.c::fight() 之 force_bonus 公式)。
//
// 玩家透過 map_skill("sword","dual-dragon-sword") 將劍法對應到本招式後﹐
// 戰鬥時 COMBAT_D->fight() 即依本表施展。步玄雙龍劍氣配合乾坤三轉心法
// (qiankun-force)的內力而威力倍增。步玄雙龍劍氣在中文字典尚無詞條﹐故於
// create() 時以 CHINESE_D->add_translate() 自行登錄中文名﹐使 skills /
// score 等指令工整顯示。
//
// 數值為本次設計值(docs 只給「必兩次命中」之機制非確切數字)﹐供日後平衡
// 微調﹕damage 15~22(入門 buxuan-sword 為 5~10)﹐高階兩式另帶 attack 8~12
// 與 force 10~18(入門無 force 係數)。
// TODO(雙擊完整化)：docs「必兩次命中」屬 perform/連擊判定系統﹐本檔先以招式
//   「雙劍連環、一招兩擊」之敘事與較高 attack/damage 體現﹐連擊保證邏輯標記為待辦。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N雙劍交錯﹐$w化作兩道青虹同時刺向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腳踏玄步﹐一式『雙龍出海』﹐$w盤旋雙撩$n的$l",
    "dodge":		-10,
    "attack":		6,
    "force":		8,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N雙劍輕顫﹐左右劍尖暴吐連環寒星﹐先後疾刺$n的$l",
    "dodge":		-12,
    "attack":		8,
    "force":		10,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身形一轉﹐一式『雙龍搶珠』﹐$w如行雲流水雙貫$n的$l",
    "dodge":		-15,
    "attack":		8,
    "force":		12,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N側身遊走﹐$w斜斜挑起一蓬青濛劍氣﹐儘數罩向$n的$l",
    "dodge":		-10,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
  // —— 攻防一體﹕正 dodge﹐雙劍互為攻守、先守後發之勢 ——
  ([
    "action":		"$N斂劍半步﹐待$n勢老即還﹐一式『雙龍纏絲』後發制人斬向$n的$l",
    "dodge":		8,
    "attack":		10,
    "force":		14,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N雙劍凝而不發﹐隨$n破綻一現﹐左劍佯攻右劍直透$n的$l",
    "dodge":		10,
    "attack":		8,
    "force":		12,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕步玄雙龍劍氣最盛一式﹐雙龍合璧、一招兩擊 ——
  ([
    "action":		"$N足尖一點凌空而起﹐一式『雙龍劍氣』兩道青芒前後相銜攢向$n的$l",
    "dodge":		-15,
    "attack":		12,
    "force":		18,
    "damage":		22,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙劍斜引﹐步法暗轉﹐宛如閒庭信步﹐雙龍蟄伏﹐靜待出手的時機。\n",
  "$N斂雙劍而立﹐劍意內蘊如行雲流水﹐殺機暗藏於波瀾不興之中。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("dual-dragon-sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("dual-dragon-sword", "步玄雙龍劍氣");
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

  damage = COMBAT_D->fight(me, opponent, "dual-dragon-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
