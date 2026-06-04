// 龍圖丹針 dragon-needle -- 龍圖丹派「龍圖丹師」進階(二轉)的最高階針法(基礎技能 needle)
//
// 龍圖丹派針法、丹道之大成(見 docs/03-門派與武功/07-方士-龍圖武陀.md §龍圖丹派)﹐
// 由入門武陀灸術【驚異二針】(amazing-needle)登峰造極而成﹐龍圖丹針出神入化、針鋒
// 所至活人無數。比照入門針法 daemon (amazing-needle.c) 與杏林神手 golden-needle.c 之
// actions 招式表模型建立﹐基礎技能型別為 needle (針術)﹐見 feature/weapon/needle.c。
//
// 因基礎技能為 needle (針法)﹐玩家透過 map_skill("needle","dragon-needle") 對應後即可
// 持銀針施展(龍圖丹師進階時師父自動掛上此映射)。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹕招式 damage 16~24(高於杏林神手
//   golden-needle 的 13~20)﹐高階式帶較高 "attack"(命中加成)與 "force"(吃龍圖真經
//   longtu force 的內力加成係數﹐見 combatd.c::fight() 之 force_bonus 公式)。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// TODO(龍圖丹師完整化)：docs 載龍圖一脈核心玩法有辨穴/針到病除之治療輔助、丹道
//   神農/黃白之術等收益機制﹐屬 heal/craft/economy 系統(非招式表)﹐標記為待辦。
//   本檔先把帶「龍圖丹針」氣象的普攻針招做實﹐與 golden-needle、白象 wen-staff 同
//   一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手腕微沉﹐一式『龍圖起手』疾點$n的$l",
    "dodge":		-6,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N指尖一抖﹐$w如游龍探爪扎入$n的$l",
    "dodge":		-9,
    "attack":		7,
    "force":		9,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝神辨穴﹐一式『龍圖封脈』精準點向$n的$l",
    "dodge":		-11,
    "attack":		8,
    "force":		10,
    "damage":		19,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指夾針﹐一式『游龍引氣』連環扎向$n的$l",
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
    "action":		"$N退步藏針卸其鋒銳﹐隨即一式『龍迴九轉』反扎$n的$l",
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
  // —— 殺著﹕龍圖丹針最盛一式﹐銀龍騰空、針勢暴漲 ——
  ([
    "action":		"$N真氣灌注於針大喝一聲﹐一式『龍圖丹針』$w攜萬鈞龍勢透穴轟向$n的$l",
    "dodge":		-16,
    "attack":		12,
    "force":		16,
    "damage":		24,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙指夾著$w﹐針身似有一縷龍形真氣繚繞﹐凝神辨認著$n身上的穴位﹐靜待出手的時機。\n",
  "$N腕底藏針﹐龍圖真經內息自丹田勃然涌入針端﹐尋找著進針的死角。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("dragon-needle");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("dragon-needle", "龍圖丹針");
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

  damage = COMBAT_D->fight(me, opponent, "dragon-needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
