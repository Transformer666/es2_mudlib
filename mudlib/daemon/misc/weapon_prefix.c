// 武器材質前綴 (weapon material prefix) daemon -- 「材質前綴」系統的資料與套用引擎。
//
// 來歷 (docs/02-遊戲系統與機制/05-裝備與強化.md L65-71、L82-99；01-屬性與三維資源.md
// L112-119)：ES2 武器有 21 種「材質前綴」(青銅、鐵棘、…、大鵬)，前綴會改寫武器的外觀名
// 與數值。少數頂級材質本身就是「屬性裝」(docs L112-119)：太陽=根骨(con)+2、巫首=靈性(spi)
// +2、焦僥=機敏(dex)+3。其餘多為純「傷害階」(青銅最低階，鐵棘<點鋼<赤血<紫陽 遞增，
// 鳳凰/天龍/澤獸/大鵬 為頂階)。各武器類的數值上限見 docs L82-99 之強化上限表。
//
// 機制對齊 (皆已驗於 mudlib 現有程式)：
//   * 武器分式 4 維存於 class damage_parameter (include/combat.h)：multipler(乘數)、
//     range(傷害區間基數)、bonus(力量修正%)、roll(傷害微調)。各武器以 setup_<type>(x,y,z,r)
//     一次設定主手/副手/雙手三條 damage/<skill> (見 feature/weapon/*.c)。
//   * 重設數值：呼叫武器物件自身的 setup_<type>(x,y,z,r)──該函式由武器 inherit 的
//     F_<TYPE> 提供 (feature/weapon/sword.c 等)，會重寫 damage/<skill>。本 daemon 不自行
//     init_damage，而是調武器既有的 setup_ 介面，確保主/副/雙手三式比例一致 (鏡
//     obj/area/obj/longsword.c::create 之 setup_sword 用法)。
//   * 讀現值：query("damage/"+skill) 回該 skill 的 class damage_parameter
//     (feature/equip.c L238)，由此取得武器「未加前綴前」的基準 x/y/z/r 作為縮放基準。
//   * 改名/改 id：set("name",新名)、set("id",新id)。屬性加成走 set("apply_weapon/"+skill,
//     mapping)──wield 時 feature/equip.c L191-192 讀此 mapping apply() 到玩家。完全鏡
//     adm/daemons/enhanced.c::enhance_weapon (L206-219) 之改名/改 id/掛 apply_weapon 模型。
//   * 屬性鍵：根骨=con、機敏=dex、靈性=spi (enhanced.c：太陽=con+2 L122-125、焦僥=dex+3
//     L150-153 即此對應；巫首靈性 docs L113→spi)。
//   * 中文字典：CHINESE_D->add_translate(key,中文) 登錄，to_chinese(key) 取回
//     (adm/daemons/chinesed.c L104、adm/simul_efun/chinese.c L16)。鏡 daemon/misc/title.c
//     L184-198 之 add_translate 用法。
//   * 上限：各武器類的 (乘數/力修) 上限照 docs L82-99 表 (見 CAP_* 區塊)。重設前一律 clamp
//     到該武器類上限，且不可逾越該武器 setup_<type> 自身的合法範圍 (feature/weapon/*.c 的
//     error() 邊界)，故 clamp 取「docs 上限」與「setup 合法上限」之較小者，永不觸發 error。
//
// 數值原則：docs 有給之屬性 (太陽/巫首/焦僥) 與各武器類上限一律照表。docs 未列明確屬性/
// 階位的材質，取「合理可驗預設」並於下方 PREFIX 表逐筆標明 (見每筆 // [docs] / // [預設])。
//
// runtime 鐵則：本檔為純資料/工具 daemon，不涉 ::die()/destruct() (#10)、不 replace_program
// (#11)、不 add_action (daemon context 無 this_player 綁定)。inherit F_CLEAN_UP 使閒置時自動
// 回收 (鏡 daemon/misc/title.c L47、daemon/misc/loot.c L30)。

#include <ansi.h>
#include <combat.h>
#include <globals.h>

inherit F_CLEAN_UP;

