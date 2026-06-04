// 霸甲針法 hegen-needle -- 武陀灸堂「香主」進階(二轉)的高階針法(基礎技能 needle)
//
// 武陀灸堂針法一脈的精進(見 docs/03-門派與武功/07-方士-龍圖武陀.md §武陀灸堂
// 進階﹕香主)。docs 載香主「霸氣針後穿滿傷害破 250﹐是團隊不可或缺的 buff 來源」﹐
// 故定位為由入門五敗針法(wuto-needle)精修而成、攻補一體的上乘針法──霸甲(霸氣)
// 一脈以針布甲、灌氣增傷。比照入門針法 daemon (wuto-needle.c) 與龍圖系
// golden-needle.c/dragon-needle.c 之 actions 招式表模型建立﹐基礎技能型別為
// needle (針術)﹐見 feature/weapon/needle.c。
//
// 因基礎技能為 needle (針法)﹐玩家透過 map_skill("needle","hegen-needle") 對應後即可
// 持銀針施展(香主進階時師父自動掛上此映射)。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹕招式 damage 14~22(高於入門五敗針法
//   wuto-needle 的 5~10)﹐高階式帶 "attack"(命中加成)與 "force"(吃武陀心法 wuto force
//   的內力加成係數﹐見 combatd.c::fight() 之 force_bonus 公式)。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// TODO(香主完整化)：docs 載香主主玩法為「霸甲(神→護甲)/霸氣(神→傷害)針 buff、
//   對自己效果 4 倍、穿滿傷害破 250」等增益機制﹐屬 buff/heal 系統(非招式表)﹐
//   標記為待辦。本檔先把帶「霸甲針法」氣象的普攻針招做實﹐與 golden-needle、
//   dragon-needle 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手腕一沉﹐一式『霸甲起手』疾點$n的$l",
    "dodge":		-5,
    "attack":		5,
    "force":		7,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N指尖一彈﹐$w灌注真氣如銀蛇吐信扎入$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝神辨穴﹐一式『霸氣封經』精準點向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		9,
    "damage":		17,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指夾針﹐一式『布甲引氣』連環扎向$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		11,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腕底翻針﹐$w攜一縷霸氣詭異地繞向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		9,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  // —— 守勢式﹕退步藏針、凝而後發(正 dodge) ——
  ([
    "action":		"$N退步藏針卸其鋒銳﹐隨即一式『霸甲反扎』疾刺$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		9,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝針候時避其攻勢﹐$w凝而後發疾刺$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		7,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕霸甲針法最盛一式﹐霸氣灌針、針勢暴漲 ——
  ([
    "action":		"$N真氣灌注於針大喝一聲﹐一式『霸氣穿甲』$w攜萬鈞之勢透穴轟向$n的$l",
    "dodge":		-14,
    "attack":		11,
    "force":		15,
    "damage":		22,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙指夾著$w﹐針身泛著一層淡淡霸氣微顫﹐凝神辨認著$n身上的穴位﹐靜待出手的時機。\n",
  "$N腕底藏針﹐一股醇厚內息自丹田涌入針端﹐尋找著進針的死角。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("hegen-needle");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("hegen-needle", "霸甲針法");
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

  damage = COMBAT_D->fight(me, opponent, "hegen-needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
