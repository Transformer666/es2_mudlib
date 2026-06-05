// 頂級稱號 (ad_rank) daemon -- 業力與聲望系統的「江湖頂級稱號」評定與加成。
//
// 來歷 (docs/02-遊戲系統與機制/04-業力與聲望.md L81-101)：
// ES2 的最高榮譽稱號 (邪魔 / 武痴 / 武聖 / 劍聖 / 劍魔 / 一代宗師 / 大魔頭 / 隱士 /
// 督主 / 大司馬 / 大元帥 / 鬼仙人 等) 需長期投入多軸聲望、殺業/惡行、精熟、屬性與
// 等級才能取得，取得後給予傷害 / 護甲 / 防禦 / 攻勢 / 攻擊能力 / 屬性等戰鬥加成。
// docs 那張表是本檔門檻與加成的權威來源──各 #define 旁皆標出 docs 行號與對應軸。
//
// 三大對外介面 (依任務規格)：
//   (1) query_ad_rank(me)  : 掃描 docs 各稱號門檻，回該玩家「目前可得的最高稱號」key
//                            (回 0 表尚無資格)。
//   (2) apply_title(me)    : 把該稱號的戰鬥加成掛上玩家 (透過 add_temp("apply/<k>",N)，
//                            戰鬥迴圈即讀這些鍵──見 feature/char/combat.c)。
//   (3) recalc(me)         : (1)+(2) 的組合──重新評定並換掛加成。供 gain_score hook
//                            與 cestablish 指令呼叫。
//
// 機制對齊 (皆已驗於 mudlib 現有程式)：
//   * 讀軸值   : me->query_score(course) ≡ query("score/"+course)
//                (feature/char/score.c:47)。
//   * 讀等級   : me->query_level()  (feature/char/score.c:7)。
//   * 讀屬性   : me->query_attr(attr) (feature/attribute.c:21)──督主/隱士等用悟性(int)/
//                偷襲(backstab skill)/潛行(sneak skill)；技能用 me->query_skill(sk)
//                (feature/char/skill.c:117)。
//   * 掛加成   : add_temp("apply/<key>", N)。戰鬥讀的鍵──傷害=apply/damage
//                (combat.c:261)、護甲=apply/armor (combat.c:277)、防禦=apply/defense
//                (combat.c:81)、攻擊=apply/attack (combat.c:72)、攻勢=apply/intimidate
//                (combat.c:90)、守勢=apply/wittiness、移動=apply/move (combat.c:122)。
//                屬性類加成 (臂力/膽識/悟性) 用 apply/<attr> (query_attr 讀 apply/<attr>，
//                feature/attribute.c)。完全鏡 cmds/std/wardance.c 之 add_temp 模型。
//   * 換掛紀律 : 重評時先把「上次掛的那一份」用 add_temp(-N) 減回去，再掛新的。
//                **不可 delete_temp("apply/...")**──那會抹掉戰舞/賦予/種族被動等其他
//                來源的同鍵加成 (與 wardance.c / strategy.c 同一鐵則)。上次掛了哪些、各
//                多少，記在 temp "ad_rank_applied" (一份 mapping)，以便精準減回。
//   * 持久性   : apply/* 走 temp (tmp_dbase 不存檔，登出即清，見 feature/dbase.c)，故
//                加成須於每次 recalc 重掛。recalc 由 gain_score (feature/char/score.c)
//                與 cestablish 指令觸發；玩家上線後第一次 survive/戰鬥 gain_score 即會
//                重新掛上。稱號 key 另存於持久屬性 "ad_rank" 供顯示/離線查詢。
//
// 數值原則：docs 已給之門檻與加成一律照表 (見各 #define 註)。docs 未給之門檻 (擂台勝場
// 無對應 score 軸) 取「合理可驗預設」並明確標出 (見 ARENA_SCORE 區塊)。
//
// runtime 鐵則：本檔為純資料/評定 daemon，不涉 ::die()/destruct() (#10)、不
// replace_program (#11)、不 add_action (daemon context 無 this_player 綁定)。

#include <ansi.h>

inherit F_CLEAN_UP;

