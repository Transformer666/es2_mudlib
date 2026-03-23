// Room: /d/weiguo/egate.c

inherit ROOM;

void create()
{
	set("short", "衛國東城門");
	set("long", @LONG
衛國鎮東面的城門﹐是一座堅固的軍事要塞大門。厚重的石牆上
佈滿了箭孔和瞭望口﹐城門洞裡架著粗大的鐵柵﹐隨時可以放下封
鎖通道。門前的地面被踩得光溜溜的﹐顯示這裡日常人員進出頻繁。
兩名全副武裝的哨兵持槍站在門邊﹐目光如炬地審視著每一個過路人。
門外是通往東方荒野的小路。
LONG
	);
	set("outdoors", "fortress");
	set("objects", ([
		__DIR__"npc/sentry" : 2,
	]));
	set("exits", ([
		"east"  : "/d/road/wild_path1",
		"west"  : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}
