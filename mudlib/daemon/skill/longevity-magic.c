// 長生禪法 longevity magic -- 寶蓮寺「長生上人」進階(二轉)的最高階佛門禪法
//
// 寶蓮寺善想一脈以慈悲濟世、維持同袍狀態的看家禪法(見 docs/03-門派與武功/
// 03-和尚-寶蓮天月白象.md §寶蓮寺-核心技能﹕「長生禪法 longevity magic」﹔docs
// 主力玩法明載「link/link2 長生：維持隊友狀態」為寶蓮成為團隊核心的關鍵)。
// 長生禪法乃寶蓮三階法術之最高一階﹐以無量壽佛之願力續命延壽、維持同袍﹐由
// 大悲咒(almsdeed magic)精進而成﹐是寶蓮治療輔助一脈的最高絕學。
//
// 因 key 含空白(「longevity magic」)﹐故檔名以連字號代之(longevity-magic.c)﹐
// register/translate 用的 key 仍為含空白原名。比照天月 太陰秘法 moon-magic.c /
// 天師 桃山密籙 taoism-of-conviction.c 之模型建立(inherit /std/magic﹐走 spells
// 槽 cast 指令)。玩家透過 map_skill("magic","longevity magic") 將法術對應到本禪
// 法後﹐戰鬥時即以長生禪法的招式出手。
//
// 設計(docs未明定確切數值)﹕長生禪法為寶蓮三階法術之最高一階﹐威力/神耗皆居寶蓮
//   諸法之冠(高於大悲咒 almsdeed magic)﹐傷害型「梵音」走無量壽願力之震懾(瘀傷)﹐
//   供日後平衡微調。
//
// TODO(寶蓮治療化)：docs 明載長生禪法之核心為「link/link2 長生：維持隊友狀態」之
//   群體續命/狀態維持(寶蓮成為團隊核心的關鍵機制)﹐屬 heal/perform/group/link
//   系統(非攻擊咒表)﹐標記為待辦﹔本檔先把帶無量壽願力氣象的攻擊咒(cast/auto-
//   attack)做實﹐link 群補/狀態維持等核心特殊功能待日後設計平衡並接線。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N結無量壽印﹐一縷澄澈的長生願力如清泉般漫向$n的$l",
    "dodge":		5,
    "damage":		14,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N口誦無量壽真言﹐一道瑩白梵光無聲無息地點向$n的$l",
    "dodge":		-5,
    "damage":		18,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N足踏長生罡步﹐一式『無量壽光』梵唱裹著瑩光噬向$n的$l",
    "dodge":		-10,
    "damage":		18,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N指尖結長生印﹐一團澄澈梵光螺旋著鑽向$n的$l",
    "dodge":		-12,
    "damage":		18,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N低喝一聲﹐周身長生梵光暴卷﹐密密匝匝地席捲$n的$l",
    "dodge":		-8,
    "damage":		16,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一輪澄澈的瑩白願輪盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		18,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團長生願力轟向$n的$l",
    "dodge":		10,
    "damage":		14,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N寶相莊嚴雙掌一合﹐一式『無量壽佛』瑩白梵光沖天而起﹐當頭澆向$n的$l",
    "dodge":		0,
    "damage":		20,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N結無量壽印低誦真言﹐指間隱隱透出一縷澄澈的瑩白梵光﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("longevity magic");
  // 登錄中文名﹐使 enable / skills 等顯示「長生禪法」而非英文代號。
  CHINESE_D->add_translate("longevity magic", "長生禪法");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIW + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "longevity magic", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "longevity magic"; }

// 長生禪法之無量壽願力一系。威力居寶蓮諸法之冠﹐神耗亦最高。
mapping query_spells()
{
  return ([
    "長生" :     ([ "id":"changsheng", "sen":20, "power":28, "type":"瘀傷",
        "action":HIW "$N結無量壽印口誦真言﹐一式『無量壽光』一道澄澈的瑩白梵光裹著願力噬向$n！" NOR ]),
    "無量壽佛" : ([ "id":"wuliangshou", "sen":40, "power":48, "type":"瘀傷",
        "action":HIW "$N寶相莊嚴足踏長生罡步﹐周身梵光暴漲﹐一式『無量壽佛』瑩白梵光沖天而起﹐當頭澆向$n！" NOR ]),
    "長生願海" : ([ "id":"yuanhai", "sen":66, "power":66, "type":"瘀傷",
        "action":HIW "$N凝神運起長生禪法至深一式﹐萬千澄澈瑩光自頂門湧現化作無量壽願海﹐將$n團團裹住！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
