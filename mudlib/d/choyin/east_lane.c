// vim: syntax=lpc
// Room: /d/choyin/east_lane.c
// Quest: 失竊的古卷 - search here to find ancient manuscript

inherit ROOM;

int do_search(string arg);

void create()
{
	set("short", "東巷");
	set("long", @LONG
書肆東側的一條僻靜小巷﹐兩旁是斑駁的青石牆壁﹐牆頭上晾著
幾件衣裳。一隻花貓蜷在窗台上打盹﹐偶爾懶洋洋地抬起眼皮。
巷子盡頭隱約可見縣衙的飛簷﹐顯得幽深而寧靜。牆根下堆著些
碎磚和枯葉﹐其中有一塊青石磚似乎有些鬆動。
LONG
	);
	set("detail", ([
		"青石磚" : "牆根處有一塊青石磚看起來比其他的新一些﹐而且似乎有些鬆動。也許可以試著搜查(search)一下。\n",
		"花貓" : "一隻懶洋洋的花貓﹐對你毫不在意。\n",
	]));
	set("exits", ([
		"west" : __DIR__"bookshop",
		"south" : __DIR__"yamen",
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
	object me, manuscript;

	me = this_player();
	if( !me ) return 0;

	if( me->query("quest/bookshop_manuscript_done") ) {
		write("你已經找過了﹐這裡沒有什麼值得注意的東西了。\n");
		return 1;
	}

	if( !me->query_temp("pending/bookshop_manuscript") ) {
		write("你在巷子裡翻找了一陣﹐除了碎磚和枯葉之外什麼也沒找到。\n");
		return 1;
	}

	if( me->query_temp("pending/bookshop_manuscript_found") ) {
		write("你已經找到古卷了﹐趕快拿回去還給書肆掌櫃吧。\n");
		return 1;
	}

	message_vision("$N蹲下身子﹐在牆根處仔細翻找。\n", me);
	write("你撥開碎磚和枯葉﹐發現那塊鬆動的青石磚可以搬開。\n");
	write("石磚後面是一個淺淺的洞穴﹐裡面塞著一卷泛黃的古卷﹗\n");
	write("你小心翼翼地將古卷取出﹐展開一看﹐正是「劍意殘篇」。\n");
	write("看來那個竊賊把贓物藏在這裡﹐卻一直沒來取。\n");

	manuscript = new(__DIR__"npc/obj/ancient_manuscript");
	manuscript->move(me);
	me->set_temp("pending/bookshop_manuscript_found", 1);
	return 1;
}
