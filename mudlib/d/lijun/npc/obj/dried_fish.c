// vim: syntax=lpc

inherit ITEM;

void create()
{
	set_name("魚乾", ({"dried_fish", "fish"}));
	set_weight(300);
	if( !clonep() ) {
		set("unit", "條");
		set("value", 10);
		set("long", "一條用鹽醃製後風乾的河魚﹐是渡口漁民常做的乾糧﹐可以存放很久。\n");
	}
	setup();
}
