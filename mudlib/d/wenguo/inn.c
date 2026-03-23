// Room: /d/wenguo/inn.c

#include <room.h>

inherit INN;

private void create()
{
	set("short", "文國客棧");
	set("long", @LONG
文國客棧佈置得雅緻整潔﹐與一般鄉鎮的客棧大不相同。大廳裡
擺著幾張檀木桌椅﹐牆上掛著幾幅字畫﹐顯得頗有書卷氣。櫃臺後
面的架子上擺著幾壇好酒﹐角落裡還放著一架古琴。這裡常有往來的
文人墨客和過路官員投宿﹐是縣城裡最體面的一家客棧。
LONG
	);
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/innkeeper" : 1,
	]));
	set("detail", ([
		"字畫" : "牆上掛著幾幅山水畫﹐筆法雋秀﹐旁邊還有幾幅文人的題詩。\n",
		"古琴" : "一張七弦琴靜靜地擱在角落的琴架上﹐看起來已經很久沒有人彈奏了。\n",
	]));
	set("exits", ([
		"south" : __DIR__"square",
	]));

	setup();
}
