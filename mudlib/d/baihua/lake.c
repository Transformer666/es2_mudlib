// vim: syntax=lpc
// Room: /d/baihua/lake.c
// Quest: 學童丟書 - search here to find student's lost book

inherit ROOM;

int do_search(string arg);

void create()
{
	set("short", "湖邊");
	set("long", @LONG
村子南邊有一個小湖﹐湖水清澈見底﹐水面上浮著幾朵粉紅色的蓮
花。湖邊長著幾棵垂柳﹐柳條拂著水面﹐倒映在湖中。幾隻白鷺站在
淺水處﹐不時低頭啄食小魚。這裡環境清幽﹐是個休憩的好地方。
湖邊的草叢裡似乎有什麼東西。
LONG
	);
	set("outdoors", "village");
	set("detail", ([
		"草叢" : "茂密的草叢﹐也許可以搜查(search)一下。\n",
		"蓮花" : "幾朵粉紅色的蓮花﹐在微風中輕輕搖曳﹐十分好看。\n",
	]));
	set("exits", ([
		"north" : __DIR__"street",
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
	object me, book;

	me = this_player();
	if( !me ) return 0;

	if( me->query("quest/student_lost_book_done") ) {
		write("你在湖邊翻找了一陣﹐沒什麼特別的東西。\n");
		return 1;
	}

	if( !me->query_temp("pending/student_lost_book") ) {
		write("你在湖邊隨意看了看﹐沒發現什麼有趣的東西。\n");
		return 1;
	}

	if( me->query_temp("pending/student_book_found") ) {
		write("你已經找到書了﹐趕快還給那個小學童吧。\n");
		return 1;
	}

	message_vision("$N蹲下身子﹐在湖邊的草叢中仔細翻找。\n", me);
	write("你撥開一叢茂密的柳草﹐在水邊的泥地裡發現了一冊薄薄的書。\n");
	write("書頁被露水打濕了﹐邊角沾了些泥巴﹐但上面的字跡還可以辨認。\n");
	write("封面上寫著「千字文」﹐扉頁上歪歪扭扭地寫著一個「林」字。\n");
	write("看來這就是那個小學童丟失的書了。\n");

	book = new(__DIR__"npc/obj/student_book");
	book->move(me);
	me->set_temp("pending/student_book_found", 1);
	return 1;
}
