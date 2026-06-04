// 達摩烈焰刀 damo blade -- 白象寺「降魔尊者」進階(二轉)的高階刀法(基礎技能 blade)
//
// 白象寺羅漢一脈最剛猛的攻擊刀法(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §白象寺-羅漢核心技能﹕「達摩烈焰刀 damo blade」)。借達摩面壁所悟的禪火、刀挾
// 烈焰降魔﹐是白象寺武僧證入「降魔尊者」一階方得傳授的殺著。比照虎刀門鬼才的
// 瘋虎刀法 daemon/skill/tiger-blade.c 之 actions 招式表模型建立﹐基礎技能為
// blade(刀法)﹐持厚背戒刀施展﹐attack_using 第三參數為兵器物件(weapon)。
//
// 因基礎技能為 blade(刀法)﹐玩家透過 map_skill("blade","damo blade") 對應後即可
// 持刀施展(降魔尊者進階時師父自動掛上此映射﹔尊者一階以刀證道﹐基礎技能由 staff
// 改習 blade)。中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate()
// 自行登錄。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹐供日後平衡微調﹕招式 damage 16~23
//   (高於入門 rid-evil 5~10、略高於鬼才瘋虎刀法 15~22)﹐高階式帶 "attack"(命中
//   加成)與 "force"(吃羅漢降魔功 luohan force 的內力加成係數)﹐另含火焰傷害(damage_type
//   "燒傷")以應「烈焰刀」之名。
//
// TODO(降魔尊者完整化)：docs 載白象寺有「18 銅人任務(reset 任務前置)」與羅漢
//   「powerup / 連擊」等絕招﹐其「無視防禦 / 連擊段數 / 火抗削減」屬 combat/perform
//   系統(非招式表)﹐標記為待辦。本檔先把帶「達摩烈焰」氣象的普攻刀招做實﹐與虎刀
//   tiger-blade、冷梅 hanshuang 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N寶刀一引佛火騰然﹐$w當頭一式『達摩開蒙』狠劈$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N腳下一個箭步搶進﹐$w化作一道烈焰連環疾斬$n的$l",
    "dodge":		-12,
    "attack":		7,
    "force":		10,
    "damage":		18,
    "damage_type":	"燒傷"
  ]),
  ([
    "action":		"$N沉腕翻刀﹐一式『面壁焚邪』$w凌空猛劈$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		17,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N默誦佛號刀挾禪火﹐一式『烈焰降魔』狠豁$n的$l",
    "dodge":		-12,
    "attack":		8,
    "force":		12,
    "damage":		19,
    "damage_type":	"燒傷"
  ]),
  ([
    "action":		"$N欺身搶進﹐$w以雷霆萬鈞之勢力劈$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		17,
    "damage_type":	"砍傷"
  ]),
  // —— 守勢式﹕達摩烈焰刀少數收勢之招﹐借勢回斬(正 dodge) ——
  ([
    "action":		"$N橫刀一引借勢卸力﹐隨即一式『迴鋒掠火』反撩$n的$l",
    "dodge":		6,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"燒傷"
  ]),
  ([
    "action":		"$N佯作退步避其鋒銳﹐刀走偏鋒斜削$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"砍傷"
  ]),
  // —— 殺著﹕達摩烈焰刀最盛一式﹐禪火暴漲、刀勢如焚 ——
  ([
    "action":		"$N周身佛火暴漲寶相莊嚴﹐一式『達摩涅槃』$w攜萬丈烈焰轟向$n的$l",
    "dodge":		-16,
    "attack":		12,
    "force":		16,
    "damage":		23,
    "damage_type":	"燒傷"
  ]),
});

string *interattack = ({
  "$N橫刀於胸刀身佛火明滅﹐殺氣如禪火蓄勢﹐只待破綻一現便要斬落。\n",
  "$N寶刀斜引烈焰繞身﹐刀勢蓄而不發﹐尋找著進招的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("damo blade");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("damo blade", "達摩烈焰刀");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (RED + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "damo blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
