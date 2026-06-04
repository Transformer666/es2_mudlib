// 困天劍訣 kuntian-sword -- 玄天教四廠都督(二轉)的上乘控場劍法(基礎技能 sword)
//
// 玄天教書生投靠朝廷諜報機構「四廠」後可得的進階劍法(見 docs/03-門派與武功/
// 04-書生-步玄玄天.md §玄天教-搭配四廠﹕「玄天劍訣傷害提高 25%、困天 delay
// 提昇為 3」)。四廠都督以諜報心術佐玄天劍道﹐困天一脈劍勢縝密、料敵於先﹐封
// 困敵手、控其進退﹐乃玄天教控場(困天/定人)的極致。
//
// 由玄天劍訣(xuantian-jue)更進一階﹐配合四廠心法(sichang force)施展。本檔比照
// daemon/skill/xuantian-jue.c / xuantian-sword.c 的結構建立﹐使技能可被指派與
// 習練﹐並因是四廠秘傳的上乘劍訣再予加成(設計值)。困天劍訣在中文字典尚無詞條
// ﹐故於 create() 時以 CHINESE_D->add_translate() 自行登錄中文名「困天劍訣」。
//
// 設計(docs未明定確切數值)﹕招式傷害較玄天劍訣再高一階﹐供日後平衡微調。
// TODO(四廠控場完整化)：docs 載四廠玄天「玄天劍訣傷害提高 25%、困天 delay 提昇
//   為 3」﹐屬 perform/控場(困天)與四廠投靠(身分/聲望)系統﹐標記為待辦。本檔先
//   接通基本攻擊判定。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N足踏奇門遁甲之位﹐$w斜斜一封困住$n的$l",
    "dodge":		5,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『困天封鎖』﹐$w化作一片寒網罩向$n的$l",
    "dodge":		-5,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍隨星轉﹐一招『四廠合圍』盤旋封困$n的$l",
    "dodge":		-10,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N斂息凝神﹐$w如周天運行﹐後發先至直點$n的$l",
    "dodge":		-15,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身形遊走如諜影潛行﹐$w斜挑而上劃向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『機鋒鎖喉』﹐$w忽地繞向$n的$l要害",
    "dodge":		-5,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N長劍斜引蓄勢﹐$w凝而後發﹐一劍困住$n的$l",
    "dodge":		10,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足尖輕點﹐一式『困天倒懸』連環封斬向$n的$l",
    "dodge":		0,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐諜影暗藏﹐神色冷峻如算無遺策﹐料敵於先﹐靜待困敵的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("kuntian-sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("kuntian-sword", "困天劍訣");
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

  damage = COMBAT_D->fight(me, opponent, "kuntian-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
