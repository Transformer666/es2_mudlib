// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "峽谷岩棚");
	set("long", @LONG
這是崖壁上一處突出的岩棚，勉強可以容納幾個人站立。從這裡俯瞰谷底，可以看到溪流如銀帶般蜿蜒而去。岩棚上有一些被風化的古老石刻，依稀能辨認出一些文字和圖案。
LONG
	);
	set("objects", ([
		__DIR__"npc/hermit" : 1,
	]));
	set("outdoors", "wilderness");
	set("exits", ([
		"north" : __DIR__"cliff_face",
	]));

	setup();
	replace_program(ROOM);
}
