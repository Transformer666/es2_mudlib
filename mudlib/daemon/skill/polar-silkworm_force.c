// 冰蠶奇功 polar-silkworm force -- 天師派素衣弟子的入門內功
//
// 這是一門內功(force)心法﹐天師派素衣一脈以冰證道的根本吐納之術。內功
// 與招式 daemon (taoism-freeze.c) 不同﹐它是被動的「力道乘數」﹕戰鬥時
// COMBAT_D->fight() 會讀取 query_skill("force") 與 skill_mapped("force")
// ﹐藉氣(kee)與功力百分比(force_ratio)放大攻擊力道﹐因此內功 daemon 不需
// 要 actions 攻擊招式表﹐也不需要 attack_using()。
//
// 玩家透過 map_skill("force","polar-silkworm force") 將內功對應到本心法
// 後﹐力道才會隨內功修為成長。修煉內功的指令是 exert（見 cmds/std/
// exert.c）﹐它會呼叫本 daemon 的 exert_function()。
//
// 本檔比照天師派朱衣 daemon/skill/sun_force.c 複製﹐將火氣易為寒氣。
// 注意 key 含連字號與空白(polar-silkworm force)﹐故檔名為
// polar-silkworm_force.c（連字號保留﹐空白換底線）。
// TODO: force-specific tuning -- exert 的特殊功能(運功療傷、護體罡氣
//       等)與相關氣/精消耗待日後設計平衡。

#include <ansi.h>

inherit SKILL;

// 天師派素衣弟子打坐運功時所現的內功氣象（純文字氛圍﹐無戰鬥數值）。
string *exert_msg = ({
  "$N閉目盤膝﹐緩緩運轉冰蠶奇功﹐周身似有一股清冽的寒氣氤氳不散。\n",
  "$N凝神吐納﹐丹田之中一輪寒月冉冉升起﹐涼意循經而行﹐生生不息。\n",
  "$N默運神功﹐但覺真氣如玄冰封脈﹐沁寒之中自有一股護體的罡正。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("polar-silkworm force");
  setup();
}

// type() 由 /std/skill 提供﹐回傳 "martial"﹐skills 指令據此顯示重數描述。

// exert_function() : 由 cmds/std/exert.c 與 std/char/npc.c 呼叫﹐
// 用以施展內功的特殊功能。冰蠶奇功目前僅提供基本的運功打坐﹐
// 尚無特殊招式。
// TODO: 接上運功療傷 / 護體等具體功能。
varargs int
exert_function (object me, string func, object target)
{
  if( !me ) me = this_player();
  if( !me ) return 0;

  message_vision(HIC + exert_msg[random(sizeof(exert_msg))] + NOR, me);
  return 1;
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
