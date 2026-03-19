// Room: /d/lijun/riverside_e.c

inherit ROOM;

void create()
{
	set("short", "河畔東段");
	set("long", @LONG
沿著河岸往東走的一條小路﹐路面泥濘﹐長滿了雜草。右邊是奔
流不息的羿水﹐左邊是幾叢茂密的蘆葦。偶爾能看到水鳥從蘆葦叢中
飛起﹐發出幾聲清脆的啼叫。這一帶比較偏僻﹐偶爾有河匪出沒﹐行
人最好結伴而行。往北走可以到小市集﹐往西回到碼頭。
LONG
	);
	set("outdoors", "water");
	set("objects", ([
		__DIR__"npc/bandit" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"dock",
		"north" : __DIR__"market",
	]));

	setup();
	replace_program(ROOM);
}
