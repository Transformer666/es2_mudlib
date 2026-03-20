// talisman.c

inherit ITEM;

void create()
{
	set_name("符紙", ({"talisman", "charm", "paper"}));
	set_weight(50);
	if( !clonep() ) {
		set("unit", "張");
		set("value", 10);
		set("long", "一張粗糙的黃紙﹐上面用硃砂畫著歪歪扭扭的符文﹐也不知道有沒有用。\n");
	}
	setup();
}
