// 太陰七損鞭 moon whip -- 天月庵神尼門下的入門鞭法
//
// 這是一門鞭(whip)武功招式﹐天月庵以太陰之力傷敵制人的根本攻擊鞭法。
// 本檔比照杖法招式 daemon (daemon/skill/rid-evil.c) 的結構建立﹐使技能可
// 被指派與習練﹐並透過 map_skill("whip","moon whip") 對應鞭招。招式以
// 鞭($w)施展﹐借太陰七損之勁傷敵筋骨。
//
// 兵器技能 key 為 "whip"：經查 feature/weapon/whip.c 的 setup_whip() 以
// init_damage(..., "whip") 登錄傷害﹐而 feature/char/attack.c 的攻擊迴圈
// 以 wielded_weapon mapping 的 key (即兵器 skill type "whip") 呼叫
// skill_mapped("whip")﹐故手持鞭(F_WHIP﹐如 obj/area/obj/whip.c 馬鞭、
// leather_whip.c 皮鞭)並 map_skill("whip","moon whip") 後即觸發本招式。
// 此與白象寺 staff→rid-evil 完全同構﹐"whip" 為既有且正確的鞭法 key。
//
// TODO: combat specifics -- dodge/damage 數值與招式平衡待實戰調校。
// TODO: 「七損」之減益(debuff)特性（損敵氣血/招式）為設計意圖﹐尚未接線。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手中$w一抖﹐一式『太陰起手』如銀蛇般捲向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N纖腕輕揚﹐$w化作一道寒光橫掃$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N嬌叱一聲﹐一式『月落寒潭』$w當頭抽向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N足踏太陰步﹐$w盤旋而下狠狠絞向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N手腕一沉﹐$w直挺挺地點向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N默運太陰真氣﹐一式『七損連環』$w連珠般纏向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N後退半步﹐$w凝而後發﹐如毒龍出洞般激射$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N清冷一笑﹐一式『太陰七損』$w攜森森月華暴卷$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
});

string *interattack = ({
  "$N纖手挽著$w﹐鞭梢隱隱透出一縷清冷月華﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("moon whip");
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

  damage = COMBAT_D->fight(me, opponent, "moon whip", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