// ── 21 材質前綴 id (內部識別字，亦為對外清單回傳值)。中文名於 create() 登錄字典。──
// 順序大致由低階往高階 (對齊 docs L69 之列序)。
#define P_QINGTONG  "qingtong"      // 青銅 (最低階)
#define P_TIEJI     "tieji"         // 鐵棘
#define P_DIANGANG  "diangang"      // 點鋼
#define P_CHIXUE    "chixue"        // 赤血
#define P_ZIYANG    "ziyang"        // 紫陽
#define P_TAIYANG   "taiyang"       // 太陽  (屬性裝：con+2)
#define P_WUCHANG   "wuchang"       // 無腸
#define P_JIAOJAO   "jiaojao"       // 焦僥  (屬性裝：dex+3)
#define P_QINGYANG  "qingyang"      // 青陽
#define P_MALIK     "malik"         // 巫首  (屬性裝：spi+2)
#define P_DIAOHUA   "diaohua"       // 雕花
#define P_JINXIANG  "jinxiang"      // 金鑲
#define P_CHANBU    "chanbu"        // 纏布
#define P_XINGTIAN  "xingtian"      // 形天
#define P_XIULUO    "xiuluo"        // 修羅
#define P_TONGYUN   "tongyun"       // 彤雲
#define P_GUDING    "guding"        // 古錠
#define P_FENGHUANG "fenghuang"     // 鳳凰 (頂階)
#define P_TIANLONG  "tianlong"      // 天龍 (頂階)
#define P_ZESHOU    "zeshou"        // 澤獸 (頂階)
#define P_DAPENG    "dapeng"        // 大鵬 (頂階)

// ── 傷害階 (tier)：1=最低 .. 5=頂階。決定對基準 x(乘數)/z(力修) 的縮放比例。──
// tier 不直接等於最終數值──最終數值仍須 clamp 到各武器類上限 (見 apply_prefix)。
#define TIER_MIN    1
#define TIER_MAX    5

// ── 各武器類「最終值」上限 (docs L82-99 強化上限表)。──
// 每筆：CAP_<type>_MULT = 乘數上限、CAP_<type>_FORCE = 力量修正(%)上限。
// (傷害區間上限由各 setup_<type> 自身 y 範圍把關，本表不另設。)
// 主手 skill 對應之武器類取「該類本身」(非雙手版) 之上限，因 setup_ 一次設好主/副/雙手，
// 只要主手不逾上限即安全。
#define CAP_SWORD_MULT      5       // Sword 乘數 5            (docs L92)
#define CAP_SWORD_FORCE     150     // Sword 力修 150%
#define CAP_BLADE_MULT      4       // Blade 乘數 4            (docs L90? 表列 Blade)
#define CAP_BLADE_FORCE     200     // Blade 力修 200%
#define CAP_AXE_MULT        5       // Axe 乘數 5              (docs L88)
#define CAP_AXE_FORCE       200     // Axe 力修 200%
#define CAP_DAGGER_MULT     3       // Dagger/Needle 乘數 3    (docs L91)
#define CAP_DAGGER_FORCE    100     // Dagger/Needle 力修 100%
#define CAP_BLUNT_MULT      6       // Blunt 乘數 6            (docs L89? 表列 Blunt)
#define CAP_BLUNT_FORCE     300     // Blunt 力修 300%
#define CAP_PIKE_MULT       5       // Pike (twohanded 表列 6，主手 pike 取 5 保守)  [預設]
#define CAP_PIKE_FORCE      100     // Twohanded Pike 力修 150%；主手 pike 取 100 保守 [預設]
#define CAP_STAFF_MULT      3       // Staff 乘數 (twohanded staff 表列 4，主手取 3)  [預設]
#define CAP_STAFF_FORCE     200     // Twohanded Staff 375%；主手 staff 取 200 保守    [預設]
#define CAP_WHIP_MULT       6       // Whip 乘數 6             (docs L99? 表列 Whip)
#define CAP_WHIP_FORCE      100     // Whip 力修 100%

// ── 前綴評定順序 (random_prefixed_weapon 依 level 選階時用)：由低階往高階。──
// 同階內隨機抽一個。階位界線見 tier_of()。
string *prefix_order = ({
    P_QINGTONG, P_TIEJI, P_DIANGANG, P_CHIXUE, P_ZIYANG,
    P_TAIYANG, P_WUCHANG, P_JIAOJAO, P_QINGYANG, P_MALIK,
    P_DIAOHUA, P_JINXIANG, P_CHANBU, P_XINGTIAN, P_XIULUO,
    P_TONGYUN, P_GUDING, P_FENGHUANG, P_TIANLONG, P_ZESHOU, P_DAPENG,
});

// 前置宣告：以下函式於定義前被引用 (lesson #12──LPC 須先宣告否則 "Undefined function")。
//   prefix_data 給多數查詢函式；tier_of/zh/color 給 apply_prefix；
//   weapon_type_of/type_cap_mult/type_cap_force/type_noun 給 apply_prefix；
//   clamp 給 apply_prefix；rescale 給 apply_prefix。
string *query_prefixes();
string prefix_zh(string p);
private mapping prefix_data(string p);
private int tier_of(string p);
private string color_of(string p);
private mapping attr_of(string p);
private string weapon_type_of(object weapon);
private int type_cap_mult(string type);
private int type_cap_force(string type);
private string type_noun(object weapon, string type);
private int clamp(int v, int lo, int hi);
private mapping current_params(object weapon, string skill);
private string primary_skill(object weapon);
int apply_prefix(object weapon, string prefix);
private int prefix_rename(object weapon, mapping d, string prefix, string type);
object make_prefixed_weapon(string base_path, string prefix);
object random_prefixed_weapon(int level);
string choose_prefix(int level);
string debug_prefix_distribution(int level, int trials);

