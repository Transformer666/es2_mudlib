// 鷹爪功 eagle-claw -- 隱教「金蛇門人」入門即習的招牌徒手武功(基礎技能 unarmed)
//
// 隱教隱於野羊山深處﹐自金蛇門一脈分出﹐專事潛行暗殺。其招牌核心招式「鷹爪
// 功」乃獨步武林的徒手搏鬥之術(見 docs/03-門派與武功/05-盜賊-瑯夷隱教.md
// §2 隱教-核心招式﹕「鷹爪功﹕獨步武林的徒手搏鬥」﹐並搭配 backstab)。十指
// 屈如鷹爪﹐抓、撕、扣、鎖﹐快狠刁鑽﹐專攻敵手要害關竅﹐見血封喉。
//
// 比照徒手招式 daemon (daemon/skill/shanren-fist.c / buddha-hands.c / quanfa.c)
// 之 actions 招式表模型建立﹐故 attack_using 第三參數是技能名(string skill)而非
// 兵器﹐招式不依賴兵器($w)。玩家透過 map_skill("unarmed","eagle-claw") 對應後
// 即以鷹爪功的招式出手(隱教 master 入門授技時掛上﹐見 d/yinjiao/npc/master.c)。
//
// 因基礎技能為 unarmed(拳腳)﹐其 attack_using 簽名為 (me, opponent, string skill)﹐
// 無 weapon 物件﹐故 COMBAT_D->fight() 不傳 weapon﹐與 shanren-fist.c 一致。
// 命中與傷害一律走既有 COMBAT_D->fight() 引擎﹐本檔僅提供招式表﹐不臆造數值公式。
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「鷹爪功」。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹐比照範本尺度供日後平衡微調﹕
//   招式 damage 12~18(入門 quanfa 為 5~10)﹐高階式帶 "attack"(命中加成)與
//   "force"(吃隱教內功 fade shadow / yinjiao force 的內力加成係數﹐見 combatd.c::
//   fight() 之 force_bonus 公式)。隱教「全憑一身機敏、抓撕刁鑽」﹐故守勢式取正
//   dodge、身法輕靈﹐殺著一式內勁灌注、抓筋鎖喉。
//
// TODO(隱教完整化)：docs 載鷹爪功「搭配 backstab(背刺)」、另有「殺手本能 / 攻勢
//   等級」等屬 perform/combat 系統(非招式表)﹐標記為待辦。本檔先把帶「鷹爪抓撕」
//   氣象的普攻招式做實﹐與冷梅、封山、白象諸進階徒手招式同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N十指箕張屈如鷹爪﹐一式『餓鷹擒兔』疾抓$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N身形一矮欺近﹐雙爪如鷹一式『雙鷹奪食』疾扣$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		6,
    "damage":		14,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N腳下一錯側身游走﹐一爪『鷹翻雲際』反手撕向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N指力暗吐﹐一式『摧鋒折翼』屈指狠扣$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N驟然拔身而起﹐一式『鷹擊長空』居高撲抓$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  // —— 守勢式﹕隱教「全憑一身機敏」之意﹐身法輕靈、卸力反抓(正 dodge) ——
  ([
    "action":		"$N側身一卸借力游走﹐隨即一爪『盤鷹回旋』反扣$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		6,
    "damage":		13,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N佯作飄退避其鋒銳﹐忽地一爪『落雁驚鴻』撕向$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"瘀傷"
  ]),
  // —— 殺著﹕鷹爪功最盛一式﹐內勁灌注十指、抓筋鎖喉、見血封喉 ——
  ([
    "action":		"$N周身殺氣陡盛﹐一式『鷹搏狡兔』雙爪挾內勁直鎖$n的咽喉要害",
    "dodge":		-12,
    "attack":		10,
    "force":		12,
    "damage":		18,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N十指微屈如鷹爪﹐身形輕靈游走﹐冷冷凝視著$n的破綻。\n",
  "$N雙爪緩緩游移﹐爪勢蓄而不發﹐如餓鷹盤旋﹐尋找著進招的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("eagle-claw");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("eagle-claw", "鷹爪功");
  setup();
}

void
attack_using (object me, object opponent, string skill)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (CYN + interattack[random(sizeof(interattack))] + NOR, me, opponent);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "eagle-claw", actions[random(sizeof(actions))]);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
