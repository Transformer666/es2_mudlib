// vim: syntax=lpc
// Room: /d/choyin/back_alley.c
// Quest: 算命先生的龜殼 - search here to find turtle shell

inherit ROOM;

int do_search(string arg);

void create()
{
	set("short", "後巷");
	set("long", @LONG
店鋪後面的一條窄巷﹐堆著些廢棄的木箱和破舊的竹筐。幾條野
狗在垃圾堆裡翻找著食物﹐見人來也不怎麼害怕。牆角長著青苔﹐
地上濕漉漉的﹐瀰漫著一股潮濕腐朽的氣味。
LONG
	);
	set("detail", ([
		"木箱" : "幾個破爛的木箱﹐有的已經散了架﹐裡面堆著些碎木片和破布。\n",
		"竹筐" : "幾個破舊的竹筐﹐筐底已經穿了﹐看起來早就沒有人用了。\n",
		"垃圾堆" : "一堆雜七雜八的垃圾﹐散發著難聞的氣味。仔細翻找的話﹐也許能發現些什麼。\n",
	]));
	set("exits", ([
		"north" : __DIR__"shop",
		"east" : __DIR__"teahouse",
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object me = this_player();

	if( !me ) return 0;

	if( !me->query_temp("pending/fortune_turtle") ) {
		write("你在後巷翻找了一陣﹐除了一些垃圾之外什麼也沒找到。\n");
		return 1;
	}

	if( me->query("quest/fortune_teller_turtle_done") ) {
		write("你已經找過了﹐這裡沒有什麼值得注意的東西了。\n");
		return 1;
	}

	if( me->query_temp("pending/fortune_turtle_found") ) {
		write("你已經找到龜殼了﹐趕快拿回去還給算命先生吧。\n");
		return 1;
	}

	object shell;

	write("你蹲下身子﹐在那堆破木箱和竹筐之間仔細翻找。\n");
	say(me->query("name") + "蹲下身子在巷子裡翻翻找找。\n");
	write("在一個破竹筐的底下﹐你發現了一隻沾滿泥垢的龜殼﹗\n");
	write("你小心翼翼地把龜殼撿起來﹐擦去上面的灰塵﹐上面刻著密密麻麻的卦象。\n");

	shell = new(__DIR__"npc/obj/turtle_shell");
	shell->move(me);
	me->set_temp("pending/fortune_turtle_found", 1);
	return 1;
}
