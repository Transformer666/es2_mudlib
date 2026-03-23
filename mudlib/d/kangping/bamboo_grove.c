// vim: syntax=lpc
// Quest support: anlan_test (search for jade flute in bamboo grove)

inherit ROOM;

int flute_found = 0;

void create()
{
	set("short", "竹林");
	set("long", @LONG
村外一片幽靜的竹林﹐翠竹參天﹐密密匝匝地遮住了大半天光。微
風拂過﹐竹葉沙沙作響﹐彷彿在低聲細語。一條鋪著青石板的小徑穿林
而過﹐石板上覆著薄薄的苔蘚。林間清幽寧靜﹐偶有幾聲鳥鳴傳來。
地面上厚厚地堆積著枯黃的竹葉﹐踩上去軟綿綿的。
LONG
	);
	set("detail", ([
		"竹葉" : "厚厚的竹葉堆積在地面上﹐下面不知藏著什麼東西。\n",
		"落葉" : "枯黃的落葉鋪了厚厚一層﹐似乎很久沒人打理了。\n",
		"石板" : "青石板小徑上覆著苔蘚﹐看起來頗有些年頭。\n",
	]));
	set("outdoors", "wilderness");
	set("no_clean_up", 1);
	set("exits", ([
		"north" : __DIR__"creek",
		"east"  : __DIR__"path",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	if( arg != "竹林" && arg != "竹叢" && arg != "落葉"
	&&  arg != "竹葉" && arg != "地面" )
		return 0;

	if( flute_found ) {
		message_vision("$N撥開層層落葉仔細搜尋﹐除了幾根枯竹枝之外什麼也沒找到。\n",
			this_player());
		return 1;
	}

	if( !this_player()->query_temp("pending/anlan_test") ) {
		message_vision("$N隨手撥了撥竹葉﹐只看到一些蟲子從落葉下竄出。\n",
			this_player());
		return 1;
	}

	flute_found = 1;

	message_vision(
		"$N蹲下身來﹐仔細撥開厚厚的竹葉﹐忽然手指碰到了一個硬物。\n"
		"拿起來一看﹐原來是一支翠綠色的玉笛﹐上面沾滿了泥土和落葉。\n"
		"擦拭乾淨後﹐笛身上的梅花雕紋清晰可見﹐這應該就是安懶道人的玉笛了。\n",
		this_player());

	object ob = new(__DIR__"npc/obj/jade_flute");
	ob->move(this_player());
	tell_object(this_player(), "( 你獲得了一支玉笛 )\n");
	return 1;
}

void reset()
{
	flute_found = 0;
	::reset();
}
