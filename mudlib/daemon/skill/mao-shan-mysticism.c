// 茅山道法【奇門術】 mao-shan mysticism -- 茅山幻霧觀的奇門秘法(magic 槽 / conjure 指令)
//
// 來歷(docs/03-門派與武功/02-道士-天師與茅山.md L271-281)：奇門術乃茅山幻霧觀
// 二轉之上乘秘法﹐門檻為「茅山奇術(taoism of darkness) ≥100」(docs L273)。它不是
// 攻擊咒術﹐而是位移/役鬼/控屍的奇門之術﹐故掛在 magic 槽、走 conjure 指令
// (同 daemon/skill/taoism-cloud.c 素雲書、taoism-of-dunja.c 遁甲書的定位)﹐而非
// spells 槽 / cast 指令。道士可同時 `enable spells with taoism of darkness`(攻擊鬼火)
// 與 `enable magic with mao-shan-mysticism`(役鬼控屍)﹐兩槽兩不相礙。
//
// 五式(docs L275-281)：
//   記憶之術 memory  ── `conjure memory`(或 `conjure 記憶之術`)
//       記錄當前房間路徑於玩家 set("mysticism/recall_room", base_name(environment(me)))。
//       純記不戰﹐耗少量神(sen)。
//   翔空之術 recall  ── `conjure recall`(或 `conjure 翔空之術`)
//       飛回記錄點：load_object(query("mysticism/recall_room")) 後 me->move(dest)。
//       未記錄/載不起/交戰中皆 notify_fail。鏡 taoism-cloud.c 的駕雲傳送範式。
//   集靈之術 collect ── `conjure collect`(或 `conjure 集靈之術`)
//       分解同房一具屍體(obj/corpse.c﹐is_corpse() 為真)得「陰魂」一縷﹐記於控魂
//       計數 set_temp("mysticism/souls", n+1)。最多控制數 = 本身靈性 query_attr("spi")。
//       鏡 cmds/std/devour.c 的「房間找屍 -> destruct -> 計數」範式。
//   通靈之術 slave   ── `conjure slave on <目標>`
//       役一縷陰魂附入同房「一般 NPC」之軀﹐令其護衛施法者：被附身者 guard_ob(me)
//       (引擎既有護衛機制﹐見 feature/char/attack.c)﹐並記入控制清單。對玩家(userp)
//       /動物(set("animal",1) 之物)無效→notify_fail。每役一身耗一縷已集之陰魂。
//   噬魂之術 devour  ── `conjure devour [on <目標>]`
//       犧牲一個被通靈控制的目標﹐恢復施法者大量氣(kee)神(sen)：supplement_stat 大量
//       回補﹐並 destruct 被犧牲目標(runtime 鐵則 #10：destruct 殿後)。未指定目標則
//       取控制清單首一個。
//
// === 派發路徑(cmds/std/conjure.c::main L20-33)===
//   玩家鍵入 `conjure recall` 或 `conjure slave on wolf`。conjure.c 以
//   sscanf(arg,"%s on %s",spl,trg) 切出 spl 與 trg﹐present(trg) 解出 target 物件﹐
//   再 spl = replace_string(spl," ","_")(本門式名皆無空白﹐不受影響)﹐取
//   me->skill_mapped("magic")(= 已掛上的 magic key﹐此處為 "mao-shan-mysticism")﹐
//   呼 SKILL_D("mao-shan-mysticism")->conjure_magic(me, spl, target)。本檔接到 spl ∈
//   {memory,recall,collect,slave,devour}(或中文記憶之術/翔空之術/集靈之術/通靈之術/
//   噬魂之術)即自行施展﹔其餘 spl 逕自 notify_fail 後回 0。
//
//   注意：/std/magic 基底只提供 cast_spell、並無 conjure_magic﹐故不識之式**不可**
//   落回 ::conjure_magic(會是 undefined call)﹔鏡 taoism-cloud.c / taoism-of-dunja.c﹐
//   逕自 notify_fail 後回 0。
//
// runtime 鐵則：噬魂之術涉 destruct(被犧牲目標)﹐一律殿後(#10)﹔本檔不
// replace_program(#11)﹔為 magic daemon(inherit /std/magic)﹐不 include <weapon.h>。
//
// 簡化與註明(docs「複雜處可簡化並註明」)：
//   * 「陰魂」以控魂計數(temp)表示﹐不另建陰魂物件﹐避免臆造未建物件藍本。
//   * 「動物」一族本 mudlib 並無註冊(走獸皆 set_race("human")﹐見 d/tianling/npc/
//     baiyuan.c L43-45)﹐故無可靠引擎旗標﹔slave 對「動物」之擋﹐改以可由內容端
//     標記的 set("animal",1)(或 set("no_slave",1))判定﹐並以 userp() 擋玩家(權威)。
//   * 控制清單以 query_temp/set_temp 持有物件陣列﹐死亡/登出自然清空﹐符合「被役之
//     鬼不長久」的合理設定。

