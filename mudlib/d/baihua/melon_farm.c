// Room: /d/baihua/melon_farm.c

inherit ROOM;

void create()
{
	set("short", "瓜田");
	set("long", @LONG
一片綠油油的瓜田﹐藤蔓在地上四處蔓延﹐碩大的西瓜藏在葉子
底下﹐圓滾滾的十分喜人。一個老農蹲在田裡﹐一邊察看瓜苗的長勢
﹐一邊自言自語。田邊搭著一個簡陋的草棚﹐用來遮陽避雨。
LONG
	);
	set("objects", ([
		__DIR__"npc/melon_farmer" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"garden",
	]));

	setup();
	replace_program(ROOM);
}