private void
create()
{
    seteuid(getuid());

    // 登錄 21 材質前綴中文名 (供 to_chinese / 顯示用；已有則覆寫同值)。
    CHINESE_D->add_translate(P_QINGTONG,  "青銅");
    CHINESE_D->add_translate(P_TIEJI,     "鐵棘");
    CHINESE_D->add_translate(P_DIANGANG,  "點鋼");
    CHINESE_D->add_translate(P_CHIXUE,    "赤血");
    CHINESE_D->add_translate(P_ZIYANG,    "紫陽");
    CHINESE_D->add_translate(P_TAIYANG,   "太陽");
    CHINESE_D->add_translate(P_WUCHANG,   "無腸");
    CHINESE_D->add_translate(P_JIAOJAO,   "焦僥");
    CHINESE_D->add_translate(P_QINGYANG,  "青陽");
    CHINESE_D->add_translate(P_MALIK,     "巫首");
    CHINESE_D->add_translate(P_DIAOHUA,   "雕花");
    CHINESE_D->add_translate(P_JINXIANG,  "金鑲");
    CHINESE_D->add_translate(P_CHANBU,    "纏布");
    CHINESE_D->add_translate(P_XINGTIAN,  "形天");
    CHINESE_D->add_translate(P_XIULUO,    "修羅");
    CHINESE_D->add_translate(P_TONGYUN,   "彤雲");
    CHINESE_D->add_translate(P_GUDING,    "古錠");
    CHINESE_D->add_translate(P_FENGHUANG, "鳳凰");
    CHINESE_D->add_translate(P_TIANLONG,  "天龍");
    CHINESE_D->add_translate(P_ZESHOU,    "澤獸");
    CHINESE_D->add_translate(P_DAPENG,    "大鵬");
}

