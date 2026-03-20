// Room: /d/lijun/dock.c

inherit ROOM;

void create()
{
	set("short", "碼頭");
	set("long", @LONG
這裡是鯉君渡的碼頭﹐也是整個渡口最重要的地方。幾根粗大的
木樁釘在河岸邊﹐上面繫著粗麻繩﹐一條寬底渡船正隨著波浪上下起
伏。羿水在腳下奔流而過﹐河面寬闊﹐水流湍急﹐對岸隱約可見一片
蘆葦蕩。碼頭的木板被河水浸泡得發黑﹐走上去嘎吱作響。東邊和西
邊各有一條沿河小路﹐往南是一片開闊的河灘。
你可以搭乘渡船(board)到對岸去。
LONG
	);
	set("outdoors", "water");
	set("detail", ([
		"渡船" : "一條寬底平船﹐足以載十餘人。船頭插著一面破舊的旗子﹐上面寫著一個大大的「渡」字。你可以 board 搭船過河。\n",
		"河水" : "羿水滾滾東流﹐河面寬約十丈﹐水色青碧﹐不時有魚兒躍出水面。\n",
		"木樁" : "幾根碗口粗的木樁深深釘入泥中﹐上面繫著粗麻繩﹐用來拴住渡船。\n",
	]));
	set("objects", ([
		__DIR__"npc/ferryman" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"street",
		"east" : __DIR__"riverside_e",
		"west" : __DIR__"riverside_w",
		"south" : __DIR__"riverbank",
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

	if( this_player()->query("life_form") == "ghost" ) {
		write("你現在是鬼魂﹐沒辦法搭船。\n");
		return 1;
	}
	write("你跳上渡船﹐老艄公開始撐篙。\n");
	message_vision("$N跳上了渡船。\n", this_player());
	ferry = new(__DIR__"ferry");
	this_player()->move(ferry);
	return 1;
}
