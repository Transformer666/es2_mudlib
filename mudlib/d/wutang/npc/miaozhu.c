// miaozhu.c -- 老廟祝司天緣：枯守鎮天神廟內殿的鬚眉皆白老者。
//              docs 主線疑團「鎮天神廟內藏著誰？」(docs/01-世界觀與劇情/
//              05-主線任務與NPC.md:30)之伏筆人物——廟內「藏」著的人即此老廟祝
//              本身(亦守著石門後鎮著之物的秘密)。docs 未給謎底，故本 NPC 純作
//              lore 對白與伏筆 hook(ask about 神君/封印/藏著誰)，不開完整解謎
//              /獎勵——石門後鎮著誰、何時可開＝日後設計決策(caveat)。
//
// 機制：純 lore 對話 NPC(ask-handler)，不發物、不改技能、不推任務旗標。
//   旗標僅 query("quest/wutang_temple_lore")作「是否已聽過底細」之記號(無獎勵)，
//   重複 ask 給更深一層伏筆對白。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()。
//   #11：本檔為 NPC(非房間)，不涉 replace_program。
//   #14：init() 招呼加 this_player()&&interactive() 護衛(只招呼真人)；
//        本檔不覆寫 relay_say(故無 say-loop 風險)。
//   handler 守衛：do_ask 開頭即 is_fighting()/is_chatting() 守衛。
//
// 範式來源(先 grep 既有檔模仿)：
//   d/snow/npc/heiyilaoren.c(伏筆老者：ask-about 多 token、init 招呼護衛、
//     accept_fight 婉拒)；本檔去其贈物鏈、只留純 lore 對白。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIW "老廟祝" NOR, ({ "miaozhu", "lao miaozhu", "old keeper", "司天緣", "老廟祝", "廟祝" }) );
	set("nickname", HIW "老廟祝司天緣" NOR);
	set_attr("int", 22);
	set_attr("wis", 26);
	set_attr("con", 16);
	set_attr("spi", 25);
	set_race("human");
	set_class("commoner");
	set_level(20);
	set_skill("unarmed", 30);
	set_skill("dodge", 30);
	set_skill("force", 40);
	set_skill("literate", 50);

	set("gender", "male");
	set("age", 73);
	set("long",
		"一個鬚眉皆白的老廟祝﹐盤膝枯坐在內殿的蒲團上﹐一身洗得發白\n"
		"的灰布道袍﹐手裡撚著一串磨得油亮的舊念珠。他生得清癯矍鑠﹐\n"
		"一雙眼睛古井無波﹐卻深得彷彿看得透人心底的事。他自稱司天緣﹐\n"
		"守這鎮天神廟已守了大半輩子﹐廟裡廟外的舊事、神像底下鎮著的\n"
		"隱情﹐怕是再沒有第二個人比他更清楚了。他垂目誦經﹐對外間的\n"
		"喧囂恍若未聞﹐唯有偶爾抬眼望向那道森冷的石門時﹐渾濁的眼底\n"
		"才掠過一絲不易察覺的憂色。\n"
		"你或許可以問問他：ask miaozhu about 神廟。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老廟祝撚著念珠﹐低低地誦著一段古奧的經文﹐殿裡的燭火也隨之輕輕一晃。\n",
		"老廟祝抬眼望了望那道森冷的石門﹐又緩緩闔上眼﹐輕輕嘆了口氣。\n",
		"老廟祝喃喃道﹕鎮得住一時﹐鎮得住一世﹐卻未必鎮得住那一日 ...\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) && !is_fighting() ) {
		do_chat((: command,
			"say 施主也是循著香火進來的麼﹖這內殿少有人至 ... 施主若有疑問﹐但問無妨。(ask miaozhu about 神廟)" :));
	}
}

int do_ask(string arg)
{
	object me = this_player();
	int heard;

	if( !arg )
		return notify_fail("你想問老廟祝甚麼﹖（試試 ask miaozhu about 神廟）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老廟祝正闔目誦經﹐恍若未聞﹐沒空理你。\n");

	if( !me ) return 0;

	heard = me->query("quest/wutang_temple_lore");

	// ── 神廟由來 ──
	if( arg == "miaozhu about 神廟" || arg == "miaozhu about temple"
	 || arg == "miaozhu about 鎮天神廟" ) {
		do_chat(({
			(: command, "say 這鎮天神廟﹐立廟比五堂建鎮還早。廟裡供的是『鎮天神君』——傳說中曾以一己之力﹐將一頭禍亂天下的兇物鎮入這方水土地底的神將。" :),
			(: command, "say 五堂、五堂 ... 施主可知這鎮名的由來﹖『五堂』者﹐五道封堂也。當年鎮兇﹐神君在這方圓百里立下五道封印﹐這神廟﹐便是其中一道的廟祝守處。" :),
		}));
		return 1;
	}

	// ── 鎮天神君 / 神像踏著的兇物 ──
	if( arg == "miaozhu about 神君" || arg == "miaozhu about 神像"
	 || arg == "miaozhu about 兇物" || arg == "miaozhu about idol" ) {
		do_chat(({
			(: command, "say 施主也瞧出神像足下踏著的那團影子了﹖呵 ... 那便是神君當年所鎮之物的形貌。老朽奉了師門的訓誡﹐這物事的名姓﹐是萬萬說不得的。" :),
			(: command, "say 施主只消記著——這世上有些東西﹐越是叫破了名姓﹐它便越是不安生。施主在江湖上行走﹐他日若聽得『侮天』二字 ... 切記﹐切記﹐繞道走罷。" :),
		}));
		return 1;
	}

	// ── 石門後 / 封印 / 藏著誰 ──
	if( arg == "miaozhu about 石門" || arg == "miaozhu about 封印"
	 || arg == "miaozhu about 藏著誰" || arg == "miaozhu about door"
	 || arg == "miaozhu about seal" ) {
		if( !heard ) me->set("quest/wutang_temple_lore", 1);
		do_chat(({
			(: command, "say 那道石門 ... 施主方才也去探過了罷﹖門後鎮著的﹐並非甚麼妖魔﹐而是一段不該被記起的舊事﹐並 ... 一個不該再見天日的人。" :),
			(: command, "say 施主問廟裡藏著誰﹖（壓低了嗓子）老朽守了這廟一輩子﹐守的便是這一句話——廟裡藏著的﹐是當年立封印之人﹐自願以血肉之軀﹐做了這第五道封印的『鎮物』。他既未死﹐也算不得活著 ... 唉﹐造化弄人﹐造化弄人哪。" :),
			(: command, "say 老朽言盡於此。施主若是有緣人﹐他日這封印若有鬆動的一日﹐自會再來尋老朽的。去罷。" :),
		}));
		return 1;
	}

	return notify_fail("老廟祝撚著念珠搖了搖頭﹕這個 ... 施主不如問問神廟、神君、或那道石門罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 阿彌 ... 施主何苦對老朽這把枯骨動粗﹖這神君座前﹐還是莫造殺孽的好。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