// ── 稱號 key (內部識別字，亦為 query_ad_rank 回傳值)。中文名於 create() 註冊。──
#define T_XIEMO         "xiemo"         // 邪魔
#define T_WUCHI         "wuchi"         // 武痴
#define T_WUSHENG       "wusheng"       // 武聖
#define T_JIANSHENG     "jiansheng"     // 劍聖 / 刀皇
#define T_JIANMO        "jianmo"        // 劍魔 / 刀鬼
#define T_ZONGSHI       "zongshi"       // 一代宗師
#define T_DAMOTOU       "damotou"       // 大魔頭
#define T_YINSHI        "yinshi"        // 隱士
#define T_DUZHU         "duzhu"         // 督主
#define T_DASIMA        "dasima"        // 大司馬
#define T_DAYUANSHUAI   "dayuanshuai"   // 大元帥
#define T_GUIXIANREN    "guixianren"    // 鬼仙人

// ── score 軸 key (對應 data/chinese.o 之「score of <key>」中文名)。──
#define AX_KILLS        "kills"             // 殺業          (score of kills=殺業)
#define AX_SIN          "mortal sin"        // 重大惡行      (score of mortal sin=重大惡行)
#define AX_UNARMED      "unarmed mastery"   // 拳腳精熟      (score of unarmed mastery)
#define AX_WEAPON       "weapon mastery"    // 兵刃精熟      (score of weapon mastery)
#define AX_MARTIAL_M    "martial mastery"   // 武學之道      (score of martial mastery)
#define AX_MARTIAL_A    "martial art"       // 武術造詣      (score of martial art)
#define AX_REPUTATION   "reputation"        // 聲望          (score of reputation)
#define AX_MARTIAL_F    "martial fame"      // 武林聲望      (score of martial fame)
#define AX_COMBAT       "combat"            // 實戰經驗      (score of combat)
#define AX_MILITARY     "military service"  // 戰場功勛      (score of military service)
#define AX_LITERATURE   "literature"        // 文書能力      (score of literature)

// ── 擂台勝場 (docs L87-89 多個稱號需「擂台 500 勝」)。──
// 【合理預設，非 docs 給定】：grep 全 mudlib，擂台 (d/*/arena.c) 只是房間，無任何勝場
// 計數機制，也無對應 score 軸或中文字典 key。故此處新增一條專用 score 軸 "arena win"
// 來承載擂台勝場；待日後 arena.c 接上「勝一場 gain_score("arena win",1)」即自動生效。
// 在那之前此軸恆 0，需擂台勝場的稱號 (邪魔/武痴/武聖) 自然無人達標，安全且可驗。
#define AX_ARENA        "arena win"
#define ARENA_500       500                 // docs L87-89：擂台 500 勝

// ── docs L87-101 各稱號加成量 (一律照表)。──
#define B_XIEMO_DAMAGE      45      // 邪魔：傷害 45            (docs L87)
#define B_WUCHI_ARMOR       75      // 武痴：護甲 75            (docs L88)
#define B_WUSHENG_DEFENSE   100     // 武聖：防禦能力 100        (docs L89)
#define B_JIANSHENG_DEFENSE 60      // 劍聖/刀皇：防禦能力 60     (docs L90)
#define B_JIANMO_ATTACK     60      // 劍魔/刀鬼：攻擊能力 60     (docs L91)
#define B_ZONGSHI_ARMOR     45      // 一代宗師：護甲 45         (docs L92)
#define B_DAMOTOU_DAMAGE    25      // 大魔頭：傷害 25           (docs L93)
#define B_YINSHI_INT        9       // 隱士：悟性(int) 9        (docs L97)
#define B_DUZHU_INTIM       150     // 督主：攻勢 150           (docs L98)
#define B_DASIMA_STR        6       // 大司馬：臂力(str) 6       (docs L99)
#define B_DAYUANSHUAI_COR   6       // 大元帥：膽識(cor) 6       (docs L100)
#define B_GUIXIANREN_INT    6       // 鬼仙人：悟性(int) 6       (docs L101)

