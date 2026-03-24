// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "練武場");
	set("long", @LONG
廣場西面有一塊空地﹐被村民們用作練武場。地上插著幾根木樁﹐
旁邊的架子上擺著幾把生了鏽的刀槍。雖然器具簡陋﹐但地面被
踩得堅硬平實﹐看得出經常有人在此操練。一個老兵模樣的漢子
在場中央比劃著招式﹐一板一眼十分認真。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/old_soldier" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}
