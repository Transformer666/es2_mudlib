// 神威劍訣 royal-sword -- 大內巡院「大內高手」進階(二轉)的高階劍法(基礎技能 sword)
//
// 大內高手是大內巡院 docs 明列的進階(見 docs/03-門派與武功/06-軍人-振武大內.md
// §2 大內巡院 soldier.royal-進階：大內高手)。docs 載大內巡院進階授「穹槍訣
// (sky_pike)：神威下攻擊對目標精傷﹐按陰陽五行技能」。惟本門統領李天剛以大內劍法
// (sword)入門(非龍神槍法 pike)﹐故承「穹」之神威精傷之意改以劍訣承之﹐命名「神威
// 劍訣 royal-sword」﹐用以承載大內高手「神威護駕、削敵精氣」的招式氣象﹔字典
// data/chinese.o 查無此 key﹐以 CHINESE_D->add_translate() 自行登錄中文名「神威劍訣」。
//
// 比照 daemon/skill/danei_sword.c(入門大內劍法)、daemon/skill/guardtiger-blade.c
// 之 actions 招式表模型建立﹐較入門略強並帶 "attack"/"force" 係數(吃大內罡氣
// danei force 的內力加成﹐見 combatd.c::fight() force_bonus 公式)。基礎技能為
// sword(劍法)。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 12~18(入門 danei sword 為 5~10)﹐高階式帶 attack 5~10 與 force 6~12。
//
// TODO(大內高手完整化)：docs 載穹槍訣「神威狀態下對目標精傷、按陰陽五行技能」。
//   神威狀態(royal)、精氣傷害(非血傷)與按五行技能加成屬 combat/perform 系統(非招式
//   表)﹐標記為待辦。本檔先把帶神威氣象的普攻劍招做實﹐與入門 danei sword、冷梅
//   hanshuang 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N按劍肅立﹐$w一式『神威臨陣』凝勁平刺$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		12,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N沉肩進步﹐$w化作一道森寒劍光當頭劈向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		6,
    "damage":		14,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N足下錯步﹐一式『護駕巡天』$w自下撩向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N長身而進﹐$w如游龍出水﹐連環疾刺$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  // —— 守勢式﹕大內高手宿衛護駕、攻守兼備之意(正 dodge、沉穩按劍待機) ——
  ([
    "action":		"$N橫劍於身前一式『按劍待命』凝守﹐借勢回刺$n的$l",
    "dodge":		10,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N斂劍蓄勢隨$n勢老﹐$w沉穩後發貫向$n的$l",
    "dodge":		10,
    "attack":		7,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N側身一閃避其鋒銳﹐隨即一式『金鑾橫掃』平掃$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		6,
    "damage":		13,
    "damage_type":	"砍傷"
  ]),
  // —— 殺著﹕神威劍訣真氣鼓盪、一劍貫頂 ——
  ([
    "action":		"$N周身真氣鼓盪如有神威加身﹐一式『神威貫頂』$w挾雷霆之勢直刺$n的$l",
    "dodge":		-10,
    "attack":		10,
    "force":		12,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N橫劍於胸沉腰按樁穩如山嶽﹐周身似有森嚴護體真氣流轉﹐凝神注視著$n的動靜。\n",
  "$N長劍斜引劍尖微垂﹐如宿衛按劍待命﹐神威內蘊﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("royal-sword");
  // 字典查無此 key﹐自行登錄中文名「神威劍訣」。
  CHINESE_D->add_translate("royal-sword", "神威劍訣");
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

  damage = COMBAT_D->fight(me, opponent, "royal-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
