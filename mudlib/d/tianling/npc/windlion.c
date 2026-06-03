// windlion.c -- 吞風獅，摩雲麾下動物war殘部為首的孽畜之二，正史序章「逐念入山」
//              吞風獅穴(beastgrave→windlair)中的第二頭 boss﹐亦混沌珠線索之所出。
//
// 故事背景（承接 laolong.c 之後、canon 動物war 群獸名錄）：
//   吞風獅與老龍同列摩雲麾下為首的孽畜。此獸生具吞風納氣之能﹐張口能吸捲
//   數丈勁風﹐吼聲如雷﹐撲擊迅猛。摩雲既死﹐牠便潰退至獸塚更北的一處風穴﹐
//   受那縷遁來的邪念溫養蟄伏。然牠頸間繫著一片骨符——那是天靈山更深處把持
//   混沌珠的「骨屍妖王」遣孽畜佩帶、用以牽動其兇性的信物。吞風獅伏誅之際﹐
//   這片骨符便自其屍身中滑落﹐成了少俠循線探明混沌珠下落的關鍵線索。
//
// 設計（underling-tier：較老龍(lvl42)再低半檔的孽畜 boss）：
//   * level 38﹔unarmed 120 / parry 110 / dodge 120 / force 115（老龍 unarmed135/
//     parry125/dodge115/force130﹐摩雲 unarmed180...）——身手較老龍輕捷﹐然血力
//     略遜﹐仍是須有相當火候方能應付的孽畜 boss。
//   * 三圍真氣 advance_stat gin/kee/sen 240/260/240（老龍 280/300/280）。
//   * 以利爪獠牙搏殺﹐不持兵器（unarmed 主戰）。
//   * accept_fight 回傳 1——盤踞風穴、奉陪到底﹐然不主動撲噬（無 aggressive
//     attitude﹐由玩家自行 kill 起釁）。
//
// 任務推進 + 線索掉落（die()）：
//   吞風獅伏誅時﹐若下手者(last_damage_giver)是身負序章旗標(quest/main_canon1
//   == 2)的真實玩家(userp)﹕把其 quest/main_canon1 推進為 3（序章「獲知混沌珠
//   下落線索」之終點）﹐並 message 一段敘事（殘部第二頭已除﹐頸間骨符滑落﹐
//   指向更深處把持混沌珠的存在）。骨符殘片(bone talisman)以 corpse-drop 機制置
//   入屍身（須 ::die() 之後、屍體已登錄 temp("corpse") 時為之﹔屍體不存則退置
//   於房間地面）——玩家須 search/取屍 方得。防重複：旗標非 2 則僅作尋常死亡、
//   不推進、不掉骨符。末了恒呼 ::die()。另設 bounty﹐由 ::die() 結算給下手者。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落混沌珠線索信物：骨符殘片。who=下手者(真實玩家)﹔於 ::die() 之後呼叫﹐
// corpse 已存在於 temp("corpse")。骨符置入屍身﹔屍體不存則退置房間地面。
private void drop_talisman(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"obj/bone_talisman");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIY "吞風獅那龐然的屍身委地之際﹐自牠頸間散落一片晦暗的枯骨——"
		"那骨符以鬼篆刻著詰屈的咒紋﹐入手陰寒徹骨﹐分明是更深處某個邪物"
		"遣牠佩帶、用以牽動兇性的信物。混沌珠的下落﹐或許正繫於此﹗\n" NOR);
}

void create()
{
	set_name("吞風獅", ({ "wind lion", "windlion", "lion" }) );
	set("nickname", "吞風孽獅");
	set_attr("str", 28);
	set_attr("dex", 30);
	set_attr("int", 16);
	set_attr("con", 28);
	set_attr("cor", 22);
	set_race("human");
	set_class("fighter");
	set("sect", "天靈山");
	set("rank", "孽獅");

	// underling-tier：較老龍(unarmed135/parry125/dodge115/force130)再低半檔。
	set_skill("unarmed", 120);
	set_skill("parry", 110);
	set_skill("dodge", 120);
	set_skill("force", 115);

	// 真氣略遜於老龍(gin/kee/sen 280/300/280)。
	advance_stat("gin", 240);
	advance_stat("kee", 260);
	advance_stat("sen", 240);

	set("gender", "male");
	set("age", 200);
	set("long",
		"一頭軀體龐然如小牛的孽獅。牠生著一身糾結如鋼針的赤褐鬃\n"
		"毛﹐四肢虯結﹐利爪森然﹐一張血盆大口開闔之間﹐竟能吸捲起\n"
		"數丈方圓的勁風﹐捲得穴中枯葉碎石漫天打旋。據聞此獸吼聲如\n"
		"雷﹐一聲長嘯能震得人氣血翻湧。牠原是獸王摩雲麾下為首的孽\n"
		"畜﹐頸間繫著一片晦暗的枯骨符——摩雲既死﹐牠便潰退這風穴蟄\n"
		"伏﹐受那縷遁來的邪念溫養﹐一雙獸瞳裡燃著怨毒而躁動的青芒。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"吞風獅張口一吸﹐穴中勁風盡為其所納﹐繼而暴喝噴出﹐挾著碎石撲面而來。\n",
		"吞風獅一聲如雷的長嘯﹐穴頂簌簌落下碎石﹐震得人耳中嗡嗡作響、氣血翻湧。\n",
		"吞風獅頸間那片骨符隱隱泛起幽光﹐牠戾氣陡盛﹐利爪挾著腥風猛地撈來。\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 360,
		"unarmed mastery" : 80,
		"martial art"     : 48,
		"martial mastery" : 34,
		"combat"          : 40,
	]));
}

// 盤踞風穴、奉陪到底﹐然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 吞風獅張開血盆大口﹐倒吸一口勁風﹐發出一聲如雷的怒嘯﹐撲向犯境的來人﹗" :));
	return 1;
}

// 死亡：序章旗標推進(2->3，序章終點) + 敘事﹐末了恒呼 ::die()﹐再擲骨符入屍。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 下手者須為身負序章旗標(==2)的真實玩家﹐方推進旗標（防重複推進與重複掉符）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon1") == 2 )
	{
		killer->set("quest/main_canon1", 3);
		message_vision(
			HIR "吞風獅一聲如雷的悲嘯戛然而止﹐龐然的軀體重重砸落在穴中枯"
			"骨之上﹐再不動彈。$N斬了摩雲麾下這頭吞風孽獅——這場動物war的潰"
			"散殘部﹐至此算是掃平了﹗\n" NOR, killer);
		message_vision(
			HIM "你心念一動﹕這兩頭為首的孽畜頸間﹐竟都繫著同一式晦"
			"暗的骨符——分明是天靈山更深處某個把持邪物的存在﹐遣牠們佩帶、"
			"用以牽動兇性的信物。那縷遁去的邪念、那顆喚作『混沌珠』的至邪之"
			"物 ... 線索﹐怕就藏在這骨符之中。且取了這骨符﹐回幽壑去尋那守山"
			"道人參詳。\n" NOR, killer);
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼）。
	// 須先呼 ::die()(屍體於此生成並登錄 temp("corpse"))﹐再擲骨符入屍。
	::die();

	// 線索掉落：下手者須為身負序章旗標(==2→已推進為3)的真實玩家﹐方掉骨符入屍。
	if( objectp(killer) && killer != this_object() && userp(killer)
	&&	killer->query("quest/main_canon1") == 3 )
		drop_talisman(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
