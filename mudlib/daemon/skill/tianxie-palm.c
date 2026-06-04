// 天邪神掌 tianxie-palm -- 雪吟莊「天邪派弟子(神掌)」進階(二轉)的掌法(基礎技能 unarmed)
//
// 神掌一脈乃雪吟莊最高規格的二轉(見 docs/03-門派與武功/01-武者-五大門派.md
// §4 雪吟莊-天邪派弟子(神掌)﹕「『神掌』顧名思義不需要武器、擁有天邪虎嘯
// 牽制敵人/補血/定人/群體攻擊、超高血量(血牛)、陰陽眼+全體攻擊+補血+定人+
// 無視防禦」)。神掌不持兵刃﹐故基礎技能掛 unarmed(拳腳/掌法)——比照
// daemon/skill/shanren-fist.c 之 actions 招式表模型建立﹐招式 damage 係數高、
// 帶 "attack"(命中加成)與 "force"(吃天邪神功 tianxie-force 的超高 kee﹐見
// combatd.c::fight() force_bonus)﹐以體現神掌挾天邪真氣、掌挾煞風的詭烈。
//
// 因基礎技能為 unarmed﹐玩家透過 map_skill("unarmed","tianxie-palm") 對應後
// 即可施展(同 shanren-fist.c 的拳掌掛法)。注意 unarmed 的 attack_using 簽名
// 為 (me, opponent, string skill)﹐無 weapon 物件﹐故 COMBAT_D->fight() 不傳
// weapon﹐與 shanren-fist.c / quanfa.c 一致。神掌另由師父一併授予「天邪虎嘯
// tianxie-roar」(既有 daemon)作牽制群攻之能﹐玩家可自行配置使用。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「天邪神掌」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 13~18﹐高階式帶 attack 6~10 與 force 8~16﹐damage_type 取「邪氣」
//   呼應天邪一脈(同 tianxie-roar.c)。
//
// TODO(神掌完整化)：docs 載神掌「陰陽眼+全體攻擊+補血+定人+無視防禦、血牛」﹐
//   群攻/補血/定人/陰陽眼/無視防禦/超高血量等皆屬 combat/perform 系統(非招式表)﹐
//   標記為待辦。本檔先把掌法普攻做實﹐牽制群攻交由一併授予的天邪虎嘯承載。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉肩墜肘﹐一式『天邪推雲』掌挾陰風推向$n的$l",
    "dodge":		-5,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N欺身上前﹐雙掌如淵一式『陰陽奪魄』拍向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		10,
    "damage":		14,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N足下一頓﹐掌心天邪真氣鼓盪﹐一式『邪嘯穿心』直透$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		12,
    "damage":		15,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N身形詭譎一晃﹐左右雙掌挾煞氣連環拍擊$n的$l",
    "dodge":		-8,
    "attack":		7,
    "force":		12,
    "damage":		15,
    "damage_type":	"邪氣"
  ]),
  // —— 控場/牽制式﹕神掌煞氣瀰漫、震懾奪神(正 dodge) ——
  ([
    "action":		"$N掌風所至一片陰冷﹐天邪煞氣瀰漫欲奪$n心神﹐順勢一掌削向$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		10,
    "damage":		14,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N斂掌蓄勢﹐天邪真氣盤旋如淵﹐隨$n勢老一掌反拍$n的$l",
    "dodge":		10,
    "attack":		7,
    "force":		12,
    "damage":		14,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N佯作虛引避其鋒銳﹐隨即一式『回風摧魂』陰冷掌力反震$n的$l",
    "dodge":		8,
    "attack":		7,
    "force":		12,
    "damage":		15,
    "damage_type":	"邪氣"
  ]),
  // —— 殺著﹕天邪神掌最盛一式﹐周身煞氣沖天、掌挾風雷 ——
  ([
    "action":		"$N周身天邪煞氣沖天﹐一式『天邪神掌』掌挾風雷之勢罩向$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		16,
    "damage":		18,
    "damage_type":	"邪氣"
  ]),
});

string *interattack = ({
  "$N雙掌緩緩游走﹐周身天邪煞氣陰冷詭譎﹐隱隱似有風雷低鳴﹐凜然不可逼視。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("tianxie-palm");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("tianxie-palm", "天邪神掌");
  setup();
}

void
attack_using (object me, object opponent, string skill)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (MAG + interattack[random(sizeof(interattack))] + NOR, me, opponent);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "tianxie-palm", actions[random(sizeof(actions))]);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