// ── docs L87-101 各稱號門檻 (一律照表)。──
// 邪魔        : 擂台 500 勝、殺業 30000、重大惡行 30000                    (docs L87)
#define R_XIEMO_KILLS       30000
#define R_XIEMO_SIN         30000
// 武痴        : 擂台 500 勝、殺業 < 10000、武學之道 1500000               (docs L88)
#define R_WUCHI_KILLS_MAX   10000
#define R_WUCHI_MARTIAL_M   1500000
// 武聖        : 擂台 500 勝、拳腳/兵刃精熟 5000000、重大惡行 < 10000       (docs L89)
#define R_WUSHENG_MASTERY   5000000
#define R_WUSHENG_SIN_MAX   10000
// 劍聖/刀皇   : lv 50、兵刃精熟 1000000、武林聲望 50000、實戰經驗 1000000  (docs L90)
#define R_JIANSHENG_LEVEL   50
#define R_JIANSHENG_WEAPON  1000000
#define R_JIANSHENG_FAME    50000
#define R_JIANSHENG_COMBAT  1000000
// 劍魔/刀鬼   : lv 50、殺業 20000、重大惡行 15000、兵刃精熟 1500000        (docs L91)
#define R_JIANMO_LEVEL      50
#define R_JIANMO_KILLS      20000
#define R_JIANMO_SIN        15000
#define R_JIANMO_WEAPON     1500000
// 一代宗師   : lv 50、同劍聖門檻                                          (docs L92)
// 大魔頭     : lv 50、殺業 20000、重大惡行 15000、兵刃精熟 1500000         (docs L93)
#define R_DAMOTOU_LEVEL     50
#define R_DAMOTOU_KILLS     20000
#define R_DAMOTOU_SIN       15000
#define R_DAMOTOU_WEAPON    1500000
// 隱士        : lv 50、武術造詣 700000、重大惡行 < 10000、殺業 < 5000      (docs L97)
#define R_YINSHI_LEVEL      50
#define R_YINSHI_MARTIAL_A  700000
#define R_YINSHI_SIN_MAX    10000
#define R_YINSHI_KILLS_MAX  5000
// 督主        : lv 50、武術造詣 500000、偷襲暗算 140、潛行 140、殺業 5000  (docs L98)
#define R_DUZHU_LEVEL       50
#define R_DUZHU_MARTIAL_A   500000
#define R_DUZHU_BACKSTAB    140
#define R_DUZHU_SNEAK       140
#define R_DUZHU_KILLS       5000
// 大司馬      : lv 60、戰場功勛 1000000、文書能力 250000、聲望 25000       (docs L99)
#define R_DASIMA_LEVEL      60
#define R_DASIMA_MILITARY   1000000
#define R_DASIMA_LITERATURE 250000
#define R_DASIMA_REPUTATION 25000
// 大元帥      : lv 60、戰場功勛 1000000、實戰經驗 1000000、殺業 25000      (docs L100)
#define R_DAYUANSHUAI_LEVEL 60
#define R_DAYUANSHUAI_MILITARY  1000000
#define R_DAYUANSHUAI_COMBAT    1000000
#define R_DAYUANSHUAI_KILLS     25000
// 鬼仙人      : lv 50、聲望 500                                          (docs L101)
#define R_GUIXIANREN_LEVEL  50
#define R_GUIXIANREN_REPUTATION 500

// ── 評定優先序：query_ad_rank 由「最尊崇 / 最難達成」往下檢查，回第一個達標者。──
// 排序原則：頂級稀有殺業/惡行/精熟者居前，等級/單軸門檻者居後。順序集中於此，便於日後
// 依平衡調整。鬼仙人門檻最低 (聲望 500) 故置末，作為「入門級頂級稱號」。
string *rank_order = ({
    T_WUSHENG,          // 武聖   (精熟 500萬 + 擂台 500 + 清白)
    T_XIEMO,            // 邪魔   (殺業/惡行各 30000 + 擂台 500)
    T_WUCHI,            // 武痴   (武學之道 150萬 + 擂台 500 + 殺業<1萬)
    T_DASIMA,           // 大司馬 (lv60 + 戰功/文書/聲望)
    T_DAYUANSHUAI,      // 大元帥 (lv60 + 戰功/實戰/殺業)
    T_JIANMO,           // 劍魔   (lv50 + 殺業/惡行/兵刃)
    T_DAMOTOU,          // 大魔頭 (lv50 + 殺業/惡行/兵刃，同劍魔門檻，加成較弱→次序在後)
    T_JIANSHENG,        // 劍聖   (lv50 + 兵刃/武林聲望/實戰)
    T_ZONGSHI,          // 一代宗師(lv50 + 同劍聖門檻，加成不同→次序在後)
    T_DUZHU,            // 督主   (lv50 + 武術造詣/偷襲/潛行/殺業)
    T_YINSHI,           // 隱士   (lv50 + 武術造詣 + 清白)
    T_GUIXIANREN,       // 鬼仙人 (lv50 + 聲望 500，入門頂級稱號)
});

