// Room: /d/weiguo/street.c

inherit ROOM;

void create()
{
	set("short", "衛國鎮街道");
	set("long", @LONG
一條筆直的石板路穿過鎮子中央，路面被士兵們的靴子磨得十分光
滑。街道兩旁是一些結實的石頭房屋，大多是為駐軍和往來商旅提供補
給的店鋪。幾個身著甲冑的士兵三三兩兩地走過，腰間佩刀在陽光下閃
閃發光。空氣中隱約飄來鐵匠鋪的煤煙味和馬棚的氣息。
LONG
	);
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"square",
		"east"  : __DIR__"smithy",
		"west"  : __DIR__"temple",
	]));

	setup();
	replace_program(ROOM);
}
