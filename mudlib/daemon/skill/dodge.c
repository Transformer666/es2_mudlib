// /daemon/skill/dodge.c -- 閃躲技能 daemon。實作 dodge_using（決策 B-1，遵循原 ES2「雙重防禦」設計）。
//
// 由 feature/char/combat.c::defend() 於受實體攻擊時呼叫：
//     counter_ability = query_ability("defense")            // 防禦技巧 = 機敏×定力/10 + 精/32（dex 驅動已在此）
//                     + SKILL_D(skill_mapped("dodge"))->dodge_using(me, ability, strength, from);
//     命中率 chance = 50 + (攻方技巧 - 守方技巧) * 2;
//
// 設計（依 docs/02-遊戲系統與機制/02-戰鬥公式.md「閃躲：機敏 + 行動 + 技能」）：
//   閃躲技能以「技能等級為單位」加進守方技巧，與攻方 query_skill(攻擊技) 完全對稱
//   ——故閃躲 100 可抵銷攻擊 100（chance 回到 50%）。機敏(dex) 的屬性部分已在
//   query_ability("defense") = dex×cps/10 內，無需在此重複。
//
// 背景：此前 dodge_using 全專案未實作 → defend() 呼叫回 0 → 閃躲技能對防禦完全無效
//       （決策 B 之症結：練了閃躲沒用、怪/boss 的閃避值惰性）。本檔接通之。

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("dodge");
    setup();
}

// 回傳閃躲技能對「守方防禦技巧」的加成（技能等級單位，與攻擊技能對稱）。
// me=防禦者；ability/strength=來襲攻擊的技巧與力道；from=攻擊來源物件。
int
dodge_using (object me, int ability, int strength, object from)
{
    if( !objectp(me) ) return 0;
    return me->query_skill("dodge");
}

// vim: set ts=4 sw=4 syntax=lpc
