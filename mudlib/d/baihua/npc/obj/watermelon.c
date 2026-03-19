// watermelon.c

inherit ITEM;

void create()
{
	set_name("西瓜", ({"watermelon", "melon", "food"}));
	set_weight(3000);
	if( !clonep() ) {
		set("unit", "個");
		set("value", 20);
		set("long", "一個又大又圓的西瓜﹐翠綠的外皮上有深綠色的條紋﹐拍起來砰砰作響﹐一看就知道是個熟透了的好瓜。\n");
	}
	setup();
}