#include <ansi.h>

inherit "/std/magic";

// === 門檻(docs L273 載明)===
#define MM_GATE_SKILL   "taoism of darkness"    // 前置技能：茅山奇術。
#define MM_GATE_LEVEL   100                     // 茅山奇術火候下限。

// === 各式神(sen)消耗 / 效果參數(docs 未明定之細節取合理可驗值﹐集中於此便於平衡)===
#define MM_MEMORY_SEN   10      // 記憶之術：記點耗神(輕)。
#define MM_RECALL_SEN   50      // 翔空之術：傳送耗神(比照素雲書駕雲 50 神)。
#define MM_COLLECT_SEN  20      // 集靈之術：分解屍體得陰魂耗神。
#define MM_SLAVE_SEN    40      // 通靈之術：役鬼附身耗神。
#define MM_DEVOUR_SEN   10      // 噬魂之術：發動本身耗神(噬後大量回補)。

// 噬魂回補量(犧牲一隻被控目標可恢復的氣/神﹐"大量")。
#define MM_DEVOUR_KEE   200     // 噬魂回氣(kee)。
#define MM_DEVOUR_SEN_GAIN  150 // 噬魂回神(sen)。

// 控魂計數鍵 / 控制清單鍵(皆 temp﹐死亡/登出自然清空)。
#define MM_SOULS_KEY    "mysticism/souls"       // 已集陰魂縷數(int)。
#define MM_SLAVED_KEY   "mysticism/slaved"      // 被通靈控制的目標物件陣列。
#define MM_RECALL_KEY   "mysticism/recall_room" // 記憶之術所記房間路徑(持久 set)。

// 前置宣告(lesson #12：自訂函式一律檔頭前置宣告﹐免「定義前引用」編譯 Undefined
//   function﹐進而導致 daemon lazy-load 靜默失敗、conjure 指令靜默回 0)。
varargs int conjure_magic(object me, string spl, object target);
int valid_enable(string usage);
private string mm_resolve(string spl);
private int mm_gate(object me);
private object mm_find_corpse(object me);
private object *mm_live_slaves(object me);
int mm_memory(object me);
int mm_recall(object me);
int mm_collect(object me);
int mm_slave(object me, object target);
int mm_devour(object me, object target);

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("mao-shan-mysticism");
    // 登錄中文名﹐使 enable / skills 等顯示「奇門術」而非英文代號。
    CHINESE_D->add_translate("mao-shan-mysticism", "奇門術");
    setup();
}

// 本技能掛在 magic 槽(役鬼控屍)﹐而非 spells 槽(攻擊)。
// 覆寫 /std/magic.c 的 valid_enable(原本只認 "spells")﹐改認 "magic"
// (同 daemon/skill/taoism-cloud.c 素雲書、taoism-of-dunja.c 遁甲書)。
int valid_enable(string usage)
{
    return usage == "magic";
}

// 解析式名：conjure.c 已把空白換成底線(本門英文式名皆無空白)。收英文 id 與中文名。
//   回傳正規化 id(memory/recall/collect/slave/devour)﹐不識回 0。
private string
mm_resolve(string spl)
{
    if( !stringp(spl) ) return 0;
    switch( spl ) {
    case "memory":  case "記憶之術": return "memory";
    case "recall":  case "翔空之術": return "recall";
    case "collect": case "集靈之術": return "collect";
    case "slave":   case "通靈之術": return "slave";
    case "devour":  case "噬魂之術": return "devour";
    }
    return 0;
}

