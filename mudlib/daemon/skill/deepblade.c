// 數字刀 deepblade -- 雪吟莊浪人的入門刀法（基礎技能 blade）
//
// 雪吟莊本門武功並無獨到﹐這一脈「數字刀」勝在剛猛綿密、招招進逼﹐
// 攻勢凌厲(docs/03-門派與武功/01-武者-五大門派.md §4 浪人﹕強化數字刀﹐
// 攻勢可破千﹐三不五時無視防禦必殺)﹐配合源自外邦天邪國的天邪神功
// (tianxie-force) 吐納施展﹐力道愈發雄渾。玩家透過
// map_skill("blade","deepblade") 將刀法對應到本招式後﹐戰鬥時
// COMBAT_D->fight() 即依本表施展招式。
//
// 本檔比照封山劍法 daemon/skill/fonxansword.c 複製﹐只是基礎兵器由
// sword 改為 blade（雪吟莊家丁慣用單刀﹐見 d/snowmanor/npc/retainer.c
// 與 yu_tieshan.c﹐皆 wield /obj/area/obj/blade）。
//
// 數字刀在中文字典(data/chinese.o)裡尚無對應詞條﹐故於 create() 時以
// CHINESE_D->add_translate() 自行登錄中文名「數字刀」﹐使 skills / score
// 等指令能顯示中文（to_chinese() 查無詞條時會原樣回傳英文 key﹐不致出錯﹐
// 此處主動登錄以求顯示工整）。
//
// TODO: 招式攻防數值待平衡（dodge / damage / damage_type）﹐目前比照
//       fonxansword 模板。浪人「攻勢可破千」「無視防禦必殺」等進階特效
//       (perform / 必殺判定) 待日後設計平衡﹐此處僅作基礎刀法。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N沉腕橫刀﹐$w自下而上撩向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式『一刀兩斷』﹐$w當頭直劈$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N腳下進步﹐$w化作一片寒光﹐連環疾斬$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N一招『數窮勢盡』﹐$w層層遞進逼向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N刀走偏鋒﹐$w斜挑而上撩向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式『天傾地裂』﹐$w平掃而出橫斬$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N側身一錯﹐$w凝而後發直劈$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N長身而起﹐一式『刀數無窮』縱身斬向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
});

string *interattack = ({
  "$N橫刀於胸﹐刀光微沉﹐殺氣凜然﹐凝神靜候出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("deepblade");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("deepblade", "數字刀");
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

  damage = COMBAT_D->fight(me, opponent, "deepblade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
