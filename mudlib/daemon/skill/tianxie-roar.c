// 天邪虎嘯 tianxie-roar -- 冷梅莊「虎督」進階(二轉)的劍法之一(基礎技能 sword)
//
// 虎督拜入天邪後所習的另一門殺著﹐與「寒霜三千 hanshuang」並列(見
// docs/03-門派與武功/01-武者-五大門派.md §2 冷梅莊-虎督)。「天邪虎嘯」
// 在 docs 中亦見於雪吟莊-天邪派弟子(神掌)﹐有牽制敵人/補血/定人/群體攻擊
// 之能；於虎督一脈側重控場(定人)與持久續戰﹐故本招式 daemon 以霸烈虎嘯、
// 震懾牽制的招式敘述體現之(群攻/補血/定人的實際機制屬 combat/perform 系統﹐
// 為未來工作)。
//
// ⚠️ 交替使用﹕docs 明載「天邪虎嘯」與「寒霜三千」**只能交替使用**。詳見
//    daemon/skill/hanshuang.c 開頭說明﹔交替的強制邏輯標記為待辦。
//
// 比照 daemon/skill/lunmay.c 之 actions 招式表模型建立﹐並帶 "force" 係數
// 吃天邪神功(tianxie-force)的超高 kee(力道公式見 combatd.c::fight()
// force_bonus)。玩家透過 map_skill("sword","tianxie-roar") 對應後即可施展。
//
// 中文字典查無此 key﹐以 CHINESE_D->add_translate() 自行登錄「天邪虎嘯」。
//
// 數值為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   damage 14~18﹐damage_type 取「邪氣」呼應天邪一脈﹐多式帶 force 8~16。
//
// TODO(虎督完整化)：群體攻擊、補血、定人、與寒霜三千交替使用之強制邏輯
//   (皆屬 combat/perform 系統﹐非招式表)。本檔先把普攻招式做實。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N$w一震﹐似有虎嘯之聲隨劍而發﹐霸烈地劈向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		14,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N足下一頓﹐$w挾天邪煞氣﹐如猛虎撲食般直撲$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		15,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N一式『邪嘯震野』﹐$w捲起一股陰冷罡風轟向$n的$l",
    "dodge":		-12,
    "attack":		8,
    "force":		12,
    "damage":		16,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N$w縱橫如虎﹐一爪一嘯﹐連環撲擊$n的$l",
    "dodge":		-10,
    "attack":		7,
    "force":		10,
    "damage":		16,
    "damage_type":	"邪氣"
  ]),
  // —— 控場式﹕虎嘯震懾、牽制之意(正 dodge﹐穩守控場) ——
  ([
    "action":		"$N$w所指處一聲虎嘯震懾全場﹐邪氣瀰漫欲奪$n心神﹐順勢削向$n的$l",
    "dodge":		8,
    "attack":		6,
    "force":		10,
    "damage":		14,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N斂$w蓄勢﹐天邪真氣盤旋如淵﹐隨$n勢老一嘯而發貫向$n的$l",
    "dodge":		10,
    "attack":		7,
    "force":		12,
    "damage":		15,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N$w挾風雷之勢﹐一式『天邪噬魂』陰冷煞氣直灌$n的$l",
    "dodge":		-5,
    "attack":		8,
    "force":		12,
    "damage":		16,
    "damage_type":	"邪氣"
  ]),
  ([
    "action":		"$N周身煞氣沖天﹐一式『天邪虎嘯』聲動四野﹐萬鈞之勢罩向$n的$l",
    "dodge":		-12,
    "attack":		10,
    "force":		16,
    "damage":		18,
    "damage_type":	"邪氣"
  ]),
});

string *interattack = ({
  "$N$w斜引﹐周身天邪煞氣陰冷詭譎﹐隱隱似有虎嘯低鳴﹐凜然不可逼視。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("tianxie-roar");
  CHINESE_D->add_translate("tianxie-roar", "天邪虎嘯");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (MAG + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "tianxie-roar", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