// 五式共用門檻：須為道士、為茅山派、已習奇門術、且茅山奇術 ≥100(docs L273)。
//   通過回 1﹔不足 notify_fail 說明後回 0。(鏡 taoism-of-dunja.c::dj_check_caster)
private int
mm_gate(object me)
{
    if( !objectp(me) ) return 0;

    // 須為道士、且為茅山派。
    if( me->query_class() != "taoist" ) {
        notify_fail("奇門術乃茅山道門的役鬼秘法﹐你並非道士﹐運使不來。\n");
        return 0;
    }
    if( me->query("sect") != "茅山派" ) {
        notify_fail("奇門術乃茅山幻霧觀祕傳﹐外人縱知其名﹐亦無從窺其堂奧。\n");
        return 0;
    }

    // 須已習得奇門術。
    if( me->query_skill("mao-shan-mysticism", 1) <= 0
    &&  !me->query_learn("mao-shan-mysticism") ) {
        notify_fail("你並未習得「奇門術」。\n");
        return 0;
    }

    // 門檻：茅山奇術火候(docs L273：茅山奇術 ≥100)。
    if( me->query_skill(MM_GATE_SKILL, 1) < MM_GATE_LEVEL ) {
        notify_fail(sprintf(
            "你茅山奇術的根基尚淺(需茅山奇術 %d)﹐運轉不起奇門役鬼之法。\n",
            MM_GATE_LEVEL));
        return 0;
    }

    return 1;
}

// 在同房找一具可分解的屍體(is_corpse() 為真﹐骸骨不算)。鏡 cmds/std/devour.c::find_corpse。
private object
mm_find_corpse(object me)
{
    object env, ob;

    env = environment(me);
    if( !objectp(env) ) return 0;

    foreach( ob in all_inventory(env) ) {
        if( !objectp(ob) ) continue;
        if( living(ob) ) continue;              // 活物不是屍體
        if( ob->is_corpse() ) return ob;        // 新鮮屍 / 腐屍皆可
    }
    return 0;
}

// 取控制清單中仍有效(未 destruct)的被役目標﹐順手清掉失效項。
private object *
mm_live_slaves(object me)
{
    object *list;

    list = me->query_temp(MM_SLAVED_KEY);
    if( !pointerp(list) ) list = ({});
    list = filter(list, (: objectp($1) && living($1) :));
    me->set_temp(MM_SLAVED_KEY, list);
    return list;
}

// ── conjure_magic(me, spl, [target]) ──
//   玩家：cmds/std/conjure.c 傳 (me, 式名, 對象或0)。
//   NPC ：std/char/npc.c::conjure_magic 傳 (me, magic)﹐target 省略。
// 本檔接五式(memory/recall/collect/slave/devour)﹔不識之式逕自 notify_fail 回 0
// (/std/magic 基底無 conjure_magic﹐不可落回 ::conjure_magic)。
// 失敗回 0(並 notify_fail 給玩家路徑)﹐成功回 1。
varargs int
conjure_magic(object me, string spl, object target)
{
    string id;

    if( !objectp(me) ) me = this_player();
    if( !objectp(me) || !stringp(spl) ) return 0;

    id = mm_resolve(spl);
    if( !id ) {
        notify_fail(
            "奇門術現可運使五式：\n"
            "    conjure memory      記憶之術──記下當前所在\n"
            "    conjure recall      翔空之術──飛回記憶之處\n"
            "    conjure collect     集靈之術──分解屍體攝取陰魂\n"
            "    conjure slave on <目標>   通靈之術──役鬼附身護主\n"
            "    conjure devour [on <目標>] 噬魂之術──噬役鬼以復氣神\n");
        return 0;
    }

    // 共用門檻(道士/茅山派/已習/茅山奇術 ≥100)。
    if( !mm_gate(me) ) return 0;

    // 非施法之地不可運使(鏡 conjure.c 的 no_magic 守則)。
    if( !objectp(environment(me)) ) {
        notify_fail("你身處虛無之地﹐無從運使奇門之術。\n");
        return 0;
    }
    if( environment(me)->query("no_magic") ) {
        notify_fail("這裡不准施展法術﹐奇門役鬼之法亦運使不得。\n");
        return 0;
    }

    switch( id ) {
    case "memory":  return mm_memory(me);
    case "recall":  return mm_recall(me);
    case "collect": return mm_collect(me);
    case "slave":   return mm_slave(me, target);
    case "devour":  return mm_devour(me, target);
    }
    return 0;
}

