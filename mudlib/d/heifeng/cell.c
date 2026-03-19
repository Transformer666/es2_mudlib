// Room: /d/heifeng/cell.c

inherit ROOM;

void create()
{
	set("short", "囚室");
	set("long", @LONG
一間陰暗潮濕的囚室﹐牆上掛著幾副鐵鏈和枷鎖。地上鋪著一層
發霉的稻草﹐角落裡放著一個缺了口的陶碗﹐碗裡還有些剩飯殘羹。
一個衣衫襤褸的商人蜷縮在角落﹐看到有人來﹐眼中閃過一絲希望。
LONG
	);
	set("objects", ([
		__DIR__"npc/prisoner" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"yard",
	]));

	setup();
	replace_program(ROOM);
}
