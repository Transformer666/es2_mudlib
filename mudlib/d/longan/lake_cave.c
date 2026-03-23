// vim: syntax=lpc
// Quest support: storyteller_pendant (search for jade pendant, dragon may appear)

inherit ROOM;

int pendant_found = 0;

void create()
{
	set("short", "湖底洞穴");
	set("long", @LONG
從花園旁的小徑深入，穿過一片蘆葦叢，來到了一個隱匿在地下的
洞穴。洞穴中積滿了幽暗的湖水，水面泛著詭異的磷光。洞壁濕滑，
到處是巨大的鱗片和深深的爪痕。一股令人窒息的龍息瀰漫在潮濕的
空氣中，偶爾傳來低沉的龍吟，令人膽寒。水邊隱約可以看到一些散
落的物件。
LONG
	);
	set("detail", ([
		"鱗片" : "巨大的漆黑鱗片散落在地，每一片都有巴掌大小，堅硬如鐵。\n",
		"爪痕" : "深深的爪痕遍佈洞壁，不知是何等兇猛的生物留下的。\n",
		"物件" : "水邊散落著一些骨頭和碎片﹐仔細找找也許能發現什麼有價值的東西。\n",
	]));
	set("no_clean_up", 1);
	set("exits", ([
		"south" : __DIR__"garden",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	if( arg != "水邊" && arg != "物件" && arg != "地面" && arg != "鱗片" )
		return 0;

	if( pendant_found ) {
		message_vision("$N在水邊仔細搜尋﹐但除了散落的碎骨之外什麼也沒找到。\n",
			this_player());
		return 1;
	}

	if( !this_player()->query_temp("pending/storyteller_pendant") ) {
		message_vision("$N在水邊隨手翻找了一下﹐只看到一些碎骨和淤泥。\n",
			this_player());
		return 1;
	}

	pendant_found = 1;

	// 50% chance the black dragon appears when you find the pendant
	if( random(2) == 0 && !present("black dragon", environment(this_player())) ) {
		object dragon = new(__DIR__"npc/black_dragon");
		dragon->move(environment(this_player()));
		message_vision(
			"$N正在水邊翻找時﹐洞穴深處的湖水突然翻湧﹗\n"
			"一條漆黑巨龍從幽暗的湖水中破水而出﹐血紅的眼睛死死盯著你﹗\n",
			this_player());
	} else {
		message_vision(
			"$N在水邊的淤泥中翻找﹐發現了一枚被泥垢覆蓋的玉佩﹗\n",
			this_player());
	}

	object ob = new(__DIR__"npc/obj/jade_pendant");
	ob->move(this_player());
	tell_object(this_player(), "( 你獲得了一枚舊玉佩 )\n");
	return 1;
}

void reset()
{
	pendant_found = 0;
	::reset();
}
