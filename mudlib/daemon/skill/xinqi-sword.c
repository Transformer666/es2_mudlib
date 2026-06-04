// 心氣劍 xinqi-sword -- 封山派「劍客」進階(二轉)的心氣系劍法(基礎技能 sword)
//
// 封山派劍客一脈「擁有神芒、心氣四種劍系﹐4 選 2 切換」(見 docs/03-門派與
// 武功/01-武者-五大門派.md §1 封山派-劍客)。心氣系「上弦月帶下弦月(恐怖
// 精傷)」(評分 防禦 B / 續戰 B)﹐相較神芒系的強攻﹐心氣系重在綿密守勢、
// 以心馭氣、藉連月劍勢持續削敵之精(gin)。
//
// 比照 daemon/skill/aomei-jian.c / aojian-jue.c 之 actions 招式表模型建立。
// 心氣系守勢綿密﹐故本表多帶正 dodge(守勢、後發)﹐damage 中庸而 force 係數
// 偏高(以心馭氣)。玩家透過 map_skill("sword","xinqi-sword") 對應後即可施展﹐
// 與神芒劍 shenmang-sword「4 選 2 切換」由玩家自行 map_skill 切換。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「心氣劍」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 13~18(較神芒系為低﹐重守勢續戰)﹐多式帶正 dodge 與較高 force。
//
// TODO(劍客完整化)：docs 載心氣系『上弦月帶下弦月』為恐怖精傷﹐其打擊精
//   (gin)屬 combat/perform 系統(非招式表)﹐標記為待辦。本檔先把守勢普攻
//   招式做實﹐與冷梅諸進階招式同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N斂劍於懷以心馭氣﹐一式『心月含光』凝守虛指$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		8,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N長劍圓轉如環﹐先守後攻﹐$w隨$n勢老回刺$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N劍劃一彎『上弦月』綿綿不絕地纏向$n的$l",
    "dodge":		5,
    "attack":		6,
    "force":		10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N上弦月勢未盡﹐順勢一彎『下弦月』回削﹐連月劍氣切向$n的$l",
    "dodge":		8,
    "attack":		7,
    "force":		12,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式『靜水凝心』﹐劍勢沉穩封守逼向$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝劍如淵﹐心氣相隨﹐$w後發先至直透$n的$l",
    "dodge":		-5,
    "attack":		7,
    "force":		10,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N劍走綿勁如抽絲﹐一式『心隨月轉』層層纏削$n的$l",
    "dodge":		6,
    "attack":		6,
    "force":		10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  // —— 殺著﹕心氣劍最盛一式﹐上弦下弦連月並出、削敵心氣 ——
  ([
    "action":		"$N以心馭氣﹐一式『雙月連環』上弦下弦並作一道劍氣絞向$n的$l",
    "dodge":		-8,
    "attack":		9,
    "force":		14,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N長劍斜垂﹐神色從容如止水凝心﹐劍意內蘊不露鋒芒﹐靜候$n的破綻。\n",
  "$N斂劍而立﹐以心馭氣綿綿不絕﹐殺機暗藏於波瀾不興之中。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("xinqi-sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("xinqi-sword", "心氣劍");
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

  damage = COMBAT_D->fight(me, opponent, "xinqi-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
