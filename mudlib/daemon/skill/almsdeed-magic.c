// 大悲咒 almsdeed magic -- 寶蓮寺「大悲行者」進階(二轉)的上乘佛門咒法
//
// 寶蓮寺善想一脈以慈悲濟世的核心咒法(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §寶蓮寺-核心技能﹕「大悲咒 almsdeed magic」﹔docs 另載「善想禪要 almsdeed
// — 寶蓮寺、天月庵都會用」「9/2 平衡：受 almsdeed 50% 影響」)。大悲咒乃寶蓮、
// 天月兩寺共通的善想禪要﹐以大悲願力濟世度人、增益同袍、降伏邪魔﹐是寶蓮治療
// 輔助一脈的看家咒法。由善想禪法(kindness magic)精進而成。
//
// 因 key 含空白(「almsdeed magic」)﹐故檔名以連字號代之(almsdeed-magic.c)﹐
// register/translate 用的 key 仍為含空白原名。比照天師 桃山密籙
// taoism-of-conviction.c / 天月 太陰秘法 moon-magic.c 之模型建立(inherit
// /std/magic﹐走 spells 槽 cast 指令)。玩家透過 map_skill("magic","almsdeed magic")
// 將法術對應到本咒法後﹐戰鬥時即以大悲咒的招式出手。
//
// 設計(docs未明定確切數值)﹕大悲咒為寶蓮三階法術之中階﹐威力/神耗高於入階善想
//   禪法(kindness magic)、低於最高階長生禪法(longevity magic)﹐傷害型「梵音」走
//   大悲願力之震懾(瘀傷)﹐供日後平衡微調。
//
// TODO(寶蓮治療化)：docs 明載「善想禪要 almsdeed」之核心為治療/增益(寶蓮、天月
//   主力群補機制﹐「受 almsdeed 50% 影響」)﹐其療傷/增益/減傷加成屬 heal/perform
//   系統(非攻擊咒表)﹐標記為待辦﹔本檔先把帶大悲願力氣象的攻擊咒(cast/auto-attack)
//   做實﹐療傷群補等核心特殊功能待日後設計平衡並接線。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N結大悲手印﹐一縷莊嚴的願力梵光如水般漫向$n的$l",
    "dodge":		5,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N口誦大悲神咒﹐一道金紅梵光無聲無息地點向$n的$l",
    "dodge":		-5,
    "damage":		16,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N足踏蓮花罡步﹐一式『大悲願海』梵唱裹著金光噬向$n的$l",
    "dodge":		-10,
    "damage":		16,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N指尖結大悲印﹐一團莊嚴梵光螺旋著鑽向$n的$l",
    "dodge":		-12,
    "damage":		16,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N低喝一聲﹐周身大悲梵光暴卷﹐密密匝匝地席捲$n的$l",
    "dodge":		-8,
    "damage":		14,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N凝神運咒﹐一輪莊嚴的金紅願輪盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		16,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團大悲願力轟向$n的$l",
    "dodge":		10,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N寶相莊嚴雙掌一合﹐一式『大悲千手』金紅梵光沖天而起﹐當頭澆向$n的$l",
    "dodge":		0,
    "damage":		17,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N結大悲手印低誦神咒﹐指間隱隱透出一縷莊嚴的金紅梵光﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("almsdeed magic");
  // 登錄中文名﹐使 enable / skills 等顯示「大悲咒」而非英文代號。
  CHINESE_D->add_translate("almsdeed magic", "大悲咒");
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

  damage = COMBAT_D->fight(me, opponent, "almsdeed magic", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "almsdeed magic"; }

// 大悲咒之大悲願力一系。威力高於善想禪法(kindness magic)﹐神耗亦較高。
mapping query_spells()
{
  return ([
    "大悲" :     ([ "id":"dabei",   "sen":16, "power":24, "type":"瘀傷",
        "action":HIR "$N結大悲手印口誦神咒﹐一式『大悲願海』一道莊嚴的金紅梵光裹著願力噬向$n！" NOR ]),
    "大悲千手" : ([ "id":"qianshou", "sen":36, "power":42, "type":"瘀傷",
        "action":HIR "$N寶相莊嚴足踏蓮花罡步﹐周身梵光暴漲﹐一式『大悲千手』金紅梵光沖天而起﹐當頭澆向$n！" NOR ]),
    "大悲願海" : ([ "id":"yuanhai", "sen":60, "power":60, "type":"瘀傷",
        "action":HIR "$N凝神運起大悲咒至深一式﹐萬千金紅梵光自頂門湧現化作浩瀚願海﹐將$n團團裹住！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
