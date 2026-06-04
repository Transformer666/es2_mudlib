// 摧魂鞭法 destruction whip -- 天月庵「摧魂使者」進階(二轉)的高階鞭法(基礎技能 whip)
//
// 天月庵核心技能明列「摧魂鞭法 destruction whip」(見 docs/03-門派與武功/
// 03-和尚-寶蓮天月白象.md §天月庵-核心技能)。由入門太陰七損鞭(moon whip)精進
// 而成﹐鞭走詭譎森寒、攝魂奪魄﹐七損之勁化作摧魂之厲﹐攻勢凌厲而暗藏削元之意。
//
// 因基礎技能為 whip(鞭法)﹐玩家透過 map_skill("whip","destruction whip") 對應後
// 即可持鞭施展(摧魂使者進階時師父自動掛上此映射)。比照入門 moon-whip.c 與白象
// 進階 zen-staff.c 之 actions 招式表模型建立。attack_using 第三參數為兵器物件
// (weapon)﹐故 COMBAT_D->fight() 傳 weapon﹐與 moon-whip.c 一致。
//
// 注意：key 含空白(「destruction whip」)﹐故檔名以連字號代之(destruction-whip.c)﹐
// register/translate 用的 key 仍為含空白原名。字典查無此 key﹐以
// CHINESE_D->add_translate() 自行登錄中文名「摧魂鞭法」。
//
// 數值為本次設計值(docs 只給技能名非確切數字)﹐供日後平衡微調﹕招式 damage
//   10~16(高於入門太陰七損鞭)﹐dodge 多負(搶攻凌厲)﹐殺著帶高傷。
//
// TODO(摧魂特效)：docs 摧魂鞭法之「摧魂(削神/奪志)」debuff 屬 combat/perform
//   系統(非招式表)﹐標記為待辦﹔本檔先把帶森寒攝魂氣象的高階鞭招做實﹐與
//   moon-magic 諸控制特效之 TODO 同一範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N纖腕一抖﹐$w化作一道森寒銀光﹐一式『摧魂起手』攝向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N嬌叱一聲﹐$w盤旋如毒龍﹐一式『奪魄連環』狠狠絞向$n的$l",
    "dodge":		-10,
    "damage":		13,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N足踏太陰步﹐$w攜森森月華當頭暴抽$n的$l",
    "dodge":		-12,
    "attack":		6,
    "damage":		14,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N腕走詭譎難測﹐一式『月落黃泉』$w如鬼魅般點向$n的$l",
    "dodge":		-15,
    "damage":		13,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N清冷一笑﹐$w化作千道寒芒密匝匝地纏向$n的$l",
    "dodge":		-8,
    "force":		6,
    "damage":		13,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N默運太陰真氣﹐$w森寒徹骨﹐一式『攝魂奪志』直取$n的$l",
    "dodge":		-10,
    "attack":		8,
    "damage":		14,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N退步凝勁後發﹐$w如出洞毒龍激射$n的$l",
    "dodge":		3,
    "force":		8,
    "damage":		13,
    "damage_type":	"鞭傷"
  ]),
  // —— 殺著﹕摧魂鞭法盡展﹐月華暴湧、攝魂奪魄 ——
  ([
    "action":		"$N周身太陰真氣暴漲﹐一式『摧魂奪魄』$w攜森森月華沖天暴卷$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		10,
    "damage":		16,
    "damage_type":	"鞭傷"
  ]),
});

string *interattack = ({
  "$N纖手挽著$w﹐鞭梢隱隱透出一縷森寒月華﹐攝人心魄地靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("destruction whip");
  // 字典查無此 key﹐自行登錄中文名「摧魂鞭法」。
  CHINESE_D->add_translate("destruction whip", "摧魂鞭法");
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

  damage = COMBAT_D->fight(me, opponent, "destruction whip", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
