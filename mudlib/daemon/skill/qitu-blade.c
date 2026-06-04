// 棄徒反擊刀 qitu-blade -- 雪吟莊「棄徒」進階(二轉)的反擊刀法(基礎技能 blade)
//
// 棄徒一脈「靠反擊吃飯」(見 docs/03-門派與武功/01-武者-五大門派.md §4 雪吟莊-
// 棄徒﹕「看移動力而不是護甲、沒有補 hp、右手可持劍或選數字刀、perform 後
// 看得到鬼魂、天邪神功 190+ 占決定性因素、續戰 A」)。本刀法重在卸力借勢、
// 後發反撩﹐故多守勢式(正 dodge)、招式 damage 隨反擊愈烈愈高﹐並帶 "force"
// 吃天邪神功(tianxie-force)的超高 kee(力道公式見 combatd.c::fight()
// force_bonus)──呼應「天邪神功 190+ 占決定性因素」。
//
// 基礎技能為 blade(docs 載棄徒右手可持劍或數字刀﹐本門入門即慣用單刀﹐
// 故掛 blade)﹔玩家透過 map_skill("blade","qitu-blade") 對應後即可施展。
// weapon 物件由 attack_using 一路傳入 COMBAT_D->fight()﹐與 deepblade.c 一致。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「棄徒反擊刀」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 13~18﹐守勢反擊式占多數(正 dodge)﹐帶 force 8~14 吃天邪內力。
//
// TODO(棄徒完整化)：docs 載棄徒「靠反擊吃飯、看移動力非護甲、沒補 hp、
//   perform 後看得到鬼魂」﹐其反擊觸發、移動力減傷、陰陽眼等屬 combat/perform
//   系統(非招式表)﹐標記為待辦。本檔先把反擊刀招做實。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  // —— 反擊主軸﹕卸力後發、借勢反撩(正 dodge) ——
  ([
    "action":		"$N側身一卸來勢﹐$w順勢一式『以彼之道』反斬$n的$l",
    "dodge":		10,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N佯作退避﹐待$n勢老﹐$w驟然回挑撩向$n的$l",
    "dodge":		12,
    "attack":		7,
    "force":		10,
    "damage":		14,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N足下游走如鬼魅﹐$w借力打力、後發先至斬向$n的$l",
    "dodge":		8,
    "attack":		7,
    "force":		10,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N一式『還施彼身』﹐$w挾天邪煞氣纏住$n刀勢順勢回劈$n的$l",
    "dodge":		10,
    "attack":		8,
    "force":		12,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  // —— 進擊式﹕反擊得勢後乘隙搶攻(負 dodge) ——
  ([
    "action":		"$N得勢不饒人﹐$w化作一片寒光連環疾斬$n的$l",
    "dodge":		-8,
    "attack":		7,
    "force":		10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一聲冷哼﹐$w挾天邪真氣當頭直劈$n的$l",
    "dodge":		-6,
    "attack":		8,
    "force":		12,
    "damage":		16,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N身形如鬼魂飄忽﹐$w自刁鑽角度斜挑$n的$l",
    "dodge":		-10,
    "attack":		8,
    "force":		12,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
  // —— 殺著﹕棄徒反擊最盛一式﹐天邪神功貫注、後發必殺 ——
  ([
    "action":		"$N周身天邪真氣暴漲﹐一式『棄徒問天』後發制人狂斬$n的$l",
    "dodge":		6,
    "attack":		10,
    "force":		14,
    "damage":		18,
    "damage_type":	"砍傷"
  ]),
});

string *interattack = ({
  "$N橫刀斜引﹐身形如鬼魅飄忽﹐天邪煞氣陰冷流轉﹐靜候$n露出破綻。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("qitu-blade");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("qitu-blade", "棄徒反擊刀");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (MAG + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "qitu-blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
