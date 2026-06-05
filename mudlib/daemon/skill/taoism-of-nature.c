// 茅山幻術 taoism of nature -- 茅山派隱風觀(進階)的上乘幻咒
//
// 這是一門法術(magic)技能﹐茅山派隱風觀二轉「隱風觀」所授的上乘道法。
// 比照入門幽冥三箭 youmin.c / 天師桃山密籙 taoism-of-conviction.c 的結構
// 建立(走 spells 槽、cast 指令)﹐使技能可被指派、習練、施法。
//
// 設計(docs 03-門派與武功/02-道士-天師與茅山.md「隱風觀(風/nature) →
//   茅山幻術 taoism of nature」)：docs 載茅山幻術四式「喚犬 dog / 喚猿
//   monkey / 喚蟒 hydra / 喚雨 rain」﹐召役獸靈以制敵(delay/偷物/吞噬/
//   恢復)﹐命中時消耗先天符。本檔先實作其召獸傷敵的攻擊一系(獸靈撲咬)﹐
//   其控場/恢復特效(喚犬定身、喚猿偷物、喚蟒吞噬、喚雨恢復)待咒術效果
//   引擎就緒後再各自承襲。
//
// 註(收徒限制)：docs 載隱風觀「不收夜叉/形天/厭火/黑齒」之種族門檻﹐
//   屬入門/拜師階段之種族驗證﹐非本技能(已入門後習練)範疇﹐標記為 TODO。
//
// 注意：key 含空白(「taoism of nature」)﹐故檔名以連字號代之
// (taoism-of-nature.c)﹐register/translate 用的 key 仍為含空白原名。
//
// 召獸控場特效(已實作﹐走 conjure 指令)：本檔除既有 cast(spells 槽)的攻擊咒術
//   外﹐另 override conjure_magic 補上 docs L221-228 載明的茅山幻術四式具名召喚。
//   此四式自足(不需元素傷害引擎)﹐以「召役獸靈」制敵﹐命中時各焚一張先天符：
//     喚犬 dog    -- 幻犬絆纏目標﹐令其 delay 2(target->start_busy(2)﹐鏡
//                    daemon/skill/strategy.c::do_charge 對 target 之 start_busy)。
//     喚猿 monkey -- 幻猿摸竊目標一件隨身物(鏡 cmds/std/steal.c 之 all_inventory
//                    取隨機物 ->move(me) 範式)。
//     喚蟒 hydra  -- 幻蟒吞噬「非玩家」目標(即殺/重傷)；對玩家無效(僅 !userp)。
//                    吞噬以「耗盡目標 HP 當前/可癒值」令其循引擎心跳自然死亡﹐
//                    不直接 ::die()/destruct(runtime 鐵則 #10)。
//     喚雨 rain   -- 喚起甘霖﹐群補施法者周圍「玩家」的精氣神(gin/kee/sen)﹐
//                    鏡 daemon/skill/strategy.c::do_mass_aid 之群補範式﹐但只惠
//                    及 userp(docs：恢復週圍玩家精氣神)。
//
// 派發路徑(cmds/std/conjure.c)：玩家鍵入 `conjure <式> [on <目標>]`。conjure.c
//   取 me->skill_mapped("magic")(= 已掛上的法術系 key﹐此處須 `enable magic with
//   taoism of nature`)﹐將 <式> 之空白換為底線後﹐呼 SKILL_D(key)->conjure_magic
//   (me, spl, target)。本檔接到 spl ∈ {dog,monkey,hydra,rain}(或中文喚犬/喚猿/
//   喚蟒/喚雨)即自行施展﹔其餘 spl 逕自 notify_fail 後回 0(注意 /std/magic 基底
//   只提供 cast_spell、並無 conjure_magic﹐故不可落回 ::conjure_magic﹐否則 undefined
//   call)。此乃 daemon/skill/taoism-cloud.c::conjure_magic(同走 magic 槽、conjure
//   指令、不識之式即 notify_fail 回 0)的同型結構。
//
// 注意：本門攻擊咒術(query_spells 之喚獸/百獸朝元/幻霧噬靈)走 spells 槽、cast
//   指令﹔召獸四式走 magic 槽、conjure 指令。二者互不相礙﹐玩家可同時
//   `enable spells with taoism of nature`(cast 攻擊) 與
//   `enable magic with taoism of nature`(conjure 召獸)。

