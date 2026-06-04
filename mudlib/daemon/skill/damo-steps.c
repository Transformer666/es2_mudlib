// 達摩移身法 damo steps -- 白象寺進階(二轉)的高階身法(基礎技能 dodge)
//
// 白象寺羅漢一脈的上乘輕功(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §白象寺-羅漢核心技能﹕「達摩移身法 damo steps」﹔天月庵亦載此身法﹐為佛門
// 共通的移形換步之法)。由入門 dodge(縱躍閃躲之法)精進而成﹐借達摩面壁所悟的禪
// 機移形換影、後發先至。
//
// 因基礎技能為 dodge(閃躲)﹐玩家透過 map_skill("dodge","damo steps") 對應後﹐
// feature/char/combat.c::defend() 受實體攻擊時即改呼叫本 daemon 的 dodge_using()
// (見 skill_mapped("dodge") 路由﹐與 daemon/skill/dodge.c 同一介面)。本檔比照
// daemon/skill/dodge.c 實作 dodge_using﹐並因是上乘身法略予加成(設計值)。
//
// 設計(docs未明定確切數值)﹕在 dodge.c「技能等級為單位」的對稱模型上﹐達摩移身法
//   額外提供約 +10% 的閃避加成(身法精微、後發先至)﹐供日後平衡微調。
//
// TODO(身法完整化)：docs 載佛門身法尚有「達摩移身/落葉身法」的位移、脫戰等
//   perform 效果﹐屬 perform/move 系統(非 dodge 介面)﹐標記為待辦。本檔先接通
//   dodge_using 的防禦加成。

#include <ansi.h>

inherit SKILL;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("damo steps");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("damo steps", "達摩移身法");
	setup();
}

// 回傳達摩移身法對「守方防禦技巧」的加成(技能等級單位﹐與攻擊技能對稱)。
// me=防禦者﹔ability/strength=來襲攻擊的技巧與力道﹔from=攻擊來源物件。
// 較通用 dodge 略高(身法精微、後發先至)。
int
dodge_using (object me, int ability, int strength, object from)
{
	if( !objectp(me) ) return 0;
	return me->query_skill("dodge") * 11 / 10;
}

// vim: set ts=4 sw=4 syntax=lpc
