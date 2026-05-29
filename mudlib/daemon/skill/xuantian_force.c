// 玄天心法 xuantian force -- 玄天教散人門下的入門內功
//
// 這是一門內功(force)心法﹐玄天教以文心參武道、觀星問道的根本吐納之術。
// 內功與招式 daemon (xuantian-sword.c) 不同﹐它是被動的「力道乘數」﹕戰鬥時
// COMBAT_D->fight() 會讀取 query_skill("force") 與 skill_mapped("force")﹐
// 藉氣(kee)與功力百分比(force_ratio)放大攻擊力道﹐因此內功 daemon 不需要
// actions 攻擊招式表﹐也不需要 attack_using()。
//
// 玩家透過 map_skill("force","xuantian force") 將內功對應到本心法後﹐力道才會
// 隨內功修為成長。修煉內功的指令是 exert（見 cmds/std/exert.c）﹐它會呼叫
// 本 daemon 的 exert_function()。
//
// 本檔比照步玄心法 daemon/skill/myst-force.c（其本身比照七派內功
// hainmay_force.c）複製。玄天心法在中文字典尚無詞條﹐故於 create() 時以
// CHINESE_D->add_translate() 自行登錄中文名「玄天心法」。
// 注意 key「xuantian force」含空白﹐檔名以底線代之（xuantian_force.c）。
//
// TODO: force-specific tuning -- exert 的特殊功能(運功療傷、護體罡氣等)
//       與相關氣/精消耗待日後設計平衡。

#include <ansi.h>

inherit SKILL;

// 玄天教弟子打坐運功時所現的內功氣象（純文字氛圍﹐無戰鬥數值）。
string *exert_msg = ({
  "$N閉目盤膝﹐緩緩運轉玄天心法﹐周身似有一股玄奧清靈之氣如星河流轉不息。\n",
  "$N凝神吐納﹐丹田之中真氣如周天運轉﹐生生不息﹐機鋒暗藏。\n",
  "$N默運心法﹐但覺氣息澄澈空靈﹐神思之中自有一股觀星問道的玄妙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("xuantian force");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("xuantian force", "玄天心法");
  setup();
}

// type() 由 /std/skill 提供﹐回傳 "martial"﹐skills 指令據此顯示重數描述。

// exert_function() : 由 cmds/std/exert.c 與 std/char/npc.c 呼叫﹐用以施展
// 內功的特殊功能。玄天心法目前僅提供基本的運功打坐﹐尚無特殊招式。
// TODO: 接上運功療傷 / 護體等具體功能。
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