// ── 記憶之術 memory：記錄當前房間路徑。docs L277 ──
// 純記不戰﹐耗少量神。記於玩家持久欄位 set("mysticism/recall_room", 路徑)。
int
mm_memory(object me)
{
    object here;
    string path;

    here = environment(me);
    if( !objectp(here) ) {
        notify_fail("你身在虛空﹐無處可記。\n");
        return 0;
    }

    if( me->query_stat("sen") < MM_MEMORY_SEN ) {
        notify_fail("你神識微弱﹐凝不起這一道記憶之術。\n");
        return 0;
    }
    me->consume_stat("sen", MM_MEMORY_SEN);

    // base_name 取房間路徑(不含 .c)﹐與 load_object 可直接對接(同 taoism-cloud.c)。
    path = base_name(here);
    me->set(MM_RECALL_KEY, path);

    message_vision(HIM
        "$N閉目凝神﹐運起奇門術『記憶之術』﹐將此地的方位氣息默記於識海之中。\n" NOR,
        me);
    tell_object(me, HIC "你已將此處(" + (here->query("short") || path)
        + ")記入奇門識海。\n" NOR);

    if( userp(me) )
        me->improve_skill("mao-shan-mysticism", 1 + random(2));
    return 1;
}

// ── 翔空之術 recall：飛回記憶之處。docs L278 ──
// load_object(記錄路徑) 後 me->move(dest)。未記錄/載不起/交戰中皆 notify_fail。
// 完全鏡 taoism-cloud.c::conjure_magic 的駕雲傳送範式(先移動、後 start_busy)。
int
mm_recall(object me)
{
    object dest;
    string path;

    path = me->query(MM_RECALL_KEY);
    if( !stringp(path) || path == "" ) {
        notify_fail("你尚未以『記憶之術』記下任何地方﹐翔空無從施起。\n");
        return 0;
    }

    // 交戰中心神不寧﹐不可翔空遁走(鏡 taoism-cloud 之 is_fighting 守則)。
    if( me->is_fighting() ) {
        notify_fail("你正自纏鬥﹐心神不寧﹐難以運使翔空之術脫身。\n");
        return 0;
    }

    // 試載目的地房間：載不起(已拆/未建)便優雅擋下﹐且不扣神。
    if( catch(dest = load_object(path)) || !objectp(dest) ) {
        notify_fail("你記憶中的那處地方已然不可達﹐翔空之術落了空。\n");
        return 0;
    }

    if( me->query_stat("sen") < MM_RECALL_SEN ) {
        notify_fail(sprintf(
            "你的神識不足以運使翔空之術﹐至少需聚足 %d 神。\n", MM_RECALL_SEN));
        return 0;
    }

    // ── 通過所有檢查﹐正式翔空(之後不再失敗)──
    me->consume_stat("sen", MM_RECALL_SEN);

    message_vision(HIW
        "$N足下倏地騰起一片幽光﹐運起奇門術『翔空之術』﹐霎時凌空飛起化作一道流光遠去。\n" NOR,
        me);

    // 先移動﹐再 start_busy(std/char.c::move 在 is_busy() 時會拒絕移動﹐故後置)。
    me->move(dest);

    message_vision(MAG
        "$N身影自一片幽光中浮現﹐已然飛回記憶之中的地方。\n" NOR, me);
    tell_object(me, HIC "翔空之術既成﹐你已飛回先前記下的地方。\n" NOR);

    me->start_busy(2);

    if( userp(me) )
        me->improve_skill("mao-shan-mysticism", 1 + random(2));
    return 1;
}

