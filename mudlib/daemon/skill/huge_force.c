// 大邪心法 huge force -- 哭笑門護法的入門內功
//
// 這是一門內功(force)心法﹐哭笑門根本的吐納之術。內功與招式 daemon
// (chin_staff.c) 不同﹐它是被動的「力道乘數」﹕戰鬥時 COMBAT_D->fight()
// 會讀取 query_skill("force") 與 skill_mapped("force")﹐藉氣(kee)與功
// 力百分比(force_ratio)放大攻擊力道﹐因此內功 daemon 不需要 actions
// 攻擊招式表﹐也不需要 attack_using()。
//
// 玩家透過 map_skill("force","huge force") 將內功對應到本心法後﹐力道
// 才會隨內功修為成長。修煉內功的指令是 exert（見 cmds/std/exert.c）﹐
// 它會呼叫本 daemon 的 exert_function()。
//
// 本檔比照寒梅心法(hainmay_force.c)樣板撰寫﹐注冊名 huge force 與
// data/chinese.o 中 "huge force":"大邪心法" 一致。
// TODO: force-specific tuning -- exert 的特殊功能(護體罡氣、反噬硬抗
//       等)與相關氣/精消耗待日後設計平衡﹔哭笑門護法重防守續戰﹐
//       日後宜以護體 / 回氣為主軸。

#include <ansi.h>

inherit SKILL;

// 哭笑門弟子打坐運功時所現的內功氣象（純文字氛圍﹐無戰鬥數值）。
string *exert_msg = ({
  "$N盤膝閉目﹐緩緩運轉大邪心法﹐周身隱隱泛起一層暗沉的罡氣。\n",
  "$N凝神吐納﹐丹田之中一股陰寒的內勁如鬼火般明滅滋長。\n",
  "$N默運心法﹐臉上忽哭忽笑﹐渾身骨節爆出一連串脆響﹐氣勢愈發森然。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("huge force");
  setup();
}

// type() 由 /std/skill 提供﹐回傳 "martial"﹐skills 指令據此顯示重數描述。

// exert_function() : 由 cmds/std/exert.c 與 std/char/npc.c 呼叫﹐
// 用以施展內功的特殊功能。大邪心法目前僅提供基本的運功打坐﹐
// 尚無特殊招式。
// TODO: 接上護體罡氣 / 硬抗反噬等具體功能。
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
