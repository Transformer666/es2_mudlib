// 全服唯一掉落 (server-wide unique loot) daemon。
//
// 用途：承載「全服只能存在一件」的稀有掉落物。當某怪/某容器要掉一件唯一物時，
// 改呼叫 LOOT_D->unique_drop(藍本路徑, 容器)，由本 daemon 先盤點全世界該藍本現存
// 的 clone 數；若已有任何一件 (>=1) 就不再掉 (回 0)，否則 new 一件並放入容器。如此
// 同一件稀有物在整個遊戲世界中任何時刻至多只有一件存在。
//
// 機制對齊 (皆已驗於 mudlib 現有程式)：
//   * 盤點全世界實例數：sizeof(filter_array(children(path), (: clonep :)))。
//     children(path) 列出該藍本「載入過的所有實例」(含藍本本身)；filter_array 以
//     clonep 過濾，只留 clone (排除藍本)，即得「世界現存 clone 數」。此計數法完全鏡
//     feature/unique.c::violate_unique (L14：filter_array(children(base_name(...)),
//     (: clonep :)))──該處正是 ES2 判定「唯一性是否被破壞」的權威寫法。
//   * 安全產生 clone：seteuid(getuid()) 後 new(path)。鏡 feature/unique.c::
//     create_replica (L25-28：seteuid(getuid()); new(replica)) 與 cmds/std/fish.c
//     (L46/99：create 內 seteuid(getuid()); fish = new(FISH_OBJ))。daemon 自身權限
//     由 create() 一次 seteuid(getuid())；產物前再 seteuid 一次確保 euid 正確
//     (daemon 可能被各種 euid 的物件呼叫)。
//   * 放入容器並備援：if( !ob->move(container) ) ob->move(environment(container))。
//     move() 成功回 1、失敗回 0 (feature/move.c L77-90)，故 !move 為「放不進」。
//     完全鏡 cmds/std/fish.c L99-100：if( !fish->move(me) ) fish->move(environment(me))
//     ──容器若裝不下 (重量/容量限制)，退而放到容器所在環境 (通常是房間/怪物的環境)。
//
// runtime 鐵則：本檔為純工具 daemon，不涉 ::die()/destruct() (#10)、不 replace_program
// (#11)、不 add_action (daemon context 無 this_player 綁定)。inherit F_CLEAN_UP 使閒置時
// 自動回收 (鏡 daemon/misc/title.c L47)。

#include <ansi.h>

inherit F_CLEAN_UP;

// 前置宣告：world_count 於 unique_drop 之前被引用 (此處定義在前、引用在後本不需要，
// 但比照 title.c L167-176 之紀律先行宣告對外介面，便於日後在檔頭新增依賴而不致漏宣告)。
int world_count(string path);
object unique_drop(string path, object container);

private void
create()
{
    seteuid(getuid());
}

// ── world_count(path)：回世界現存「以 path 為藍本」的 clone 數。──
// path 須為藍本路徑字串 (如 "/obj/example/relic")。filter_array 以 clonep 排除藍本本身，
// 故回傳值即「目前在世的複製件數」。藍本未載入過時 children 回空陣列，自然得 0。
int
world_count(string path)
{
    if( !stringp(path) ) return 0;
    return sizeof(filter_array(children(path), (: clonep :)));
}

// ── unique_drop(path, container)：全服唯一掉落。──
// 若世界已存在該藍本任一件 (world_count >= 1) 則回 0 (不再掉，維持全服唯一)；
// 否則 new 一件放入 container (放不進則退放到 container 的環境)，回新物件。
// 守衛：path 須為字串、container 須為物件。
object
unique_drop(string path, object container)
{
    object ob;

    if( !stringp(path) || !objectp(container) ) return 0;

    // 全服已有一件 (含其他容器/房間/玩家身上者)，不再掉落。
    if( world_count(path) >= 1 ) return 0;

    seteuid(getuid());
    ob = new(path);
    if( !ob ) return 0;

    // 放入容器；若容器裝不下 (重量/容量限制)，退而放到容器所在環境。
    if( !ob->move(container) )
        ob->move(environment(container));

    return ob;
}

// vim: set ts=4 sw=4 syntax=lpc
