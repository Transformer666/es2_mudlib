// 武陀心法 wuto force -- 武陀灸堂香主弟子的入門內功
//
// 這是一門內功(force)心法﹐武陀灸堂行針施灸、養氣活人的根本吐納之術。
// 內功與招式 daemon (wuto-needle.c) 不同﹐它是被動的「力道乘數」﹕戰鬥時
// COMBAT_D->fight() 會讀取 query_skill("force") 與 skill_mapped("force")﹐
// 藉氣(kee)與功力百分比(force_ratio)放大攻擊力道﹐因此內功 daemon 不需要
// actions 攻擊招式表﹐也不需要 attack_using()。
//
// 玩家透過 map_skill("force","wuto force") 將內功對應到本心法後﹐力道才會
// 隨內功修為成長。修煉內功的指令是 exert（見 cmds/std/exert.c）﹐它會呼叫
// 本 daemon 的 exert_function()。
//
// 本檔比照隱教心法 daemon/skill/yinjiao_force.c（其本身比照七派內功
// hainmay_force.c）複製。武陀心法在中文字典尚無詞條﹐故於 create() 時以
// CHINESE_D->add_translate() 自行登錄中文名「武陀心法」（比照 danei_force.c）。
// TODO: force-specific tuning -- exert 的特殊功能(運功療傷、護體真氣、艾火
//       溫養等)與相關氣/精消耗待日後設計平衡。

#include <ansi.h>

inherit SKILL;

// 武陀灸堂弟子打坐運功時所現的內功氣象（純文字氛圍﹐無戰鬥數值）。
string *exert_msg = ({
  "$N閉目盤膝﹐緩緩運轉武陀心法﹐周身似有一股溫醇平和之氣循經流轉。\n",
  "$N凝神吐納﹐丹田之中真氣如艾火溫煦﹐溫養經脈﹐生生不息。\n",
  "$N默運心法﹐但覺氣息如灸火生暖﹐平和之中自有一股活人濟世的生機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("wuto force");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("wuto force", "武陀心法");
  setup();
}

// type() 由 /std/skill 提供﹐回傳 "martial"﹐skills 指令據此顯示重數描述。

// exert_function() : 由 cmds/std/exert.c 與 std/char/npc.c 呼叫﹐用以施展
// 內功的特殊功能。武陀心法目前僅提供基本的運功打坐﹐尚無特殊招式。
// TODO: 接上運功療傷 / 護體 / 艾火溫養等具體功能。
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
