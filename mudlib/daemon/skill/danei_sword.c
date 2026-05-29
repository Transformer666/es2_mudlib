// 大內劍法 danei sword -- 大內巡院統領的入門劍法（基礎技能 sword）
//
// 本檔比照振武軍營的龍神槍法 daemon/skill/dragon_god.c 複製﹐只是基礎
// 兵器由 pike 改為 sword（大內巡院的緝事官員慣用三尺長劍﹐見
// d/capital/npc/patrolman.c）。玩家透過 map_skill("sword","danei sword")
// 將劍法對應到本招式後﹐戰鬥時 COMBAT_D->fight() 即依本表施展招式。
//
// 大內劍法在中文字典(data/chinese.o)裡尚無對應詞條﹐故於 create() 時以
// CHINESE_D->add_translate() 自行登錄中文名「大內劍法」﹐使 skills / score
// 等指令能顯示中文（to_chinese() 查無詞條時會原樣回傳英文 key﹐不致出錯﹐
// 此處主動登錄以求顯示工整）。
//
// TODO: 招式攻防數值待平衡（dodge / damage / damage_type），目前比照
//       dragon_god / lunmay 模板。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉肩墜肘﹐手中$w平刺而出﹐一式『天闕初開』直取$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腕底一翻﹐$w化作一片寒光﹐當頭劈向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N足下錯步﹐一招『宿衛巡天』﹐$w自下撩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N沉身進步﹐$w如游龍出水﹐連環疾刺$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N劍尖一顫﹐抖出朵朵劍花﹐儘數罩向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『金鑾橫掃』﹐$w平掃而出﹐橫斬$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N側身一閃﹐$w凝而後發﹐一劍貫向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N長身而起﹐一式『大內擒龍』縱身刺向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐劍尖微垂﹐如宿衛按劍待命﹐凝神靜候破綻。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("danei sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("danei sword", "大內劍法");
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

  damage = COMBAT_D->fight(me, opponent, "danei sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
