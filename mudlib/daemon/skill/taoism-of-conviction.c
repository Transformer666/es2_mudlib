// 天師道法【桃山密籙】 taoism of conviction -- 天師派朱衣真傳(進階)的上乘火咒
//
// 這是一門法術(magic)技能﹐天師派朱衣一脈二轉「朱衣真傳」所授的上乘道法。
// 比照入門火術 taoism-fire.c / 雷術 taoism-thunder.c 的結構建立(走 spells 槽、
// cast 指令)﹐使技能可被指派、習練、施法。
//
// 設計(docs 03-門派與武功/02-道士-天師與茅山.md「桃山密籙 taoism of conviction」)：
//   桃山密籙原書載「狂雷咒 / 寒冰咒 / 炎殺咒 / 亂風咒」四式﹐短時降目標對應元素
//   防﹐`dispel` 解效果﹔習得條件為「紫薇心經 100 + 桃仙任務」。本檔屬朱衣(火)
//   真傳之承襲﹐故先實作其「炎殺咒」一系(降火抗的烈焰debuff咒)﹐其餘三系(雷/冰/
//   風)待相應元素分支二轉時再各自承襲。
//
// 注意：key 含空白(「taoism of conviction」)﹐故檔名以連字號代之
// (taoism-of-conviction.c)﹐register/translate 用的 key 仍為含空白原名。
//
// TODO(降元素防特效)：docs 載桃山密籙咒可「短時降目標對應元素防」並可被 dispel
//   強解。此降抗/debuff 特效屬未接的咒術效果引擎工作(同 taoism-fire 大業火「無視
//   抗性」、moon-magic 諸特效之 TODO)﹔本檔先交付咒文表 + 神耗 + 傷害﹐降抗特效
//   待元素抗性/debuff 系統就緒後再於 query_spells 的 "effect" 鍵掛上。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N捻訣誦籙﹐一縷幽幽桃火無聲無息地舔向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N袖中桃符無風自燃﹐化作一蓬挾著煞氣的赤焰罩向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N足踏密籙罡步﹐一式『炎殺』烈焰裹著煞氣噬向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N指尖密籙符光一閃﹐一道桃火螺旋著鑽向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N低喝一聲﹐周身桃火暴卷﹐密密匝匝地席捲$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N凝神運籙﹐一團幽赤的桃火龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一輪幽火轟向$n的$l",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N雙掌一錯﹐一式『桃山煞焰』幽赤烈火沖天而起﹐當頭澆向$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"灼傷"
  ]),
});

string *interattack = ({
  "$N默運桃山密籙﹐指間隱隱透出一縷幽赤的桃火﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism of conviction");
  // 登錄中文名﹐使 enable / skills 等顯示「桃山密籙」而非英文代號。
  CHINESE_D->add_translate("taoism of conviction", "桃山密籙");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIR + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "taoism of conviction", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "taoism of conviction"; }

// 桃山密籙【炎殺咒】一系。威力高於入門火術(taoism-fire)﹐神耗亦較高﹐以
// 對應其二轉上乘道法的定位。降火抗 debuff 特效待引擎就緒後掛 "effect"。
mapping query_spells()
{
  return ([
    "炎殺" :     ([ "id":"yansha",  "sen":18, "power":24, "type":"灼傷",
        "action":HIR "$N捻訣誦籙﹐袖中桃符無風自燃﹐一式『炎殺咒』幽赤烈焰裹著煞氣噬向$n！" NOR ]),
    "桃山煞焰" : ([ "id":"shayan",  "sen":40, "power":42, "type":"灼傷",
        "action":HIR "$N足踏密籙罡步﹐周身桃火暴漲﹐一式『桃山煞焰』幽赤烈火沖天而起﹐當頭澆向$n！" NOR ]),
    "九天焚獄" : ([ "id":"fenyu",   "sen":66, "power":60, "type":"灼傷",
        "action":HIR "$N凝神運起桃山密籙至深一式﹐九道幽赤桃火盤旋而下化作焚天獄火﹐將$n團團裹住！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
