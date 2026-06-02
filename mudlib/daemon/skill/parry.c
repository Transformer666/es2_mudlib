// /daemon/skill/parry.c -- 招架（拆招）技能 daemon。實作 parry_using（決策 B-1，遵循原 ES2 設計）。
//
// 由 feature/char/combat.c::absorb() 於「防禦失敗（沒閃過）」時呼叫：
//     strength -= SKILL_D(skill_mapped("parry"))->parry_using(me, ability, strength, from);
// 回傳「被招架吸收掉的力道」，直接削減入射力道 → 減傷（力道 <=0 則該擊 0 傷）。
//
// 設計（依 docs/02-遊戲系統與機制/02-戰鬥公式.md「招架：武器 + 定力 + 慧根；沒武器無法 parry」）：
//   - 沒佩戴武器 → 無法招架武器攻擊 → 回 0。
//   - 吸收量 = 入射力道 × f(招架技能)，並由 定力(cps)/慧根(wis) 微幅放大；遞減、封頂 75%
//     （永遠保留些許傷害，招架不能完全無敵）。
//
// 背景：此前 parry_using 全專案未實作 → absorb() 呼叫回 0 → 招架技能對減傷完全無效。本檔接通之。

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("parry");
    setup();
}

// 回傳被招架吸收的力道。me=防禦者；strength=來襲力道；from=攻擊來源。
int
parry_using (object me, int ability, int strength, object from)
{
    mapping wielded;
    int skill, absorb, cap;

    if( !objectp(me) || strength <= 0 ) return 0;

    // ES2 設計：沒佩戴武器無法招架武器攻擊。query_temp("weapon") 為 (技能->武器) mapping。
    wielded = me->query_temp("weapon");
    if( !mapp(wielded) || !sizeof(wielded) ) return 0;

    skill = me->query_skill("parry");
    if( skill <= 0 ) return 0;

    // 吸收比例隨招架技能遞增（遞減曲線）：skill 100 ≈ 43%、200 ≈ 61%。
    absorb = strength * skill / (skill + 130);
    // 定力(cps)/慧根(wis) 微幅調整：cps20+wis20 → ×1.0。
    absorb = absorb * (30 + me->query_attr("cps") + me->query_attr("wis")) / 70;

    // 封頂 75%：招架再強也保留至少 1/4 力道，避免完全無敵。
    cap = strength * 3 / 4;
    if( absorb > cap ) absorb = cap;
    if( absorb < 0 ) absorb = 0;

    return absorb;
}

// vim: set ts=4 sw=4 syntax=lpc
