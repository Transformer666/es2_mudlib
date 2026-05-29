// 慈顏除障手 buddha_zarn -- 寶蓮寺善想弟子的入門掌法
//
// 這是一門徒手(unarmed)武功招式﹐寶蓮寺善想一脈以慈悲化障的根本攻擊
// 掌法。本檔比照徒手招式 daemon (quanfa.c/unarmed.c) 的結構建立﹐故
// attack_using() 的第三參數是技能名(string skill)而非兵器﹐招式不依賴
// 兵器($w)﹐純以掌力施展。玩家透過 map_skill("unarmed","buddha_zarn")
// 將徒手招式對應到本掌法後﹐戰鬥時即以慈顏除障手的招式出手。
// 招式以掌力施展﹐借佛門慈悲之力化解魔障。
// TODO: combat specifics -- dodge/damage 數值與招式平衡待實戰調校。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N合什當胸﹐一式『慈航起手』緩緩推向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N沉肩墜肘﹐雙掌如蓮花般徐徐拍向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N默誦佛號﹐一式『普度迷津』掌風溫厚地罩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N腳踏蓮步﹐右掌畫了個圓圈柔中帶剛地按向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N雙掌一錯﹐一記綿掌綿綿不絕地搭上$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N寶相莊嚴﹐一式『慈顏除障』雙掌齊出推向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N後退半步﹐掌勢凝而後發﹐一掌沉沉印向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N慈眉低垂﹐一式『大悲無量』掌力如潮般捲向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N雙掌合什﹐口誦佛號﹐寶相慈和﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("buddha_zarn");
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

  damage = COMBAT_D->fight(me, opponent, "buddha_zarn", actions[random(sizeof(actions))]);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
