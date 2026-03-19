// Room: /d/manglin/pond.c

inherit ROOM;

void create()
{
	set("short", "林中水潭");
	set("long", @LONG
林中有一汪清澈的水潭﹐潭水碧綠﹐深不見底。潭邊長著幾叢蘆葦
﹐水面上浮著幾片落葉。幾隻不知名的水鳥在潭邊覓食﹐見到有人來便
撲楞楞地飛走了。潭水倒映著四周的樹影﹐環境十分清幽。
LONG
	);
	set("outdoors", "forest");
	set("exits", ([
		"south" : __DIR__"clearing",
	]));

	setup();
	replace_program(ROOM);
}