// 前置宣告：以下函式於定義前被引用 (qs/qa/qsk 給 qualifies、qualifies 給 query_ad_rank、
// strip_old/apply_bonus 互相引用)。LPC 須先宣告否則編譯 "Undefined function" (lesson #12)。
private int qs(object me, string course);
private int qa(object me, string attr);
private int qsk(object me, string sk);
private int qualifies(object me, string rank);
private mapping bonus_of(string rank);
private void strip_old(object me);
private void apply_bonus(object me, string rank);
string title_chinese(string rank);

private void
create()
{
    seteuid(getuid());

    // 自行登錄各稱號中文名 (字典查無時 to_chinese 仍可工整顯示；已有則覆寫同值)。
    CHINESE_D->add_translate(T_XIEMO,       "邪魔");
    CHINESE_D->add_translate(T_WUCHI,       "武痴");
    CHINESE_D->add_translate(T_WUSHENG,     "武聖");
    CHINESE_D->add_translate(T_JIANSHENG,   "劍聖");
    CHINESE_D->add_translate(T_JIANMO,      "劍魔");
    CHINESE_D->add_translate(T_ZONGSHI,     "一代宗師");
    CHINESE_D->add_translate(T_DAMOTOU,     "大魔頭");
    CHINESE_D->add_translate(T_YINSHI,      "隱士");
    CHINESE_D->add_translate(T_DUZHU,       "督主");
    CHINESE_D->add_translate(T_DASIMA,      "大司馬");
    CHINESE_D->add_translate(T_DAYUANSHUAI, "大元帥");
    CHINESE_D->add_translate(T_GUIXIANREN,  "鬼仙人");

    // 擂台勝場軸亦登錄中文 (score of arena win)，與其他軸一致 (見 reputation 指令顯示)。
    CHINESE_D->add_translate("score of " + AX_ARENA, "擂台勝場");
}

// ── 讀值小工具 (集中型別轉換，避免散落)。──
private int qs(object me, string course)
{
    return (int)me->query_score(course);
}
private int qa(object me, string attr)
{
    return (int)me->query_attr(attr);
}
private int qsk(object me, string sk)
{
    return (int)me->query_skill(sk);
}

// ── qualifies(me, rank)：玩家是否滿足該稱號的全部 docs 門檻。──
// 每個 case 逐條對照 docs L87-101 (門檻 #define 旁已標 docs 行)。
private int
qualifies(object me, string rank)
{
    if( !objectp(me) ) return 0;

    switch( rank ) {
    case T_XIEMO:           // docs L87
        return qs(me, AX_ARENA) >= ARENA_500
            && qs(me, AX_KILLS) >= R_XIEMO_KILLS
            && qs(me, AX_SIN)   >= R_XIEMO_SIN;
    case T_WUCHI:           // docs L88
        return qs(me, AX_ARENA) >= ARENA_500
            && qs(me, AX_KILLS) <  R_WUCHI_KILLS_MAX
            && qs(me, AX_MARTIAL_M) >= R_WUCHI_MARTIAL_M;
    case T_WUSHENG:         // docs L89 (拳腳「或」兵刃精熟達標即可)
        return qs(me, AX_ARENA) >= ARENA_500
            && (qs(me, AX_UNARMED) >= R_WUSHENG_MASTERY
                || qs(me, AX_WEAPON) >= R_WUSHENG_MASTERY)
            && qs(me, AX_SIN) < R_WUSHENG_SIN_MAX;
    case T_JIANSHENG:       // docs L90
        return me->query_level() >= R_JIANSHENG_LEVEL
            && qs(me, AX_WEAPON) >= R_JIANSHENG_WEAPON
            && qs(me, AX_MARTIAL_F) >= R_JIANSHENG_FAME
            && qs(me, AX_COMBAT) >= R_JIANSHENG_COMBAT;
    case T_JIANMO:          // docs L91
        return me->query_level() >= R_JIANMO_LEVEL
            && qs(me, AX_KILLS) >= R_JIANMO_KILLS
            && qs(me, AX_SIN)   >= R_JIANMO_SIN
            && qs(me, AX_WEAPON) >= R_JIANMO_WEAPON;
    case T_ZONGSHI:         // docs L92：lv50 + 同劍聖門檻
        return me->query_level() >= R_JIANSHENG_LEVEL
            && qs(me, AX_WEAPON) >= R_JIANSHENG_WEAPON
            && qs(me, AX_MARTIAL_F) >= R_JIANSHENG_FAME
            && qs(me, AX_COMBAT) >= R_JIANSHENG_COMBAT;
    case T_DAMOTOU:         // docs L93
        return me->query_level() >= R_DAMOTOU_LEVEL
            && qs(me, AX_KILLS) >= R_DAMOTOU_KILLS
            && qs(me, AX_SIN)   >= R_DAMOTOU_SIN
            && qs(me, AX_WEAPON) >= R_DAMOTOU_WEAPON;
    case T_YINSHI:          // docs L97
        return me->query_level() >= R_YINSHI_LEVEL
            && qs(me, AX_MARTIAL_A) >= R_YINSHI_MARTIAL_A
            && qs(me, AX_SIN)   <  R_YINSHI_SIN_MAX
            && qs(me, AX_KILLS) <  R_YINSHI_KILLS_MAX;
    case T_DUZHU:           // docs L98 (偷襲暗算=backstab、潛行=sneak 技能)
        return me->query_level() >= R_DUZHU_LEVEL
            && qs(me, AX_MARTIAL_A) >= R_DUZHU_MARTIAL_A
            && qsk(me, "backstab") >= R_DUZHU_BACKSTAB
            && qsk(me, "sneak")    >= R_DUZHU_SNEAK
            && qs(me, AX_KILLS) >= R_DUZHU_KILLS;
    case T_DASIMA:          // docs L99
        return me->query_level() >= R_DASIMA_LEVEL
            && qs(me, AX_MILITARY)   >= R_DASIMA_MILITARY
            && qs(me, AX_LITERATURE) >= R_DASIMA_LITERATURE
            && qs(me, AX_REPUTATION) >= R_DASIMA_REPUTATION;
    case T_DAYUANSHUAI:     // docs L100
        return me->query_level() >= R_DAYUANSHUAI_LEVEL
            && qs(me, AX_MILITARY) >= R_DAYUANSHUAI_MILITARY
            && qs(me, AX_COMBAT)   >= R_DAYUANSHUAI_COMBAT
            && qs(me, AX_KILLS)    >= R_DAYUANSHUAI_KILLS;
    case T_GUIXIANREN:      // docs L101
        return me->query_level() >= R_GUIXIANREN_LEVEL
            && qs(me, AX_REPUTATION) >= R_GUIXIANREN_REPUTATION;
    default:
        return 0;
    }
}