// ── 集靈之術 collect：分解同房屍體得「陰魂」一縷。docs L279 ──
// 最多控制(集靈)數 = 本身靈性 query_attr("spi")。鏡 cmds/std/devour.c：房間找屍 ->
// destruct -> 計數。已集陰魂縷數記於 temp(MM_SOULS_KEY)。
int
mm_collect(object me)
{
    object corpse;
    int souls, cap;

    corpse = mm_find_corpse(me);
    if( !objectp(corpse) ) {
        notify_fail("這裡沒有可供分解攝魂的屍體。\n");
        return 0;
    }

    // 控魂上限 = 靈性(spi)。已集滿則攝不進更多陰魂。
    cap = me->query_attr("spi");
    if( cap < 1 ) cap = 1;
    souls = me->query_temp(MM_SOULS_KEY);
    if( souls < 0 ) souls = 0;
    if( souls >= cap ) {
        notify_fail(sprintf(
            "你靈性所能駕馭的陰魂已滿(%d 縷)﹐再多便要反噬己身﹐攝不進了。\n", cap));
        return 0;
    }

    if( me->query_stat("sen") < MM_COLLECT_SEN ) {
        notify_fail("你神識不足以運起集靈之術分解這具屍體。\n");
        return 0;
    }
    me->consume_stat("sen", MM_COLLECT_SEN);

    message_vision(HIM
        "$N結印掐訣﹐運起奇門術『集靈之術』﹐一縷幽魂自" + corpse->name()
        + HIM "中緩緩抽離﹐沒入$N袖中。\n" NOR, me);

    // 屍體被分解殆盡(每次攝魂都得有新屍體﹐杜絕無限刷)。destruct 殿後(鐵則 #10)。
    me->set_temp(MM_SOULS_KEY, souls + 1);
    destruct(corpse);

    tell_object(me, sprintf(HIC
        "你已攝得一縷陰魂(現掌控 %d / %d 縷)。\n" NOR, souls + 1, cap));

    if( userp(me) )
        me->improve_skill("mao-shan-mysticism", 1 + random(2));
    return 1;
}

// ── 通靈之術 slave：役一縷陰魂附入同房「一般 NPC」之軀﹐令其護衛施法者。docs L280 ──
// 對玩家(userp)/動物(set("animal",1) 或 set("no_slave",1))無效→notify_fail。
// 役成則被附身者 guard_ob(me)(引擎既有護衛機制﹐feature/char/attack.c)﹐並記入
// 控制清單﹐每役一身耗一縷已集之陰魂。
int
mm_slave(object me, object target)
{
    object *slaved;
    int souls;

    if( !objectp(target) || !target->is_character() || !living(target) ) {
        notify_fail("你要役使陰魂附入誰的身軀﹖(conjure slave on <目標>)\n");
        return 0;
    }
    if( target == me ) {
        notify_fail("你總不能役陰魂附自己的身罷﹖\n");
        return 0;
    }
    if( environment(target) != environment(me) ) {
        notify_fail("通靈的對象不在這裡。\n");
        return 0;
    }
    // docs L280：對玩家無效。
    if( userp(target) ) {
        notify_fail("活人神魂自固﹐陰魂附他不得﹐通靈之術對" + target->name()
            + "無效。\n");
        return 0;
    }
    // docs L280：對動物無效。本 mudlib 無「動物」一族(走獸皆 set_race("human")﹐
    //   見 d/tianling/npc/baiyuan.c)﹐故以可由內容端標記的 animal/no_slave 旗標判定。
    if( target->query("animal") || target->query("no_slave") ) {
        notify_fail("這等畜生靈識渾噩﹐陰魂附不上去﹐通靈之術對它無效。\n");
        return 0;
    }

    // 須有已集之陰魂可役(集靈之術所攝)。
    souls = me->query_temp(MM_SOULS_KEY);
    if( souls < 1 ) {
        notify_fail("你手上並無攝得的陰魂可供役使﹐先以『集靈之術』分解屍體攝魂。\n");
        return 0;
    }

    // 不可重複役同一目標。
    slaved = mm_live_slaves(me);
    if( member_array(target, slaved) >= 0 ) {
        notify_fail(target->name() + "已被你的陰魂附身﹐毋須再役。\n");
        return 0;
    }

    if( me->query_stat("sen") < MM_SLAVE_SEN ) {
        notify_fail("你神識不足以運起通靈之術役使陰魂。\n");
        return 0;
    }
    me->consume_stat("sen", MM_SLAVE_SEN);

    // 耗去一縷陰魂﹐記入控制清單﹐令其護衛施法者(引擎護衛機制)。
    me->set_temp(MM_SOULS_KEY, souls - 1);
    slaved += ({ target });
    me->set_temp(MM_SLAVED_KEY, slaved);
    target->guard_ob(me);

    message_vision(HIM
        "$N捏訣一引﹐一縷陰魂破袖而出﹐沒入$n的身軀﹗\n" NOR, me, target);
    tell_object(me, HIC "陰魂附體﹐" + target->name()
        + "雙目幽光一閃﹐自此聽你號令、為你護法。\n" NOR);

    if( userp(me) )
        me->improve_skill("mao-shan-mysticism", 1 + random(2));
    me->start_busy(2);
    return 1;
}

