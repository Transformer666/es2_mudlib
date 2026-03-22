// roast_chicken.c

inherit ITEM;

void create()
{
	set_name("龍安燒雞", ({"roast_chicken", "chicken", "food"}));
	set_weight(300);
	if( !clonep() ) {
		set("unit", "隻");
		set("value", 50);
		set("long", "一隻烤得金黃油亮的燒雞﹐外皮酥脆﹐肉質鮮嫩﹐是龍安城的招牌名菜。\n");
	}
	setup();
}
