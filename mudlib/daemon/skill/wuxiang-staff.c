// 無相冰杖 wuxiang-staff -- 哭笑門「素衣衛」進階(二轉)的高階冰系杖法(基礎技能 staff)
//
// 哭笑門素衣衛一脈的杖法副技(見 docs/03-門派與武功/01-武者-五大門派.md §3 哭笑門-
// 素衣衛)。docs 載素衣衛為「太乙觀(天師)與青邪宮結盟之組合﹐既有天師法術冰咒﹐又有
// 青邪杖法﹐靠無相冰、兆冰交替使用(定人、打對手 sen)」(評分 攻擊 A~D / 防禦 A- /
// 續戰 A- / 靈活 A)。本杖法即青邪杖法 chin_staff 與天師冰術交融而成的冰系杖法﹐杖
// 招挾寒、damage_type 多為寒傷﹐dodge 介於攻守之間。
//
// 比照入門 daemon/skill/chin_staff.c、白象 daemon/skill/zen-staff.c 之 actions 招式表
// 模型建立﹐並參酌天師冰咒 daemon/skill/taoism-freeze.c 之寒傷氣象﹐招式帶 "force"
// (吃大邪心法 huge force 的內力加成係數﹐見 combatd.c::fight() 之 force_bonus 公式)。
// 基礎技能為 staff(杖法)﹐玩家透過 map_skill("staff","wuxiang-staff") 對應後即可持杖
// 施展(素衣衛進階時師父自動掛上此映射)﹐與走 magic 槽的冰咒互不相礙、可交替切換。
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕damage 12~18
//   (入門 chin_staff 為 5~10)﹐帶 force 7~12﹐dodge 攻守參半。
//
// TODO(素衣衛完整化)：docs 載素衣衛靠「無相冰、兆冰交替使用(定人、打對手 sen)」﹐其
//   「定人/削 sen」屬 combat/perform 系統(非招式表)﹐標記為待辦。本檔先把帶「無相冰」
//   氣象的冰系杖招做實﹐與封山 zen-staff、天師 taoism-freeze 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N$w凝起一層寒霜﹐一式『無相起手』挾冰氣橫掃$n的$l",
    "dodge":		5,
    "force":		7,
    "damage":		12,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N沉腰運勁﹐$w如寒龍出淵直搗$n的$l",
    "dodge":		-5,
    "force":		8,
    "damage":		14,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐$w盤旋著捲起一片冰晶罩向$n的$l",
    "dodge":		-8,
    "force":		8,
    "damage":		14,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N一式『兆冰封脈』﹐$w凝而後發點向$n的$l",
    "dodge":		8,
    "force":		10,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N杖頭霜華暴卷﹐一式『素衣覆雪』當頭壓向$n的$l",
    "dodge":		-6,
    "force":		8,
    "damage":		15,
    "damage_type":	"寒傷"
  ]),
  // —— 守勢式﹕無相冰杖收勢之招﹐借勢回掃、寒氣罩身(正 dodge) ——
  ([
    "action":		"$N$w一引借勢卸力﹐冰氣繞身﹐隨即反撩$n的$l",
    "dodge":		10,
    "force":		8,
    "damage":		12,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N退步穩樁寒霜凝杖﹐借勢一頓重砸$n的$l",
    "dodge":		10,
    "force":		7,
    "damage":		12,
    "damage_type":	"挫傷"
  ]),
  // —— 殺著﹕無相冰杖最盛一式﹐寒氣暴漲、冰封杖勢 ——
  ([
    "action":		"$N周身寒氣暴漲似哭似笑﹐一式『無相凝寒』$w攜玄冰之勢轟向$n的$l",
    "dodge":		-12,
    "force":		12,
    "damage":		18,
    "damage_type":	"寒傷"
  ]),
});

string *interattack = ({
  "$N雙手橫持鐵杖﹐杖身隱隱泛起一層寒霜﹐靜待出手的時機。\n",
  "$N足踏罡步杖引冰氣﹐寒芒蓄而不發﹐尋找著進招的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("wuxiang-staff");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("wuxiang-staff", "無相冰杖");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIC + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "wuxiang-staff", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
