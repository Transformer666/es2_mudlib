// ghost_lantern.c

inherit ITEM;

void create()
{
	set_name("鬼火燈", ({"ghost_lantern", "lantern"}));
	set_weight(300);
	if( !clonep() ) {
		set("unit", "盞");
		set("value", 100);
		set("long",
			"一盞散發著幽幽綠光的燈籠﹐燈罩是用某種半透明的材料做成\n"
			"的﹐裡面似乎沒有燈芯或油﹐但卻自己發出微弱的光芒。據說這\n"
			"是用亂葬崗的磷火封在燈罩裡做成的。\n");
	}
	setup();
}
