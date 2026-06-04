// 武陀灸術【三自回針法】 recovery-needle -- 武陀灸堂的自我回補針法
//
// 武陀灸堂一脈的自療針術(docs/03-門派與武功/07-方士-龍圖武陀.md L63、
// docs/02-遊戲系統與機制/06-煉丹與書本系統.md L102)：「gin-up / kee-up / sen-up
// — 增疲勞回對應屬性」。三自回者﹐以針引氣自回己身三圍(精氣神)﹐代價是累積
// 疲勞(fatigue)。基礎技能型別為 needle (針術)﹐見 feature/weapon/needle.c。
//
// 灸術派發鏈(同 amazing-needle.c)：玩家 `enable cauterization with recovery-needle`
// 後﹐`acupuncture gin up`(或 `acupuncture gin-up`) 經 cmds/std/acupuncture.c 取
// skill_mapped("cauterization")(=「recovery-needle」)﹐呼
// SKILL_D("recovery-needle")->acupuncture_cauterization(me, "gin_up", target)。
// 注意 acupuncture.c 將 func 中空白換為底線(L37)﹐故 "gin up"->"gin_up"﹔
// 玩家若鍵 "gin-up" 則 func=="gin-up"。本檔兩種寫法都接。
//
// 三自回(對「施術者自己」回補三圍當前值﹐docs：增疲勞)：
//   gin_up -> 回精(gin)    kee_up -> 回氣(kee)    sen_up -> 回神(sen)
// 回補以 supplement_stat(自動封頂於 heal/max﹐見 feature/statistic.c)﹔
// 代價以 supplement_stat("fatigue", N) 增疲勞(fatigue 達上限將無法研讀﹐
// 見 feature/study.c)。
//
// runtime 鐵則：不涉 ::die()/destruct()(#10)、不 replace_program(#11)﹔針法 daemon
// (inherit SKILL)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。本式為「自回」﹐
// 效果即時生效(supplement_stat 立即改 current)﹐無持續性簡化問題。

#include <ansi.h>

inherit SKILL;

// 三自回參數(docs 只給定性﹐下為本次設計值)。
#define RC_RECOVER      30      // 每次回補對應三圍的量(supplement 自動封頂)。
#define RC_FATIGUE      15      // 每次施術累積的疲勞(fatigue)。

// 引氣自回的入門針招(無對手時的蓄勢氣象)。
mapping *actions = ({
  ([
    "action":		"$N回腕引針﹐$w自點$n的$l",
    "dodge":		0,
    "damage":		7,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『回元歸經』﹐$w順經點向$n的$l",
    "dodge":		-5,
    "damage":		9,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N指間轉著$w﹐似在凝氣自調﹐凝神辨認著$n身上的穴位。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("recovery-needle");
  CHINESE_D->add_translate("recovery-needle", "三自回針法");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "recovery-needle", actions[random(sizeof(actions))], weapon);
}

// 本針法可掛上 cauterization 灸術槽(enable cauterization with recovery-needle)。
int
valid_enable (string usage)
{
  return usage == "cauterization";
}

// 三自回 -> (三圍 key, 中文名, 針名)對照。兼容底線與連字號兩種 func 寫法。
private mapping recover_map = ([
  "gin_up" : ({ "gin", "精", "回精針" }),
  "gin-up" : ({ "gin", "精", "回精針" }),
  "kee_up" : ({ "kee", "氣", "回氣針" }),
  "kee-up" : ({ "kee", "氣", "回氣針" }),
  "sen_up" : ({ "sen", "神", "回神針" }),
  "sen-up" : ({ "sen", "神", "回神針" }),
]);

// acupuncture <三自回>(簽名嚴格依 cmds/std/acupuncture.c)。三自回乃自療之術﹐
// 一律作用於施術者自身﹐target 略而不用(docs：「自回」)。
int
acupuncture_cauterization (object me, string func, object target)
{
  string stat, cname, nname;
  mixed *spec;
  int healed, tired;

  if( !objectp(me) ) me = this_player();
  if( !objectp(me) ) return 0;

  if( undefinedp(spec = recover_map[func]) )
    return notify_fail("三自回針法並無此回。(可用﹕gin up / kee up / sen up)\n");

  stat  = spec[0];
  cname = spec[1];
  nname = spec[2];

  // 三圍已滿(當前達可癒上限)則毋須回補。
  if( me->query_stat_current(stat) >= me->query_stat_effective(stat) )
    return notify_fail("你的" + cname + "已然飽滿﹐毋須自回。\n");

  // 疲勞已達上限則無力再施。
  if( me->query_stat_maximum("fatigue") > 0
  &&  me->query_stat("fatigue") >= me->query_stat_maximum("fatigue") )
    return notify_fail("你已疲憊不堪﹐再也運不起三自回針法了。\n");

  healed = me->supplement_stat(stat, RC_RECOVER);
  tired  = me->supplement_stat("fatigue", RC_FATIGUE);

  message_vision(HIY
    "$N以針自點周身大穴﹐一式『" + nname + "』引動源氣回流﹐"
    "周身一陣痠麻過後﹐" + cname + "為之一充。\n" NOR, me);
  tell_object(me, sprintf(HIW
    "你引氣自回﹐%s回復 %d﹐卻也累積了幾分疲勞(+%d)。\n" NOR,
    cname, healed, tired));

  return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
