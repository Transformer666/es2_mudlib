// Room: /d/choyin/choyin_road.c

inherit ROOM;

void create()
{
	set("short", "喬陰官道");
	set("long", @LONG
一條寬闊平坦的官道﹐連接著喬陰縣城和五堂鎮。路面鋪著碎石﹐
兩旁栽種著楊柳﹐柳條在風中輕輕搖曳。遠處可以看到五堂鎮的城牆
輪廓﹐不時有來往的商旅和趕路的行人經過。路邊偶爾能看到官府設置
的里程碑和指路牌。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"north" : __DIR__"sgate",
		"south" : "/d/wutang/sgate",
	]));

	setup();
	replace_program(ROOM);
}
