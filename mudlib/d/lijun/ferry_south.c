// Room: /d/lijun/ferry_south.c

inherit ROOM;

void create()
{
	set("short", "羿水南岸");
	set("long", @LONG
這裡是羿水的南岸﹐一個簡陋的小碼頭。幾根歪歪斜斜的木樁從
水中探出﹐上面繫著渡船的纜繩。岸邊長滿了蘆葦和水草﹐一條泥濘
的小路蜿蜒伸向遠方。回頭望去﹐北岸的鯉君渡隱約可見﹐只能搭乘
渡船才能回去。這裡人煙稀少﹐四周一片荒蕪﹐只有風吹蘆葦的沙沙
聲。
LONG
	);
	set("outdoors", "water");
	set("detail", ([
		"蘆葦" : "一大片蘆葦在風中搖曳﹐白色的蘆花紛飛﹐如同下雪一般。\n",
		"小路" : "一條泥濘的小路往南延伸﹐不知通向何方。也許將來會有道路連接到更遠的地方。\n",
	]));
	set("exits", ([
		"north" : __DIR__"dock",
	]));

	setup();
	replace_program(ROOM);
}
