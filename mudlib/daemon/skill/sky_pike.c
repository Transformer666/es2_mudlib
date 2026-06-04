// 穹槍訣 sky_pike -- 天月庵「太陰尊者」進階(二轉)的高階槍法(基礎技能 pike)
//
// 天月庵核心技能明列「穹槍訣 sky_pike」(見 docs/03-門派與武功/03-和尚-寶蓮
// 天月白象.md §天月庵-核心技能﹔英文 key 即 sky_pike)。data/chinese.o 已有
// key "sky_pike":"穹槍訣"。此為天月庵以槍演太陰之意的上乘槍法﹐槍走長遠、
// 一槍貫頂如皓月當空、清光照野﹐攻勢沉長而暗藏寒勁﹐並帶 force 係數吃太陰
// 真經(taiyin force)的內力。基礎技能為 pike(槍法)。
//
// 因基礎技能為 pike(槍法)﹐玩家透過 map_skill("pike","sky_pike") 對應後即可持槍
// 施展(太陰尊者進階時師父自動掛上此映射)。比照 daemon/skill/serpent-pike.c
// (蛇形槍法)、sky-sword.c(穹劍訣)之 actions 招式表模型建立。attack_using 第三
// 參數為兵器物件(weapon)﹐故 COMBAT_D->fight() 傳 weapon。
//
// 字典已有此 key﹐仍以 CHINESE_D->add_translate() 重登錄以求自足(idempotent)。
//
// 數值為本次設計值(docs 只給技能名非確切數字)﹐供日後平衡微調﹕招式 damage
//   12~18(槍法沉長重擊)﹐dodge 多負(長兵搶攻、破綻較大)﹐高階式帶 force 吃內力。
//
// TODO(穹槍訣完整化)：docs 大內版穹槍訣載「神威下攻擊對目標精傷、按陰陽五行
//   技能」(見 sky-sword.c 註)﹐天月庵版以太陰之意承之﹐精傷/特效屬 combat/perform
//   系統(非招式表)﹐標記為待辦﹔本檔先把帶皓月貫頂氣象的高階槍招做實。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N長槍一引如皓月初升﹐$w一式『穹頂連環』沉沉刺向$n的$l",
    "dodge":		-8,
    "damage":		12,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N沉腰墜肘灌勁於槍﹐$w一式『清光貫野』直搗$n的$l",
    "dodge":		-12,
    "attack":		6,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足踏太陰步槍走長遠﹐$w攜寒勁當頭貫向$n的$l",
    "dodge":		-10,
    "force":		8,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一聲清嘯勁貫槍身﹐$w化作一道月華長虹掃向$n的$l",
    "dodge":		-14,
    "attack":		8,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N槍走中宮以正禦邪﹐$w借勢一頓沉沉壓向$n的$l",
    "dodge":		-6,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N默運太陰真氣鼓盪槍身﹐$w寒芒暴漲直取$n的$l",
    "dodge":		-12,
    "force":		10,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N退步凝槍蓄勢待發﹐借勢一記寒槍貫向$n的$l",
    "dodge":		2,
    "force":		8,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕穹槍訣盡展﹐皓月當空、一槍貫頂 ——
  ([
    "action":		"$N周身太陰真氣盡灌槍身﹐一式『皓月貫頂』$w攜當空清光儘數貫向$n的$l",
    "dodge":		-16,
    "attack":		12,
    "force":		14,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N長槍斜引月華流轉﹐沉腰蓄勁如滿弓﹐寒勁鼓盪﹐只待一槍貫頂。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("sky_pike");
  // 字典已有 "sky_pike":"穹槍訣"﹐仍重登錄以求自足(idempotent)。
  CHINESE_D->add_translate("sky_pike", "穹槍訣");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIW + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "sky_pike", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
