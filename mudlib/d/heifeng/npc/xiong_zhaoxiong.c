// xiong_zhaoxiong.c -- 黑風寨二頭目 熊兆雄（綽號「鐵臂熊」），黑風寨四頭目之一。
//
// 設定（依 docs/02-遊戲系統與機制/05-裝備與強化.md L184-186「黑風寨四頭目」掉裝副本）：
//   docs 僅具名大寨主閰狂風一人並列出四件掉裝；本副本依「四頭目」之名，補擬餘三位頭目
//   並將 docs 餘下三件分屬之。此「二頭目」熊兆雄掌黑風寨校場、操練嘍囉，慣使一對鐵臂與
//   一桿狼牙棒，力大勢沉﹐故掉落 docs-named「紫羅點翠戰甲」(/obj/topgear/zilo_armor.c)。
//
// 戰力定位（boss，lv 52，次於大寨主閰狂風 lv60）：
//   * con/str 偏高(力士型)﹐技以 unarmed/blunt 為主﹐advance_stat kee 厚而 gin/sen 略遜。
//   * accept_fight 回傳 1；「不」設 aggressive(由玩家 kill 起釁)。
//   * die() 鏡諸頭目慣式：先 ::die()(屍體生成、登錄 temp("corpse"))﹐再於下手者為真實玩家
//     時將簽名裝置入屍身。此戰甲屬「頂防(可量產)、非全服唯一」，故恒掉一件(不走 LOOT_D)。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

#define XIONG_LOOT  "/obj/topgear/zilo_armor"   // 簽名掉落 紫羅點翠戰甲(頂防、非 unique)

void die();
private void drop_signature(object who);

void create()
{
	set_name("熊兆雄", ({ "xiong zhaoxiong", "zhaoxiong", "tiebixiong", "xiong" }) );
	set("nickname", "鐵臂熊");
	set_attr("str", 29);
	set_attr("dex", 22);
	set_attr("int", 18);
	set_attr("wis", 19);
	set_attr("spi", 22);
	set_attr("cps", 23);
	set_attr("con", 30);
	set_attr("cor", 24);
	set_race("human");
	set_level(52);
	set_class("fighter");
	set("sect", "黑風寨");
	set("rank", "二頭目");

	// 力士型：拳腳與狼牙棒俱沉猛﹐血厚力大﹐身法稍遜。
	set_skill("unarmed", 150);
	set_skill("blunt", 150);
	set_skill("parry", 140);
	set_skill("dodge", 100);
	set_skill("force", 130);

	advance_stat("gin", 260);
	advance_stat("kee", 300);
	advance_stat("sen", 240);

	set("gender", "male");
	set("age", 44);
	set("long",
		"這便是黑風寨的二頭目、綽號「鐵臂熊」的熊兆雄。他生得虎背\n"
		"熊腰﹐一身橫練的腱子肉鼓脹如鐵﹐兩條臂膀粗如尋常人的大\n"
		"腿﹐傳聞他這一身鐵臂功夫煉了二十餘年﹐刀劍砍上去也只留一\n"
		"道白痕。他在這黑風寨裡掌著校場﹐日日操練那數百名嘍囉﹐喝\n"
		"罵聲震得整座校場嗡嗡作響。他手中那桿烏沉沉的狼牙棒掄將起\n"
		"來呼呼生風﹐尋常三五條漢子近不得他的身。一張粗豪的黑臉上\n"
		"橫著一道刀疤﹐瞪起眼來自有一股莽撞兇悍的煞氣。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"熊兆雄一聲悶吼﹐掄起狼牙棒當頭砸落﹐棒風呼呼﹐勢沉力猛﹗\n",
		"熊兆雄鐵臂一振﹕來得好﹐讓你嘗嘗你熊爺爺的鐵臂功﹗\n",
		"熊兆雄橫棒一掃﹐挾著一股莽撞的蠻勁﹐震得地面碎石亂跳。\n",
	}));
	set("bounty", ([
		"survive"         : 1100,
		"unarmed mastery" : 200,
		"martial art"     : 150,
		"martial mastery" : 90,
		"combat"          : 90,
		"martial fame"    : 80,
		"reputation"      : 50,
	]));
	setup();
	carry_money("coin", 1200);
}

// boss：奉陪到底、兇悍反擊（不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 熊兆雄一聲悶吼﹕哪裡來的雜碎﹐也敢闖我黑風寨的校場﹗" :));
	return 1;
}

// 簽名掉落：下手者須為真實玩家；於 ::die() 之後呼叫，corpse 已生成於 temp("corpse")。
//   紫羅點翠戰甲屬頂防(可量產、非全服唯一)，故恒 new 一件入屍(不走 LOOT_D)。
private void drop_signature(object who)
{
	object corpse, loot;

	if( !objectp(who) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) ) return;

	loot = new(XIONG_LOOT);
	if( !objectp(loot) ) return;
	if( !loot->move(corpse) ) loot->move(environment());

	message_vision(HIY
		"熊兆雄那魁梧的屍身轟然倒地之際﹐身上那件暗紫華貴的戰甲應聲鬆脫——羅面點翠的"
		"雲紋猶自隨光流轉﹐赫然便是這二頭目壓陣的「紫羅點翠戰甲」﹗\n" NOR);
}

// 死亡：先 ::die()(屍體/bounty/善後悉依之﹐恒呼不可略﹐屍體於此生成並登錄 temp("corpse"))﹐
//   再於下手者為真實玩家時﹐自屍身遺落簽名戰甲。
void die()
{
	object killer;

	killer = last_damage_giver();

	::die();

	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_signature(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
