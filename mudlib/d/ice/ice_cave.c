// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "冰洞");
	set("long", @LONG
這個天然的冰洞深嵌在冰壁之中，洞壁全由藍色的冰層構成，透著一股幽幽的冷光。洞頂掛滿了尖銳的冰錐，隨時可能掉落。地面上結著厚厚的冰，走在上面十分滑溜。洞穴深處不時傳來冰層擠壓碎裂的聲響。
LONG
	);
	set("objects", ([
		__DIR__"npc/snow_leopard" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"ice_field",
	]));

	setup();
	replace_program(ROOM);
}
