// 強力格擋技巧 heavy_parry -- 虎刀門「太守」進階(二轉)的高階格擋 sr(基礎技能 parry)
//
// 太守一脈的格擋絕學﹐docs 載「多 sr 系列…強力格擋技巧(heavy_parry)」(見
// docs/03-門派與武功/01-武者-五大門派.md §5 虎刀門-太守﹐評分 防禦 C+)。中文名
// 「強力格擋技巧」於 data/chinese.o 已有對應 key "heavy_parry":"強力格擋技巧"﹐
// 故本檔沿用該 romanization "heavy_parry"﹐add_translate 僅作備援(字典已有則覆寫
// 同值﹐無害)。
//
// 基礎技能為 parry(招架/拆招)。玩家透過 map_skill("parry","heavy_parry") 將招架
// 對應到本招式後﹐feature/char/combat.c::absorb() 於防禦失敗時即呼叫本檔的
// parry_using() 來吸收力道減傷。本檔比照入門 daemon/skill/parry.c 之 parry_using
// 機制建立﹐但為「強力」格擋﹕吸收曲線更快飽和、定力(cps)放大更顯著、封頂略高
// (但仍保留些許傷害﹐格擋不能完全無敵)﹐以體現太守剛猛硬擋的厚重防禦。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   入門 parry.c skill 100 ≈ 43% / 200 ≈ 61%、封頂 75%﹔
//   本檔(強力)   skill 100 ≈ 50% / 200 ≈ 67%、封頂 80%。
//
// TODO(太守完整化)：docs 將強力格擋技巧列為 sr(特殊招/perform 系列)﹐其依技能
//   機率主動觸發的「強力格擋」狀態屬 combat/perform 系統。本檔先把「映射到 parry
//   時的被動減傷曲線」做實(較入門 parry 強)﹐與專案既有 parry.c 同一機制﹐
//   主動觸發部分標記為待辦。

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("heavy_parry");
    // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示(字典已有則覆寫同值)。
    CHINESE_D->add_translate("heavy_parry", "強力格擋技巧");
    setup();
}

// 回傳被招架吸收的力道。me=防禦者；strength=來襲力道；from=攻擊來源。
// 比照 daemon/skill/parry.c::parry_using﹐但係「強力格擋」﹐吸收更高、封頂略寬。
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

    // 強力格擋：吸收比例隨招架技能遞增﹐曲線較入門 parry 更快飽和。
    // skill 100 ≈ 50%、200 ≈ 67%(入門 parry 為 /(skill+130)﹐此處 /(skill+100))。
    absorb = strength * skill / (skill + 100);
    // 定力(cps)放大更顯著：cps20+wis20 → ×1.0﹐但 cps 權重較入門高。
    absorb = absorb * (25 + me->query_attr("cps") * 3 / 2 + me->query_attr("wis")) / 70;

    // 封頂 80%：強力格擋再硬也保留至少 1/5 力道﹐避免完全無敵。
    cap = strength * 4 / 5;
    if( absorb > cap ) absorb = cap;
    if( absorb < 0 ) absorb = 0;

    return absorb;
}

int
valid_enable (string usage)
{
    return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
