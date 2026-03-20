// Room: /d/lijun/ferry_south.c

inherit ROOM;

void create()
{
	set("short", "羿水南岸");
	set("long", @LONG
這裡是羿水的南岸﹐一個簡陋的小碼頭。幾根歪歪斜斜的木樁從
水中探出﹐上面繫著渡船的纜繩。岸邊長滿了蘆葦和水草﹐一條泥濘
的小路蜿蜒伸向遠方。回頭望去﹐北岸的鯉君渡隱約可見﹐只能搭乘
渡船(board)才能回去。這裡人煙稀少﹐四周一片荒蕪﹐只有風吹蘆葦
的沙沙聲。
LONG
	);
	set("outdoors", "water");
	set("detail", ([
		"蘆葦" : "一大片蘆葦在風中搖曳﹐白色的蘆花紛飛﹐如同下雪一般。\n",
		"小路" : "一條泥濘的小路往東南延伸﹐隱約可以聞到梅花的清香。\n",
		"渡船" : "岸邊停著渡船﹐你可以搭船到鯉君渡(board lijun)或五堂鎮(board wutang)。\n",
	]));
	set("exits", ([
		"southeast" : "/d/lengmei/road",
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_board", "board");
}

int do_board(string arg)
{
	object ferry;
	string ferry_file;

	if( this_player()->query("life_form") == "ghost" ) {
		write("你現在是鬼魂﹐沒辦法搭船。\n");
		return 1;
	}

	switch(arg) {
	case "lijun":
	case "鯉君渡":
		write("你跳上渡船﹐船夫撐篙往鯉君渡划去。\n");
		ferry_file = __DIR__"ferry_back";
		break;
	case "wutang":
	case "五堂":
		write("你跳上渡船﹐船夫撐篙往五堂鎮划去。\n");
		ferry_file = "/d/wutang/ferry_back";
		break;
	default:
		write("你要搭船去哪裡﹖可以去鯉君渡(board lijun)或五堂鎮(board wutang)。\n");
		return 1;
	}

	message_vision("$N跳上了渡船。\n", this_player());
	ferry = new(ferry_file);
	this_player()->move(ferry);
	return 1;
}
