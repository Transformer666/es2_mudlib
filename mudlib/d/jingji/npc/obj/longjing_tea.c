// longjing_tea.c

inherit ITEM;

void create()
{
	set_name("龍井茶", ({"longjing_tea", "tea", "drink"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "壺");
		set("value", 30);
		set("long", "一壺上等龍井茶﹐茶湯碧綠清澈﹐幽香撲鼻﹐令人心曠神怡。\n");
	}
	setup();
}
