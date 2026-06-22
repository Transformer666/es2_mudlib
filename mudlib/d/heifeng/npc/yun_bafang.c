// yun_bafang.c -- 黑風寨三頭目 雲八方（綽號「翻雲手」），黑風寨四頭目之一。
//
// 設定（依 docs/02-遊戲系統與機制/05-裝備與強化.md L184-186「黑風寨四頭目」掉裝副本）：
//   docs 僅具名大寨主閰狂風並列四件掉裝；本副本依「四頭目」之名補擬餘三位頭目並分屬其
//   餘三件。此「三頭目」雲八方守黑風寨寨門﹐身法輕靈詭變、慣使一柄快刀﹐人稱「翻雲手」﹐
//   故掉落 docs-named「天地雲衫」(/obj/topgear/tiandi_cloth.c)——輕軟飄逸、利於身法之衫﹐
//   正合其輕功路數。
//
// 戰力定位（boss，lv 50，四頭目中身法最捷、血量稍薄）：
//   * dex 偏高(身法型)﹐技以 blade/dodge 為主﹐advance_stat gin/sen 厚而 kee 略遜。
//   * accept_fight 回傳 1；「不」設 aggressive(由玩家 kill 起釁)。
//   * die() 鏡諸頭目慣式：::die() 後將簽名雲衫(頂防、非全服唯一)恒掉一件入屍。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

#define YUN_LOOT  "/obj/topgear/tiandi_cloth"   // 簽名掉落 天地雲衫(頂防、非 unique)

void die();
private void drop_signature(object who);

void create()
{
	set_name("雲八方", ({ "yun bafang", "bafang", "fanyunshou", "yun" }) );
	set("nickname", "翻雲手");
	set_attr("str", 24);
	set_attr("dex", 30);
	set_attr("int", 23);
	set_attr("wis", 22);
	set_attr("spi", 24);
	set_attr("cps", 25);
	set_attr("con", 24);
	set_attr("cor", 24);
	set_race("human");
	set_level(50);
	set_class("fighter");
	set("sect", "黑風寨");
	set("rank", "三頭目");

	// 身法型：快刀與閃避俱捷﹐攻守靈動﹐血量稍薄。
	set_skill("unarmed", 120);
	set_skill("blade", 160);
	set_skill("parry", 130);
	set_skill("dodge", 160);
	set_skill("force", 130);

	advance_stat("gin", 280);
	advance_stat("kee", 240);
	advance_stat("sen", 280);

	set("gender", "male");
	set("age", 39);
	set("long",
		"這便是黑風寨的三頭目、綽號「翻雲手」的雲八方。他身形瘦削\n"
		"頎長﹐一襲灰撲撲的勁裝裹著精悍的身板﹐行走坐臥都透著一股\n"
		"貓兒似的輕靈。他面皮白淨﹐一雙眼睛卻精光四射﹐顧盼之間滴\n"
		"溜溜地轉﹐似乎隨時在打量人身上有甚麼油水。他掌著這黑風寨\n"
		"的寨門﹐專一盤查上山的肥羊﹔一手翻雲覆雨的快刀使得出神入\n"
		"化﹐人未近身﹐刀光已到﹐江湖上「翻雲手」三字﹐便是這般翻\n"
		"手為雲、刀快如風的意思。寨中嘍囉都說﹐這位三頭目笑面之\n"
		"下﹐最是心狠手辣。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"雲八方身形一晃﹐快刀已自意想不到的刁鑽角度斜削而至﹐刀光如一抹翻飛的流雲﹗\n",
		"雲八方嘿嘿一笑﹕小兄弟﹐上了我黑風寨的山﹐還想囫圇下去﹖\n",
		"雲八方足尖一點﹐倏地欺近又倏地飄開﹐快刀連環﹐教人眼花繚亂。\n",
	}));
	set("bounty", ([
		"survive"         : 1000,
		"blade mastery"   : 200,
		"martial art"     : 150,
		"martial mastery" : 90,
		"combat"          : 90,
		"martial fame"    : 80,
		"reputation"      : 50,
	]));
	setup();
	carry_money("coin", 1500);
}

// boss：奉陪到底、兇悍反擊（不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 雲八方嘿嘿一笑﹕想硬闖黑風寨的寨門﹖先問過你雲三爺的快刀﹗" :));
	return 1;
}

// 簽名掉落：下手者須為真實玩家；於 ::die() 之後呼叫，corpse 已生成於 temp("corpse")。
//   天地雲衫屬頂防(可量產、非全服唯一)，故恒 new 一件入屍(不走 LOOT_D)。
private void drop_signature(object who)
{
	object corpse, loot;

	if( !objectp(who) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) ) return;

	loot = new(YUN_LOOT);
	if( !objectp(loot) ) return;
	if( !loot->move(corpse) ) loot->move(environment());

	message_vision(HIY
		"雲八方一個踉蹌頹然倒地之際﹐身上那件灰白飄逸的外衫應聲滑落——衫上雲水紋樣猶自"
		"隨光流轉﹐輕得似一捧流雲﹐赫然便是這三頭目護身的「天地雲衫」﹗\n" NOR);
}

// 死亡：先 ::die()(屍體/bounty/善後悉依之﹐恒呼不可略﹐屍體於此生成並登錄 temp("corpse"))﹐
//   再於下手者為真實玩家時﹐自屍身遺落簽名雲衫。
void die()
{
	object killer;

	killer = last_damage_giver();

	::die();

	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_signature(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
