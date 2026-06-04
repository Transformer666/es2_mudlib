// 幻劍術 illusion-sword -- 道士通用「以氣御劍、虛實相生」的進階法術(基底 /std/magic)
//
// 來歷(docs/03-門派與武功/02-道士-天師與茅山.md §道士通用技能-幻劍術 L30-35)：
//   「lv 5、與張齡對話」習得﹔內功 90、幻劍術 90 後 parry 時自動施展幻劍術。
//   六道具名劍式 ten / thirty-six / forty-nine / sixty-four / eighty-one /
//   ninety-nine 對應 +10/+36/+49/+64/+81/+99 傷害﹔消耗神(sen) = 該式總傷害一半﹔
//   自身 delay 1。振武軍營軍師(docs 06)亦「獲得 古文、咒術、幻劍術」﹐共用本檔。
//
// 機制：幻劍術走 magic 槽以 cast 主動施展(valid_enable 由 /std/magic 提供)﹐玩家
//   `enable spells with illusion-sword` 後﹐`cast <劍式> [on <對象>]`(劍式可用英文
//   id ten… 或中文名「十」「三十六」…)。NPC 由 std/char/npc.c::cast_spell 觸發。
//   master.c::do_advance 將 base "magic" map 到本技能(map_skill("magic",
//   "illusion-sword"))﹐故道士/軍師走 magic 槽施展幻劍術。
//
// 數值對齊 docs(本檔覆寫 cast_spell﹐不走 /std/magic 的 power*技能 縮放﹐改用 docs
//   明定的「具名劍式 → 固定 +N 傷害」表)：
//     劍式            id            +傷害  耗神(=傷害一半﹐向下取整)  自身delay
//     十              ten            10        5                        1
//     三十六          thirty-six     36       18                        1
//     四十九          forty-nine     49       24 (49/2=24.5→24)         1
//     六十四          sixty-four     64       32                        1
//     八十一          eighty-one     81       40 (81/2=40.5→40)         1
//     九十九          ninety-nine    99       49 (99/2=49.5→49)         1
//   傷害以 docs 之固定 +N 為基數﹐另加一道隨幻劍術火候微幅成長的虛劍寒芒
//   (damage/4 內的技能加成)﹐使高階仍有意義﹐但 docs 的 +N 仍為下限、耗神/delay
//   嚴格照 docs。耗神不足 / 對象不合法 → 優雅擋下﹐不扣神、不開戰。
//
// 字典 data/chinese.o 查無 "illusion-sword" key﹐以 CHINESE_D->add_translate()
// 自行登錄中文名「幻劍術」﹐並登錄六劍式中文名﹐使 cast 中文名亦可、顯示工整。
//
// TODO(parry 自動施展)：docs 載「內功 90、幻劍術 90 後 parry 時自動施展幻劍術」﹐
//   其「招架成功時依技能門檻自動觸發劍式」屬 combat/parry perform 系統耦合﹐
//   與 powerblow 爆 hp、berserk 多段連擊之 perform TODO 同類﹐標記為待辦。本檔
//   先把六道具名劍式之 cast 主動施展、耗神/delay 做實﹐並保留普攻招式表。

#include <ansi.h>

inherit "/std/magic";

