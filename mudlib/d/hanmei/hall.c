// Room: /d/hanmei/hall.c

inherit ROOM;

void create()
{
	set("short", "冷梅莊正廳");
	set("long", @LONG
這是冷梅莊的正廳﹐廳堂寬敞﹐正中懸著一幅水墨梅花圖﹐畫下一
張紫檀木的太師椅﹐想是莊主平日待客議事之所。兩側牆上掛著數柄名
劍﹐劍鞘上俱結著一縷紅纓。廳中焚著一爐沉香﹐淡淡的煙氣與窗外飄
進的梅香交織﹐令人心神俱清。往西可回到前院。
LONG
	);
	set("detail", ([
		"梅花圖" : "一幅水墨梅花圖以淡墨寫意﹐疏影橫斜﹐筆意孤高﹐落款只有
「冷梅」二字。
",
		"名劍" : "牆上幾柄名劍鞘身古樸﹐顯是傳承已久的利器﹐非莊中高手不得佩
用。
",
	]));
	set("objects", ([
		__DIR__"npc/master" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"yard",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
