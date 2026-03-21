// Room: /d/graveyard/shrine.c

#include <ansi.h>

inherit ROOM;

string shrine_long();

void create()
{
	set("short", "破廟");
	set("long", (: shrine_long :));
	set("objects", ([
		__DIR__"npc/grave_keeper" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"grave3",
		"down" : "/d/hell/entrance",
	]));

	setup();
	// 不使用 replace_program — 有自訂函數
}

string shrine_long()
{
	string desc =
"一座破敗不堪的小廟﹐屋頂塌了一半﹐牆壁裂開了好幾條大縫。廟\n"
"裡的神像早已面目全非﹐只剩下一個模糊的輪廓。供桌上積滿了灰塵﹐\n"
"蜘蛛網從屋角一直拉到門框。儘管如此﹐廟中還是住著一個守墓人﹐日\n"
"夜看守著這片亂葬崗。\n";

	if( this_player() && this_player()->query("life_form") == "ghost" )
		desc += "    你注意到神像底座有一道" RED "裂縫(crack)" NOR "﹐"
			"隱約透出陣陣陰風﹐似乎可以往下(down)走。\n";

	return desc;
}

void init()
{
	::init();
	if( this_player() && this_player()->query("life_form") == "ghost" )
		add_action("do_go_down", "down");
}

int do_go_down(string arg)
{
	if( this_player()->query("life_form") != "ghost" ) {
		write("你不知道要怎麼往下走。\n");
		return 1;
	}
	write("你的鬼魂穿過裂縫﹐向下飄去 ...\n");
	message_vision("$N的身影漸漸消融在裂縫中。\n", this_player());
	this_player()->move("/d/hell/entrance");
	return 1;
}
