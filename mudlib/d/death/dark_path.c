// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "幽暗長廊");
	set("long", @LONG
一條似乎永無盡頭的幽暗長廊向前延伸，兩側的牆壁上掛著忽明忽暗的鬼火，散發著詭異的綠色光芒。地面上佈滿了裂痕，縫隙中不時冒出陣陣黑煙。空氣冰冷而潮濕，每走一步都感覺身體在被某種力量侵蝕。
LONG
	);
	set("objects", ([
		__DIR__"npc/wandering_soul" : 2,
	]));
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"bone_field",
		"east" : __DIR__"soul_river",
	]));

	setup();
	replace_program(ROOM);
}
