// 金剛鎚法 jingang-zarn -- 龍圖丹派「劍甲門傳人」進階(二轉)的鈍器鎚法(基礎技能 blunt)
//
// 龍圖/武陀兩派方士共通進階「劍甲門」的戰鬥武功(見 docs/03-門派與武功/07-方士-龍圖
// 武陀.md §劍甲門﹔典型玩家 Kankichi 載「金剛鎚法 200」)。劍甲門使方士得一身戰力與
// 灌裝強化之能﹐金剛鎚法剛猛沉雄、以鈍器破甲碎堅。比照虎刀門鬼才的瘋虎刀法 daemon/
// skill/tiger-blade.c 與白象 wen-staff.c 之 actions 招式表模型建立﹐基礎技能型別為
// blunt (鈍器)﹐見 feature/weapon/blunt.c (rod.c 等鈍器兵器以此為武器型別)。
//
// 因基礎技能為 blunt (鈍器)﹐玩家透過 map_skill("blunt","jingang-zarn") 對應後即可
// 持鎚/杵類鈍器施展(劍甲門傳人進階時師父自動掛上此映射)。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹕招式 damage 14~22﹐高階式帶 "attack"
//   (命中加成)與 "force"(吃靈甲術 lingjia force 的內力加成係數﹐見 combatd.c::fight()
//   之 force_bonus 公式)。鈍器以重擊、破甲為主﹐damage_type 為「挫傷」。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// TODO(劍甲門完整化)：docs 載劍甲門核心玩法有 enchance(強化之術 golden_bless/
//   silver_bless)、灌裝備(金屋內丹提屬性)等裝備經濟機制﹐屬 craft/equip 系統(非招式
//   表)﹐標記為待辦。本檔先把帶「金剛鎚法」氣象的普攻鎚招做實﹐與 wen-staff、虎刀
//   tiger-blade 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉腰運力﹐$w一式『金剛起手』當頭砸向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "force":		6,
    "damage":		14,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N雙手持鎚﹐$w一式『力劈金剛』狠搗$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N運勁於臂﹐$w一式『金剛碎甲』橫掃$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		17,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N腳踏實步﹐$w一式『伏魔搗珠』盤旋砸向$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		10,
    "damage":		17,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N藉腰送力﹐$w一式『金剛點地』直挺挺杵向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"挫傷"
  ]),
  // —— 守勢式﹕借勢卸力、凝而後發(正 dodge) ——
  ([
    "action":		"$N沉鎚一引借勢卸力﹐隨即一式『迴鎚反搗』撩向$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N後退半步避其鋒銳﹐$w凝而後發猛砸$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		6,
    "damage":		14,
    "damage_type":	"挫傷"
  ]),
  // —— 殺著﹕金剛鎚法最盛一式﹐鎚勢暴漲、雷霆萬鈞 ——
  ([
    "action":		"$N大喝一聲﹐一式『金剛伏魔』$w攜雷霆萬鈞之勢轟砸$n的$l",
    "dodge":		-14,
    "attack":		10,
    "force":		14,
    "damage":		22,
    "damage_type":	"挫傷"
  ]),
});

string *interattack = ({
  "$N雙手橫持鐵鎚﹐運氣於臂﹐沉雄之氣蓄而不發﹐靜待出手的時機。\n",
  "$N持鎚下沉﹐一股醇厚內息自丹田貫注鎚身﹐尋找著進招的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("jingang-zarn");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("jingang-zarn", "金剛鎚法");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIR + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "jingang-zarn", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
