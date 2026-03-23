// Room: /d/choyin/temple.c
// Quest: beggar_past - search under statue to find jade bracelet

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "城隍廟");
	set("long", @LONG
一座香火不算旺盛的城隍廟﹐廟門有些斑駁﹐但裡面倒還乾淨整齊。
正殿供奉著城隍爺的塑像﹐面容嚴肅﹐手持判官筆。神像前的香爐裡插
著幾根快要燃盡的香﹐嫋嫋的青煙在廟中繚繞。一個廟祝正在慢悠悠地
打掃著殿前的落葉。
LONG
	);
	set("objects", ([
		__DIR__"npc/monk" : 1,
	]));
	set("no_fight", 1);
	set("detail", ([
		"神像" : "城隍爺的泥塑金身﹐面容肅穆﹐手持判官筆﹐底座是一塊厚重的石台。\n",
		"香爐" : "一隻銅香爐﹐上面滿是香灰﹐爐壁已經被熏得烏黑。\n",
		"石台" : "神像的底座是一塊厚重的石台﹐石台與地面之間似乎有一條細小的縫隙。\n",
	]));
	set("exits", ([
		"east"  : __DIR__"square",
		"north" : "/d/baolian/mountain_path",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object me, bracelet;

	me = this_player();
	if( !me ) return 0;

	if( !arg || (strsrch(arg, "神像") < 0 && strsrch(arg, "statue") < 0
	&&  strsrch(arg, "底座") < 0 && strsrch(arg, "石台") < 0
	&&  strsrch(arg, "底下") < 0) )
		return notify_fail("你想搜索什麼？\n");

	if( me->query("quest/beggar_past_done") ) {
		write("你仔細看了看神像底下﹐什麼也沒有。\n");
		return 1;
	}

	if( !me->query_temp("pending/beggar_past") ) {
		write("你在神像附近查看了一番﹐除了灰塵什麼也沒發現。\n");
		return 1;
	}

	if( me->query_temp("pending/beggar_past_found") ) {
		write("你已經找到玉鐲了﹐趕快拿回去還給老乞婆吧。\n");
		return 1;
	}

	write("你蹲下身來﹐仔細查看神像石台底下的縫隙。\n");
	say(me->query("name") + "蹲在神像底下摸索著什麼。\n");
	write("你伸手探入縫隙﹐指尖觸到一個被布包裹的硬物。\n");
	write("小心翼翼地取出來﹐打開布包﹐裡面是一只翠綠的玉鐲﹗\n");

	bracelet = new(__DIR__"npc/obj/jade_bracelet");
	bracelet->move(me);
	me->set_temp("pending/beggar_past_found", 1);
	return 1;
}
