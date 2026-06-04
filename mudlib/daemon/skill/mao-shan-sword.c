// 茅山劍法 mao-shan sword -- 茅山遺址「茅山劍士」轉職(三轉/側線)所授的高階劍法
//
// 來歷(docs/03-門派與武功/02-道士-天師與茅山.md「茅山劍士」)：三百年前祖師
// 林正英憑《幽冥三箭》與《茅山劍法》創派﹐茅山劍法後與茅山心經一同藏於藏書
// 閣﹐總壇大火付之一炬﹐鳳盈盈內疚而死。茅山劍法殘卷與心法後埋於茅山遺址(鳳
// 盈盈墓地)的三層石陣中﹐唯有與茅山有淵源(三觀弟子)、修為到家者﹐方能在小霸
// 王張天的指點下於石壁、石陣間悟得這一脈以符入劍、劍咒同流的劍法。
//
// 比照已驗證的進階劍法 daemon/skill/aomei-sword.c(冷梅莊劍士「傲梅暗劍訣」)的
// actions 招式表模型建立﹕基礎技能為 sword﹐玩家以 map_skill("sword","mao-shan
// sword") 對應後﹐戰鬥時 COMBAT_D->fight() 即依本表施展招式。招式帶 "force"
// 係數(內力加成﹐見 combatd.c::fight() 之 force_bonus 公式)﹐體現「以茅山心經
// 之靈力催發劍勢、劍咒同流」的特性。
//
// 註(key 含空白)：技能 key「mao-shan sword」含空白﹐故檔名以連字號代之
// (mao-shan-sword.c)﹐register/map 用的 key 仍為含空白原名「mao-shan sword」
// (同 daemon/skill/mao-shan-lightning.c 的命名先例)。中文名「茅山劍法」另以
// CHINESE_D->add_translate() 登錄﹐使 skills / score 等指令工整顯示中文。
//
// 數值為本次設計值(docs 只給劇情、未給確切數字)﹐略高於冷梅劍士「傲梅暗劍訣」
// (damage 15~22)以體現其三轉側線之尊﹐供日後平衡微調。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手腕一沉﹐$w畫出一道符弧﹐一式『符引劍走』悄然點向$n的$l",
    "dodge":		-8,
    "attack":		6,
    "force":		8,
    "damage":		16,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐$w如靈符出竅﹐一式『茅山引雷』疾斬$n的$l",
    "dodge":		-10,
    "attack":		8,
    "force":		12,
    "damage":		19,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N劍指並引﹐$w劍尖暴吐一縷幽冥之氣﹐連環疾刺$n的$l",
    "dodge":		-12,
    "attack":		9,
    "force":		14,
    "damage":		20,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N口誦真言﹐$w化作三道符光﹐一式『五行劍咒』漫卷$n的$l",
    "dodge":		-10,
    "attack":		8,
    "force":		12,
    "damage":		18,
    "damage_type":	"割傷"
  ]),
  // —— 劍咒同流﹕正 dodge﹐以符護身、後發制人之勢 ——
  ([
    "action":		"$N斂劍凝符﹐待$n勢老即還﹐一式『符鎮山河』後發斬向$n的$l",
    "dodge":		10,
    "attack":		10,
    "force":		16,
    "damage":		20,
    "damage_type":	"割傷"
  ]),
  // —— 殺著﹕茅山劍法最盛一式﹐以茅山心經靈力盡催劍勢 ——
  ([
    "action":		"$N凌空而起﹐$w盡吞一身靈符之氣﹐一式『遺址劍冢』漫天符劍儘攢向$n的$l",
    "dodge":		-15,
    "attack":		13,
    "force":		20,
    "damage":		23,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N長劍橫引﹐劍身浮起一層淡淡的硃砂符光﹐劍意與符氣交纏不息。\n",
  "$N斂劍凝立﹐口中真言低誦﹐周身靈符之氣隱隱流轉﹐殺機暗藏。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("mao-shan sword");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("mao-shan sword", "茅山劍法");
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

  damage = COMBAT_D->fight(me, opponent, "mao-shan sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
