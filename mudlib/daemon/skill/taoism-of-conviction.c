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
// 降元素防特效(2026-06-05 接上元素引擎)：docs L71-73 載桃山密籙四式「狂雷咒
//   thunder-conviction / 寒冰咒 / 炎殺咒 / 亂風咒」可「短時降目標對應元素防」並可被
//   `dispel` 強解。元素抗性/debuff 引擎已建於 /std/magic.c
//   (magic_element_debuff(victim,elem,amt,dur) 對 apply/<elem>_def 暫時 -amt、到期
//   復原)。本檔承襲朱衣(火)一脈﹐除既有「炎殺咒」攻擊一系外﹐補上四元素的「降防咒」
//   (cast 後對目標降對應元素防)與 `dispel`(解掉本門掛在目標身上的降防)。
//   元素鍵 fire/freeze/wind/thunder 對齊 /std/magic.c 引擎標頭﹔docs 的「亂風咒」對應
//   引擎 wind 鍵。降防屬攻擊向(對敵施放)﹐故走既有 cast 攻擊流程(::cast_spell 解目標、
//   開戰、扣神、傷害)後再掛 debuff﹔本門 override cast_spell 以「先解目標→呼 ::cast_spell
//   →成功則 magic_element_debuff」接上﹐base cast_spell(/std/magic.c)逐字未動。

#include <ansi.h>

inherit "/std/magic";

// === 降元素防參數(docs：短時降目標對應元素防)。集中於此便於調校。===
#define TC_DEBUFF_AMT       25      // 降防：apply/<elem>_def 下降百分點。
#define TC_DEBUFF_DURATION  20      // 降防持續秒數(call_out 以秒計)。

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯 Undefined
//   function﹐進而 daemon lazy-load 靜默失敗、cast 指令靜默回 0)。
varargs int cast_spell(object me, string spl, object target);
private object tc_resolve_target(object me, object target);
private string tc_spell_elem(string spl);

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

// 桃山密籙【炎殺咒】攻擊一系 + 四式【降防咒】。威力高於入門火術(taoism-fire)﹐神耗
// 亦較高﹐以對應其二轉上乘道法的定位。降防咒走 cast 攻擊流程後再掛 magic_element_debuff
// (見下方 cast_spell override)﹐"elem" 鍵標其降的元素。
mapping query_spells()
{
  return ([
    "炎殺" :     ([ "id":"yansha",  "sen":18, "power":24, "type":"灼傷",
        "action":HIR "$N捻訣誦籙﹐袖中桃符無風自燃﹐一式『炎殺咒』幽赤烈焰裹著煞氣噬向$n！" NOR ]),
    "桃山煞焰" : ([ "id":"shayan",  "sen":40, "power":42, "type":"灼傷",
        "action":HIR "$N足踏密籙罡步﹐周身桃火暴漲﹐一式『桃山煞焰』幽赤烈火沖天而起﹐當頭澆向$n！" NOR ]),
    "九天焚獄" : ([ "id":"fenyu",   "sen":66, "power":60, "type":"灼傷",
        "action":HIR "$N凝神運起桃山密籙至深一式﹐九道幽赤桃火盤旋而下化作焚天獄火﹐將$n團團裹住！" NOR ]),

    // ── 四式降防咒(docs L71-73：短時降目標對應元素防﹐dispel 可解)──
    "炎殺咒" :   ([ "id":"yanshazhou",  "sen":24, "power":18, "type":"灼傷", "elem":"fire",
        "action":HIR "$N捻訣誦『炎殺咒』﹐一道幽赤桃火纏上$n﹐灼得$n護身的火氣為之一弱！" NOR ]),
    "寒冰咒" :   ([ "id":"hanbingzhou", "sen":24, "power":18, "type":"寒傷", "elem":"freeze",
        "action":HIC "$N捻訣誦『寒冰咒』﹐一股徹骨陰寒滲入$n體內﹐$n禦冰的真氣為之一滯！" NOR ]),
    "亂風咒" :   ([ "id":"luanfengzhou","sen":24, "power":18, "type":"罡傷", "elem":"wind",
        "action":HIG "$N捻訣誦『亂風咒』﹐一陣亂罡之風絞向$n﹐$n護身的風氣為之一散！" NOR ]),
    "狂雷咒" :   ([ "id":"thunder-conviction", "sen":24, "power":18, "type":"雷殛", "elem":"thunder",
        "action":HIY "$N捻訣誦『狂雷咒』﹐一道幽雷劈落$n周身﹐$n禦雷的真氣為之一亂！" NOR ]),
  ]);
}

// ── 降防咒派發：override cast_spell﹐先解目標→走 ::cast_spell 攻擊流程→成功則對
//    目標掛 magic_element_debuff。標 "elem" 鍵的咒文才降防﹔未標者(炎殺/桃山煞焰/
//    九天焚獄純攻擊)直接落回 ::cast_spell﹐行為與原本完全一致。 ──
// 解目標邏輯鏡 /std/magic.c::cast_spell：cast 未帶 on 時取當前敵人首個。
private object
tc_resolve_target(object me, object target)
{
  object *es;

  if( objectp(target) ) return target;
  es = me->query_enemy();
  if( arrayp(es) ) {
    es -= ({ 0 });
    if( sizeof(es) ) return es[0];
  }
  return 0;
}

// 由咒名/英文 id 反查該咒所降的元素(query_spells 的 "elem" 鍵)﹐非降防咒回 0。
private string
tc_spell_elem(string spl)
{
  mapping spells, sp;
  string nm;

  spells = query_spells();
  if( !mapp(spells) ) return 0;
  sp = spells[spl];
  if( !mapp(sp) ) foreach( nm, mapping m in spells )
    if( mapp(m) && m["id"] == spl ) { sp = m; break; }
  if( !mapp(sp) ) return 0;
  return stringp(sp["elem"]) ? sp["elem"] : 0;
}

// 引擎元素鍵 -> 顯示中文(避免 to_chinese(fire) 回英文﹐字典無此 key)。
private mapping tc_elem_cn = ([
  "fire":"火", "freeze":"冰", "wind":"風", "thunder":"雷",
]);

varargs int
cast_spell(object me, string spl, object target)
{
  string elem, cn;
  object victim;
  int r;

  if( !objectp(me) || !stringp(spl) ) return ::cast_spell(me, spl, target);

  elem = tc_spell_elem(spl);
  if( !elem ) return ::cast_spell(me, spl, target);   // 純攻擊咒﹐原樣派發

  // 降防咒：先把目標定下來(交給 ::cast_spell 沿用﹐使「降防的對象」=「被打的對象」)。
  victim = tc_resolve_target(me, target);

  r = ::cast_spell(me, spl, victim);
  if( r != 1 ) return r;   // ::cast_spell 失敗(無目標/神不足/和平房…)﹐不掛 debuff

  // 攻擊已成功(已開戰、扣神、結算傷害)﹐對目標短時降對應元素防。
  if( objectp(victim) && living(victim) ) {
    magic_element_debuff(victim, elem, TC_DEBUFF_AMT, TC_DEBUFF_DURATION);
    cn = stringp(tc_elem_cn[elem]) ? tc_elem_cn[elem] : elem;
    message_vision(HIR
      "$n周身禦" + cn + "的護身真氣被這道密籙咒法生生壓下一截！\n" NOR,
      me, victim);
  }
  return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
