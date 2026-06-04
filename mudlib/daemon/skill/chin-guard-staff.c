// 青邪伏魔杖 chin-guard-staff -- 哭笑門「護法」進階(二轉)的高階守勢杖法(基礎技能 staff)
//
// 哭笑門護法一脈的上乘守勢杖法(見 docs/03-門派與武功/01-武者-五大門派.md §3 哭笑門-
// 護法)。docs 載護法為「ES2 最堅強的後盾、頂級完全防禦﹐唯一可在戰鬥中回 hp 的
// class﹐拿一根杖逛大街幾乎立於不敗之地」(評分 攻擊 D / 防禦 S / 續戰 S / 靈活 B)。
// 故本杖法由入門青邪杖法(chin_staff)精進而成﹐招式偏重沉穩格擋與纏鬥消耗﹐dodge
// 值多為正(易被閃避但自身破綻亦小)﹐damage 平實綿密而非剛猛搶攻。
//
// 比照白象禪師守勢杖法 daemon/skill/zen-staff.c、入門 daemon/skill/chin_staff.c 之
// actions 招式表模型建立﹐但更精進﹕招式帶 "force"(吃大邪心法 huge force 的內力加成
// 係數﹐見 combatd.c::fight() 之 force_bonus 公式)。基礎技能為 staff(杖法)﹐玩家透過
// map_skill("staff","chin-guard-staff") 對應後即可持鐵杖施展(護法進階時師父自動掛上
// 此映射)。中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕damage 11~17
//   (入門 chin_staff 為 5~10)﹐多帶正 dodge(守勢)與 force 6~12。
//
// TODO(護法完整化)：docs 載護法核心玩法為「青邪杖 perform + 戰鬥中吐血回 hp」﹐其
//   「戰鬥回 hp」與「perform 完全防禦」屬 combat/perform/heal 系統(非招式表)﹐標記為
//   待辦。本檔先把帶「青邪伏魔」氣象的守勢杖招做實﹐與封山 zen-staff 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N雙手橫$w沉腰落樁﹐一式『判官封門』穩穩盪開來勢﹐反手戳向$n的$l",
    "dodge":		10,
    "force":		8,
    "damage":		11,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N腳下生根紋絲不動﹐$w如銅牆鐵壁般擋格後直搗$n的$l",
    "dodge":		12,
    "force":		8,
    "damage":		11,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N怪笑一聲﹐$w盤旋纏繞一式『哭喪鎖魂』死死纏住$n的$l",
    "dodge":		8,
    "force":		10,
    "damage":		13,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N退步穩樁卸去來力﹐借勢一頓重砸$n的$l",
    "dodge":		10,
    "force":		8,
    "damage":		12,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N身形微沉似哭似笑﹐$w如毒蛇吐信沉穩點向$n的$l",
    "dodge":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『青邪護身』杖影森森罩住周身﹐而後反撩$n的$l",
    "dodge":		14,
    "force":		10,
    "damage":		11,
    "damage_type":	"挫傷"
  ]),
  // —— 少數進手之招﹕守中帶攻﹐借纏鬥之勢猛搗(略負 dodge) ——
  ([
    "action":		"$N杖走中宮陰惻惻一笑﹐一式『笑面索命』直搗$n的$l",
    "dodge":		-4,
    "force":		10,
    "damage":		15,
    "damage_type":	"挫傷"
  ]),
  // —— 殺著﹕青邪伏魔杖最沉之式﹐凝守而後勃發、罡氣暴漲 ——
  ([
    "action":		"$N周身罡氣暴漲忽哭忽笑﹐凌空一式『青邪伏魔』攜千鈞之勢當頭壓向$n的$l",
    "dodge":		2,
    "force":		12,
    "damage":		17,
    "damage_type":	"挫傷"
  ]),
});

string *interattack = ({
  "$N雙手橫杖當胸﹐沉腰落樁如銅牆鐵壁﹐似哭似笑地靜待著破綻。\n",
  "$N腳下生根紋絲不動﹐杖頭凝而不發﹐守得密不透風。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("chin-guard-staff");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("chin-guard-staff", "青邪伏魔杖");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "chin-guard-staff", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
