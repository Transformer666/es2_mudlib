// vim: syntax=lpc
// Quest support: herbalist_herb (search for fire_herb, dragon may appear)

inherit ROOM;

int herb_found = 0;

void create()
{
	set("short", "石洞");
	set("long", @LONG
藥圃後方的山壁上有一個隱蔽的石洞，洞口被藤蔓遮掩，若非刻意
尋找很難發現。洞內空間不小，地面散落著一些碎骨和焦痕，空氣中
瀰漫著一股濃重的腥臭味。洞壁上留有巨大的爪痕，顯然有什麼可
怕的生物棲息在這裡。潮濕的角落裡似乎長著一些暗紅色的草藥。
LONG
	);
	set("detail", ([
		"爪痕" : "深入岩壁的巨大爪痕，似乎是某種強大生物所留。\n",
		"碎骨" : "散落的碎骨上有灼燒的痕跡，此處的主人顯然極為危險。\n",
		"草藥" : "角落裡長著一些暗紅色的草藥﹐似乎就是傳說中的火靈草。\n",
	]));
	set("no_clean_up", 1);
	set("exits", ([
		"south" : __DIR__"herb_garden",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object ob;

	if( arg != "草藥" && arg != "火靈草" && arg != "角落" && arg != "洞壁" )
		return 0;

	if( herb_found ) {
		message_vision("$N在洞裡仔細搜尋﹐但除了碎骨和焦痕之外什麼也沒找到。\n",
			this_player());
		return 1;
	}

	if( !this_player()->query_temp("pending/herbalist_herb") ) {
		message_vision("$N在洞裡隨手翻找了一下﹐只看到一些枯萎的雜草。\n",
			this_player());
		return 1;
	}

	herb_found = 1;

	// 50% chance the red dragon appears when you find the herb
	if( random(2) == 0 && !present("red dragon", environment(this_player())) ) {
		object dragon = new(__DIR__"npc/red_dragon");
		dragon->move(environment(this_player()));
		message_vision(
			"$N正小心翼翼地拔取一株火靈草時﹐洞穴深處傳來一聲震耳的咆哮﹗\n"
			"一條赤紅巨龍從黑暗中現身﹐灼熱的龍息撲面而來﹗\n",
			this_player());
	} else {
		message_vision(
			"$N在洞穴角落的岩縫中發現了一株暗紅色的草藥﹐小心翼翼地將它拔了出來。\n",
			this_player());
	}

	ob = new(__DIR__"npc/obj/fire_herb");
	ob->move(this_player());
	tell_object(this_player(), "( 你獲得了一株火靈草 )\n");
	return 1;
}

void reset()
{
	herb_found = 0;
	::reset();
}
