// 幻劍術 illusion-sword -- 振武軍營「軍師」進階(二轉)所授的法術(基底 /std/magic)
//
// docs 載振武軍營軍師「獲得 古文、咒術、幻劍術﹔軍師 strategy 受法術強度額外影響」
// (見 docs/03-門派與武功/06-軍人-振武大內.md §進階-軍師)。本檔將「幻劍術」實作為一門
// 法術(magic)技能﹐比照天師上乘火咒 taoism-of-conviction.c / 入門火術 taoism-fire.c
// 的結構建立(走 spells 槽、cast 指令﹐valid_enable/cast_spell 由 /std/magic 提供)﹐
// 使軍師之「咒術/法術」可被指派、習練、施法——軍師戰鬥手段更像道士(戰術 + 法術)。
//
// 字典 data/chinese.o 查無 "illusion-sword" key﹐以 CHINESE_D->add_translate() 自行
// 登錄中文名「幻劍術」。注意：master.c::do_advance 將 base "magic" map 到本技能
// (map_skill("magic","illusion-sword"))﹐故軍師走 magic 槽施展幻劍術。
//
// 設計(docs未明定招式數值)：docs 只給「幻劍術」之名與「軍師戰術受法術強度額外影響」
//   的定位﹐未列具體咒文/數值。本檔咒文表 query_spells() 與招式 actions 之數值為本次
//   設計值(供日後平衡微調)﹐以「凝氣化劍、虛實相生」的幻劍意象體現之。
//
// TODO(軍師 strategy 連動)：docs 載「軍師 strategy 受法術強度額外影響」﹐其「以本門
//   magic 火候/法術強度放大戰術(strategy/tactic)效果」屬戰術兵法 strategy 系統與
//   法術強度公式的耦合工作(同 powerblow 的爆 hp、berserk 的多段連擊之 perform TODO)﹐
//   標記為待辦。本檔先把幻劍術之 magic 槽攻擊咒做實。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N捏訣凝氣﹐指尖虛引一道幻劍無聲無息地刺向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N袖中真氣化作三五點幻劍寒芒﹐虛實莫辨地攢向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足踏奇步﹐一式『幻劍亂影』漫天劍影真假交錯地罩向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝指成劍﹐一道幻劍螺旋著鑽向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N低喝一聲﹐周身幻劍暴漲﹐密密匝匝地席捲$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N運起幻劍術﹐一柄虛凝的氣劍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一輪幻劍劍輪轟向$n的$l",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指一錯﹐一式『萬幻歸真』千百道幻劍儘數匯成一劍當頭澆向$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N默運幻劍術﹐指間隱隱凝出一縷虛實莫辨的劍氣﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("illusion-sword");
  // 自行登錄中文名﹐字典查無此 key﹐使 enable / skills 等顯示「幻劍術」而非英文代號。
  CHINESE_D->add_translate("illusion-sword", "幻劍術");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIC + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "illusion-sword", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "illusion-sword"; }

// 幻劍術以氣御劍、虛實相生﹐威力隨法術強度成長。耗神對應其二轉上乘法術定位。
mapping query_spells()
{
  return ([
    "幻劍" :     ([ "id":"huanjian", "sen":18, "power":24, "type":"刺傷",
        "action":HIC "$N捏訣凝氣﹐袖中真氣化作數點幻劍寒芒﹐一式『幻劍』虛實莫辨地攢向$n！" NOR ]),
    "幻劍亂影" : ([ "id":"luanying", "sen":40, "power":42, "type":"刺傷",
        "action":HIC "$N足踏奇步運起幻劍術﹐一式『幻劍亂影』漫天劍影真假交錯﹐儘數罩向$n！" NOR ]),
    "萬幻歸真" : ([ "id":"guizhen",  "sen":66, "power":60, "type":"刺傷",
        "action":HIC "$N凝神運起幻劍術至深一式﹐千百道幻劍儘數匯成一柄真劍﹐攜雷霆之勢當頭澆向$n！" NOR ]),
  ]);
}

// vim: set ts=4 sw=4 syntax=lpc