// ── 21 前綴資料表。每筆：([ "zh":中文材質名, "tier":傷害階1~5, "color":ANSI 色,
//    "attr":屬性加成 mapping (無則 0), "id":英文 id 前綴 ])。──
// tier→數值縮放見 rescale()；attr 之 docs/預設 標於各筆右側。
private mapping
prefix_data(string p)
{
    switch( p ) {
    // ── 低階傷害材質 (tier 1) ──
    case P_QINGTONG:    // [docs L69 列首=最低階]
        return ([ "zh":"青銅", "tier":1, "color":CYN, "attr":0, "id":"bronze" ]);
    case P_TIEJI:       // [docs L69：鐵棘 低階，遞增起點] 鏡 enhanced.c 鐵棘=str+1/damage+2 之低階定位
        return ([ "zh":"鐵棘", "tier":1, "color":HIK, "attr":0, "id":"thorny" ]);
    // ── 入門偏中 (tier 2) ──
    case P_DIANGANG:    // [docs L69：點鋼，鐵棘<點鋼] 鏡 enhanced.c 點鋼=attack+5/damage+2
        return ([ "zh":"點鋼", "tier":2, "color":HIW, "attr":0, "id":"steel" ]);
    case P_CHANBU:      // [預設] 纏布：握柄材質，定位低中階純傷害 (enhanced.c 纏布=cps+1/armor+3)
        return ([ "zh":"纏布", "tier":2, "color":HIK, "attr":0, "id":"wrapped-hilt" ]);
    case P_DIAOHUA:     // [預設] 雕花：工藝材質，中低階 (enhanced.c 雕花=dex+1/defense+5)
        return ([ "zh":"雕花", "tier":2, "color":HIM, "attr":0, "id":"engraved" ]);
    // ── 中階 (tier 3) ──
    case P_CHIXUE:      // [docs L69：赤血，點鋼<赤血] 鏡 enhanced.c 赤血=damage+5 (中階傷害)
        return ([ "zh":"赤血", "tier":3, "color":RED, "attr":0, "id":"blood" ]);
    case P_GUDING:      // [預設] 古錠：古樸金屬，中階 (enhanced.c 古錠=defense+10/cps+1)
        return ([ "zh":"古錠", "tier":3, "color":YEL, "attr":0, "id":"darkmetal" ]);
    case P_TONGYUN:     // [預設] 彤雲：中階 (enhanced.c 彤雲=wis+1/cor+1)
        return ([ "zh":"彤雲", "tier":3, "color":HIR, "attr":0, "id":"cloudy" ]);
    case P_QINGYANG:    // [預設] 青陽：與紫陽同系，中階純傷害 (enhanced.c 青陽=wis+2)
        return ([ "zh":"青陽", "tier":3, "color":HIC, "attr":0, "id":"shining" ]);
    // ── 屬性材質 (tier 3，docs 明列屬性) ──
    case P_TAIYANG:     // [docs L113/117] 太陽=根骨(con)+2 (enhanced.c L122-125 同)
        return ([ "zh":"太陽", "tier":3, "color":HIY, "attr":([ "con":2 ]), "id":"sun" ]);
    case P_MALIK:       // [docs L113] 巫首=靈性(spi)+2 (種族專屬裝亦同)
        return ([ "zh":"巫首", "tier":3, "color":HIB, "attr":([ "spi":2 ]), "id":"malik" ]);
    case P_JIAOJAO:     // [docs L115/118] 焦僥=機敏(dex)+3 (enhanced.c L150-153 dex+3)
        return ([ "zh":"焦僥", "tier":3, "color":HIG, "attr":([ "dex":3 ]), "id":"jiaojao" ]);
    case P_WUCHANG:     // [預設] 無腸：種族材質，悟性向 (enhanced.c 無腸=int+3/con-1)；取 int+2 純加成
        return ([ "zh":"無腸", "tier":3, "color":CYN, "attr":([ "int":2 ]), "id":"woochanian" ]);
    // ── 高階 (tier 4) ──
    case P_ZIYANG:      // [docs L69：紫陽，赤血<紫陽 為高階界] 鏡 enhanced.c 紫陽=cps+2
        return ([ "zh":"紫陽", "tier":4, "color":HIM, "attr":0, "id":"dawn" ]);
    case P_JINXIANG:    // [預設] 金鑲：貴金屬鑲嵌，高階 (enhanced.c 金鑲=con+1/int+1)
        return ([ "zh":"金鑲", "tier":4, "color":HIY, "attr":0, "id":"golden" ]);
    case P_XINGTIAN:    // [預設] 形天 (刑天)：戰神材質，高階傷害 (種族裝『形天之怒』)
        return ([ "zh":"形天", "tier":4, "color":HIR, "attr":0, "id":"headless" ]);
    case P_XIULUO:      // [預設] 修羅：阿修羅材質，高階 (種族裝『修羅之面』)
        return ([ "zh":"修羅", "tier":4, "color":HIK, "attr":0, "id":"ashura" ]);
    // ── 頂階 (tier 5，docs L70「頂階材質」) ──
    case P_FENGHUANG:   // [docs L69 列尾頂階群] 鳳凰：火屬頂階
        return ([ "zh":"鳳凰", "tier":5, "color":HIR, "attr":0, "id":"phoenix" ]);
    case P_TIANLONG:    // [docs L71 明舉「天龍刀」為天龍系列] 天龍：頂階
        return ([ "zh":"天龍", "tier":5, "color":HIW, "attr":0, "id":"wyvern" ]);
    case P_ZESHOU:      // [docs L69 列尾頂階群] 澤獸：頂階
        return ([ "zh":"澤獸", "tier":5, "color":HIG, "attr":0, "id":"beast" ]);
    case P_DAPENG:      // [docs L69 列尾頂階群] 大鵬：頂階
        return ([ "zh":"大鵬", "tier":5, "color":HIC, "attr":0, "id":"roc" ]);
    default:
        return 0;
    }
}

// ── 各取值小工具 (集中讀 prefix_data，避免散落)。──
private int
tier_of(string p)
{
    mapping d = prefix_data(p);
    if( !mapp(d) ) return 0;
    return d["tier"];
}

private string
color_of(string p)
{
    mapping d = prefix_data(p);
    if( !mapp(d) ) return NOR;
    return d["color"];
}

private mapping
attr_of(string p)
{
    mapping d = prefix_data(p);
    if( !mapp(d) || !mapp(d["attr"]) ) return 0;
    return d["attr"];
}

// ── (1) query_prefixes()：回 21 個前綴 id 清單 (副本，防外部竄改內部陣列)。──
string *
query_prefixes()
{
    return prefix_order + ({ });
}

// ── (2) prefix_zh(p)：回材質中文名 (查無回空字串)。──
string
prefix_zh(string p)
{
    mapping d = prefix_data(p);
    if( !mapp(d) ) return "";
    return d["zh"];
}

