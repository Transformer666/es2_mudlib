// 善想禪法 kindness magic -- 寶蓮寺「善想禪師」進階(二轉)的入階佛門禪法
//
// 寶蓮寺善想一脈以慈悲度世的禪法(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §寶蓮寺-核心技能﹕「善想禪法 kindness magic」)。寶蓮寺定位為「治療輔助」之
// 寺院﹐善想禪法乃其上乘佛法之入階一式﹐由入門慈顏除障手(buddha_zarn)所悟的
// 慈悲心化作禪定法力﹐既可凝為金剛梵音震懾邪魔、亦藏濟世度人之機。
//
// 因 key 含空白(「kindness magic」)﹐故檔名以連字號代之(kindness-magic.c)﹐
// register/translate 用的 key 仍為含空白原名。比照天月庵 太陰秘法
// daemon/skill/moon-magic.c 與天師 桃山密籙 taoism-of-conviction.c 之模型建立
// (inherit /std/magic﹐走 spells 槽 cast 指令)﹐使技能可被指派、習練、施法。
// 玩家透過 map_skill("magic","kindness magic") 將法術對應到本禪法後﹐戰鬥時即
// 以善想禪法的招式出手﹐由 COMBAT_D->fight() 結算傷害。
//
// 設計(docs未明定確切數值)﹕善想禪法為寶蓮三階法術之入階一式﹐威力/神耗皆居中
//   偏低(高於入門掌法 buddha_zarn 5~10﹐低於大悲咒 almsdeed magic)﹐傷害型「梵音」
//   走精神震懾(瘀傷)﹐供日後平衡微調。
//
// TODO(寶蓮治療化)：docs 載寶蓮寺主力玩法為「link/link2 群補、ena;#tick 自動群補、
//   sarira 佛舍利」等治療輔助機制﹐屬 heal/perform/group 系統(非招式表/攻擊咒)﹐
//   標記為待辦﹔本檔先把帶禪法氣象的攻擊咒(cast/auto-attack)做實﹐與 moon-magic、
//   taoism-of-conviction 同一範圍﹐療傷群補等核心特殊功能待日後設計平衡並接線。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N合什垂眉﹐一縷溫煦的禪定法力如春風般拂向$n的$l",
    "dodge":		5,
    "damage":		8,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N低誦善想禪偈﹐一道祥和的金光無聲無息地點向$n的$l",
    "dodge":		-5,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『慈心三昧』溫厚的法力罩向$n的$l",
    "dodge":		-10,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N指尖結善想印﹐一團柔和的梵光螺旋著鑽向$n的$l",
    "dodge":		-12,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N默運禪法﹐周身梵唱隱隱﹐法力如潮般捲向$n的$l",
    "dodge":		-8,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N寶相安詳﹐一縷祥和金光盤旋而下撲向$n的$l",
    "dodge":		-5,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團溫煦的禪定法力沉沉壓向$n的$l",
    "dodge":		10,
    "damage":		8,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N雙掌一合﹐一式『善想梵音』金光暴漲﹐如鐘磬般震向$n的$l",
    "dodge":		0,
    "damage":		13,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N雙掌合什垂眉默誦善想禪偈﹐指間隱隱透出一縷祥和金光﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("kindness magic");
  // 登錄中文名﹐使 enable / skills 等顯示「善想禪法」而非英文代號。
  CHINESE_D->add_translate("kindness magic", "善想禪法");
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

  damage = COMBAT_D->fight(me, opponent, "kindness magic", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "kindness magic"; }

// 善想禪法之金剛梵音一系。威力居中偏低(寶蓮三階法術之入階)﹐神耗亦低。
mapping query_spells()
{
  return ([
    "慈心" :     ([ "id":"cixin",   "sen":10, "power":14, "type":"瘀傷",
        "action":HIY "$N合什垂眉低誦善想禪偈﹐一式『慈心三昧』溫煦的禪定法力如春風般拂向$n！" NOR ]),
    "金剛梵音" : ([ "id":"fanyin",  "sen":22, "power":26, "type":"瘀傷",
        "action":HIY "$N寶相莊嚴雙掌一合﹐周身梵唱大作﹐一式『金剛梵音』化作沖天金光如鐘磬般震向$n！" NOR ]),
    "善想度世" : ([ "id":"dushi",   "sen":40, "power":40, "type":"瘀傷",
        "action":HIY "$N凝神運起善想禪法至深一式﹐萬千祥和金光自頂門湧現化作普度法輪﹐將$n團團裹住！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
