// 千葉掌法 buddha hands -- 白象寺「羅漢」進階(二轉)的高階掌法(基礎技能 unarmed)
//
// 白象寺羅漢一脈攻擊型的徒手掌法(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §白象寺-羅漢核心技能﹕「千葉掌法 buddha hands」)。掌開千葉、層層疊發﹐如千葉
// 寶蓮綻放﹐純以掌力降魔。比照徒手招式 daemon (quanfa.c/buddha_zarn.c/
// shanren-fist.c) 之模型建立﹐故 attack_using 第三參數是技能名(string skill)而非
// 兵器﹐招式不依賴兵器($w)。玩家透過 map_skill("unarmed","buddha hands") 對應後
// 即以千葉掌法的招式出手(羅漢進階時可自行在杖法/掌法間 map_skill 切換)。
//
// 因基礎技能為 unarmed(拳腳)﹐其 attack_using 簽名為 (me, opponent, string skill)﹐
// 無 weapon 物件﹐故 COMBAT_D->fight() 不傳 weapon﹐與 quanfa.c / shanren-fist.c
// 一致。中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹐供日後平衡微調﹕招式 damage 12~18
//   (入門 buddha_zarn 為 5~10)﹐高階式帶 "attack"(命中加成)與 "force"(吃羅漢降魔功
//   luohan force 的內力加成係數)。
//
// TODO(羅漢完整化)：docs 載羅漢「kee→heal、cc liuye、powerup」等絕招屬 combat/heal/
//   perform 系統(非招式表)﹐標記為待辦。本檔先把帶「千葉綻放」氣象的普攻掌招做實。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N合什當胸﹐一式『一葉知秋』掌風溫厚地推向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N沉肩墜肘﹐雙掌如千葉舒展層層拍向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		6,
    "damage":		14,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N默誦佛號﹐一式『千葉重台』掌力綿綿不絕地罩向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N腳踏蓮步﹐右掌畫了個圓圈柔中帶剛地按向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N雙掌一錯﹐一式『蓮開見佛』掌勢層疊搭上$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  // —— 守勢式﹕千葉掌法綿守之招﹐借勢回拍(正 dodge) ——
  ([
    "action":		"$N掌勢一引借力卸勁﹐隨即一式『落葉迴風』反拍$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		6,
    "damage":		13,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N後退半步避其鋒銳﹐掌勢凝而後發沉沉印向$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		6,
    "damage":		13,
    "damage_type":	"瘀傷"
  ]),
  // —— 殺著﹕千葉掌法最盛一式﹐千葉齊綻、掌力如潮 ——
  ([
    "action":		"$N寶相莊嚴﹐一式『千葉降魔』雙掌齊出掌力如潮般捲向$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		12,
    "damage":		18,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N雙掌合什﹐口誦佛號﹐寶相慈和﹐靜待出手的時機。\n",
  "$N雙掌緩緩游走如千葉舒卷﹐掌勢蓄而不發﹐尋找著進招的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("buddha hands");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("buddha hands", "千葉掌法");
  setup();
}

void
attack_using (object me, object opponent, string skill)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (YEL + interattack[random(sizeof(interattack))] + NOR, me, opponent);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "buddha hands", actions[random(sizeof(actions))]);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
