// vim: syntax=lpc
// golden_herb.c - 金線蓮 (quest item for haidafu quest)

inherit ITEM;

void create()
{
	set_name("金線蓮", ({"golden herb", "herb", "golden orchid"}));
	set_weight(100);
	if( !clonep() ) {
		set("unit", "株");
		set("value", 200);
		set("long",
			"一株珍貴的金線蓮﹐葉面上有一條條金色的脈絡﹐在光線下閃\n"
			"閃發亮。這種草藥性溫味甘﹐是配製金創藥的關鍵藥材。\n");
	}
	setup();
}
