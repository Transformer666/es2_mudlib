// 藏雲身法 cangyun steps -- 玄天教藏雲客(二轉)的進階身法(基礎技能 dodge)
//
// 玄天教評分「靈活 S」﹐藏雲客一脈最重身法游走、脫戰避實(見 docs/03-門派與
// 武功/04-書生-步玄玄天.md §玄天教-核心技能「藏雲訣 ── 拆招招架時若氣不足
// 50% 有機會自動脫離戰鬥」﹐及散人進階「脫離戰鬥進入潛行狀態」)。藏雲身法
// 由入門 dodge(縱躍閃躲之法)精進而成﹐身隨星轉、藏形匿跡﹐後發先至。
//
// 因基礎技能為 dodge(閃躲)﹐玩家透過 map_skill("dodge","cangyun steps") 對應
// 後﹐受實體攻擊防禦時即改呼叫本 daemon 的 dodge_using()(見 skill_mapped
// ("dodge") 路由﹐與 daemon/skill/dodge.c / damo-steps.c 同一介面)。本檔比照
// daemon/skill/damo-steps.c 實作 dodge_using﹐並因是上乘身法略予加成(設計值)。
// 注意 key 含空白﹐檔名以連字號代之﹐並自行登錄中文名「藏雲身法」。
//
// 設計(docs未明定確切數值)﹕在 dodge.c「技能等級為單位」的對稱模型上﹐藏雲
//   身法額外提供約 +10% 的閃避加成(身法精微、藏形游走)﹐供日後平衡微調。
//
// TODO(脫戰完整化)：docs 載藏雲訣「氣不足 50% 自動脫離戰鬥」、散人進階「脫戰
//   入潛行、對自身 1 delay」屬 perform/脫戰系統(非 dodge 介面)﹐標記為待辦。
//   本檔先接通 dodge_using 的防禦加成。

#include <ansi.h>

inherit SKILL;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("cangyun steps");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("cangyun steps", "藏雲身法");
	setup();
}

// 回傳藏雲身法對「守方防禦技巧」的加成(技能等級單位﹐與攻擊技能對稱)。
// me=防禦者﹔ability/strength=來襲攻擊的技巧與力道﹔from=攻擊來源物件。
// 較通用 dodge 略高(身法精微、藏形游走)。
int
dodge_using (object me, int ability, int strength, object from)
{
	if( !objectp(me) ) return 0;
	return me->query_skill("dodge") * 11 / 10;
}

int
valid_enable (string usage)
{
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
