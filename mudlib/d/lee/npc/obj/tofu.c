// tofu.c

inherit ITEM;

void create()
{
	set_name("豆腐", ({"tofu", "food"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "塊");
		set("value", 8);
		set("long", "一塊白嫩嫩的豆腐﹐是李家村祖傳手藝做出來的﹐入口即化﹐豆香濃郁。\n");
	}
	setup();
}
