// Room: /d/manglin/path2.c

inherit ROOM;

void create()
{
	set("short", "莽林深處");
	set("long", @LONG
莽林深處﹐光線更加昏暗﹐巨大的樹幹上纏繞著粗壯的藤蔓﹐有
些樹根裸露在外﹐形成天然的障礙。空氣中瀰漫著一股腐朽的氣味﹐
地上散落著一些白骨﹐不知是獸骨還是人骨。偶爾能聽到低沉的嗥叫
聲從更深處傳來。
LONG
	);
	set("outdoors", "forest");
	set("objects", ([
		__DIR__"npc/black_bear" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"path1",
		"north" : __DIR__"path3",
	]));

	setup();
	replace_program(ROOM);
}
