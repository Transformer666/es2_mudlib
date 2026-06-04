// 文殊杖法 wen-staff -- 白象寺「羅漢」進階(二轉)的高階杖法(基礎技能 staff)
//
// 白象寺羅漢一脈攻擊型的上乘杖法(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §白象寺-羅漢核心技能﹕「文殊杖法 wen-staff」)。由入門金剛伏魔杖法(rid-evil)
// 精進而成﹐借文殊菩薩智劍般若之力降魔﹐杖走剛猛而暗藏定慧。比照虎刀門鬼才的
// 瘋虎刀法 daemon/skill/tiger-blade.c 之 actions 招式表模型建立﹐但因基礎技能為
// staff(杖法)﹐attack_using 第三參數為兵器物件(weapon)﹐故 COMBAT_D->fight() 傳
// weapon﹐與入門 rid-evil.c / chin_staff.c 一致。
//
// 因基礎技能為 staff(杖法)﹐玩家透過 map_skill("staff","wen-staff") 對應後即可
// 持禪杖施展(羅漢進階時師父自動掛上此映射)。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹐供日後平衡微調﹕招式 damage
//   13~20(入門 rid-evil 為 5~10)﹐高階式帶 "attack"(命中加成)與 "force"(吃羅漢
//   降魔功 luohan force 的內力加成係數﹐見 combatd.c::fight() 之 force_bonus 公式)。
//
// TODO(羅漢完整化)：docs 載羅漢主力玩法有「ppp(powerup)、kee→heal、cc liuye」等
//   絕招﹐其 powerup / 連擊段數屬 combat/perform 系統(非招式表)﹐標記為待辦。本檔
//   先把帶「文殊降魔」氣象的普攻杖招做實﹐與冷梅 hanshuang、虎刀 tiger-blade 同
//   一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N寶杖一橫﹐一式『文殊起手』挾般若之力當頭壓向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "force":		6,
    "damage":		13,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N沉腰運力﹐$w如智劍開蒙橫掃$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N默誦文殊心咒﹐$w一式『獅吼破障』狠搗$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		16,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N腳踏蓮花步﹐$w盤旋而下一式『智炬焚邪』劈向$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N雙手持杖﹐$w一式『金剛點睛』直挺挺點向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"挫傷"
  ]),
  // —— 守勢式﹕文殊杖法少數收勢之招﹐借勢回掃(正 dodge) ——
  ([
    "action":		"$N寶杖一引借勢卸力﹐隨即一式『迴鋒掃葉』反撩$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N後退半步避其鋒銳﹐$w凝而後發猛擊$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		6,
    "damage":		13,
    "damage_type":	"挫傷"
  ]),
  // —— 殺著﹕文殊杖法最盛一式﹐般若智火、杖勢暴漲 ——
  ([
    "action":		"$N寶相莊嚴大喝一聲﹐一式『文殊降魔』$w攜千鈞智火轟向$n的$l",
    "dodge":		-14,
    "attack":		10,
    "force":		14,
    "damage":		20,
    "damage_type":	"挫傷"
  ]),
});

string *interattack = ({
  "$N雙手橫持寶杖﹐口誦文殊心咒﹐寶相莊嚴﹐靜待出手的時機。\n",
  "$N寶杖斜引杖頭銅環輕響﹐金剛之氣蓄而不發﹐尋找著進招的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("wen-staff");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("wen-staff", "文殊杖法");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (YEL + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "wen-staff", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
