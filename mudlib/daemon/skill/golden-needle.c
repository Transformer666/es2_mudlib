// 金針渡劫針法 golden-needle -- 龍圖丹派「杏林神手」進階(二轉)的高階針法(基礎技能 needle)
//
// 龍圖丹派針法一脈的精進(見 docs/03-門派與武功/07-方士-龍圖武陀.md §龍圖丹派
// 進階﹕醫師)﹐由入門武陀灸術【驚異二針】(amazing-needle)精修而成﹐金針渡厄、
// 辨穴施針、針到病除。比照入門針法 daemon (amazing-needle.c/wuto-needle.c) 之
// actions 招式表模型建立﹐基礎技能型別為 needle (針術)﹐見 feature/weapon/needle.c。
//
// 因基礎技能為 needle (針法)﹐玩家透過 map_skill("needle","golden-needle") 對應後即可
// 持銀針施展(杏林神手進階時師父自動掛上此映射)。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹕招式 damage 13~20(入門 amazing-needle
//   為 5~10)﹐高階式帶 "attack"(命中加成)與 "force"(吃龍圖心經 dragon force 的內力
//   加成係數﹐見 combatd.c::fight() 之 force_bonus 公式)。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// TODO(杏林神手完整化)：docs 載龍圖針法主玩法有辨穴/封脈/針到病除之治療輔助與
//   神(sen)消耗等機制﹐屬 heal/combat 系統(非招式表)﹐標記為待辦。本檔先把帶「金針
//   渡劫」氣象的普攻針招做實﹐與 amazing-needle、白象 wen-staff 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手腕一沉﹐一式『金針渡劫』疾點$n的$l",
    "dodge":		-5,
    "attack":		5,
    "force":		6,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N指尖一彈﹐$w如金蛇吐信扎入$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝神辨穴﹐一式『渡厄封經』精準點向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指夾針﹐一式『金針引氣』連環扎向$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腕底翻針﹐$w詭異地繞向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  // —— 守勢式﹕退步藏針、凝而後發(正 dodge) ——
  ([
    "action":		"$N退步藏針卸其鋒銳﹐隨即一式『迴針倒馬』反扎$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝針候時避其攻勢﹐$w凝而後發疾刺$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		6,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕金針渡劫最盛一式﹐金光乍現、針勢暴漲 ——
  ([
    "action":		"$N凝神貫氣於針﹐一式『金針渡劫』$w攜千鈞之勁透穴扎向$n的$l",
    "dodge":		-14,
    "attack":		10,
    "force":		14,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙指夾著$w﹐針尖泛著金光微顫﹐凝神辨認著$n身上的穴位﹐靜待出手的時機。\n",
  "$N腕底藏針﹐一股醇和內息自指端涌入針身﹐尋找著進針的死角。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("golden-needle");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("golden-needle", "金針渡劫針法");
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

  damage = COMBAT_D->fight(me, opponent, "golden-needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
