// 逍遙遊 xiaoyao-steps -- 步玄派「逍遙居士」進階(二轉)的最上乘身法(基礎技能 dodge)
//
// 步玄派評分「靈活 B」﹐入門已有冠絕天下的步玄七絕(myst-steps)輕功﹔逍遙
// 居士一脈更精進為逍遙遊身法(見 docs/03-門派與武功/04-書生-步玄玄天.md
// §步玄派-核心技能「逍遙遊 ── 120 級後視悟性恢復精氣現在值﹐獲得四倍
// 躲閃」)。逍遙遊由入門 dodge(縱躍閃躲之法)精進而成﹐身隨意走、逍遙
// 自在﹐閃避之能登峰造極。
//
// 因基礎技能為 dodge(閃躲)﹐玩家透過 map_skill("dodge","xiaoyao-steps")
// 對應後﹐受實體攻擊防禦時即改呼叫本 daemon 的 dodge_using()(見 skill_mapped
// ("dodge") 路由﹐與 daemon/skill/dodge.c / cangyun-steps.c / damo-steps.c
// 同一介面)。本檔比照 daemon/skill/cangyun-steps.c 實作 dodge_using﹐並因
// 是步玄最上乘身法略予加成(設計值)。docs 英文未給 key﹐故 daemon 註冊名
// 取直觀的 "xiaoyao-steps"﹐並自行登錄中文名「逍遙遊」。
//
// 數值為本次設計值(docs「四倍躲閃」屬 120 級之 perform/精氣系統﹐非常駐
//   dodge 加成)﹐供日後平衡微調﹕在 dodge.c「技能等級為單位」的對稱模型
//   上﹐逍遙遊額外提供約 +15% 的常駐閃避加成(身法逍遙、身隨意走)。
//
// TODO(逍遙遊完整化)：docs 載逍遙遊「120 級後視悟性恢復精氣現在值、獲得
//   四倍躲閃」屬 perform/精氣恢復系統(非 dodge 介面)﹐標記為待辦。本檔先
//   接通 dodge_using 的常駐防禦加成。

#include <ansi.h>

inherit SKILL;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("xiaoyao-steps");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("xiaoyao-steps", "逍遙遊");
	setup();
}

// 回傳逍遙遊對「守方防禦技巧」的加成(技能等級單位﹐與攻擊技能對稱)。
// me=防禦者﹔ability/strength=來襲攻擊的技巧與力道﹔from=攻擊來源物件。
// 較通用 dodge 略高(身法逍遙、身隨意走)。
int
dodge_using (object me, int ability, int strength, object from)
{
	if( !objectp(me) ) return 0;
	return me->query_skill("dodge") * 23 / 20;
}

int
valid_enable (string usage)
{
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