// ── primary_skill(weapon)：回武器主手 skill (wield_as 的第一個非 secondhand/twohanded 者)。──
// wield_as 可能是字串或陣列 (見 obj/area/obj/*.c)。優先取「基礎主手」skill 作 setup/讀值基準。
private string
primary_skill(object weapon)
{
    mixed wa;
    string s;

    wa = weapon->query("wield_as");
    if( stringp(wa) ) return wa;
    if( !arrayp(wa) || !sizeof(wa) ) return 0;

    // 優先回不含 "secondhand"/"twohanded" 的基礎 skill。
    foreach( s in wa )
        if( stringp(s)
        &&  strsrch(s, "secondhand") == -1
        &&  strsrch(s, "twohanded") == -1 )
            return s;
    return wa[0];
}

// ── weapon_type_of(weapon)：回武器「基礎類型」字串 (sword/blade/axe/dagger/needle/
//    pike/staff/whip/blunt)，用以選 setup_<type> 與上限。由主手 skill 推得。──
private string
weapon_type_of(object weapon)
{
    string s = primary_skill(weapon);

    if( !stringp(s) ) return 0;
    // 主手 skill 名即基礎類型 (sword/blade/...)。secondhand/twohanded 前綴已於
    // primary_skill 過濾；保險再剝一次。
    if( strsrch(s, "twohanded ") == 0 ) s = s[10..];
    if( strsrch(s, "secondhand ") == 0 ) s = s[11..];
    return s;
}

// ── type_cap_mult/type_cap_force：回該武器類的乘數/力修上限 (docs L82-99)。──
private int
type_cap_mult(string type)
{
    switch( type ) {
    case "sword":   return CAP_SWORD_MULT;
    case "blade":   return CAP_BLADE_MULT;
    case "axe":     return CAP_AXE_MULT;
    case "dagger":  return CAP_DAGGER_MULT;
    case "needle":  return CAP_DAGGER_MULT;
    case "blunt":   return CAP_BLUNT_MULT;
    case "pike":    return CAP_PIKE_MULT;
    case "staff":   return CAP_STAFF_MULT;
    case "whip":    return CAP_WHIP_MULT;
    default:        return 3;   // 保守預設。
    }
}

private int
type_cap_force(string type)
{
    switch( type ) {
    case "sword":   return CAP_SWORD_FORCE;
    case "blade":   return CAP_BLADE_FORCE;
    case "axe":     return CAP_AXE_FORCE;
    case "dagger":  return CAP_DAGGER_FORCE;
    case "needle":  return CAP_DAGGER_FORCE;
    case "blunt":   return CAP_BLUNT_FORCE;
    case "pike":    return CAP_PIKE_FORCE;
    case "staff":   return CAP_STAFF_FORCE;
    case "whip":    return CAP_WHIP_FORCE;
    default:        return 100;
    }
}

// ── type_noun(weapon, type)：回改名要用的中文兵器名 (劍/刀/斧/匕/針/槍/棍/鞭)。──
// 優先取武器原中文名末字 (如「長劍」→「劍」)；無法取得時退而用 type→中文 對照表。
private string
type_noun(object weapon, string type)
{
    string nm = weapon->query("name");

    // 武器原名末一個中文字通常即兵器類名 (長劍→劍、馬鞭→鞭、長槍→槍)。
    // 中文字在 UTF-8 為 3 bytes；取末 3 bytes 作末字。
    if( stringp(nm) && strlen(nm) >= 3 ) {
        string last = nm[<3..];
        // 過濾掉可能殘留的 ANSI 重置碼以外的單純中文末字即可。
        if( last != "" ) return last;
    }

    switch( type ) {
    case "sword":   return "劍";
    case "blade":   return "刀";
    case "axe":     return "斧";
    case "dagger":  return "匕";
    case "needle":  return "針";
    case "pike":    return "槍";
    case "staff":   return "棍";
    case "whip":    return "鞭";
    case "blunt":   return "鞭";   // 鐵鞭類 (鈍器) 中文亦作鞭。
    default:        return "兵";
    }
}

private int
clamp(int v, int lo, int hi)
{
    if( v < lo ) return lo;
    if( v > hi ) return hi;
    return v;
}

// ── current_params(weapon, skill)：回該 skill 之 (x,y,z,r) 現值 (mapping)。──
// 讀 query("damage/"+skill) 之 class damage_parameter (feature/equip.c L238)。查無回 0。
private mapping
current_params(object weapon, string skill)
{
    class damage_parameter dam;

    if( !stringp(skill) ) return 0;
    dam = weapon->query("damage/" + skill);
    if( !classp(dam) ) return 0;
    return ([
        "x": dam->multipler,
        "y": dam->range,
        "z": dam->bonus,
        "r": dam->roll,
    ]);
}