#include <ansi.h>

inherit "/std/magic";

// 召獸四式參數(docs L221-228﹐未明給之細節取合理可驗值)。集中於此便於平衡微調。
#define TN_FU           "先天符"  // 命中時所焚之符(同 query_spells 各式之 "fu")。
#define TN_DOG_SEN      20      // 喚犬：耗神。
#define TN_DOG_DELAY    2       // 喚犬：令目標 delay 2(docs)。
#define TN_MONKEY_SEN   25      // 喚猿：耗神。
#define TN_HYDRA_SEN    40      // 喚蟒：耗神(吞噬即殺﹐神耗最高)。
#define TN_RAIN_SEN     30      // 喚雨：耗神(群補)。
#define TN_RAIN_HEAL    50      // 喚雨：群補基礎量(再加幻術火候加成)。

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐袖中竄出一道幻犬虛影﹐撲咬$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N掐訣引靈﹐一頭幻猿虛影縱身抓向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N袖中先天符燃起﹐化作一條幻蟒纏向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N足踏罡步﹐一式『百獸朝元』群獸虛影齊撲$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N揮手撒出一蓬幻影﹐密密匝匝地撲向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N凝神運法﹐一頭幻獸盤旋著噬向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N後退半步﹐喚起一道幻雨化作獸潮捲向$n的$l",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"幻獸"
  ]),
  ([
    "action":		"$N雙手結印﹐一式『幻霧噬靈』群獸虛影沖天撲落﹐淹沒$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"幻獸"
  ]),
});

