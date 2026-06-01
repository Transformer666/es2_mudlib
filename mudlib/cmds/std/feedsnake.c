// feedsnake.c -- 雨師妾種族主動技能「餵蛇」
//
// 雨師妾 (rainnar) 為四元素之屬，能以水氣豢養小蛇盤繞己身，最多五條，作為
// 護身的裝備familiar。見 docs/01-世界觀與劇情/03-種族設定.md：雨師妾 主動
// 「最多可餵養五條小蛇作為裝備」。
//
// 本指令放在 /cmds/std/ ，用 query_race() 鎖死成只有雨師妾能用，其他種族
// 得到「你不會這種本事」（同 spitfire.c / maul.c 的做法──race daemon 的
// setup() 在 daemon context 跑，無法替玩家 add_action，見 content-race-active.md）。
//
// 機制摘要（裝備familiar型，比照 obj/clan_symbol.c 的隨身物件 + wardance.c 的
// add_temp 暫時加成）：
//   * 鎖定：query_race()=="rainnar"，否則 notify_fail。
//   * 每次餵蛇 new("/obj/race/rainnar_snake") 一條小蛇，move 進玩家身上，
//     並呼叫 snake->attach_to(me) 對玩家 add_temp("apply/armor"+"apply/defense")
//     施加護身加成（每條 armor+3、defense+2，五條疊加 armor+15、defense+10）。
//   * 上限：每次清點玩家身上現有小蛇，已滿五條則拒絕餵第六條（杜絕無限疊加）。
//   * 冷卻：set_temp("feedsnake_cooldown", time()+N) + time() 判定（同 spitfire/maul）。
//   * 硬直：start_busy（凝水化蛇需要片刻）。
//   小蛇本身 no_steal/no_sell/no_drop/value 0，失去（死亡/釋放）即減回加成，
//   無刷資源漏洞。

#include <ansi.h>

inherit F_CLEAN_UP;

// 平衡參數，集中在此方便調整。
#define FEEDSNAKE_MAX        5      // 最多可同時豢養的小蛇數
#define FEEDSNAKE_COOLDOWN   20     // 兩次餵蛇之間的冷卻秒數
#define FEEDSNAKE_BUSY       2      // 餵蛇後的硬直 (heart beat 數)
#define SNAKE_OB             "/obj/race/rainnar_snake"

void do_feedsnake(object me);

private void create() { seteuid(getuid()); }

// 清點玩家身上現有的小蛇數（以物件檔名認定，避免被改名物冒充）。
int count_snakes(object me)
{
    object ob;
    int n;

    n = 0;
    foreach(ob in all_inventory(me)) {
        if( !ob ) continue;
        if( base_name(ob) == SNAKE_OB ) n++;
    }
    return n;
}

int main(object me, string arg)
{
    int left;

    // 只有雨師妾能豢養小蛇，其他種族不會這種本事。
    if( me->query_race() != "rainnar" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 上限：清點現有小蛇，已滿五條便駕馭不住第六條。
    if( count_snakes(me) >= FEEDSNAKE_MAX )
        return notify_fail("你已餵養了五條小蛇，再多便駕馭不住了。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("feedsnake_cooldown") - time();
    if( left > 0 )
        return notify_fail("你體內水氣方才耗去，還得再凝聚 " + left + " 秒才能再餵一條。\n");

    do_feedsnake(me);
    return 1;
}

void do_feedsnake(object me)
{
    object snake;

    // 再次確認狀態（do_feedsnake 與 main 之間若有變化）。
    if( !me ) return;
    if( count_snakes(me) >= FEEDSNAKE_MAX ) {
        tell_object(me, "你已餵養了五條小蛇，再多便駕馭不住了。\n");
        return;
    }

    // 先設冷卻、進入硬直（無論成不成都只判一次代價）。
    me->set_temp("feedsnake_cooldown", time() + FEEDSNAKE_COOLDOWN);
    me->start_busy(FEEDSNAKE_BUSY);

    // 凝水化蛇。
    snake = new(SNAKE_OB);
    if( !objectp(snake) ) {
        tell_object(me, "你凝聚水氣，卻不知怎地未能化出小蛇來。\n");
        return;
    }

    // 移入玩家身上；失敗則銷毀以免殘留。
    if( !snake->move(me) ) {
        tell_object(me, "你身上已盤滿了小蛇，再容不下了。\n");
        destruct(snake);
        return;
    }

    // 施加護身加成（apply/armor + apply/defense，由小蛇物件內部 add_temp）。
    snake->attach_to(me);

    message_vision(CYN "\n$N口中念念有詞，掌心凝出一團翠青水氣，化作一條"
        + HIC "小蛇" CYN "，溫馴地盤上$N的身子。\n" NOR, me);
    tell_object(me, CYN "小蛇吞吐之間，一層護身的水氣將你圍裹起來。\n" NOR);
}

int help(object me)
{
    write(@HELP
指令格式：feedsnake   (餵蛇／馴蛇)

雨師妾一族為四元素之屬，能以掌心水氣豢養翠青小蛇，溫馴地盤繞己身作為護身的
靈寵。每餵一條小蛇，便為你添一層護身的水氣（提升armor與防禦）。

你最多只能同時豢養五條小蛇，再多便駕馭不住；每次餵蛇都需片刻凝聚水氣，不能
連續施放。小蛇不可偷、不可賣、不可丟棄；若主人陣亡或將小蛇放生，護身的水氣
便會隨之散去。

只有雨師妾種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
