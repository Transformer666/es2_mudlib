// jade_bracelet.c - 老乞婆的玉鐲

inherit ITEM;

void create()
{
	set_name("玉鐲", ({"jade bracelet", "bracelet", "jade_bracelet"}));
	set_weight(200);
	if( !clonep() ) {
		set("unit", "只");
		set("value", 500);
		set("long",
			"一只溫潤的翠玉手鐲﹐質地通透﹐隱隱泛著柔和的綠光。鐲子\n"
			"內側刻著兩個細小的字﹕「念慈」。雖然在灰塵中埋了不知多少年﹐\n"
			"擦拭之後依舊晶瑩剔透﹐顯然不是凡品。\n");
	}
	setup();
}
