// refine.c -- 方士「煉丹」：在丹爐前以藥材煉製丹藥。
//
// 設計與來源：docs/02-遊戲系統與機制/06-煉丹與書本系統.md
//   ──方士在丹爐前合藥材煉成丹藥。本指令保持 v1 簡單、安全：
//   只認一條固定配方，消耗手中指定藥材，產出一粒丹藥，不掛失敗
//   毀爐風險，也不接 produce_param / requirement 那套完整生產系統
//   （留待日後擴充）。
//
// 機制全部比照現有、已讀過原始碼確認的做法：
//   * 指令查找：檔名 == 動詞（adm/daemons/cmd_d.c 用 get_dir + verb+".c"）。
//     放在 /cmds/std/ 所有人都搜得到，故在此用 query_class() 鎖死成
//     只有方士 (alchemist) 能用──比照 spitfire.c 以 query_race() 鎖種族。
//   * 職業判定：me->query_class()（見 feature/char/score.c）。龍圖丹派／
//     武陀拜師後 set_class("alchemist")（見 d/longtu/npc/master.c）。
//   * 場地判定：須在丹房（房間 set("danfang", 1)）。
//   * 消耗藥材：藥材是 COMBINED_ITEM（見 std/item/combined.c），以
//     present(id, me) 取得後 add_amount(-1) 逐份消耗，歸零自動 destruct。
//   * 產出丹藥：new(PILL)->move(me)，比照 enchant.c 之外的標準做法。
//   * 訊息：message_vision，$N=施者（見現有指令）。
//
// 安全性：每次煉丹確實扣掉一份靈芝＋一支當歸，非無限資源；藥材不足、
// 非方士、不在丹房一律拒絕、不消耗任何東西。

inherit F_CLEAN_UP;

// 唯一配方：靈芝 + 當歸 -> 養氣丹。
// key = 藥材物件檔；value = 煉一爐所需份數。
#define HERB_LINGZHI    "/obj/reagent/lingzhi"
#define HERB_DANGGUI    "/obj/reagent/danggui"
#define PILL_YANGQI     "/obj/reagent/yangqi_pill"

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    object lingzhi, danggui, pill;

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 只有方士懂得煉丹。
    if( me->query_class() != "alchemist" )
        return notify_fail("你又不是方士﹐哪會煉什麼丹？\n");

    // 須在丹房（架著丹爐）才能起火煉丹。
    if( !environment(me) || !environment(me)->query("danfang") )
        return notify_fail("這裡沒有丹爐﹐你得到丹房裡才煉得了丹。\n");

    // 取出手中藥材。present() 回傳該物件（見 doc/efuns/present）。
    lingzhi = present("lingzhi", me);
    danggui = present("danggui", me);

    if( !lingzhi || (int)lingzhi->query_amount() < 1 )
        return notify_fail("煉製養氣丹得有靈芝才行﹐你身上沒有。\n");
    if( !danggui || (int)danggui->query_amount() < 1 )
        return notify_fail("煉製養氣丹還少了一支當歸。\n");

    // 消耗各一份藥材；歸零時 COMBINED_ITEM 會自行 destruct。
    lingzhi->add_amount(-1);
    danggui->add_amount(-1);

    // 產出一粒養氣丹，移入施者身上（會與既有同類丹藥自動合併）。
    pill = new(PILL_YANGQI);
    pill->move(me);

    message_vision("$N將一株靈芝、一支當歸投入丹爐﹐添炭搧風﹐文火慢煉。\n", me);
    message_vision("$N守爐運氣﹐良久﹐爐中藥香漸濃﹐凝成一粒深褐色的養氣丹。\n", me);

    return 1;
}

int help(object me)
{
    write(@HELP
指令格式﹕refine     （中文﹕煉丹）

方士站在丹房的丹爐前﹐手中備齊藥材時﹐可用此指令煉製丹藥。

目前可煉的配方﹕
    靈芝 一株 ＋ 當歸 一支  ->  養氣丹 一粒（服之可調養精氣神、癒合些許外傷）

每煉一爐便消耗對應的藥材﹐藥材不足、不在丹房、或非方士出身﹐都煉不成丹。
煉成後可用 eat yangqi 服下（本遊戲物件以英文代號指認﹐養氣丹代號 yangqi）。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
