// fengyingying.c -- 鳳盈盈：茅山遺址(其墓地)的一縷殘魂(描述陪襯 NPC)
//
// 來歷(docs/03-門派與武功/02-道士-天師與茅山.md「茅山三觀劇情背景」＋
//   docs/01-世界觀與劇情/04-地圖與場景.md「茅山劍士 @ 茅山遺址(鳳盈盈墓地)」)：
//   林遠橋修茅山心經走火入魔失常絕跡﹐其妻鳳盈盈暫任掌門﹔五年後總壇大火﹐藏書
//   閣(藏茅山劍譜、茅山心經)被焚﹐鳳盈盈內疚而死。她葬於此處(茅山遺址)﹐墓前留
//   下三層茅山石陣﹐石壁上刻著殘存的茅山劍法、心經口訣。
//
// 定位：鳳盈盈早已身死﹐此處僅以「一縷縈繞墓前不散的殘魂/虛影」呈現﹐純為茅山
//   劍士轉職(由小霸王張天 do_advance 主持)增添 docs 劇情氛圍與指路﹐本身不主持轉
//   職、不發物、不戰鬥(殘魂虛影﹐accept_fight 直接回 0)。實際授技一律走張天的
//   「進階 茅山劍士」。
//
// 比照已驗證的氛圍 NPC 建檔(d/maoshan/npc/laodao.c、d/capital/npc/gongsunzhi.c)：
//   set_name/long/chat_msg + 不 replace_program。do_ask 守 is_fighting/is_chatting﹐
//   只擺風味與指路(引玩家去找張天「進階 茅山劍士」)。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIW "鳳盈盈" NOR,
		({ "fengyingying", "feng yingying", "spirit", "apparition" }) );
	set("nickname", "茅山故掌門");
	set_attr("str", 14);
	set_attr("dex", 20);
	set_attr("int", 26);
	set_attr("wis", 26);
	set_attr("spi", 30);
	set_attr("con", 16);
	set_attr("cor", 22);
	set_race("human");
	set_level(20);
	set_class("taoist");
	set("sect", "茅山派");
	set("rank", "故掌門");
	set("title", "茅山派故掌門");

	set_skill("dodge", 80);
	set_skill("force", 90);
	set_skill("dao force", 90);
	map_skill("force", "dao force");
	set_skill("magic", 100);

	set("age", 36);
	set("gender", "female");
	set("long",
		"一縷縈繞在墓碑前久久不散的虛影﹐隱約是個身著青色道袍的清麗女\n"
		"子﹐眉目間鎖著一抹化不開的愁緒。她便是當年總壇大火後內疚而死的\n"
		"茅山故掌門鳳盈盈——藏書閣連同那茅山劍譜、茅山心經一道焚於那場大\n"
		"火﹐她自覺愧對列祖﹐魂魄竟眷戀著這片遺址不肯離去。她的身影時濃時\n"
		"淡﹐似真似幻﹐偶爾抬眼望向墓前那三層斑駁的石陣﹐眼神裡盡是哀矜與\n"
		"期盼﹐彷彿仍在守望著茅山劍法的一線傳承。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		WHT "鳳盈盈的虛影幽幽一嘆﹐輕聲道﹕那一場大火……是我守不住藏書閣啊。\n" NOR,
		WHT "鳳盈盈的身影飄至石陣之前﹐伸出近乎透明的手指﹐輕撫石壁上殘存的劍痕。\n" NOR,
		WHT "鳳盈盈望著遺址出神﹐喃喃道﹕茅山劍法不能斷在我手裡……總會有有緣人的。\n" NOR,
		WHT "鳳盈盈的虛影漸漸淡去﹐又於墓碑旁緩緩凝聚﹐似去而復返﹐終究捨不得離開。\n" NOR,
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg ||
		(arg != "fengyingying about 石陣"
		&& arg != "fengyingying about 茅山劍法"
		&& arg != "fengyingying about 茅山心經"
		&& arg != "fengyingying about 轉職"
		&& arg != "fengyingying about 茅山劍士"
		&& arg != "fengyingying about 大火"
		&& arg != "fengyingying about 藏書閣"
		&& arg != "feng yingying about 石陣"
		&& arg != "spirit about 石陣"
		&& arg != "apparition about 石陣"
		&& arg != "fengyingying about maoshan sword") )
		return notify_fail("你想問這縷虛影甚麼﹖（試試 ask fengyingying about 石陣）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("鳳盈盈的虛影怔怔望著石陣﹐恍若未聞。\n");

	do_chat(({
		WHT "鳳盈盈的虛影緩緩轉過身來﹐哀矜地望著你。\n" NOR,
		(: command, "say 你也是為了這墓前的三層石陣而來麼……當年大火焚了藏書閣﹐茅山劍譜與心經盡付一炬﹐我便將殘存的口訣刻進了這石壁石陣之中。" :),
		(: command, "say 石陣認的是茅山的根﹐唯三觀出身、修為到家者﹐方能在那劍痕符文間悟得真意。你若有意﹐去尋那遊蕩遺址的小霸王張天﹐他熟知這石陣的門徑。" :),
		(: command, "say 在他面前『進階 茅山劍士』罷——只要石陣認你﹐茅山劍法這一線香火﹐便算是接上了……我也好瞑目了。" :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat(WHT "你的兵刃穿過鳳盈盈的虛影﹐恍如劈在一縷青煙之上﹐她渾不在意﹐只是哀哀地望著石陣。\n" NOR);
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
