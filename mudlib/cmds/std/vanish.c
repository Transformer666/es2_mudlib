// vanish.c -- 焦僥種族主動技能「遁」(逃遁)
//
// 焦僥 (jiaojao) 身形短小、生性機警（被動：守勢+15、警覺+100，另有種族裝
// 焦僥靴）。其族最擅脫身：一遇兇險便能瞬間脫離纏鬥、竄入鄰處藏匿。
// 見 docs/01-世界觀與劇情/03-種族設定.md：焦僥 主動「逃逸戰鬥並原地躲藏」。
//
// 本指令放在 /cmds/std/ ，用 query_race() 鎖死成只有焦僥能用，其他種族
// 得到「你不會這種本事」（同 spitfire.c 的做法──race daemon 的 setup() 在
// daemon context 跑，無法替玩家 add_action，見 content-race-active.md）。
//
// 機制摘要（脫戰 + 躲藏，全部比照引擎既有機制，未自創 efun）：
//   * 鎖定：query_race()=="jiaojao"，否則 notify_fail。
//   * 脫戰：呼叫 me->remove_all_killer()（見 feature/char/attack.c:245）──
//     這是引擎裡「徹底脫離一切戰鬥」的方法：先清空自己的 killer mapping，
//     再請所有敵人 remove_killer 忘掉自己，最後 enemy=({})。
//     （註：remove_all_enemy() 對「正在 kill 自己」的敵人無效，因為 remove_enemy
//      遇 is_killing 會回 0，見 attack.c:201；故脫戰要用 remove_all_killer。）
//   * 逃竄：脫戰後比照 cmds/std/go.c 的 "escape" 流程──讀 env->query("exits")
//     (mapping)，keys() 取方向，隨機挑一個，env->query("exits/"+dir) 取目的地
//     (string 路徑則 load_object)，再 me->move(obj)（見 feature/move.c:51）。
//     刻意不使用 force_me("go escape")：force_me 需 previous_object 為 ROOT_UID
//     (見 command.c:90)，本指令 euid 不符會 error。
//   * 躲藏：移動後 set_temp("pending/hidden", N)──這是引擎的隱匿屬性
//     （sneak 成功時即設此值，kill/backstab 則設 0 表示現身，見 sneak.c:125 /
//      kill.c:44 / backstab.c:87）。藏匿值越高越難被察覺（對上敵方 awarness）。
//   * 無路 / 無敵：見下方各 notify_fail。
//   * 冷卻：set_temp("vanish_cooldown", time()+N) + time() 判定。

#include <ansi.h>

inherit F_CLEAN_UP;

// 冷卻秒數、藏匿基值，集中在此方便調整平衡。
#define VANISH_COOLDOWN     30      // 兩次遁走之間的冷卻秒數
#define VANISH_HIDE_BASE    10      // 躲藏基值（再加少許隨機與潛行技巧）

void do_vanish(object me);

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int left;
    mapping exits;

    // 只有焦僥擅長遁走藏匿，其他種族不會這種本事。
    if( me->query_race() != "jiaojao" )
        return notify_fail("你不會這種本事。\n");

    if( me->query("life_form") == "ghost" )
        return notify_fail("人死了就一了百了, 快去找城隍復活吧!!\n");

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 冷卻檢查：set_temp 存下次可用的時間戳。
    left = me->query_temp("vanish_cooldown") - time();
    if( left > 0 )
        return notify_fail("你方才竄逃過急，這會兒喘息未定，還得再等 " + left + " 秒。\n");

    if( !environment(me) )
        return notify_fail("你身處虛無之地，無處可遁。\n");

    // 需有出路才能遁走（戰鬥中尤須有路可逃）。
    exits = environment(me)->query("exits");
    if( !mapp(exits) || !sizeof(exits) ) {
        // 無路可逃：戰鬥中就真的逃不掉，否則只是原地一晃沒處躲。
        if( me->is_fighting() )
            return notify_fail("四面無路，你被困在此處，逃不了了！\n");
        return notify_fail("這裡無路可竄，無處可遁。\n");
    }

    do_vanish(me);
    return 1;
}

void do_vanish(object me)
{
    mapping exits;
    string *dirs, dir;
    object env, old_env, dest;
    mixed d;
    int fighting, hide;

    // 再次確認狀態（do_vanish 與 main 之間若有變化）。
    if( !me ) return;
    old_env = environment(me);
    if( !old_env ) return;

    exits = old_env->query("exits");
    if( !mapp(exits) || !sizeof(exits) ) {
        tell_object(me, "你環顧四周，竟已無路可遁。\n");
        return;
    }

    fighting = me->is_fighting();

    // 先設冷卻（無論成功與否都付代價，杜絕連續嘗試刷狀態）。
    me->set_temp("vanish_cooldown", time() + VANISH_COOLDOWN);

    // 脫離一切戰鬥：remove_all_killer 連 killer 帶 enemy 一併清掉（見檔頭）。
    if( fighting ) {
        me->remove_all_killer();
        message_vision(HIC
            "\n$N身形一矮，竟如鬼魅般自纏鬥中倏地抽身，眨眼便沒了影蹤！\n" NOR, me);
    }

    // 隨機挑一個出口（比照 go.c 的 escape）。
    dirs = keys(exits);
    dir = dirs[random(sizeof(dirs))];
    d = old_env->query("exits/" + dir);
    if( stringp(d) ) {
        if( catch(dest = load_object(d)) ) dest = 0;
    } else if( objectp(d) ) {
        dest = d;
    }

    if( !objectp(dest) ) {
        // 出口壞了：脫戰仍算數，只是沒能竄出去，原地躲藏。
        tell_object(me, "你想往別處竄逃，那出口卻像有問題，只得就地藏身。\n");
        hide = VANISH_HIDE_BASE + random(VANISH_HIDE_BASE)
            + me->query_skill("sneak");
        me->set_temp("pending/hidden", hide);
        tell_object(me, HIC "你屏息斂跡，悄悄藏進暗處。\n" NOR);
        return;
    }

    // 竄出本房間。
    if( me->move(dest) && environment(me) == dest ) {
        env = environment(me);
        // 躲藏：set_temp("pending/hidden", N)──引擎隱匿屬性（見檔頭）。
        // 藏匿值 = 基值 + 隨機 + 潛行技巧，越高越難被察覺。
        hide = VANISH_HIDE_BASE + random(VANISH_HIDE_BASE)
            + me->query_skill("sneak");
        me->set_temp("pending/hidden", hide);

        tell_object(me, HIC "你竄入鄰處，旋即斂息伏低，藏進暗影之中。\n" NOR);
    } else {
        // 移動失敗（負重 / valid_leave 等）：脫戰已成，原地躲藏。
        tell_object(me, "你想竄逃卻沒能脫身，只得就地藏匿。\n");
        hide = VANISH_HIDE_BASE + random(VANISH_HIDE_BASE)
            + me->query_skill("sneak");
        me->set_temp("pending/hidden", hide);
        tell_object(me, HIC "你屏息斂跡，悄悄藏進暗處。\n" NOR);
    }
}

int help(object me)
{
    write(@HELP
指令格式：vanish   (遁、逃遁)

焦僥一族身形短小、生性機警，最擅脫身遁走。施展此技，可瞬間脫離當前的一切
纏鬥，竄入鄰近一處，並就地斂息藏匿，教人一時難以察覺。

若你身陷戰鬥，這一遁能讓所有敵人停手；遁走之後你會藏進暗處，藏得好不好得
看你的身手。四面無路時自然遁不出去。每次遁走之後須喘息片刻，不能連用。

只有焦僥種族能使用這項本事。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