// ── (3) apply_prefix(weapon, prefix)：把材質前綴套到既有武器物件。回 1 成功、0 失敗。──
// 步驟：
//   a. 驗 weapon/prefix 合法、取得武器類型 type 與主手 skill。
//   b. 讀現有 (x,y,z,r) 作基準，依 tier 縮放乘數 x 與力修 z，clamp 到 docs 武器類上限
//      與該武器 setup_<type> 自身合法上限之較小者；傷害區間 y 略增 (clamp 到 setup 範圍)。
//   c. 調武器自身 setup_<type>(x,y,z,r) 重設主/副/雙手三式 (比例由 setup_ 內部維持)。
//   d. 改名為「<材質中文><原兵器名>」、id 加材質英文前綴。
//   e. 若該材質帶屬性，對每個 wield_as skill set("apply_weapon/"+skill, attr)。
//   f. set("prefix", prefix) 記之，供日後查詢/避免重複套。
int
apply_prefix(object weapon, string prefix)
{
    mapping d, params;
    string type, skill;
    int tier, x, y, z, r;
    int cap_x, cap_z, set_x_max, set_y_max, set_z_max;

    if( !objectp(weapon) ) return 0;
    d = prefix_data(prefix);
    if( !mapp(d) ) return 0;

    type = weapon_type_of(weapon);
    skill = primary_skill(weapon);
    if( !stringp(type) || !stringp(skill) ) return 0;

    params = current_params(weapon, skill);
    if( !mapp(params) ) return 0;

    tier = d["tier"];

    // ── b. 依 tier 縮放並 clamp。──
    // 乘數 x：基準 + (tier-1) 提升，但最多 +tier 階且不逾武器類上限。
    // 力修 z：基準 * (100 + tier*15)% 概略提升 (頂階 +75%)，clamp 到上限。
    x = params["x"] + (tier - 1);
    z = params["z"] * (100 + tier * 15) / 100;
    y = params["y"] + (tier - 1);   // 傷害區間隨階略增。
    r = params["r"];

    // docs 武器類上限。
    cap_x = type_cap_mult(type);
    cap_z = type_cap_force(type);

    // 各 setup_<type> 自身的合法上限 (feature/weapon/*.c 的 error 邊界)，避免觸發 error。
    // 取 docs 上限與 setup 上限之較小者作最終 clamp 天花板。
    switch( type ) {
    case "sword":   set_x_max = 5;  set_y_max = 20; set_z_max = 150; break;
    case "blade":   set_x_max = 4;  set_y_max = 25; set_z_max = 200; break;
    case "axe":     set_x_max = 5;  set_y_max = 25; set_z_max = 200; break;
    case "dagger":  set_x_max = 3;  set_y_max = 20; set_z_max = 100; break;
    case "needle":  set_x_max = 3;  set_y_max = 18; set_z_max = 100; break;
    case "blunt":   set_x_max = 6;  set_y_max = 15; set_z_max = 300; break;
    case "pike":    set_x_max = 5;  set_y_max = 20; set_z_max = 100; break;
    case "staff":   set_x_max = 3;  set_y_max = 25; set_z_max = 250; break;
    case "whip":    set_x_max = 6;  set_y_max = 15; set_z_max = 100; break;
    default:        set_x_max = 3;  set_y_max = 15; set_z_max = 100; break;
    }

    if( cap_x > set_x_max ) cap_x = set_x_max;
    if( cap_z > set_z_max ) cap_z = set_z_max;

    x = clamp(x, 1, cap_x);
    y = clamp(y, 1, set_y_max);
    z = clamp(z, 1, cap_z);
    // roll r 之合法下界為 -x；保持原值但不低於 -x。
    if( r < -x ) r = -x;

    // ── c. 調武器自身 setup_<type> 重設三式。──
    if( !function_exists("setup_" + type, weapon) ) return 0;
    call_other(weapon, "setup_" + type, x, y, z, r);

    // 改名 / 改 id / 屬性加成移至 prefix_rename (分攤區域變數，避免 too-many-locals)。
    return prefix_rename(weapon, d, prefix, type);
}

