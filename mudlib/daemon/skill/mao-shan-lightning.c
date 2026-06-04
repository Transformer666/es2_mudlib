// 茅山道法【五雷術】 mao-shan lightning -- 茅山派靈雲觀(進階)的上乘雷咒
//
// 這是一門法術(magic)技能﹐茅山派靈雲觀二轉「靈雲觀」所授的上乘道法。
// 比照入門幽冥三箭 youmin.c / 天師雷術 taoism-thunder.c 的結構建立(走
// spells 槽、cast 指令)﹐使技能可被指派、習練、施法。
//
// 設計(docs 03-門派與武功/02-道士-天師與茅山.md「靈雲觀 → 茅山【五雷術】
//   mao-shan lightning」)：docs 載五雷術由林正陽授(需幽冥三箭 ≥90)﹐三式
//   「凝聚 cleanse / 賦予 bless / 補給 consume」屬增益/恢復系﹐皆消神 +
//   靈力 + 先天符。本檔屬靈雲觀(雷/purify)之承襲﹐先實作其攻擊雷咒一系
//   (五行雷罡傷敵)﹐其增益/恢復三式(凝聚/賦予/補給)待咒術效果引擎就緒
//   後再各自承襲。
//
// 註(先天符/正陽符)：docs 五雷術消耗先天符、幽冥三箭消耗正陽符。本門攻擊
//   咒沿幽冥一脈引氣﹐故 query_spells 以 "fu":"正陽符" 接通 /std/magic.c 的
//   符閘(施法前驗符、施成燃符)﹔賦予/補給之「先天符」屬增益式專用資源﹐
//   待增益咒實作時再掛。
//
// 注意：key 含空白(「mao-shan lightning」)﹐故檔名以連字號代之
// (mao-shan-lightning.c)﹐register/translate 用的 key 仍為含空白原名。
//
// TODO(增益/恢復特效)：凝聚(cleanse)/賦予(bless)/補給(consume)之全面提升
//   屬性與元素抗、恢復精神等特效﹐屬未接的咒術效果引擎工作(同 youmin、
//   taoism-of-conviction 諸特效之 TODO)。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖凝起一點靈雷﹐化作一道雷罡射向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N掐訣引雷﹐一道五行雷罡破空轟向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N袖中正陽符燃起﹐化作一片紫芒雷網罩向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N足踏罡步﹐一式『五雷正法』五道靈雷齊射$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N揮手撒出一蓬雷珠﹐密密匝匝地激射$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N凝神運法﹐一道靈雷化龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團靈雷轟向$n的$l",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"雷殛"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『天罡五雷』霹靂沖天暴鳴﹐當頭劈向$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"雷殛"
  ]),
});

string *interattack = ({
  "$N默運五雷正法﹐指間隱隱透出一縷靈雷紫芒﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("mao-shan lightning");
  // 登錄中文名﹐使 enable / skills 等顯示「五雷術」而非英文代號。
  CHINESE_D->add_translate("mao-shan lightning", "五雷術");
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

  damage = COMBAT_D->fight(me, opponent, "mao-shan lightning", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "mao-shan lightning"; }

// 茅山靈雲觀【五雷術】攻擊一系。威力高於入門幽冥三箭(youmin)﹐神耗亦較高﹐
// 以對應其二轉上乘道法的定位。每式焚一張「正陽符」引氣(沿幽冥一脈)。
mapping query_spells()
{
  return ([
    "靈雷" :     ([ "id":"linglei", "sen":18, "power":24, "type":"雷殛", "fu":"正陽符",
        "action":HIY "$N口誦真言﹐掐訣引雷﹐一道五行雷罡破空而出﹐霹靂轟向$n！" NOR ]),
    "五雷正法" : ([ "id":"wulei",   "sen":40, "power":42, "type":"雷殛", "fu":"正陽符",
        "action":HIY "$N足踏罡步﹐袖中正陽符燃起﹐一式『五雷正法』五道靈雷齊發﹐攢射$n！" NOR ]),
    "天罡五雷" : ([ "id":"tiangang","sen":66, "power":60, "type":"雷殛", "fu":"正陽符",
        "action":HIY "$N凝神運起五雷至深一式﹐周身雷光暴漲﹐一式『天罡五雷』霹靂沖天暴鳴﹐當頭劈向$n！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
