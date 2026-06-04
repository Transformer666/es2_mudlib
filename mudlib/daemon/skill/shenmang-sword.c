// 神芒劍 shenmang-sword -- 封山派「劍客」進階(二轉)的神芒系劍法(基礎技能 sword)
//
// 封山派劍客一脈「擁有神芒、心氣四種劍系﹐4 選 2 切換」(見 docs/03-門派與
// 武功/01-武者-五大門派.md §1 封山派-劍客)。神芒系「強攻、雙握劍或兩手劍﹐
// 可出『上弦月』(定人/對氣)、『搗亂七星步』(恐怖精傷)」(評分 攻擊 A-)。
//
// 比照 daemon/skill/aomei-sword.c / aojian-jue.c 之 actions 招式表模型建立。
// 神芒系主強攻﹐故本表 damage 與 attack 係數在封山諸劍法中最高﹐多帶 force
// (吃封山派內功 fonxanforce)。玩家透過 map_skill("sword","shenmang-sword")
// 對應後即可施展﹐另一手/另一系可 map 心氣劍 xinqi-sword(體現「4 選 2 切換」﹐
// 由玩家自行 map_skill 切換)。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「神芒劍」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 16~23(封山諸劍法中最高﹐主強攻)﹐高階式帶 attack 8~13、force 8~16。
//
// TODO(劍客完整化)：docs 載神芒系『上弦月』可定人/對氣、『搗亂七星步』為
//   恐怖精傷﹐其定身、打擊氣(kee)/精(gin)屬 combat/perform 系統(非招式表)﹐
//   標記為待辦。本檔先把強攻普攻招式做實﹐與冷梅諸進階招式同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N長劍平引﹐神芒一吐﹐一式『芒刺破雲』疾刺$n的$l",
    "dodge":		-8,
    "attack":		6,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙手握劍勢沉力猛﹐一式『神芒裂石』大開大闔斬向$n的$l",
    "dodge":		-12,
    "attack":		8,
    "force":		8,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍尖暴吐三點神芒﹐一式『芒星亂墜』連環疾刺$n的$l",
    "dodge":		-10,
    "attack":		8,
    "force":		10,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足踏奇步繞至側翼﹐一式『搗亂七星步』神芒亂閃撩向$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		12,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍走偏鋒﹐$w斜挑起一蓬神芒劍雨儘數罩向$n的$l",
    "dodge":		-10,
    "attack":		8,
    "force":		10,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N雙手劍勢一沉﹐神芒大盛﹐一式『芒鋒貫日』直透$n的$l",
    "dodge":		-13,
    "attack":		10,
    "force":		12,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
  // —— 控場式﹕神芒『上弦月』牽制之意(稍守﹐定人對氣) ——
  ([
    "action":		"$N長劍劃出一彎『上弦月』神芒﹐光華牽住$n身形﹐順勢削向$n的$l",
    "dodge":		5,
    "attack":		8,
    "force":		10,
    "damage":		17,
    "damage_type":	"割傷"
  ]),
  // —— 殺著﹕神芒劍最盛一式﹐神芒漫天、強攻爆發 ——
  ([
    "action":		"$N足尖一點凌空而起﹐一式『神芒漫天』萬道劍芒儘數攢向$n的$l",
    "dodge":		-15,
    "attack":		13,
    "force":		16,
    "damage":		23,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙手握劍斜引﹐劍身神芒隱隱欲吐﹐鋒銳逼人﹐靜待出手的時機。\n",
  "$N劍尖一線神芒流轉不息﹐殺機外露如芒在背﹐凝神鎖住$n的破綻。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("shenmang-sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("shenmang-sword", "神芒劍");
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

  damage = COMBAT_D->fight(me, opponent, "shenmang-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