// ── (1) query_ad_rank(me)：回該玩家目前可得的「最高」稱號 key (依 rank_order)；無則 0。──
string
query_ad_rank(object me)
{
    string rank;

    if( !objectp(me) ) return 0;
    foreach( rank in rank_order )
        if( qualifies(me, rank) )
            return rank;
    return 0;
}

// ── bonus_of(rank)：回該稱號要掛的 apply 加成 (([ "apply/<key>": N ]))。──
// key 即戰鬥迴圈會讀到的 apply 鍵 (見檔頭機制對齊)。docs 未指明攻防是「能力(ability)」還
// 是「技巧」者，依 docs 用字對應 combat.c 之 query_ability 軸：「防禦能力」→apply/defense、
// 「攻擊能力」→apply/attack、「攻勢」→apply/intimidate。「傷害」→apply/damage、「護甲」→
// apply/armor。屬性類 (臂力/膽識/悟性) → apply/<attr> (query_attr 讀)。
private mapping
bonus_of(string rank)
{
    switch( rank ) {
    case T_XIEMO:       return ([ "apply/damage"    : B_XIEMO_DAMAGE ]);
    case T_WUCHI:       return ([ "apply/armor"     : B_WUCHI_ARMOR ]);
    case T_WUSHENG:     return ([ "apply/defense"   : B_WUSHENG_DEFENSE ]);
    case T_JIANSHENG:   return ([ "apply/defense"   : B_JIANSHENG_DEFENSE ]);
    case T_JIANMO:      return ([ "apply/attack"    : B_JIANMO_ATTACK ]);
    case T_ZONGSHI:     return ([ "apply/armor"     : B_ZONGSHI_ARMOR ]);
    case T_DAMOTOU:     return ([ "apply/damage"    : B_DAMOTOU_DAMAGE ]);
    case T_YINSHI:      return ([ "apply/int"       : B_YINSHI_INT ]);
    case T_DUZHU:       return ([ "apply/intimidate": B_DUZHU_INTIM ]);
    case T_DASIMA:      return ([ "apply/str"       : B_DASIMA_STR ]);
    case T_DAYUANSHUAI: return ([ "apply/cor"       : B_DAYUANSHUAI_COR ]);
    case T_GUIXIANREN:  return ([ "apply/int"       : B_GUIXIANREN_INT ]);
    default:            return ([ ]);
    }
}

