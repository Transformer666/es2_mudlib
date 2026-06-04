// 茅山幻術 taoism of nature -- 茅山派隱風觀(進階)的上乘幻咒
//
// 這是一門法術(magic)技能﹐茅山派隱風觀二轉「隱風觀」所授的上乘道法。
// 比照入門幽冥三箭 youmin.c / 天師桃山密籙 taoism-of-conviction.c 的結構
// 建立(走 spells 槽、cast 指令)﹐使技能可被指派、習練、施法。
//
// 設計(docs 03-門派與武功/02-道士-天師與茅山.md「隱風觀(風/nature) →
//   茅山幻術 taoism of nature」)：docs 載茅山幻術四式「喚犬 dog / 喚猿
//   monkey / 喚蟒 hydra / 喚雨 rain」﹐召役獸靈以制敵(delay/偷物/吞噬/
//   恢復)﹐命中時消耗先天符。本檔先實作其召獸傷敵的攻擊一系(獸靈撲咬)﹐
//   其控場/恢復特效(喚犬定身、喚猿偷物、喚蟒吞噬、喚雨恢復)待咒術效果
//   引擎就緒後再各自承襲。
//
// 註(收徒限制)：docs 載隱風觀「不收夜叉/形天/厭火/黑齒」之種族門檻﹐
//   屬入門/拜師階段之種族驗證﹐非本技能(已入門後習練)範疇﹐標記為 TODO。
//
// 注意：key 含空白(「taoism of nature」)﹐故檔名以連字號代之
// (taoism-of-nature.c)﹐register/translate 用的 key 仍為含空白原名。
//
// TODO(召獸控場特效)：喚犬(目標delay)/喚猿(偷物)/喚蟒(吞噬非玩家)/喚雨
//   (恢復週圍玩家精氣神)等特效﹐屬未接的咒術效果引擎工作(同 youmin、
//   taoism-of-conviction 諸特效之 TODO)。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐袖中竄出一道幻犬虛影﹐撲咬$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N掐訣引靈﹐一頭幻猿虛影縱身抓向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N袖中先天符燃起﹐化作一條幻蟒纏向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N足踏罡步﹐一式『百獸朝元』群獸虛影齊撲$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N揮手撒出一蓬幻影﹐密密匝匝地撲向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N凝神運法﹐一頭幻獸盤旋著噬向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N後退半步﹐喚起一道幻雨化作獸潮捲向$n的$l",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N雙手結印﹐一式『幻霧噬靈』群獸虛影沖天撲落﹐淹沒$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
});

string *interattack = ({
  "$N默運茅山幻術﹐周身隱隱浮起一層獸靈虛影﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism of nature");
  // 登錄中文名﹐使 enable / skills 等顯示「茅山幻術」而非英文代號。
  CHINESE_D->add_translate("taoism of nature", "茅山幻術");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIG + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "taoism of nature", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "taoism of nature"; }

// 茅山隱風觀【茅山幻術】召獸攻擊一系。威力高於入門幽冥三箭(youmin)﹐神耗
// 亦較高﹐以對應其二轉上乘道法的定位。每式命中焚一張「先天符」引靈。
mapping query_spells()
{
  return ([
    "喚獸" :     ([ "id":"huanshou", "sen":18, "power":24, "type":"幻獸", "fu":"先天符",
        "action":HIG "$N口誦真言﹐袖中先天符燃起﹐一頭幻獸虛影破符而出﹐縱身撲咬$n！" NOR ]),
    "百獸朝元" : ([ "id":"baishou",  "sen":40, "power":42, "type":"幻獸", "fu":"先天符",
        "action":HIG "$N足踏罡步﹐結印引靈﹐一式『百獸朝元』群獸虛影沖天而起﹐齊撲$n！" NOR ]),
    "幻霧噬靈" : ([ "id":"shiling",  "sen":66, "power":60, "type":"幻獸", "fu":"先天符",
        "action":HIG "$N凝神運起茅山幻術至深一式﹐周身幻霧翻湧獸靈暴漲﹐一式『幻霧噬靈』獸潮鋪天蓋地﹐淹沒$n！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
