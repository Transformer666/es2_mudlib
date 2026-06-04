// 落葉身法 falling-leaf steps -- 天月庵「摧魂使者」進階(二轉)的身法(基礎技能 dodge)
//
// 天月庵核心技能列有「落葉身法」(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §天月庵-核心技能﹔docs 該列英文未載﹐故英文 key 取意譯 falling-leaf steps)。
// 此為天月庵輕靈飄忽的閃躲身法﹐身隨太陰之意﹐如落葉迴旋、隨風卸力﹐長於閃避
// 與游走﹐基礎技能為 dodge(閃避身法)。
//
// 比照白象進階身法 daemon/skill/damo-steps.c(達摩移身法)之結構建立﹕身法 daemon
// 屬被動閃避輔技﹐其閃避加成由 dodge 技能與 COMBAT_D 計算承擔﹐本檔負責註冊
// 技能名、登錄中文名﹐並以正 dodge、低 damage 的身法招式表提供移形換步的氣象。
// 玩家透過 map_skill("dodge","falling-leaf steps") 對應後即以本身法閃躲(摧魂使者
// 進階時師父自動掛上此映射)。
//
// 注意：key 含空白(「falling-leaf steps」)﹐故檔名以連字號代之
// (falling-leaf-steps.c)﹐register/translate 用的 key 仍為含空白原名。字典查無此
// key﹐以 CHINESE_D->add_translate() 自行登錄中文名「落葉身法」。
//
// 數值為本次設計值(docs 只給技能名非確切數字)﹐供日後平衡微調﹕dodge 多正
//   (閃身游走、破綻極小)﹐damage 平實(身法非主攻)。
//
// TODO(身法完整化)：身法的實際閃避加成由 dodge 技能(daemon/skill/dodge.c)與
//   combat 命中判定承擔﹐本檔只負責移形換步的攻擊氣象﹐與 damo-steps.c 同範圍。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N身形一晃如落葉迴旋﹐借勢卸力後反手一拂$n的$l",
    "dodge":		12,
    "damage":		6,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N足尖輕點飄然錯步﹐順勢一掌斜推$n的$l",
    "dodge":		15,
    "damage":		6,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N身隨太陰之意隨風游走﹐繞至側後一指點向$n的$l",
    "dodge":		14,
    "damage":		8,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N衣袂翻飛如葉墜空﹐借飄忽之勢輕撩$n的$l",
    "dodge":		12,
    "damage":		6,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N踏一步落葉步閃過鋒芒﹐迴身一拂$n的$l",
    "dodge":		16,
    "damage":		8,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N身形飄忽如殘葉打旋﹐順手一帶卸向$n的$l",
    "dodge":		14,
    "damage":		6,
    "damage_type":	"挫傷"
  ]),
});

string *interattack = ({
  "$N身形隨太陰之意輕輕浮動﹐如落葉隨風﹐飄忽難測地候著破綻。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("falling-leaf steps");
  // 字典查無此 key﹐自行登錄中文名「落葉身法」。
  CHINESE_D->add_translate("falling-leaf steps", "落葉身法");
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

  damage = COMBAT_D->fight(me, opponent, "falling-leaf steps", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
