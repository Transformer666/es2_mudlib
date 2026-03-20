// torch.c

inherit ITEM;

void create()
{
	set_name("火把", ({"torch"}));
	set_weight(400);
	if( !clonep() ) {
		set("unit", "支");
		set("value", 10);
		set("long", "一支用松脂浸過的火把﹐點燃後可以照亮四周。\n");
	}
	setup();
}
