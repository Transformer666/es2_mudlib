// 封山派內功 fonxanforce -- 封山派劍客的入門內功
//
// 這是一門內功(force)心法﹐封山派根本的吐納之術。內功與招式 daemon
// (fonxansword.c) 不同﹐它是被動的「力道乘數」﹕戰鬥時 COMBAT_D->fight()
// 會讀取 query_skill("force") 與 skill_mapped("force")﹐藉氣(kee)與功
// 力百分比(force_ratio)放大攻擊力道﹐因此內功 daemon 不需要 actions
// 攻擊招式表﹐也不需要 attack_using()。
//
// 玩家透過 map_skill("force","fonxanforce") 將內功對應到本心法後﹐力道
// 才會隨內功修為成長。修煉內功的指令是 exert（見 cmds/std/exert.c）﹐
// 它會呼叫本 daemon 的 exert_function()。
//
// 本檔比照寒梅心法(hainmay_force.c)、大邪心法(huge_force.c)樣板撰寫﹐
// 注冊名 fonxanforce 與 data/chinese.o 中 "fonxanforce":"封山派內功"
// 一致。
// TODO: force-specific tuning -- exert 的特殊功能(護體罡氣、運功療傷
//       等)與相關氣/精消耗待日後設計平衡﹔封山派重守正續戰﹐日後宜
//       以護體 / 凝氣為主軸。

#include <ansi.h>

inherit SKILL;

// 封山派弟子打坐運功時所現的內功氣象（純文字氛圍﹐無戰鬥數值）。
string *exert_msg = ({
  "$N盤膝閉目﹐緩緩運轉封山派內功﹐周身似有一股沉凝如山的真氣流轉不息。\n",
  "$N凝神吐納﹐丹田之中一股渾厚的內勁如萬鈞磐石﹐徐徐生根滋長。\n",
  "$N默運心法﹐但覺氣息如靜水深流﹐穩固之中自有一股奔雷待發的勁勢。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("fonxanforce");
  setup();
}

// type() 由 /std/skill 提供﹐回傳 "martial"﹐skills 指令據此顯示重數描述。

// exert_function() : 由 cmds/std/exert.c 與 std/char/npc.c 呼叫﹐
// 用以施展內功的特殊功能。封山派內功目前僅提供基本的運功打坐﹐
// 尚無特殊招式。
// TODO: 接上護體罡氣 / 運功療傷等具體功能。
varargs int
exert_function (object me, string func, object target)
{
  if( !me ) me = this_player();
  if( !me ) return 0;

  message_vision(WHT + exert_msg[random(sizeof(exert_msg))] + NOR, me);
  return 1;
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
