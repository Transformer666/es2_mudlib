// bandit.c -- 莽林盜匪，落草為寇、據莽林深處劫掠行旅的悍匪嘍囉。
//
// 結構沿用 /d/heifeng/npc/greywolf.c 之 score 範式（可 kill、會還手、不主動
// 攻擊路人、殺後只給 score 無錢），人形持械則參 /d/wutang/npc/escort.c（fighter
// class + blade 技能 + carry STOCK_WEAPON("blade")->wield()）。戰力定在 level
// 27 一線——莽林獵場中段、嘍囉級對手，成群出沒。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("莽林盜匪", ({ "bandit", "robber", "daofei" }) );
	set("nickname", "盜匪");
	set_attr("str", 32);
	set_attr("con", 30);
	set_attr("dex", 26);
	set_race("human");
	set_class("fighter");
	set_level(27);

	// 落草前多是行伍亡命或江湖浪人﹐刀法粗悍、拆招閃躲尚可﹐略諳吐納。
	set_skill("blade", 48);
	set_skill("parry", 36);
	set_skill("dodge", 32);
	set_skill("unarmed", 30);
	set_skill("force", 26);

	set("age", 31);
	set("gender", "male");
	set("long",
		"一個落草為寇的莽林盜匪﹐生得獐頭鼠目﹐一臉橫肉﹐穿一身污\n"
		"穢襤褸的短打﹐腰裡胡亂束著條麻繩。他手裡攥著把缺了口的單\n"
		"刀﹐刀身鏽跡斑斑﹐卻也沾過不少過路客的血。他斜著眼睛上下\n"
		"打量你﹐喉間發出一聲不懷好意的冷笑——這莽林深處官府難管﹐\n"
		"正是他這等亡命之徒攔路劫財的好去處。\n");
	// 純 score：江湖歷練(升級)、刀法精熟、武術造詣、實戰經驗。無錢幣(score-only 獵場)。
	set("bounty", ([
		"survive"        : 380,
		"blade mastery"  : 78,
		"martial art"    : 56,
		"combat"         : 30,
	]));
	setup();
	carry_object( STOCK_WEAPON("blade") )->wield();
}

// 奉陪到底、凶悍反擊（不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 盜匪獰笑一聲﹕哪來的肥羊自己送上門﹗識相的留下買路錢﹐不然莫怪刀下無情﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