// ── 普攻招式表：cast 之外﹐幻劍術掛在 magic 槽參與一般戰鬥的劍影招式 ──
// (數值為虛劍意象的設計值﹔具名劍式之 docs 數值另由下方 query_spells/cast_spell 管。)
mapping *actions = ({
  ([
    "action":		"$N捏訣凝氣﹐指尖虛引一道幻劍無聲無息地刺向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N袖中真氣化作三五點幻劍寒芒﹐虛實莫辨地攢向$n的$l",
    "dodge":		-5,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足踏奇步﹐一式『幻劍亂影』漫天劍影真假交錯地罩向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝指成劍﹐一道幻劍螺旋著鑽向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N低喝一聲﹐周身幻劍暴漲﹐密密匝匝地席捲$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指一錯﹐一式『萬幻歸真』千百道幻劍儘數匯成一劍當頭澆向$n的$l",
    "dodge":		0,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N默運幻劍術﹐指間隱隱凝出一縷虛實莫辨的劍氣﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("illusion-sword");
  // 自行登錄中文名﹐字典查無此 key﹐使 enable / skills / cast 等顯示「幻劍術」。
  CHINESE_D->add_translate("illusion-sword", "幻劍術");
  // 六劍式中文名﹐使 `cast 十` / `cast 三十六` … 與 cast 英文 id 等價可用。
  CHINESE_D->add_translate("ten", "十");
  CHINESE_D->add_translate("thirty-six", "三十六");
  CHINESE_D->add_translate("forty-nine", "四十九");
  CHINESE_D->add_translate("sixty-four", "六十四");
  CHINESE_D->add_translate("eighty-one", "八十一");
  CHINESE_D->add_translate("ninety-nine", "九十九");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIC + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "illusion-sword", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門技能名 + 六道具名劍式咒文表 ──
string magic_skill() { return "illusion-sword"; }

// 幻劍術六劍式：以 docs 明定的具名劍式建表。
//   id    : cast 的英文代號(ten / thirty-six …)。
//   name  : 顯示用中文名。
//   damage: docs 之固定 +N 傷害(該式總傷害基數)。
//   sen   : 耗神 = damage / 2(向下取整)﹐嚴格照 docs「消耗神 = 總傷害一半」。
//   type  : 傷害型(刺傷﹔幻劍以氣化劍、攢刺為主)。
//   action: 施法訊息($N 施法者 / $n 對象)。
mapping query_spells()
{
  return ([
    "ten" :		([ "id":"ten",         "name":"十",     "damage":10, "sen":5,  "type":"刺傷",
	"action":HIC "$N捏訣凝氣﹐指尖虛引一道幻劍﹐一式『十』無聲無息地刺向$n！" NOR ]),
    "thirty-six" :	([ "id":"thirty-six",  "name":"三十六", "damage":36, "sen":18, "type":"刺傷",
	"action":HIC "$N袖中真氣化作三十六點幻劍寒芒﹐一式『三十六』虛實莫辨地攢向$n！" NOR ]),
    "forty-nine" :	([ "id":"forty-nine",  "name":"四十九", "damage":49, "sen":24, "type":"刺傷",
	"action":HIC "$N足踏奇步﹐四十九道幻劍漫天交錯﹐一式『四十九』真假莫辨地罩向$n！" NOR ]),
    "sixty-four" :	([ "id":"sixty-four",  "name":"六十四", "damage":64, "sen":32, "type":"刺傷",
	"action":HIC "$N凝指成劍﹐六十四道幻劍盤旋如輪﹐一式『六十四』螺旋著鑽向$n！" NOR ]),
    "eighty-one" :	([ "id":"eighty-one",  "name":"八十一", "damage":81, "sen":40, "type":"刺傷",
	"action":HIC "$N低喝一聲周身幻劍暴漲﹐八十一道劍影﹐一式『八十一』密密匝匝席捲$n！" NOR ]),
    "ninety-nine" :	([ "id":"ninety-nine", "name":"九十九", "damage":99, "sen":49, "type":"刺傷",
	"action":HIC "$N雙指一錯運起幻劍術絕詣﹐九十九道幻劍儘數匯成一劍﹐一式『九十九』攜雷霆之勢當頭澆向$n！" NOR ]),
  ]);
}

// cast_spell(me, spl, [target]) ── 覆寫 /std/magic 之版本﹐改用 docs 的「具名劍式
//   → 固定 +N 傷害、耗神 = 傷害一半、自身 delay 1」語意(不走 power*技能 縮放)。
//   玩家路徑：cmds/std/cast.c 傳 (me, 劍式, 對象或0)。
//   NPC 路徑：std/char/npc.c 傳 (me, 劍式)﹐target 省略 → 取當前敵人。
//   失敗回 0(notify_fail 給玩家路徑)﹐成功回 1。各檢查與 /std/magic 同序﹐
//   確保未通過前不扣神、不開戰(優雅擋下)。
varargs int
cast_spell(object me, string spl, object target)
{
  mapping spells, sp;
  string sk, nm, action, dtype;
  int cost, base, skill, damage;

  if( !objectp(me) || !stringp(spl) ) return 0;

  sk = magic_skill();
  spells = query_spells();
  if( !sk || !mapp(spells) || !sizeof(spells) ) {
    notify_fail("你還沒有可施展的劍式。\n");
    return 0;
  }

  // 找劍式：先比 key/中文名、再比英文 id。
  sp = spells[spl];
  if( !mapp(sp) ) foreach( nm, mapping m in spells )
    if( mapp(m) && (m["id"] == spl || m["name"] == spl) ) { sp = m; break; }
  if( !mapp(sp) ) {
    notify_fail("幻劍術之中並無「" + spl + "」這一道劍式。\n");
    return 0;
  }

  // 須已習得幻劍術。
  if( me->query_skill(sk) <= 0 && !me->query_learn(sk) ) {
    notify_fail("你並未習得「" + to_chinese(sk) + "」。\n");
    return 0;
  }

  // 取施法對象(cast 未指定時取當前敵人)。
  if( !objectp(target) ) {
    object *es = me->query_enemy();
    if( arrayp(es) ) {
      es -= ({ 0 });
      if( sizeof(es) ) target = es[0];
    }
  }
  if( !objectp(target) || !living(target)
  ||  target->query("life_form") == "ghost" ) {
    notify_fail("你要對誰施展幻劍術？（cast " + spl + " on <對象>）\n");
    return 0;
  }
  if( target == me ) {
    notify_fail("你不能對自己施展幻劍術。\n");
    return 0;
  }
  if( environment(me) != environment(target) ) {
    notify_fail("施展的對象不在這裡。\n");
    return 0;
  }

  // 非戰之地不可施展攻擊劍式(與 combatd.c::fight 的 no_fight 規則一致)。
  if( environment(me)->query("no_fight")
  && !target->query("unprotect_mark") && !me->query("unprotect_mark") ) {
    notify_fail("這裡是清靜之地，不可動手施展劍式。\n");
    return 0;
  }

  // 神(sen)消耗檢查：docs 明定耗神 = 該式總傷害一半﹐已預存於 sp["sen"]。
  cost = sp["sen"];
  if( me->query_stat("sen") < cost ) {
    notify_fail("你的神識不足以凝起這道幻劍。\n");
    return 0;
  }

  // ── 通過所有檢查﹐正式施展(之後不再失敗)──
  // 若尚未交戰則開戰。
  if( !me->is_fighting(target) ) {
    me->kill_ob(target);
    if( userp(target) ) target->fight_ob(me);
    else target->kill_ob(me);
  }

  me->consume_stat("sen", cost);

  // 傷害：docs 固定 +N 為基數﹐另加一道隨幻劍術火候微幅成長的寒芒(至多 base/4 內)。
  base = sp["damage"];
  skill = me->query_skill(sk);
  damage = base + base * skill / 400;       // skill 100 → +25%；200 → +50%
  damage += random(base / 4 + 1);           // 虛實相生的浮動

  // 施法訊息。
  action = sp["action"];
  if( !stringp(action) ) action = "$N凝氣化劍﹐一道幻劍激射向$n！";
  message_vision(action + "\n", me, target);

  // 套用傷害(與物理攻擊同走 receive_damage)。
  dtype = sp["type"]; if( !stringp(dtype) ) dtype = "刺傷";
  target->receive_damage(damage, me, me);
  COMBAT_D->report_status(target);

  // 練幻劍術(僅玩家﹔NPC 技能固定)。
  if( userp(me) )
    me->improve_skill(sk, 1 + random(2));

  // 自身 delay 1(docs 明定「自身 delay 1」)。
  me->start_busy(1);

  return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
