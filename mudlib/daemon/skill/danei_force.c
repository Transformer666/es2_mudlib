// 大內罡氣 danei force -- 大內巡院統領門下的入門內功
//
// 這是一門內功(force)心法﹐大內巡院宿衛禁中、護駕緝兇的根本吐納之術。
// 內功與招式 daemon (danei_sword.c) 不同﹐它是被動的「力道乘數」﹕戰鬥時
// COMBAT_D->fight() 會讀取 query_skill("force") 與 skill_mapped("force")﹐
// 藉氣(kee)與功力百分比(force_ratio)放大攻擊力道﹐因此內功 daemon 不需要
// actions 攻擊招式表﹐也不需要 attack_using()。
//
// 玩家透過 map_skill("force","danei force") 將內功對應到本心法後﹐力道才會
// 隨內功修為成長。修煉內功的指令是 exert（見 cmds/std/exert.c）﹐它會呼叫
// 本 daemon 的 exert_function()。
//
// 本檔比照振武軍營的瘋虎功 daemon/skill/tiger_force.c（其本身比照七派內功
// hainmay_force.c）複製。大內罡氣在中文字典尚無詞條﹐故於 create() 時以
// CHINESE_D->add_translate() 自行登錄中文名「大內罡氣」。
//
// TODO: force-specific tuning -- exert 的特殊功能(運功療傷、護體罡氣等)
//       與相關氣/精消耗待日後設計平衡。

#include <ansi.h>

inherit SKILL;

// 大內巡院弟子打坐運功時所現的內功氣象（純文字氛圍﹐無戰鬥數值）。
string *exert_msg = ({
  "$N閉目盤膝﹐緩緩運轉大內罡氣﹐周身似有一層森嚴肅穆的護體真氣流轉。\n",
  "$N凝神吐納﹐丹田之中一股醇正剛猛之力沛然而生﹐如禁苑深嚴﹐凜然不可犯。\n",
  "$N默運神功﹐但覺真氣端凝厚重﹐剛正之中自有一股宿衛禁中的肅殺之意。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("danei force");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("danei force", "大內罡氣");
  setup();
}

// type() 由 /std/skill 提供﹐回傳 "martial"﹐skills 指令據此顯示重數描述。

// exert_function() : 由 cmds/std/exert.c 與 std/char/npc.c 呼叫﹐用以施展
// 內功的特殊功能。大內罡氣目前僅提供基本的運功打坐﹐尚無特殊招式。
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
