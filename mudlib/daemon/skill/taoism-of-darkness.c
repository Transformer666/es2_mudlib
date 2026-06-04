// 茅山奇術 taoism of darkness -- 茅山派幻霧觀(進階)的上乘陰咒
//
// 這是一門法術(magic)技能﹐茅山派幻霧觀二轉「幻霧觀」所授的上乘道法。
// 比照入門幽冥三箭 youmin.c / 天師桃山密籙 taoism-of-conviction.c 的結構
// 建立(走 spells 槽、cast 指令)﹐使技能可被指派、習練、施法。
//
// 設計(docs 03-門派與武功/02-道士-天師與茅山.md「幻霧觀(陰/darkness) →
//   茅山奇術 taoism of darkness」)：docs 載茅山奇術四式「入陰 hell / 鬼火術
//   ghost_fire / 鬼煙術 smoke / 幽冥之火 hell_fire」﹐皆消少陰符﹐其中鬼火術、
//   幽冥之火為法術傷害。本檔先實作其陰火傷敵的攻擊一系(鬼火/幽冥之火)﹐
//   其位移/脫戰特效(入陰飛地獄、鬼煙脫戰隱身)待咒術效果引擎就緒後再承襲。
//
// 註(收徒限制)：docs 載幻霧觀「只收阿修羅/巫首/雨師妾/無腸/夜叉」之種族
//   門檻﹐屬入門/拜師階段之種族驗證﹐非本技能(已入門後習練)範疇﹐標記為
//   TODO。
//
// 注意：key 含空白(「taoism of darkness」)﹐故檔名以連字號代之
// (taoism-of-darkness.c)﹐register/translate 用的 key 仍為含空白原名。
//
// TODO(位移/脫戰特效)：入陰(飛地獄)/鬼煙術(脫離戰鬥並隱藏)等特效﹐屬未接
//   的咒術效果引擎工作(同 youmin、taoism-of-conviction 諸特效之 TODO)。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N口誦陰咒﹐指尖凝起一點鬼火﹐幽幽飄向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"陰火"
  ]),
  ([
    "action":		"$N掐訣引陰﹐一蓬幽綠鬼火破空噬向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"陰火"
  ]),
  ([
    "action":		"$N袖中少陰符燃起﹐化作一片陰火罩向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"陰火"
  ]),
  ([
    "action":		"$N足踏罡步﹐一式『鬼火術』幽綠鬼火盤旋著鑽向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"陰火"
  ]),
  ([
    "action":		"$N揮手撒出一蓬鬼火﹐密密匝匝地席捲$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"陰火"
  ]),
  ([
    "action":		"$N凝神運法﹐一團幽冥之火化龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"陰火"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一輪鬼火轟向$n的$l",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"陰火"
  ]),
  ([
    "action":		"$N雙手結印﹐一式『幽冥之火』幽綠陰火沖天而起﹐當頭澆向$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"陰火"
  ]),
});

string *interattack = ({
  "$N默運茅山奇術﹐指間隱隱透出一縷幽綠鬼火﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism of darkness");
  // 登錄中文名﹐使 enable / skills 等顯示「茅山奇術」而非英文代號。
  CHINESE_D->add_translate("taoism of darkness", "茅山奇術");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (GRN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "taoism of darkness", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "taoism of darkness"; }

// 茅山幻霧觀【茅山奇術】陰火攻擊一系。威力高於入門幽冥三箭(youmin)﹐神耗
// 亦較高﹐以對應其二轉上乘道法的定位。每式焚一張「少陰符」引陰。
mapping query_spells()
{
  return ([
    "鬼火術" :   ([ "id":"guihuo",  "sen":18, "power":24, "type":"陰火", "fu":"少陰符",
        "action":GRN "$N口誦陰咒﹐袖中少陰符燃起﹐一蓬幽綠鬼火破符而出﹐幽幽噬向$n！" NOR ]),
    "幽冥之火" : ([ "id":"hellfire","sen":40, "power":42, "type":"陰火", "fu":"少陰符",
        "action":GRN "$N足踏罡步﹐結印引陰﹐一式『幽冥之火』幽綠陰火沖天而起﹐當頭澆向$n！" NOR ]),
    "九幽煉獄" : ([ "id":"jiuyou",  "sen":66, "power":60, "type":"陰火", "fu":"少陰符",
        "action":GRN "$N凝神運起茅山奇術至深一式﹐周身陰火翻湧鬼影暴漲﹐一式『九幽煉獄』幽冥獄火鋪天蓋地﹐將$n團團裹住！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
