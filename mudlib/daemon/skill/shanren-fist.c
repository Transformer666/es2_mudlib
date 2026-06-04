// 封山伏虎拳 shanren-fist -- 封山派「山人」進階(二轉)的高階拳法(基礎技能 unarmed)
//
// 山人一脈捨劍習拳﹐是 ES2 唯二使用拳法的武者門派之一(見 docs/03-門派與
// 武功/01-武者-五大門派.md §1 封山派-山人)。本拳法由入門拳腳 unarmed 精進
// 而成﹐比照 daemon/skill/quanfa.c 之 actions 招式表模型建立﹐但更強﹕招式
// damage 係數更高、另帶 "attack"(命中加成)與 "force"(吃山人心法 shanren_force
// 的內力加成係數﹐見 combatd.c::fight() 之 force_bonus 公式)。山人「類似拳法
// 但可定人 / 打擊精 / 氣﹐穿移動力裝﹐極靈活」(評分 攻擊 C+ / 防禦 C /
// 續戰 C+ / 靈活 A)﹐故本表招式身法輕靈、纏鬥綿密。
//
// 因基礎技能為 unarmed(拳腳)﹐玩家透過 map_skill("unarmed","shanren-fist")
// 對應後即可施展(同 daemon/skill/buddha_zarn.c 的拳法掛法)。注意 unarmed 的
// attack_using 簽名為 (me, opponent, string skill)﹐無 weapon 物件﹐故
// COMBAT_D->fight() 不傳 weapon﹐與 quanfa.c 一致。
//
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「封山伏虎拳」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 12~18(入門 quanfa 為 5~10)﹐高階式帶 attack 5~10 與 force 6~12。
//
// TODO(山人完整化)：docs 載山人可「定人 / 打擊精 / 氣」﹐其定身與打擊
//   精(gin)/氣(kee)屬 combat/perform 系統(非招式表)﹐標記為待辦。本檔先把
//   普攻拳招做實﹐與冷梅諸進階招式同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉腰坐馬﹐一記『伏虎沉橋』直拳搶攻$n的$l",
    "dodge":		-5,
    "attack":		5,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N欺身上前﹐雙掌如山一式『青嶂排雲』推向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		6,
    "damage":		14,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N腳下一錯﹐一記橫肘藉山勢沉沉撞向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N身形輕靈一矮﹐一式『伏虎撩陰』由下而上撩向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N大喝一聲﹐右掌挾內勁一式『風落千巖』劈向$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		8,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  // —— 守勢﹕山人「極靈活、纏鬥」之意﹐正 dodge、身法圓融 ——
  ([
    "action":		"$N步隨身轉圓融如環﹐一式『游山步』纏住$n﹐順勢反撩$n的$l",
    "dodge":		10,
    "attack":		5,
    "force":		6,
    "damage":		13,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N佯作後退避其鋒銳﹐隨即一掌『回峰探掌』反撩$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"瘀傷"
  ]),
  // —— 殺著﹕封山伏虎拳最盛一式﹐內勁灌注、拳沉如嶽 ——
  ([
    "action":		"$N周身內勁鼓盪﹐一式『伏虎降龍』雙拳挾雷霆之勢轟向$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		12,
    "damage":		18,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N擺開拳架﹐身形輕靈如山雲流轉﹐凝神注視著$n的動靜。\n",
  "$N雙拳緩緩游走﹐拳勢蓄而不發﹐尋找著進招的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("shanren-fist");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("shanren-fist", "封山伏虎拳");
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

  damage = COMBAT_D->fight(me, opponent, "shanren-fist", actions[random(sizeof(actions))]);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
