// 太陰冰心訣 moon-frost magic -- 天月庵「太陰尊者」進階(二轉)的上乘控制法術(基礎技能 magic)
//
// 這是一門法術(magic)技能﹐天月庵二轉「太陰尊者」所授的上乘月法。天月庵定位
// 為「治療 / 控制」(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md §三大寺院定位
// 與 §天月庵主力玩法﹕conjure / zazengo / link 群補等控制治療玩法)。本檔承入門
// 太陰秘法(moon magic)之冰寒控制一系而成﹐以太陰冰心化月華為冰封寒獄﹐凍敵
// 筋骨、奪敵神識﹐威力與神耗皆高於入門月法。
//
// 比照入門太陰秘法 moon-magic.c 與天師進階 taoism-of-conviction.c 的結構建立
// (走 spells 槽 cast 指令 + auto-attack actions)﹐使技能可被指派、習練、施法。
// 玩家透過 map_skill("magic","moon-frost magic") 將法術對應到本訣後(太陰尊者
// 進階時師父自動掛上此映射)﹐戰鬥時即以太陰冰心訣的招式出手﹔亦可
// enable spells with 太陰冰心訣 後 cast 寒咒。
//
// 注意：key 含空白(「moon-frost magic」)﹐故檔名以連字號代之(moon-frost.c)﹐
// register/translate 用的 key 仍為含空白原名。字典查無此 key﹐以
// CHINESE_D->add_translate() 自行登錄中文名「太陰冰心訣」。
//
// 設計(docs未明定):docs 天月庵以「控制」為定位但未明列其控制法術名﹔「太陰
//   冰心訣」為承入門太陰秘法冰寒控制一系的上乘月法﹐與天師太乙真人冰咒
//   taoism-freeze、白象進階諸技同階對位。
//
// TODO(冰封控制特效)：docs 天月庵核心玩法為治療/控制(沉睡、冰封、群補 link/link2)。
//   此 freeze/sleep 等控制 debuff 與群補 heal 屬未接的咒術效果引擎工作(同 moon-magic
//   諸特效之 TODO)﹔本檔先交付咒文表 + 神耗 + 寒傷﹐冰封控制特效待引擎就緒後
//   再於 query_spells 的 "effect" 鍵掛上。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N纖手結印﹐一縷太陰冰心化作森寒霜華漫向$n的$l",
    "dodge":		5,
    "damage":		12,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N口誦冰心真言﹐一道清冷月華凝成寒冰點向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N素手輕揚﹐一式『太陰冰封』寒霧瀰漫籠罩$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N凝神運訣﹐一輪冰魄寒月森森地壓向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N掐訣引月﹐千點冰晶如寒星灑向$n的$l",
    "dodge":		-10,
    "damage":		12,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N默運冰心訣﹐一團太陰寒氣盤旋著凍向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一片冰魄寒潭緩緩漫向$n的$l",
    "dodge":		10,
    "damage":		12,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N雙掌一合﹐一式『冰心寒獄』月華暴湧化作徹骨寒冰﹐儘數封向$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"寒傷"
  ]),
});

string *interattack = ({
  "$N默運太陰冰心訣﹐指間隱隱透出一縷森寒的冰魄月華﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("moon-frost magic");
  // 字典查無此 key﹐自行登錄中文名「太陰冰心訣」。
  CHINESE_D->add_translate("moon-frost magic", "太陰冰心訣");
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

  damage = COMBAT_D->fight(me, opponent, "moon-frost magic", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "moon-frost magic"; }

// 太陰冰心訣【寒咒】一系。威力與神耗皆高於入門太陰秘法(moon magic)﹐以對應其
// 二轉上乘控制月法的定位。冰封/沉睡 control 特效待引擎就緒後掛 "effect"。
mapping query_spells()
{
  return ([
    "冰魄" :     ([ "id":"bingpo",  "sen":18, "power":24, "type":"陰寒",
        "action":HIW "$N纖手結印﹐口誦冰心真言﹐一道清冷月華凝成冰魄寒芒點向$n！" NOR ]),
    "太陰冰封" : ([ "id":"bingfeng", "sen":40, "power":42, "type":"陰寒",
        "action":HIW "$N素手輕揚周身月華暴湧﹐一式『太陰冰封』寒霧瀰漫化作徹骨寒冰﹐森森地籠罩$n！" NOR ]),
    "冰心寒獄" : ([ "id":"hanyu",   "sen":66, "power":60, "type":"陰寒",
        "action":HIW "$N凝神運起太陰冰心訣至深一式﹐一輪冰魄寒月當空墜落化作萬里寒獄﹐將$n團團封凍！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
