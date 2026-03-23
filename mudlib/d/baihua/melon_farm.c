// Room: /d/baihua/melon_farm.c
// Quest: melon_pest - search for boar tracks here

inherit ROOM;

void create()
{
	set("short", "瓜田");
	set("long", @LONG
一片綠油油的瓜田﹐藤蔓在地上四處蔓延﹐碩大的西瓜藏在葉子
底下﹐圓滾滾的十分喜人。一個老農蹲在田裡﹐一邊察看瓜苗的長勢
﹐一邊自言自語。田邊搭著一個簡陋的草棚﹐用來遮陽避雨。
LONG
	);
	set("objects", ([
		__DIR__"npc/melon_farmer" : 1,
	]));
	set("detail", ([
		"草棚" : "用幾根竹竿搭起來的簡陋棚子﹐上面蓋著稻草﹐勉強能遮陽避雨。\n",
		"瓜苗" : "綠油油的瓜苗長勢喜人﹐但仔細看﹐有幾株被踩踏得亂七八糟﹐\n"
			"泥土裡還有一些深深的蹄印。\n",
	]));
	set("exits", ([
		"north" : __DIR__"garden",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object me;

	me = this_player();
	if( !me ) return 0;

	if( !me->query_temp("pending/melon_pest") ) {
		write("你在瓜田裡看了看﹐西瓜長得很好﹐沒什麼特別的。\n");
		return 1;
	}

	if( me->query("quest/melon_pest_done") ) {
		write("瓜田一片安寧﹐不再有野豬出沒的跡象。\n");
		return 1;
	}

	if( me->query_temp("pending/melon_pest_tracked") ) {
		write("你已經找到了野豬的蹤跡﹐往北邊花園去找找吧。\n");
		return 1;
	}

	write("你蹲下身仔細查看﹐發現幾株瓜苗被踩得稀巴爛﹐泥地上\n"
		"有幾個深深的蹄印﹐還有被啃了一半的西瓜皮。\n");
	write("順著蹄印的方向看去﹐足跡往北邊的花園方向延伸過去。\n");

	me->set_temp("pending/melon_pest_tracked", 1);
	return 1;
}
