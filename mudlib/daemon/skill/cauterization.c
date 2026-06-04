// 武陀灸術【針灸之術】 cauterization -- 武陀灸堂的根本灸術(基本技能)
//
// docs/03-門派與武功/07-方士-龍圖武陀.md L64、docs/02-遊戲系統與機制/
// 06-煉丹與書本系統.md L103：「針灸之術 cauterization：基本技能﹐每 5 級
// +10 gin/kee/sen」。這是武陀灸堂灸術系統的「基礎技能」——驚異二針、五敗、引源、
// 三自回四門針法都掛在 cauterization 灸術槽上(各 needle daemon 的
// valid_enable("cauterization")=1)使用。針灸之術自身的看家本領「灸/烙」則由本檔
// 實作：依施術者灸術火候永久提升精氣神(gin/kee/sen)三圍上限。
//
// cauterization 亦是 feature/char/combat.c::query_ability 內建的能力軸
// (case "cauterization": cor*wis/10 + gin/40)﹐故本技能等級愈高、灸力愈強。
//
// 派發鏈(cmds/std/acupuncture.c)：玩家若 `enable cauterization`(不掛任何 needle)﹐
// skill_mapped("cauterization") 即回 "cauterization" 自身(feature/char/skill.c
// ::skill_mapped)﹐`acupuncture 灸`(或 cauterize / moxa) 便派到本檔
// SKILL_D("cauterization")->acupuncture_cauterization(me, "灸", target)。
// 簽名嚴格依該指令殼：acupuncture_cauterization(object me, string func, object target)。
//
// 「每 5 級 +10 gin/kee/sen」(docs)：以 advance_stat 永久抬高三圍 max。
//   每施一次灸/烙﹐依 (query_skill("cauterization") / 5) * 10 計可達上限﹐
//   只補到「尚未灸到」的差額(以 query("cauterized/<stat>") 記已灸量)﹐故反覆施灸
//   不會無限疊加﹐而是把三圍上限抬到「當前火候應有的水準」為止。火候增長後再灸
//   即可再抬。advance_stat 改的是 stats_max(永久)﹐符合 docs「永久提升」之意。
//
// runtime 鐵則：不涉 ::die()/destruct()(#10)、不 replace_program(#11)﹔灸術 daemon
// (inherit SKILL)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。
// 本式為永久型(advance_stat 改 max + query/set 記帳)﹐無持續性簡化問題。

#include <ansi.h>

inherit SKILL;

// 灸術參數(嚴格照 docs：每 5 級 +10)。
#define CAU_PER_LEVEL   5       // 每 5 級。
#define CAU_PER_STEP    10      // +10 gin/kee/sen。
#define CAU_SEN_COST    20      // 每施一次灸/烙所耗的神(sen)現值。

// 受灸的三圍。
private string *cau_stats = ({ "gin", "kee", "sen" });
private mapping cau_cname = ([ "gin":"精", "kee":"氣", "sen":"神" ]);

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("cauterization");
  CHINESE_D->add_translate("cauterization", "針灸之術");
  setup();
}

// 針灸之術自身即灸術槽的基本技能﹐可被 enable cauterization (映射到自身)使用。
int
valid_enable (string usage)
{
  return usage == "cauterization";
}

// 依當前灸術火候應達的三圍上限增量：(skill / 5) * 10。
private int target_cap (object me)
{
  return (me->query_skill("cauterization", 1) / CAU_PER_LEVEL) * CAU_PER_STEP;
}

// acupuncture 灸 / 烙 (簽名嚴格依 cmds/std/acupuncture.c)。
// 灸/烙乃自身淬鍊三圍之術﹐作用於施術者自己(docs 未言可灸他人)。
int
acupuncture_cauterization (object me, string func, object target)
{
  string stat;
  int cap, advanced, total, already, gain;

  if( !objectp(me) ) me = this_player();
  if( !objectp(me) ) return 0;

  // 接受「灸」「烙」及英文別名 cauterize / moxa / burn。
  if( func != "灸" && func != "烙"
   && func != "cauterize" && func != "moxa" && func != "burn" )
    return notify_fail("針灸之術可施「灸」或「烙」以淬鍊三圍。"
      "(acupuncture 灸 / acupuncture cauterize)\n");

  cap = target_cap(me);
  if( cap <= 0 )
    return notify_fail("你的針灸之術火候尚淺(未達五級)﹐灸不出半分功效。\n");

  if( me->query_stat("sen") < CAU_SEN_COST )
    return notify_fail("你神識不足﹐運不起灸火淬鍊三圍。\n");

  // 逐一把三圍上限灸到「當前火候應有的水準」(差額才補)。
  advanced = 0;
  foreach( stat in cau_stats )
    {
      already = me->query("cauterized/" + stat);  // 已灸抬的量。
      if( already >= cap ) continue;              // 該圍已灸滿當前火候。
      gain = cap - already;
      me->advance_stat(stat, gain);               // 永久抬 max。
      me->set("cauterized/" + stat, cap);
      advanced += gain;
    }

  if( advanced <= 0 )
    return notify_fail("以你目前的火候﹐三圍上限已灸至極限﹐"
      "須待針灸之術更上層樓方能再進。\n");

  me->consume_stat("sen", CAU_SEN_COST, me);

  total = me->query("cauterized/gin");  // 三圍同步﹐取其一示之。
  message_vision(HIR
    "$N凝神運針﹐以灸火徐徐溫灼周身大穴﹐一股熱流自針端滲入經脈﹐"
    "丹田如爐、精氣神三寶為之淬鍊昇華。\n" NOR, me);
  tell_object(me, sprintf(HIW
    "灸火淬體﹐你的精、氣、神上限各被灸抬至 +%d。(本次共 +%d﹐消 sen %d)\n" NOR,
    total, advanced, CAU_SEN_COST));

  return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
