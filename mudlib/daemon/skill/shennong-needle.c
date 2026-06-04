// 神農針法 shennong-needle -- 武陀灸堂「神農上人」進階(二轉)的最高階針法(基礎技能 needle)
//
// 武陀灸堂針法、灸術之大成(見 docs/03-門派與武功/07-方士-龍圖武陀.md §武陀灸堂﹔
// docs 載武陀堂「可修習神農之術」、核心技能 alchemy-medication 為「丹道【神農之術】」)。
// 神農針法承五敗針法(wuto-needle)、霸甲針法(hegen-needle)登峰造極而成﹐神農嘗百草、
// 辨穴施針、針鋒所至活人無數。比照入門針法 daemon (wuto-needle.c) 與龍圖系最高階
// dragon-needle.c 之 actions 招式表模型建立﹐基礎技能型別為 needle (針術)﹐見
// feature/weapon/needle.c。
//
// 因基礎技能為 needle (針法)﹐玩家透過 map_skill("needle","shennong-needle") 對應後即可
// 持銀針施展(神農上人進階時師父自動掛上此映射)。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹕招式 damage 16~24(高於霸甲針法
//   hegen-needle 的 14~22)﹐高階式帶較高 "attack"(命中加成)與 "force"(吃神農真經
//   shennong force 的內力加成係數﹐見 combatd.c::fight() 之 force_bonus 公式)。
//
// 設計(docs未明定分支名)：docs 武陀灸堂明列進階為「香主、劍甲門傳人」二路﹔
//   「神農上人」為承武陀「神農之術」一脈、針法/灸術之大成的最高一階﹐與龍圖丹派
//   最高階「龍圖丹師」對位。詳見師父 d/wuto/npc/master.c 的進階註解。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// TODO(神農上人完整化)：docs 載武陀灸堂主玩法有辨穴/針到病除之治療輔助、神農之術
//   (alchemy-medication)等收益/治療機制﹐屬 heal/craft 系統(非招式表)﹐標記為待辦。
//   本檔先把帶「神農針法」氣象的普攻針招做實﹐與 dragon-needle、golden-needle 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手腕微沉﹐一式『神農起手』疾點$n的$l",
    "dodge":		-6,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N指尖一抖﹐$w如百草拂風扎入$n的$l",
    "dodge":		-9,
    "attack":		7,
    "force":		9,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝神辨穴﹐一式『神農封脈』精準點向$n的$l",
    "dodge":		-11,
    "attack":		8,
    "force":		10,
    "damage":		19,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指夾針﹐一式『嘗草引氣』連環扎向$n的$l",
    "dodge":		-13,
    "attack":		8,
    "force":		12,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腕底翻針﹐$w化作一道銀虹繞向$n的$l",
    "dodge":		-9,
    "attack":		7,
    "force":		10,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  // —— 守勢式﹕退步藏針、凝而後發(正 dodge) ——
  ([
    "action":		"$N退步藏針卸其鋒銳﹐隨即一式『神農迴針』反扎$n的$l",
    "dodge":		9,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝針候時避其攻勢﹐$w凝而後發疾刺$n的$l",
    "dodge":		11,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕神農針法最盛一式﹐百草歸元、針勢暴漲 ——
  ([
    "action":		"$N真氣灌注於針大喝一聲﹐一式『神農百草針』$w攜萬鈞醇厚之勁透穴轟向$n的$l",
    "dodge":		-16,
    "attack":		12,
    "force":		16,
    "damage":		24,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙指夾著$w﹐針身似有一縷草木生機繚繞﹐凝神辨認著$n身上的穴位﹐靜待出手的時機。\n",
  "$N腕底藏針﹐神農真經內息自丹田勃然涌入針端﹐尋找著進針的死角。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("shennong-needle");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("shennong-needle", "神農針法");
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

  damage = COMBAT_D->fight(me, opponent, "shennong-needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
