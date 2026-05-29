// dispatch.c -- 京畿支線任務的信物：大內巡院巡檢託人送往尚書府的密函

inherit ITEM;

void create()
{
	set_name("密函", ({ "sealed dispatch", "dispatch", "letter" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "封");
		set("value", 1);
		set("long",
			"一封用火漆密密封緘的文函﹐封皮上鈐著大內巡院的硃紅關防﹐\n"
			"角上一行蠅頭小楷寫著「呈史部尚書府門下」。看那鄭重的封\n"
			"樣﹐裡頭怕是要緊的公文﹐該趕緊送到尚書府門房手上。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
