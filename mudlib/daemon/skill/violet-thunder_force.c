// 紫府雷經 violet-thunder force -- 天師派紫衣弟子的入門內功
//
// 這是一門內功(force)心法﹐天師派紫衣一脈以雷證道的根本吐納之術。內功
// 與招式 daemon (taoism-thunder.c) 不同﹐它是被動的「力道乘數」﹕戰鬥時
// COMBAT_D->fight() 會讀取 query_skill("force") 與 skill_mapped("force")
// ﹐藉氣(kee)與功力百分比(force_ratio)放大攻擊力道﹐因此內功 daemon 不需
// 要 actions 攻擊招式表﹐也不需要 attack_using()。
//
// 玩家透過 map_skill("force","violet-thunder force") 將內功對應到本心法
// 後﹐力道才會隨內功修為成長。修煉內功的指令是 exert（見 cmds/std/
// exert.c）﹐它會呼叫本 daemon 的 exert_function()。
//
// 本檔比照天師派玄衣 daemon/skill/galewind-force.c 複製﹐將罡風易為紫雷。
// 注意 key 含空白(violet-thunder force)﹐故檔名為
// violet-thunder_force.c（空白換底線）。
// TODO: force-specific tuning -- exert 的特殊功能(運功療傷、護體雷罡
//       等)與相關氣/精消耗待日後設計平衡。

#include <ansi.h>

inherit SKILL;

// 天師派紫衣弟子打坐運功時所現的內功氣象（純文字氛圍﹐無戰鬥數值）。
string *exert_msg = ({
  "$N閉目盤膝﹐緩緩運轉紫府雷經﹐周身似有一團幽幽的紫雷盤旋不散。\n",
  "$N凝神吐納﹐丹田之中一道雷氣冉冉升起﹐雷意循經而行﹐生生不息。\n",
  "$N默運神功﹐但覺真氣如紫府裂空﹐霹靂之中自有一股護體的雷罡。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("violet-thunder force");
  setup();
}

// type() 由 /std/skill 提供﹐回傳 "martial"﹐skills 指令據此顯示重數描述。

// exert_function() : 由 cmds/std/exert.c 與 std/char/npc.c 呼叫﹐
// 用以施展內功的特殊功能。紫府雷經目前僅提供基本的運功打坐﹐
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
