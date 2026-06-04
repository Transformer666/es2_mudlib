// 雨花劍法 rain-flower sword -- 天月庵「雨花仙子」進階(二轉)的高階劍法(基礎技能 sword)
//
// 天月庵核心技能明列「雨花劍法 rain-flower sword」(見 docs/03-門派與武功/
// 03-和尚-寶蓮天月白象.md §天月庵-核心技能)。此為天月庵以劍演太陰之意的上乘
// 劍法﹐劍勢輕靈飄逸、漫天劍光如天女散花、似驟雨梨花﹐清冷之中暗藏鋒芒﹐
// 故招式 dodge 多平實偏正(輕靈難測)、damage 綿密如雨﹐並帶 force 係數吃太陰真經
// (taiyin force)的內力。基礎技能為 sword(劍法)。
//
// 因基礎技能為 sword(劍法)﹐玩家透過 map_skill("sword","rain-flower sword") 對應後
// 即可持劍施展(雨花仙子進階時師父自動掛上此映射)。比照 daemon/skill/shenmang-sword.c
// (神芒劍)、aomei-sword.c(傲梅暗劍訣)之 actions 招式表模型建立。attack_using 第三
// 參數為兵器物件(weapon)﹐故 COMBAT_D->fight() 傳 weapon。
//
// 注意：key 含空白(「rain-flower sword」)﹐故檔名以連字號代之(rain-flower-sword.c)﹐
// register/translate 用的 key 仍為含空白原名。字典查無此 key﹐以
// CHINESE_D->add_translate() 自行登錄中文名「雨花劍法」。
//
// 數值為本次設計值(docs 只給技能名非確切數字)﹐供日後平衡微調﹕招式 damage
//   10~16﹐dodge 多平實偏正(輕靈飄逸)﹐高階式帶 force 8~12 吃太陰真經內力。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N腕走輕靈﹐$w一式『梨花初綻』漫天劍光點向$n的$l",
    "dodge":		3,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N劍尖一顫如天女散花﹐$w化作千點劍芒灑向$n的$l",
    "dodge":		5,
    "damage":		12,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足踏太陰步﹐$w如驟雨梨花密匝匝地刺向$n的$l",
    "dodge":		2,
    "force":		6,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身形飄逸劍走輕雲﹐一式『雨花滿天』$w綿綿不絕地纏向$n的$l",
    "dodge":		6,
    "damage":		12,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N清冷一笑﹐$w如冷雨澆花﹐一式『花落知多少』漫卷$n的$l",
    "dodge":		0,
    "force":		8,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N默運太陰真氣灌於劍身﹐$w寒芒暴漲直取$n的$l",
    "dodge":		-3,
    "attack":		6,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N退步凝劍輕雲蔽月﹐後發一劍斜挑$n的$l",
    "dodge":		8,
    "force":		8,
    "damage":		12,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕雨花劍法盡展﹐漫天劍雨、月華傾瀉 ——
  ([
    "action":		"$N周身太陰真氣盡灌劍身﹐一式『雨打梨花』$w化作漫天劍雨傾瀉而下﹐儘數罩向$n的$l",
    "dodge":		2,
    "attack":		8,
    "force":		12,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引清光流轉﹐身形輕靈如御風﹐漫天劍意似雨欲落﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("rain-flower sword");
  // 字典查無此 key﹐自行登錄中文名「雨花劍法」。
  CHINESE_D->add_translate("rain-flower sword", "雨花劍法");
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

  damage = COMBAT_D->fight(me, opponent, "rain-flower sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