// ── strip_old(me)：把「上次掛上的稱號加成」逐鍵 add_temp(-N) 減回去並清紀錄。──
// 用 add_temp(-N) 而非 delete_temp，以保住戰舞/賦予/種族被動等其他來源的同鍵加成
// (與 cmds/std/wardance.c、daemon/skill/strategy.c 同一鐵則)。
private void
strip_old(object me)
{
    mapping applied;
    string key;
    int amt;

    applied = me->query_temp("ad_rank_applied");
    if( !mapp(applied) ) return;
    foreach( key, amt in applied )
        me->add_temp(key, -amt);
    me->delete_temp("ad_rank_applied");
}

// ── apply_bonus(me, rank)：掛上該稱號加成，並把掛了哪些/各多少記入 temp 供日後減回。──
private void
apply_bonus(object me, string rank)
{
    mapping bonus, applied;
    string key;
    int amt;

    bonus = bonus_of(rank);
    if( !mapp(bonus) || !sizeof(bonus) ) return;
    applied = ([ ]);
    foreach( key, amt in bonus ) {
        me->add_temp(key, amt);
        applied[key] = amt;
    }
    me->set_temp("ad_rank_applied", applied);
}

// ── (2) apply_title(me)：依目前可得最高稱號換掛加成 (先減舊、再掛新)，回稱號 key。──
// 同時把稱號 key 寫入持久屬性 "ad_rank" 供顯示與離線查詢。回 0 表目前無資格 (加成清空)。
string
apply_title(object me)
{
    string rank;

    if( !objectp(me) ) return 0;

    strip_old(me);                          // 先收回上次掛的那一份。
    rank = query_ad_rank(me);
    if( rank ) {
        apply_bonus(me, rank);
        me->set("ad_rank", rank);
    } else {
        me->delete("ad_rank");
    }
    return rank;
}

// ── (3) recalc(me)：重評並換掛；若稱號有變動則通知玩家。供 hook / 指令呼叫。──
// 回傳目前稱號 key (或 0)。為「便宜可頻繁呼叫」而設計：每次 gain_score 都會進來。
string
recalc(object me)
{
    string old_rank, new_rank;

    if( !objectp(me) ) return 0;

    old_rank = me->query("ad_rank");
    new_rank = apply_title(me);

    // 稱號升格時恭賀；失格 (例：殺業超過清白上限) 時告知。其餘 (無變動) 靜默。
    if( new_rank != old_rank ) {
        if( new_rank )
            tell_object(me, HIY "\n江湖傳言四起──你已被尊為一代「" +
                title_chinese(new_rank) + "」﹗\n" NOR);
        else if( old_rank )
            tell_object(me, NOR "\n你已不再配得上「" +
                title_chinese(old_rank) + "」這個稱號了。\n");
    }
    return new_rank;
}

// ── title_chinese(rank)：回稱號中文名 (字典查無則原樣回 key)。──
string
title_chinese(string rank)
{
    if( !stringp(rank) ) return "";
    return to_chinese(rank);
}

// ── 唯讀輔助：給指令/顯示用，回該稱號加成的人話描述 (鍵→中文+量)。──
// 例：邪魔 → "傷害 +45"。供 cestablish 指令列出。
string
describe_bonus(string rank)
{
    mapping bonus;
    string key, desc, label;
    int amt;

    bonus = bonus_of(rank);
    if( !mapp(bonus) || !sizeof(bonus) ) return "無";
    desc = "";
    foreach( key, amt in bonus ) {
        switch( key ) {
        case "apply/damage":     label = "傷害";     break;
        case "apply/armor":      label = "護甲";     break;
        case "apply/defense":    label = "防禦能力"; break;
        case "apply/attack":     label = "攻擊能力"; break;
        case "apply/intimidate": label = "攻勢";     break;
        case "apply/wittiness":  label = "守勢";     break;
        case "apply/move":       label = "移動力";   break;
        case "apply/str":        label = "臂力";     break;
        case "apply/cor":        label = "膽識";     break;
        case "apply/int":        label = "悟性";     break;
        default:                 label = key;        break;
        }
        if( desc != "" ) desc += "、";
        desc += sprintf("%s +%d", label, amt);
    }
    return desc;
}

// ── 唯讀輔助：回完整稱號評定順序 (供指令列出所有稱號)。──
string *
query_rank_order()
{
    return rank_order + ({ });
}

// vim: set ts=4 sw=4 syntax=lpc
