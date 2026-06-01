// idler.c -- 衛國市集上趕集閒逛的鄉民（純氣氛閒談）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("趕集鄉民", ({ "idler", "villager", "ganjixiangmin" }) );
	set("nickname", "趕集鄉民");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 38);
	set("gender", "male");
	set("long",
		"一個趕集的本地鄉民﹐裹著件半舊的粗布短褐﹐褲腳還沾著\n"
		"田裡的泥﹐挎著個空了大半的菜籃﹐在市集上慢悠悠地閒逛挑揀。\n"
		"他臉膛黝黑﹐透著莊稼人的憨實﹐東家長西家短的閒話倒是知道\n"
		"得最多。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"趕集鄉民挎著菜籃﹐在攤前蹲下身﹐拿起一把青菜捏了捏﹐又和攤主有一搭沒一搭地搭話。\n",
		"趕集鄉民抹了把汗﹐瞇眼望著日頭﹐盤算著趕集回去還趕得上晌午的農活。\n",
		"趕集鄉民壓低嗓子道﹕後生家﹐這鎮上的閒話﹐可沒有我老李不曉得的。\n",
	}));
	setup();
	carry_money("coin", 10);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這鄉民打聽甚麼﹖（試試 ask idler about 衛國鎮）\n");

	if( arg == "idler about 衛國鎮"
	||  arg == "idler about 市集"
	||  arg == "idler about 鎮"
	||  arg == "idler about 衛國"
	||  arg == "idler about weiguo" ) {
		do_chat(({
			(: command, "say 衛國鎮啊﹐就這麼巴掌大的地方﹐一個市集逛到頭。可別小瞧了它﹐打斐縣再往南進山﹐這兒是最後一處趕集打尖的鎮子了﹐過往的客商都得在這兒備足了乾糧再出鎮。" :),
			(: command, "say 場東是衛國客棧﹐場西雜貨鋪﹐西北茶寮﹐東北炒米坊那炒米的焦香﹐老遠就聞著了。閒著沒事﹐上茶寮聽人擺龍門陣﹐最是消遣。" :),
		}));
		return 1;
	}

	return notify_fail("趕集鄉民憨憨一笑﹕後生家問這做甚﹖閒著也是閒著﹐隨我逛逛這集罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎哎哎﹗有話好說﹗光天化日趕集的地界﹐動甚麼粗﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
