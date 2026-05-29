// 虎刀心法 hudao force -- 虎刀門護衛的入門內功
//
// 這是一門內功(force)心法﹐虎刀門賴以煉氣養刀的根本吐納之術。內功
// 與招式 daemon (bawang_blade.c) 不同﹐它是被動的「力道乘數」﹕戰鬥時
// COMBAT_D->fight() 會讀取 query_skill("force") 與 skill_mapped("force")﹐
// 藉氣(kee)與功力百分比(force_ratio)放大攻擊力道﹐因此內功 daemon 不需要
// actions 攻擊招式表﹐也不需要 attack_using()。
//
// 玩家透過 map_skill("force","hudao force") 將內功對應到本心法後﹐力道才會
// 隨內功修為成長。修煉內功的指令是 exert（見 cmds/std/exert.c）﹐它會呼叫
// 本 daemon 的 exert_function()。
//
// 本檔比照封山派內功(fonxanforce.c)、大內罡氣(danei_force.c)樣板撰寫。
// 注意「瘋虎功」(tiger force) 已為振武軍營所用﹐虎刀門另立一脈﹐故本心法
// 別名「虎刀心法」。此名在中文字典(data/chinese.o)裡尚無對應詞條﹐故比照
// danei_force.c 於 create() 時以 CHINESE_D->add_translate() 自行登錄中文名
//「虎刀心法」﹐使 skills / score 等指令能顯示中文。
//
// TODO: force-specific tuning -- exert 的特殊功能(運功療傷、護體罡氣等)
//       與相關氣/精消耗待日後設計平衡﹔虎刀門重剛猛搶攻﹐日後宜以
//       催動氣血、暴起發力為主軸。

#include <ansi.h>

inherit SKILL;

// 虎刀門弟子打坐運功時所現的內功氣象（純文字氛圍﹐無戰鬥數值）。
string *exert_msg = ({
  "$N盤膝閉目﹐緩緩運轉虎刀心法﹐周身似有一股剽悍燥烈的真氣如猛虎在籠般奔突鼓盪。\n",
  "$N凝神吐納﹐丹田之中一股霸烈剛猛之力沛然而生﹐血脈賁張﹐隱隱有虎嘯之聲在胸臆間迴盪。\n",
  "$N默運心法﹐但覺氣血翻騰如沸﹐一股催刀奪命的剛勁自筋骨深處節節暴起。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("hudao force");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("hudao force", "虎刀心法");
  setup();
}

// type() 由 /std/skill 提供﹐回傳 "martial"﹐skills 指令據此顯示重數描述。

// exert_function() : 由 cmds/std/exert.c 與 std/char/npc.c 呼叫﹐用以施展
// 內功的特殊功能。虎刀心法目前僅提供基本的運功打坐﹐尚無特殊招式。
// TODO: 接上催動氣血 / 護體等具體功能。
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
