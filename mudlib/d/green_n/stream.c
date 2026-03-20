// Room: /d/green_n/stream.c

inherit ROOM;

void create()
{
	set("short", "北溪邊");
	set("long", @LONG
一條清澈的小溪從北方的山脈蜿蜒流下，在草原上劃出一道銀色
的弧線。溪水冰涼刺骨，水底的鵝卵石清晰可見。溪邊長著幾叢蘆
葦，偶爾有水鳥從中飛起。
LONG
	);
	set("outdoors", "wilderness");
	set("detail", ([
		"小溪" : "溪水清澈見底，水流湍急，偶爾能看到幾條小魚在水中穿梭。\n",
	]));
	set("exits", ([
		"west" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}
