// receipt.c -- 京畿支線任務的信物：尚書府門房收下密函後回給的回執

inherit ITEM;

void create()
{
	set_name("回執", ({ "signed receipt", "receipt" }) );
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "紙");
		set("value", 1);
		set("long",
			"一紙尚書府門房簽押的回執﹐上頭註明密函業已收訖﹐末尾按著\n"
			"一個鮮紅的指模與門房的花押。把這回執帶回去交給巡檢﹐這趟\n"
			"差事便算辦妥了。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
