// rainnar_snake.c -- 雨師妾豢養的「小蛇」靈寵（裝備型隨身familiar）
//
// 雨師妾 (rainnar) 為四元素之屬，能以水氣豢養小蛇盤繞己身，最多五條，作為
// 護身的裝備familiar。見 docs/01-世界觀與劇情/03-種族設定.md：雨師妾 主動
// 「最多可餵養五條小蛇作為裝備」。
//
// 設計取捨（已查證）──為何「不走護具slot」而走「隨身familiar + 直接 buff」：
//   * 護具slot（feature/equip.c 的 wear/wield）受 std/race/humanoid.c:225 的
//     valid_wear 限制──slot 名必須在固定的 wear_type 九格之內（armor / cloth
//     / feet_eq / ... / waist_eq），小蛇沒有對應格；且「每格只能一件」，五條
//     小蛇無法共用同一格。
//   * 故比照 obj/clan_symbol.c 的「隨身物件」做法：小蛇 new() 後 move 進玩家，
//     由 feedsnake 指令在豢養時直接對玩家 add_temp("apply/<key>", N) 加成，
//     失去時 add_temp(key, -N) 減回（不可 delete_temp，否則連雨師妾被動
//     apply/defense+20 一併抹掉──同 wardance.c 的教訓，見 content-race-active.md）。
//
// 加成鍵（皆為「戰鬥確實會讀」的已驗證鍵，避免臆造）：
//   * apply/armor   ── resist_damage() 直接讀此鍵抵減傷害（feature/char/combat.c:272）。
//   * apply/defense ── 防禦能力 query_ability("defense") 直接加此鍵（combat.c:81，
//                      wiz analyze 亦顯示）。雨師妾被動本就用 apply/defense，主題相符。
//   四元素／水氣只入敘述flavor，不另開 apply/armor_vs_water 之類未證實的per-element鍵。
//
// 防漏洞：no_steal / no_sell / no_drop / value 0──小蛇不可偷不可賣不可丟棄
// （丟棄會脫離掌控而失去加成），杜絕無限刷資源；數量上限由 feedsnake 指令把關。

#include <ansi.h>

inherit ITEM;

// 每條小蛇給予的加成（壓低，五條疊加仍在合理範圍：armor+15、defense+10）。
#define SNAKE_ARMOR     3       // 每條小蛇提供的 apply/armor
#define SNAKE_DEFENSE   2       // 每條小蛇提供的 apply/defense

// 加成是否已施加在目前 owner 身上（避免重複加 / 重複減）。
int applied;

void create()
{
    // 英文 id 供 i / look / drop / release snake 等指令辨識；中文為顯示名。
    set_name(HIC "小蛇" NOR, ({ "snake", "little snake", "xiaoshe" }));
    set_weight(200);

    if( !clonep() ) {
        set("unit", "條");
        set("long",
            "一條翠青色的小蛇，是雨師妾以四元素水氣豢養而成的靈寵，溫馴地\n"
            "盤繞在主人身上，吞吐之間隱隱透出一層護身的水氣。\n");
        set("value", 0);        // 不值錢
        set("no_steal", 1);     // 不可被偷
        set("no_sell", 1);      // 不可販賣（杜絕刷資源）
        set("no_drop", 1);      // 不可隨手丟棄
        set("no_get", 1);       // 別人撿不走
    }

    applied = 0;
    setup();
}

// attach_to(owner)
//   由 feedsnake 指令於豢養時呼叫：把加成施加到 owner 身上並記旗標。
//   只在尚未施加時才加，避免重複疊加同一條的加成。
void attach_to(object owner)
{
    if( applied ) return;
    if( !objectp(owner) || !owner->is_character() ) return;

    owner->add_temp("apply/armor", SNAKE_ARMOR);
    owner->add_temp("apply/defense", SNAKE_DEFENSE);
    applied = 1;
}

// detach_from(owner)
//   失去 / 釋放 / 主人死亡時呼叫：把先前加的加成減回（add_temp 負值，
//   不可 delete_temp，以免抹掉雨師妾被動 apply/defense）。
void detach_from(object owner)
{
    if( !applied ) return;
    if( objectp(owner) && owner->is_character() ) {
        owner->add_temp("apply/armor", -SNAKE_ARMOR);
        owner->add_temp("apply/defense", -SNAKE_DEFENSE);
    }
    applied = 0;
}

// release()
//   主人主動放生小蛇：先把加成自 environment()（即主人）減回，再自毀。
int release()
{
    object owner;

    owner = environment();
    detach_from(owner);
    if( objectp(owner) )
        tell_object(owner, CYN "你低聲一喚，將一條小蛇放回了水氣之中，牠化作一縷水霧散去。\n" NOR);
    destruct(this_object());
    return 1;
}

// owner_is_killed(killer)
//   主人陣亡時（比照 obj/clan_symbol.c 的同名 hook）：減回加成並自毀，
//   小蛇隨主人一同散去，不會殘留加成。
void owner_is_killed(object killer)
{
    detach_from(environment());
    destruct(this_object());
}

// vim: set ts=4 sw=4 syntax=lpc
