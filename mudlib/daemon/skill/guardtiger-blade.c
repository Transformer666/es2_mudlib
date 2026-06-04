// 猛虎護身刀 guardtiger blade -- 虎刀門「護衛」進階(二轉)的高階刀法(基礎技能 blade)
//
// 設計(docs未明定)：護衛是虎刀門最早開放的二轉(見 docs/03-門派與武功/
// 01-武者-五大門派.md §5 虎刀門-護衛)﹐docs 載其特色為「一招定技、100% 出
// 第一追、powerup 後恢復力大量提升、deathwish(powerup 下每 tick 回 1000 氣
// 1000 精並 delay 目標)」(評分 攻擊 A- / 防禦 C / 續戰 A / 靈活 B)。docs 並
// 未替護衛命名一套新刀法(其特色為定技與 powerup 狀態)﹐故本招式名「猛虎護身
// 刀 guardtiger blade」為本次設計值﹐用以承載護衛「攻守兼備、續戰持久」的招式
// 氣象﹔字典 data/chinese.o 查無此 key﹐以 add_translate 自行登錄中文名。
//
// 比照 daemon/skill/bawang_blade.c 之 actions 招式表模型建立﹐較入門略強並帶
// "attack"/"force" 係數(吃虎刀心法 hudao force 的內力加成﹐見 combatd.c::fight()
// force_bonus 公式)﹐damage 中庸、守勢招(正 dodge)較多以體現護衛的「續戰 A、
// 防禦尚可」定位。基礎技能為 blade(刀法)。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 12~18(入門 bawang blade 為 5~10)﹐高階式帶 attack 5~10 與 force 6~12。
//
// TODO(護衛完整化)：docs 載護衛有「一招定技、第一追、powerup、deathwish」﹐其
//   定身、追擊、powerup 狀態與 deathwish 回氣回精屬 combat/perform 系統(非招式
//   表)﹐標記為待辦。本檔先把普攻刀招做實﹐與虎刀 tiger-blade、冷梅 hanshuang
//   同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉腰按刀﹐$w一式『猛虎守山』穩穩劈向$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		12,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N腳下一錯﹐$w一式『虎踞待撲』搶攻$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		6,
    "damage":		14,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N大喝一聲﹐$w化作一道沉光直劈$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N欺身搶進﹐一式『護身斷刃』$w橫掃$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  // —— 守勢式﹕護衛「續戰、攻守兼備」之意﹐正 dodge、沉穩固守(較多) ——
  ([
    "action":		"$N橫刀於身前一式『虎背藏鋒』凝守待機﹐借勢回劈$n的$l",
    "dodge":		10,
    "attack":		6,
    "force":		8,
    "damage":		13,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N沉刀蓄勢隨$n勢老﹐$w沉穩後發豁向$n的$l",
    "dodge":		10,
    "attack":		7,
    "force":		8,
    "damage":		14,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N佯作退步避其鋒銳﹐隨即一式『反虎噬』反撩$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		6,
    "damage":		13,
    "damage_type":	"割傷"
  ]),
  // —— 殺著﹕猛虎護身刀蓄勁一擊﹐守而後發、刀沉如山 ——
  ([
    "action":		"$N周身內勁鼓盪﹐一式『猛虎下山』$w挾雷霆之勢力劈$n的$l",
    "dodge":		-10,
    "attack":		10,
    "force":		12,
    "damage":		18,
    "damage_type":	"砍傷"
  ]),
});

string *interattack = ({
  "$N橫刀於胸沉腰落樁穩如山嶽﹐凝神注視著$n的動靜﹐攻守之勢蓄而不發。\n",
  "$N按刀而立刀尖斜指﹐殺氣內蘊如猛虎守山﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("guardtiger blade");
  // 字典查無此 key﹐自行登錄中文名「猛虎護身刀」。
  CHINESE_D->add_translate("guardtiger blade", "猛虎護身刀");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIY + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "guardtiger blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