// ── prefix_rename：套前綴後的改名 / 改 id / 屬性加成。由 apply_prefix 呼叫、獨立成函式以
//   分攤區域變數 (避免 apply_prefix 一函式內變數過多)。d=prefix_data(prefix)、type=武器類。回 1。
private int
prefix_rename(object weapon, mapping d, string prefix, string type)
{
    mapping attr;
    string newname, oldid, base_name;
    string *base_ids, *new_ids;
    mixed stored, wa, ws;

    // ── d. 改名 / 改 id。──
    // 名稱 = <材質色><材質中文><原武器全名> (例：太陽 + 長劍 = 太陽長劍)。
    // 「原武器全名」取未加前綴前的乾淨基準名 base_name：首次套用時把當下 name 存進
    //  set("base_name",..)，日後重複套用一律以 base_name 重建，避免材質名層層堆疊。
    stored = weapon->query("base_name");
    if( stringp(stored) )
        base_name = stored;
    else {
        stored = weapon->query("name");
        base_name = stringp(stored) ? stored : type_noun(weapon, type);
        weapon->set("base_name", base_name);
    }
    newname = d["color"] + d["zh"] + base_name + NOR;

    // id 清單 = 原武器各 id token + 材質英文 id (set_name 會更新 my_id，使玩家可用材質字
    //  瞄準武器──id() 讀 my_id 而非 query("id")，見 feature/name.c L32)。同步把 base id
    //  token 存於 base_ids，重複套用時以 base_ids 重建，避免 id 堆疊。
    stored = weapon->query("base_ids");
    if( arrayp(stored) )
        base_ids = stored;
    else {
        stored = weapon->parse_command_id_list();
        if( arrayp(stored) )
            base_ids = stored;
        else {
            oldid = weapon->query("id");
            base_ids = stringp(oldid) ? ({ oldid }) : ({ type });
        }
        weapon->set("base_ids", base_ids);
    }
    new_ids = base_ids + ({ d["id"], d["id"] + " " + (sizeof(base_ids) ? base_ids[0] : type) });
    weapon->set_name(newname, new_ids);

    // ── e. 屬性加成 (若有)。對每個可揮舞 skill 掛 apply_weapon。──
    attr = attr_of(prefix);
    if( mapp(attr) && sizeof(attr) ) {
        wa = weapon->query("wield_as");
        if( stringp(wa) )
            weapon->set("apply_weapon/" + wa, copy(attr));
        else if( arrayp(wa) )
            foreach( ws in wa )
                if( stringp(ws) )
                    weapon->set("apply_weapon/" + ws, copy(attr));
    }

    // ── f. 記錄前綴。──
    weapon->set("prefix", prefix);

    return 1;
}

// ── (4) make_prefixed_weapon(base_path, prefix)：clone 基礎武器後套前綴，回該武器。──
// base_path 為基礎武器藍本路徑 (如 STOCK_WEAPON("sword") = /obj/area/obj/sword，或直接給
// /obj/area/obj/longsword)。clone 失敗或套用失敗回 0。
object
make_prefixed_weapon(string base_path, string prefix)
{
    object weapon;

    if( !stringp(base_path) || !mapp(prefix_data(prefix)) ) return 0;

    seteuid(getuid());
    weapon = new(base_path);
    if( !objectp(weapon) ) return 0;

    if( !apply_prefix(weapon, prefix) ) {
        // 套用失敗則銷毀剛 clone 的物件，避免遺留半成品。
        destruct(weapon);
        return 0;
    }
    return weapon;
}

// ── tier_of_level(level)：依怪物/掉落等級換算合理材質傷害階 1~5。──
// 低階怪 (lv<10) → tier1、<20→2、<35→3、<50→4、>=50→5。供 random_prefixed_weapon 選階。
private int
tier_of_level(int level)
{
    if( level < 10 ) return 1;
    if( level < 20 ) return 2;
    if( level < 35 ) return 3;
    if( level < 50 ) return 4;
    return 5;
}

// ── 基礎武器藍本清單 (obj/area/obj/ 下各武器類藍本，供隨機選底)。──
// 各武器類至少一個代表藍本 (axe/blade/sword/dagger/pike/blunt/whip)。以字面路徑列出
// (等同 STOCK_WEAPON(x) = "/obj/area/obj/"+x，見 include/globals.h L52)，避免於全域初始式
// 用巨集字串相接而觸發部分 driver 的「初始式須常量」限制 (鏡 combatd.c 之字面字串陣列)。
// 註：staff 在 obj/area/obj/ 無獨立藍本，以 rod(blunt)/pike 等現有藍本涵蓋；此處只列實檔。
string *base_weapons = ({
    "/obj/area/obj/longsword",      // sword 劍
    "/obj/area/obj/shortsword",     // sword 短劍
    "/obj/area/obj/blade",          // blade 刀
    "/obj/area/obj/curved_blade",   // blade 彎刀
    "/obj/area/obj/axe",            // axe 斧
    "/obj/area/obj/broadaxe",       // axe 板斧
    "/obj/area/obj/dagger",         // dagger 匕
    "/obj/area/obj/knife",          // dagger 小刀
    "/obj/area/obj/pike",           // pike 槍
    "/obj/area/obj/rod",            // blunt 鐵鞭
    "/obj/area/obj/whip",           // whip 鞭
});

// ── 屬性前綴 (升級加精氣神者：太陽con/焦僥dex/巫首spi/無腸int) 稀有度。──
// 這些前綴永久拉高升級時的精氣神成長 (query_attr→各 class advance_stat)，價值遠勝純傷害材質，
// 故「帶前綴的武器」中只有 ATTR_DROP_PCT% 會落在屬性前綴池，其餘一律純傷害材質——避免「升級
// 屬性頂裝」太易取得 (使用者調校項；docs 未給確切掉率，取合理可驗預設，集中此 #define 便調整)。
#define ATTR_DROP_PCT   6

