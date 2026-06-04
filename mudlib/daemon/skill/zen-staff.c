// 降魔禪杖 zen-staff -- 白象寺「禪師」進階(二轉)的高階杖法(基礎技能 staff)
//
// 白象寺禪師一脈防守型(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §白象寺-進階分支﹕「禪師：防守型」)。docs 只標明禪師為防守型而未列其招式
// 名﹐故招式名「降魔禪杖」為設計(docs未明定):與羅漢攻擊型的文殊杖法 wen-staff
// 對位的守勢杖法。由入門金剛伏魔杖法(rid-evil)精進而成﹐杖走沉穩、以守為攻、
// 借勢卸力、坐如禪定﹐故招式 dodge 多為正(易被閃避但自身破綻小)、damage 平實
// 綿密﹐重在格擋纏鬥與久戰。比照 daemon/skill/chin_staff.c(哭笑門護法守勢杖法
// D攻/S防/S續戰)之偏守模型建立﹐基礎技能為 staff(杖法)﹐持禪杖施展。
//
// 因基礎技能為 staff(杖法)﹐玩家透過 map_skill("staff","zen-staff") 對應後即可
// 持禪杖施展(禪師進階時師父自動掛上此映射)。attack_using 第三參數為兵器物件
// (weapon)﹐故 COMBAT_D->fight() 傳 weapon﹐與 rid-evil.c / chin_staff.c 一致。
//
// 數值為本次設計值(docs 只給定位非確切數字)﹐供日後平衡微調﹕招式 damage 8~13
//   (與入門 rid-evil 同階偏守)﹐dodge 多正(守勢)﹐少數收勢式帶 force(吃蓮華心法/
//   降魔內功的內力加成)。
//
// TODO(禪師完整化)：docs 載白象寺禪師為「防守型」但未細列招式與 perform﹐其格擋
//   減傷實由 parry 技能(daemon/skill/parry.c)承擔﹐本杖法只負責守勢攻擊氣象﹔
//   定身/結界等 perform 效果標記為待辦。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N雙手持$w沉腰一封﹐一式『金剛守山』穩穩格向$n的$l",
    "dodge":		8,
    "damage":		8,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N腳下生根坐如禪定﹐$w凝而後發直搗$n的$l",
    "dodge":		10,
    "damage":		8,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N寶杖一引借勢卸力﹐隨即一式『迴遮護法』反掃$n的$l",
    "dodge":		6,
    "force":		6,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N默誦佛號身形微沉﹐$w如老僧入定般沉沉壓向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N杖走中宮以靜制動﹐$w借勢一頓格點$n的$l",
    "dodge":		8,
    "damage":		8,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N退步穩樁守得滴水不漏﹐$w順勢一撩$n的$l",
    "dodge":		10,
    "force":		6,
    "damage":		10,
    "damage_type":	"挫傷"
  ]),
  ([
    "action":		"$N橫杖如壁封住門戶﹐$w凝定後猛點$n的$l",
    "dodge":		6,
    "damage":		8,
    "damage_type":	"挫傷"
  ]),
  // —— 守極反攻﹕禪師久守後一式沉雄的反擊 ——
  ([
    "action":		"$N寶相莊嚴守極而發﹐一式『伏魔定海』$w攜沉雄之勢頓向$n的$l",
    "dodge":		4,
    "force":		8,
    "damage":		13,
    "damage_type":	"挫傷"
  ]),
});

string *interattack = ({
  "$N雙手橫杖當胸﹐沉腰落樁坐如禪定﹐守得滴水不漏地靜待破綻。\n",
  "$N寶杖斜封門戶﹐口誦佛號寶相安詳﹐以靜制動地候著時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("zen-staff");
  // 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
  CHINESE_D->add_translate("zen-staff", "降魔禪杖");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (YEL + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "zen-staff", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
