// trade_ledger.c — 行商帳冊（匪營搜贓任務獎勵）

inherit ITEM;

void create()
{
	set_name("行商帳冊", ({"trade_ledger", "trade ledger", "ledger"}));
	set_weight(300);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 800);
		set("long",
			"一本陳舊的帳冊﹐裡面詳細記錄了從康平到雪亭鎮之間的商路\n"
			"信息﹐包括各地的物價、驛站位置和安全路線。這對行商來說是非\n"
			"常珍貴的資料。封面上寫著「周記商行」四個字。\n");
	}
	setup();
}