// ── choose_prefix(level)：依等級選一個材質前綴 (屬性前綴稀有化)。獨立成函式以便除錯驗分佈。──
//   純傷害材質：取 tier 落 [want_tier-1, want_tier] 的窗 (傷害貼合等級)。
//   屬性材質  ：tier <= want_tier 即「等級夠格」(屬性與傷害階無關，不綁傷害窗，使高階怪亦能偶掉)；
//               且僅 ATTR_DROP_PCT% 機率落此池。低階 (want_tier<3，等級<20) 無屬性前綴可選。
string
choose_prefix(int level)
{
    int want_tier, t;
    string p;
    string *plain_pool, *attr_pool, *pool;
    mapping a;

    want_tier = tier_of_level(level);

    plain_pool = ({ });
    attr_pool = ({ });
    foreach( p in prefix_order ) {
        t = tier_of(p);
        a = attr_of(p);
        if( mapp(a) ) {
            // 屬性前綴：等級夠格 (tier <= want_tier) 即入屬性池。
            if( t <= want_tier ) attr_pool += ({ p });
        } else {
            // 純傷害前綴：取貼合等級的傷害窗 [want_tier-1, want_tier]。
            if( t == want_tier || t == want_tier - 1 ) plain_pool += ({ p });
        }
    }

    // 屬性前綴稀有：僅小機率落屬性池，且該等級須有屬性前綴可選。
    if( sizeof(attr_pool) && random(100) < ATTR_DROP_PCT )
        pool = attr_pool;
    else
        pool = plain_pool;

    // 防呆：選中的池空則退另一池，再退全表。
    if( !sizeof(pool) ) pool = sizeof(plain_pool) ? plain_pool : attr_pool;
    if( !sizeof(pool) ) pool = prefix_order + ({ });

    return pool[random(sizeof(pool))];
}

// ── (5) random_prefixed_weapon(level)：依 level 選前綴 (屬性前綴稀有) + 隨機基礎武器，產一把。──
//   回該武器 (失敗回 0)。
object
random_prefixed_weapon(int level)
{
    string p, base;

    p = choose_prefix(level);
    base = base_weapons[random(sizeof(base_weapons))];

    return make_prefixed_weapon(base, p);
}

// ── 除錯：跑 trials 次 choose_prefix(level)，回一行字串摘要 (屬性前綴占比 + 各屬性前綴次數)。──
//   屬性前綴 (太陽/焦僥/巫首/無腸) 合計應約佔 ATTR_DROP_PCT%。唯讀、無副作用。
string
debug_prefix_distribution(int level, int trials)
{
    mapping m = ([ ]);
    int i, attr_n = 0;
    string p, out;

    if( trials < 1 ) trials = 100;
    if( trials > 500 ) trials = 500;    // 防 eval-cost 超限靜默中止 (每次掃 21 前綴×2 switch；≳1000 會超限)。
    for( i = 0; i < trials; i++ ) {
        p = choose_prefix(level);
        m[p] = (undefinedp(m[p]) ? 0 : m[p]) + 1;
        if( mapp(attr_of(p)) ) attr_n++;
    }

    out = sprintf("lv%d: 屬性前綴 %d/%d (%d%%)；", level, attr_n, trials,
        trials ? attr_n * 100 / trials : 0);
    foreach( p in prefix_order )
        if( mapp(attr_of(p)) && !undefinedp(m[p]) )
            out += prefix_zh(p) + "=" + m[p] + " ";
    return out;
}

// ── 唯讀輔助：回某前綴的人話效果描述 (供指令/除錯顯示)。──
// 例：太陽 → "傷害階 3／根骨 +2"。
string
describe_prefix(string p)
{
    mapping d, attr;
    string desc, k, label;
    int v;

    d = prefix_data(p);
    if( !mapp(d) ) return "無此材質";

    desc = sprintf("%s%s" NOR "：傷害階 %d", d["color"], d["zh"], d["tier"]);

    attr = d["attr"];
    if( mapp(attr) && sizeof(attr) )
        foreach( k, v in attr ) {
            switch( k ) {
            case "con": label = "根骨"; break;
            case "dex": label = "機敏"; break;
            case "spi": label = "靈性"; break;
            case "int": label = "悟性"; break;
            case "str": label = "膂力"; break;
            case "cor": label = "膽識"; break;
            case "wis": label = "慧根"; break;
            default:    label = k;      break;
            }
            desc += sprintf("／%s %+d", label, v);
        }
    else
        desc += "／純傷害";

    return desc;
}

// vim: set ts=4 sw=4 syntax=lpc
