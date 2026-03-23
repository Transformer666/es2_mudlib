// vim: syntax=lpc
// Room: /d/baihua/shrine.c
// Quest: 仙女畫卷之謎 - examine painting to find jade offering

#include <room.h>

inherit TEMPLE;

int do_examine_painting(string arg);

void create()
{
	set("short", "小祠堂");
	set("long", @LONG
一座小小的祠堂﹐供奉著百花村歷代先人的牌位。祠堂雖小﹐但打
掃得一塵不染﹐供桌上擺著幾盤鮮花和幾碟供品。牆上掛著一幅褪色的
畫卷﹐畫的是一個手持花籃的仙女﹐據說是百花村的守護神。
LONG
	);
	set("no_fight", 1);
	set("detail", ([
		"牌位" : "一排排木製牌位﹐上面用金漆寫著歷代先人的名諱﹐最古老的已經看不清字跡了。\n",
		"供品" : "供桌上擺著幾碟水果和一盤剛摘的鮮花﹐看得出有人天天在打理。\n",
		"畫卷" : "一幅褪色的古畫﹐畫中一位身著白衣的仙女手持花籃﹐衣袂飄飄。\n"
			"仔細看去﹐畫卷下緣似乎有些鬆動﹐像是被人動過的樣子。\n"
			"也許可以試試 examine painting 仔細看看。\n",
	]));
	set("exits", ([
		"south" : __DIR__"inn",
	]));
	set("objects", ([
		__DIR__"npc/shrine_keeper" : 1,
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_examine_painting", "examine");
}

int do_examine_painting(string arg)
{
	object me = this_player();

	if( !arg || (strsrch(arg, "painting") < 0 && strsrch(arg, "畫卷") < 0
	&&  strsrch(arg, "畫") < 0) )
		return 0;

	if( !me ) return 0;

	if( !me->query_temp("pending/shrine_painting") ) {
		write("你仔細端詳著這幅畫卷﹐畫中的仙女栩栩如生﹐手中的花籃似乎\n"
			"和供桌上的鮮花遙相呼應。畫的下緣有些鬆動﹐但你不確定是否\n"
			"應該動它。也許該問問祠堂婆婆。\n");
		return 1;
	}

	if( me->query("quest/shrine_painting_done") ) {
		write("畫卷後面已經空了﹐你已經把古玉交給婆婆了。\n");
		return 1;
	}

	if( me->query_temp("pending/shrine_jade_found") ) {
		write("你已經找到古玉了﹐趕快拿給婆婆看看吧。\n");
		return 1;
	}

	object jade;

	write("你小心翼翼地掀起畫卷的下緣﹐發現畫卷背面的牆上有一個淺淺的凹槽。\n");
	say(me->query("name") + "小心地掀起牆上的畫卷查看。\n");
	write("凹槽裡靜靜地躺著一塊雕成花籃形狀的古玉﹐和畫中仙女手持的花籃一模一樣﹗\n");
	write("你把古玉取了出來﹐它觸手溫潤﹐似乎還帶著一絲暖意。\n");

	jade = new(__DIR__"npc/obj/jade_offering");
	jade->move(me);
	me->set_temp("pending/shrine_jade_found", 1);
	return 1;
}