string *interattack = ({
  "$N默運茅山幻術﹐周身隱隱浮起一層獸靈虛影﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism of nature");
  // 登錄中文名﹐使 enable / skills 等顯示「茅山幻術」而非英文代號。
  CHINESE_D->add_translate("taoism of nature", "茅山幻術");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIG + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "taoism of nature", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable/cast_spell 由 /std/magic 提供）──
string magic_skill() { return "taoism of nature"; }

// 前置宣告(lesson #12：自訂函式一律先前置宣告﹐免「定義前引用」編譯 Undefined
//   function﹐進而導致 daemon lazy-load 靜默失敗、conjure 指令靜默回 0)。
varargs int conjure_magic(object me, string spl, object target);
private string tn_resolve(string spl);
private int tn_gate(object me);
private int tn_burn_fu(object me);
private int tn_need_target(object me, object target);
int tn_dog(object me, object target);
int tn_monkey(object me, object target);
int tn_hydra(object me, object target);
int tn_rain(object me, object target);

// 茅山隱風觀【茅山幻術】召獸攻擊一系。威力高於入門幽冥三箭(youmin)﹐神耗
// 亦較高﹐以對應其二轉上乘道法的定位。每式命中焚一張「先天符」引靈。
mapping query_spells()
{
  return ([
    "喚獸" :     ([ "id":"huanshou", "sen":18, "power":24, "type":"幻獸", "fu":"先天符",
        "action":HIG "$N口誦真言﹐袖中先天符燃起﹐一頭幻獸虛影破符而出﹐縱身撲咬$n！" NOR ]),
    "百獸朝元" : ([ "id":"baishou",  "sen":40, "power":42, "type":"幻獸", "fu":"先天符",
        "action":HIG "$N足踏罡步﹐結印引靈﹐一式『百獸朝元』群獸虛影沖天而起﹐齊撲$n！" NOR ]),
    "幻霧噬靈" : ([ "id":"shiling",  "sen":66, "power":60, "type":"幻獸", "fu":"先天符",
        "action":HIG "$N凝神運起茅山幻術至深一式﹐周身幻霧翻湧獸靈暴漲﹐一式『幻霧噬靈』獸潮鋪天蓋地﹐淹沒$n！" NOR ]),
  ]);
}

// ── 召獸四式(conjure 指令)：本技能可掛 magic 槽﹐故覆寫 /std/magic 的
//    valid_enable(原只認 "spells")使其同時認 "magic"。如此玩家既可
//    `enable spells with taoism of nature`(cast 攻擊)﹐亦可
//    `enable magic with taoism of nature`(conjure 召獸)﹐兩槽互不相礙。──
int valid_enable(string usage)
{
    return usage == "spells" || usage == "magic";
}

// 解析召獸式名：conjure.c 已把空白換成底線﹐故英文 id 即 dog/monkey/hydra/rain。
//   另收中文喚犬/喚猿/喚蟒/喚雨。回傳正規化 id(dog/monkey/hydra/rain)﹐不識回 0。
private string
tn_resolve(string spl)
{
    if( !stringp(spl) ) return 0;
    switch( spl ) {
    case "dog":    case "喚犬": return "dog";
    case "monkey": case "喚猿": return "monkey";
    case "hydra":  case "喚蟒": return "hydra";
    case "rain":   case "喚雨": return "rain";
    }
    return 0;
}

// 召獸四式共用門檻：須為道士、已習得茅山幻術、所在非禁法之地。
//   通過回 1﹔不足 notify_fail 說明後回 0。(鏡 taoism-cloud.c::conjure_magic 之 gate)
private int
tn_gate(object me)
{
    object here;

    // 須為道士方能運使茅山道法。
    if( me->query_class() != "taoist" ) {
        notify_fail("茅山幻術乃道門召役獸靈的上乘道法﹐你並非道門中人﹐運使不來。\n");
        return 0;
    }

    // 須已習得茅山幻術。
    if( me->query_skill("taoism of nature", 1) <= 0
    &&  !me->query_learn("taoism of nature") ) {
        notify_fail("你並未習得「茅山幻術」。\n");
        return 0;
    }

    here = environment(me);
    if( !objectp(here) ) {
        notify_fail("你身處虛無之地﹐無從召役獸靈。\n");
        return 0;
    }
    if( here->query("no_magic") ) {
        notify_fail("這裡不准施展法術﹐召獸之術亦運使不得。\n");
        return 0;
    }

    return 1;
}

// 焚符(命中時消耗先天符﹐docs L228)：身上須備有先天符且張數>=1﹐焚去一張。
//   有符回 1﹔無符 notify_fail 後回 0。(鏡 std/magic.c::cast_spell 之 fu 機制)
private int
tn_burn_fu(object me)
{
    object fu;

    fu = present(TN_FU, me);
    if( !objectp(fu) || (int)fu->query_amount() < 1 ) {
        notify_fail("你身上沒有施展此法所需的" + TN_FU + "。\n");
        return 0;
    }
    fu->add_amount(-1);
    return 1;
}

// 召獸對敵共用：須有合法且同房的活物目標﹐且非自己。通過回 1﹐否則 notify_fail 回 0。
private int
tn_need_target(object me, object target)
{
    if( !objectp(target) || !target->is_character() || !living(target) ) {
        notify_fail("你要召役獸靈撲向誰﹖(conjure <式> on <目標>)\n");
        return 0;
    }
    if( target == me ) {
        notify_fail("你總不能召獸來咬自己罷﹖\n");
        return 0;
    }
    if( environment(target) != environment(me) ) {
        notify_fail("施法的對象不在這裡。\n");
        return 0;
    }
    // 非戰之地不可對人召獸傷敵(鏡 std/magic.c::cast_spell 的 no_fight 守則)。
    if( environment(me)->query("no_fight")
    &&  !target->query("unprotect_mark") && !me->query("unprotect_mark") ) {
        notify_fail("這裡是清靜之地﹐不可動手召獸。\n");
        return 0;
    }
    return 1;
}

// ── conjure_magic(me, spl, [target]) ──
//   玩家：cmds/std/conjure.c 傳 (me, 式名(空白已換底線), 對象或0)。
//   NPC ：std/char/npc.c::conjure_magic 傳 (me, magic)﹐target 省略。
// 本檔接召獸四式(dog/monkey/hydra/rain)﹔不識之式逕自 notify_fail 回 0
// (/std/magic 基底無 conjure_magic﹐不可落回 ::conjure_magic)。
// 失敗回 0(並 notify_fail 給玩家路徑)﹐成功回 1。
varargs int
conjure_magic(object me, string spl, object target)
{
    string id;

    if( !objectp(me) ) me = this_player();
    if( !objectp(me) || !stringp(spl) ) return 0;

    id = tn_resolve(spl);
    if( !id ) {
        // /std/magic 基底並無 conjure_magic(只提供 cast_spell)﹐不識之式不可
        // 落回 ::conjure_magic(會是 undefined call)﹔鏡 taoism-cloud.c﹐逕自
        // notify_fail 後回 0。
        notify_fail("茅山幻術中並無「" + spl + "」這一式召獸口訣。\n");
        return 0;
    }

    // 共用門檻(道士/已習/非禁法之地)。
    if( !tn_gate(me) ) return 0;

    switch( id ) {
    case "dog":    return tn_dog(me, target);
    case "monkey": return tn_monkey(me, target);
    case "hydra":  return tn_hydra(me, target);
    case "rain":   return tn_rain(me, target);
    }
    return 0;
}

// ── 喚犬 dog：耗神 + 焚符﹐召幻犬絆纏目標﹐令其 delay 2。docs L221-224 ──
// delay 鏡 daemon/skill/strategy.c::do_charge 對 target->start_busy 之硬直。
int
tn_dog(object me, object target)
{
    if( !tn_need_target(me, target) ) return 0;

    if( me->query_stat("sen") < TN_DOG_SEN ) {
        notify_fail("你的神識不足以召出幻犬。\n");
        return 0;
    }
    if( !tn_burn_fu(me) ) return 0;

    me->consume_stat("sen", TN_DOG_SEN);

    // 若尚未交戰則開戰(鏡 cast_spell：玩家攻擊型法術主動開戰)。
    if( !me->is_fighting(target) ) {
        me->kill_ob(target);
        if( userp(target) ) target->fight_ob(me);
        else target->kill_ob(me);
    }

    message_vision(HIG
        "$N口誦真言﹐袖中竄出一道幻犬虛影﹐張口咬住$n的衣袂死纏不放﹗\n" NOR,
        me, target);
    tell_object(target, HIR "一頭幻犬纏住了你的手腳﹐你登時動彈不得﹗\n" NOR);

    // 幻犬絆纏：令目標短暫遲滯(delay 2)。
    target->start_busy(TN_DOG_DELAY);

    if( userp(me) )
        me->improve_skill("taoism of nature", 1 + random(2));
    me->start_busy(2);
    return 1;
}

// ── 喚猿 monkey：耗神 + 焚符﹐召幻猿摸竊目標一件隨身物。docs L221-225 ──
// 偷物鏡 cmds/std/steal.c：取 all_inventory(target) 之隨機一件 ->move(me)。
int
tn_monkey(object me, object target)
{
    object *inv, ob;

    if( !tn_need_target(me, target) ) return 0;

    if( me->query_stat("sen") < TN_MONKEY_SEN ) {
        notify_fail("你的神識不足以召出幻猿。\n");
        return 0;
    }

    // 先確認目標身上有可摸之物(剔除裝備中/不可偷者)﹐無物則不耗神/不焚符。
    inv = all_inventory(target);
    inv = filter(inv, (: objectp($1)
        && !$1->query("no_steal")
        && !$1->query("equipped") :));
    if( !sizeof(inv) ) {
        notify_fail(target->name() + "身上沒有什麼好摸的東西。\n");
        return 0;
    }

    if( !tn_burn_fu(me) ) return 0;
    me->consume_stat("sen", TN_MONKEY_SEN);

    ob = inv[random(sizeof(inv))];

    message_vision(HIG
        "$N掐訣引靈﹐一頭幻猿虛影竄向$n﹐探爪在$n身上一抓﹗\n" NOR, me, target);

    // 摸竊：移入施法者懷中﹔滿載則落地於施法者所在環境(鏡 steal.c 之 move 失敗回退)。
    if( !ob->move(me) ) {
        ob->move(environment(me));
        tell_object(me, "幻猿摸出一" + ob->query("unit") + ob->name()
            + "﹐你卻拿捏不住﹐它落到了地上。\n");
    } else {
        tell_object(me, HIW "幻猿替你摸來一" + ob->query("unit") + ob->name()
            + "﹗\n" NOR);
    }
    tell_object(target, HIR "一頭幻猿在你身上一抓﹐捲走了你的"
        + ob->name() + "﹗\n" NOR);

    if( userp(me) )
        me->improve_skill("taoism of nature", 1 + random(2));
    me->start_busy(2);
    return 1;
}

// ── 喚蟒 hydra：耗神 + 焚符﹐召幻蟒吞噬「非玩家」目標(即殺/重傷)。docs L221-226 ──
// 對玩家無效(僅 !userp)。吞噬以「耗盡目標 HP 當前值與可癒上限」令其循引擎心跳
// 自然死亡﹐不直接 ::die()/destruct(runtime 鐵則 #10)。先 kill_ob 入殺戮模式。
int
tn_hydra(object me, object target)
{
    int hp;

    if( !tn_need_target(me, target) ) return 0;

    // docs：喚蟒只吞「非玩家」目標﹔對玩家(userp)無效。
    if( userp(target) ) {
        notify_fail("幻蟒纏向" + target->name()
            + "﹐卻吞不下這等修為的活人﹐悻悻散去。\n");
        return 0;
    }

    if( me->query_stat("sen") < TN_HYDRA_SEN ) {
        notify_fail("你的神識不足以召出幻蟒。\n");
        return 0;
    }
    if( !tn_burn_fu(me) ) return 0;

    me->consume_stat("sen", TN_HYDRA_SEN);

    // 進入殺戮模式(使後續對 HP 的耗損被引擎認作致命傷)。
    me->kill_ob(target);
    target->kill_ob(me);

    message_vision(HIR
        "$N袖中先天符燃起﹐化作一條丈許巨蟒﹐張開血盆大口將$n整個吞了下去﹗\n" NOR,
        me, target);

    // 吞噬：耗盡目標 HP 之當前值與可癒上限﹐令其於下次心跳因 HP 力竭而死。
    hp = (int)target->query_stat_maximum("HP");
    if( hp < 1 ) hp = 1;
    target->damage_stat("HP", hp, me);    // 削可癒上限(重創形體)。
    target->consume_stat("HP", hp, me);   // 削當前值至 0(力竭)。

    if( userp(me) )
        me->improve_skill("taoism of nature", 1 + random(2));
    me->start_busy(2);
    return 1;
}

// ── 喚雨 rain：耗神 + 焚符﹐喚甘霖群補施法者周圍「玩家」的精氣神。docs L221-227 ──
// 群補鏡 daemon/skill/strategy.c::do_mass_aid﹐但只惠及 userp(docs：恢復週圍玩家)。
int
tn_rain(object me, object target)
{
    object env, ob;
    int heal, n;

    if( me->query_stat("sen") < TN_RAIN_SEN ) {
        notify_fail("你的神識不足以喚起甘霖。\n");
        return 0;
    }

    env = environment(me);
    if( !objectp(env) ) {
        notify_fail("你身在虛空﹐無從喚雨。\n");
        return 0;
    }
    if( !tn_burn_fu(me) ) return 0;

    me->consume_stat("sen", TN_RAIN_SEN);

    // 回補量隨幻術火候成長(supplement_stat 自動封頂於 heal/max)。
    heal = TN_RAIN_HEAL + me->query_skill("taoism of nature", 1);
    if( heal < 1 ) heal = 1;

    message_vision(HIC
        "$N足踏罡步﹐仰天一聲清嘯﹐召起一陣濛濛甘霖灑落﹐滋潤在場眾人的精氣神識﹗\n" NOR,
        me);

    // 只群補周圍「玩家」(含施法者本人﹐若為玩家)的精氣神。
    foreach(ob in all_inventory(env)) {
        if( !objectp(ob) || !userp(ob) ) continue;
        ob->supplement_stat("gin", heal);
        ob->supplement_stat("kee", heal);
        ob->supplement_stat("sen", heal);
        tell_object(ob, HIC "甘霖入體﹐你只覺精氣神為之一振。\n" NOR);
        n++;
    }

    if( userp(me) )
        me->improve_skill("taoism of nature", 1 + random(2));
    me->start_busy(2);
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
