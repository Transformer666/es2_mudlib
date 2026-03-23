// Room: /d/qianchang/inn.c

#include <room.h>

inherit INN;

private void create()
{
	set("short", "前場客棧");
	set("long", @LONG
一間樸素的小客棧，大廳裡擺著幾張粗木桌椅，桌面被擦得還算
乾淨。空氣中瀰漫著飯菜的香氣，夾雜著淡淡的酒味。櫃臺後面
的架子上擺著幾罈土釀米酒，牆角堆著一摞洗好的碗碟。來往的多
是過路的行商和趕腳的腳夫，三三兩兩地圍坐在一起吃飯聊天。
LONG
	);
	set("objects", ([
		__DIR__"npc/innkeeper" : 1,
	]));
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"square",
	]));

	setup();
}
