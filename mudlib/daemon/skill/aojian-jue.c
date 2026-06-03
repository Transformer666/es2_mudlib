// 傲劍絕 aojian-jue -- 冷梅莊「古劍門傳人」進階(二轉)的右手劍法(基礎技能 sword)
//
// 古劍門傳人﹕右手「傲劍絕」、左手「傲梅劍」﹐最新版推薦雙握劍(見
// docs/03-門派與武功/01-武者-五大門派.md §2 冷梅莊-古劍門傳人﹐評分
// 攻擊 B / 防禦 A+ / 續戰 A+ / 靈活 C)。古劍門「劍招華麗但缺乏威力——
// 是打不死的蟑螂」﹐故本表 damage 係數中庸(較劍士傲梅暗劍訣為低)﹐但多帶
// 正 dodge 防禦招式﹐重在防守、續戰與「每使出一次 parry 即回 kee」的纏鬥。
//
// 比照 daemon/skill/lunmay.c 之 actions 招式表模型建立。玩家透過
// map_skill("sword","aojian-jue") 對應後﹐戰鬥時 COMBAT_D->fight() 即依本表
// 施展招式。古劍門「靠手動 perform 絕招(無視防禦)」與「parry 回 kee」屬戰
// 鬥外掛機制﹐本招式 daemon 只負責普攻招式表﹐perform/回 kee 為未來工作。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行
// 登錄中文名「傲劍絕」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 12~16(介於入門 lunmay 與劍士傲梅暗劍訣之間)﹐多式帶正 dodge
//   體現「打不死」的高防續戰特性。
//
// TODO(古劍門完整化)：手動 perform「傲劍絕」無視防禦絕招、parry 成功回 kee
//   的戰鬥機制(屬 combat/perform 系統﹐非招式表)。本檔先把普攻劍法做實。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N右手$w平引而出﹐一式『古劍含光』穩穩刺向$n的$l",
    "dodge":		0,
    "attack":		5,
    "damage":		12,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N右腕一沉﹐$w如古松盤虯﹐迴身斬向$n的$l",
    "dodge":		5,
    "attack":		5,
    "damage":		14,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式『傲劍橫江』﹐右手$w大開大闔橫掃$n的$l",
    "dodge":		-8,
    "attack":		6,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N右手劍勢一緩﹐隨即驟疾﹐$w連環疾點$n的$l",
    "dodge":		-5,
    "attack":		6,
    "damage":		14,
    "damage_type":	"刺傷"
  ]),
  // —— 守勢﹕古劍門「打不死」的根本﹐正 dodge、纏鬥續戰 ——
  ([
    "action":		"$N斂右手劍於懷﹐一式『古劍封塵』凝守待機﹐劍尖虛指$n的$l",
    "dodge":		12,
    "attack":		4,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N右手劍圓轉如環﹐先守後攻﹐$w隨$n勢老回刺$n的$l",
    "dodge":		10,
    "attack":		6,
    "damage":		13,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『古木逢春』﹐右手$w綿綿不絕地纏向$n的$l",
    "dodge":		8,
    "attack":		5,
    "damage":		12,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N右手劍光暴漲﹐一式『傲劍絕』華光萬丈罩向$n的$l",
    "dodge":		-10,
    "attack":		8,
    "damage":		16,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N右手古劍斜垂﹐劍身古樸無華﹐神色從容如老樹臨風﹐靜候$n的破綻。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("aojian-jue");
  CHINESE_D->add_translate("aojian-jue", "傲劍絕");
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

  damage = COMBAT_D->fight(me, opponent, "aojian-jue", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
