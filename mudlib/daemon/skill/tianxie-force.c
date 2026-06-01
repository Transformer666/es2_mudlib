// 天邪神功 tianxie-force -- 雪吟莊浪人的入門內功
//
// 這是一門內功(force)心法﹐源自外邦「天邪國」﹐乃雪吟莊一脈根本的吐納
// 之術(docs/03-門派與武功/01-武者-五大門派.md §4﹕雪吟莊本門武功並無獨到﹐
// 然源自天邪國的內功強悍﹔棄徒一脈「天邪神功 190+ 占決定性因素」)。內功
// 與招式 daemon (deepblade.c) 不同﹐它是被動的「力道乘數」﹕戰鬥時
// COMBAT_D->fight() 會讀取 query_skill("force") 與 skill_mapped("force")﹐
// 藉氣(kee)與功力百分比(force_ratio)放大攻擊力道﹐因此內功 daemon 不需要
// actions 攻擊招式表﹐也不需要 attack_using()。
//
// 玩家透過 map_skill("force","tianxie-force") 將內功對應到本心法後﹐力道
// 才會隨內功修為成長。修煉內功的指令是 exert（見 cmds/std/exert.c）﹐它會
// 呼叫本 daemon 的 exert_function()。
//
// 本檔比照封山派內功 daemon/skill/fonxanforce.c（其本身比照七派內功
// hainmay_force.c）複製。天邪神功在中文字典(data/chinese.o)尚無詞條﹐故於
// create() 時以 CHINESE_D->add_translate() 自行登錄中文名「天邪神功」。
//
// TODO: force-specific tuning -- exert 的特殊功能(護體、運功療傷、天邪虎嘯
//       等)與相關氣/精消耗待日後設計平衡﹔天邪一脈以高 kee、高 attr 與牽制
//       見長(虎督/天邪派弟子分支)﹐日後宜以此為主軸。

#include <ansi.h>

inherit SKILL;

// 雪吟莊浪人打坐運功時所現的內功氣象（純文字氛圍﹐無戰鬥數值）。
string *exert_msg = ({
  "$N盤膝閉目﹐緩緩運轉天邪神功﹐周身似有一股陰冷詭譎的真氣流轉不息。\n",
  "$N凝神吐納﹐丹田之中一股源出外邦的雄渾邪勁沛然而生﹐剛猛之中暗藏煞氣。\n",
  "$N默運心法﹐但覺氣息渾厚難測﹐如天邪國萬里風雪﹐凜然不可逼視。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("tianxie-force");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("tianxie-force", "天邪神功");
  setup();
}

// type() 由 /std/skill 提供﹐回傳 "martial"﹐skills 指令據此顯示重數描述。

// exert_function() : 由 cmds/std/exert.c 與 std/char/npc.c 呼叫﹐用以施展
// 內功的特殊功能。天邪神功目前僅提供基本的運功打坐﹐尚無特殊招式。
// TODO: 接上護體 / 運功療傷 / 牽制等具體功能。
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
