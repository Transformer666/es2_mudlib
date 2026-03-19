// herb_tea.c

inherit ITEM;

void create()
{
	set_name("草藥茶", ({"herb_tea", "tea", "drink"}));
	set_weight(300);
	if( !clonep() ) {
		set("unit", "碗");
		set("value", 15);
		set("long", "一碗用山裡採來的草藥熬製的茶﹐顏色微黃﹐帶著淡淡的苦味和草香。\n");
	}
	setup();
}
