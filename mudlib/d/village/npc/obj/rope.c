// rope.c

inherit ITEM;

void create()
{
	set_name("麻繩", ({"rope"}));
	set_weight(300);
	if( !clonep() ) {
		set("unit", "條");
		set("value", 15);
		set("long", "一條結實的麻繩﹐大約有數丈長﹐可以用來攀爬或捆綁東西。\n");
	}
	setup();
}
