// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "西側牢房");
	set("long", @LONG
這間牢房的鐵欄已經被鏽蝕得不成樣子，但依然堅固地鎖著。房內除了一堆爛草和幾根鐵鏈之外什麼都沒有。牆壁上刻著密密麻麻的字跡，有些是求救的話語，有些則是瘋狂的囈語，讓人看了不寒而慄。
LONG
	);
	set("exits", ([
		"east" : __DIR__"corridor",
	]));

	setup();
	replace_program(ROOM);
}