// ── 噬魂之術 devour：犧牲一個被通靈控制的目標﹐恢復施法者大量氣神。docs L281 ──
// supplement_stat 大量回補氣(kee)神(sen)﹐並 destruct 被犧牲目標(鐵則 #10：殿後)。
// 未指定 target 則取控制清單首一個﹔指定者須在控制清單內。
int
mm_devour(object me, object target)
{
    object *slaved;
    int kee_back, sen_back;

    slaved = mm_live_slaves(me);
    if( !sizeof(slaved) ) {
        notify_fail("你並無通靈控制的陰魂傀儡可供噬取﹐先以『通靈之術』役鬼附身。\n");
        return 0;
    }

    // 未指定目標則取清單首一個﹔指定者須確在控制清單內。
    if( !objectp(target) ) {
        target = slaved[0];
    } else if( member_array(target, slaved) < 0 ) {
        notify_fail(target->name() + "並非你通靈控制的傀儡﹐噬魂之術噬它不得。\n");
        return 0;
    }
    if( !objectp(target) || !living(target) ) {
        notify_fail("那具傀儡已然不在﹐無從噬取。\n");
        return 0;
    }
    if( environment(target) != environment(me) ) {
        notify_fail("你要噬取的傀儡不在這裡。\n");
        return 0;
    }

    if( me->query_stat("sen") < MM_DEVOUR_SEN ) {
        notify_fail("你神識微弱﹐連噬魂之術也運使不起。\n");
        return 0;
    }
    me->consume_stat("sen", MM_DEVOUR_SEN);

    message_vision(HIR
        "$N厲喝一聲﹐運起奇門術『噬魂之術』﹐$n體內的陰魂連同其精魄一併被$N吸納入體﹗\n" NOR,
        me, target);

    // 噬魂大量回補氣神(supplement_stat 補到 heal/max 上限為止)。
    kee_back = me->supplement_stat("kee", MM_DEVOUR_KEE);
    sen_back = me->supplement_stat("sen", MM_DEVOUR_SEN_GAIN);
    tell_object(me, sprintf(HIW
        "一股精魄之氣自丹田升騰﹐你只覺氣(+%d)神(+%d)為之大振﹗\n" NOR,
        kee_back, sen_back));

    // 自控制清單移除被犧牲者(先解護衛、再出清單)。
    if( target->query_guarding() == me )
        target->guard_ob(0);
    slaved -= ({ target });
    me->set_temp(MM_SLAVED_KEY, slaved);

    if( userp(me) )
        me->improve_skill("mao-shan-mysticism", 1 + random(2));
    me->start_busy(2);

    // ── 犧牲被通靈控制的目標(鐵則 #10：destruct 殿後)──
    destruct(target);
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
