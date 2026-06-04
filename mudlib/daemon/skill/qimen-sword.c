// 奇門劍訣 qimen-sword -- 步玄派「奇門劍士」進階(二轉)的奇門控場劍法(基礎技能 sword)
//
// 步玄派書生投身奇門遁甲之術﹐由入門「小步玄劍 buxuan-sword」精進而成的
// 上乘劍訣(見 docs/03-門派與武功/04-書生-步玄玄天.md §步玄派-搭配四廠/
// 居士進階「累積七點後發動奇門劍訣 ── 出招機率跟 int 有關、發招次數跟
// 五行有關、威力跟古文有關」﹔§居士進階「乾坤三轉…同時下次攻擊觸發奇門
// 劍訣」)。奇門劍訣以五行奇門佈陣、料敵機先﹐劍走奇正相生、封困敵手﹐
// 乃步玄居士控場(奇門/定人)的看家劍訣。
//
// 配合乾坤三轉心法(qiankun-force)施展。本檔比照 daemon/skill/aomei-sword.c /
// xuantian-jue.c 的招式表模型建立﹐使技能可被指派與習練﹐並因是奇門上乘
// 劍訣較入門小步玄劍再高一階(設計值)。奇門劍訣在中文字典尚無詞條﹐故於
// create() 時以 CHINESE_D->add_translate() 自行登錄中文名。
//
// 數值為本次設計值(docs 只給機制非確切數字)﹐供日後平衡微調。
// TODO(奇門 perform 完整化)：docs 載奇門劍訣「累積七點後發動、出招機率跟 int
//   有關、發招次數跟五行有關、威力跟古文有關」﹐屬 perform/奇門點數系統(同
//   乾坤三轉「下次攻擊觸發奇門劍訣」)﹐標記為待辦。本檔先接通基本攻擊判定。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N足踏奇門遁甲之位﹐$w斜斜一引封向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『五行錯位』﹐$w化作一道青芒掠向$n的$l",
    "dodge":		-10,
    "attack":		6,
    "force":		8,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍隨奇門遁轉﹐一招『奇正相生』盤旋直點$n的$l",
    "dodge":		-12,
    "attack":		8,
    "force":		10,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N斂息布陣﹐$w如周天運行﹐後發先至直貫$n的$l",
    "dodge":		-15,
    "attack":		8,
    "force":		12,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N側身遊走如奇門換位﹐$w斜挑而上劃向$n的$l",
    "dodge":		-10,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
  // —— 控場一脈﹕正 dodge﹐封困敵手、先守後發之勢 ——
  ([
    "action":		"$N斂劍半步﹐一式『奇門封鎖』封住$n進退﹐待勢老即還斬向$n的$l",
    "dodge":		8,
    "attack":		10,
    "force":		14,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N長劍凝而不發﹐隨$n破綻一現﹐$w如奇門驚變直透$n的$l",
    "dodge":		10,
    "attack":		8,
    "force":		12,
    "damage":		18,
    "damage_type":	"刺傷"
  ]),
  // —— 殺著﹕奇門劍訣最盛一式﹐五行齊發、奇門大成 ——
  ([
    "action":		"$N足尖輕點﹐一式『奇門劍訣』五行劍氣連環攢向$n的$l",
    "dodge":		-15,
    "attack":		12,
    "force":		18,
    "damage":		22,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐足布奇門﹐神色不動如觀星問道﹐料敵於先﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("qimen-sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("qimen-sword", "奇門劍訣");
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

  damage = COMBAT_D->fight(me, opponent, "qimen-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
