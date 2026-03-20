// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "軍營附近的大路");
    set("long", @LONG
大路在這裡分出一條岔路往北通往振武軍營﹐路口豎著一面大旗﹐
上面寫著「振武」二字﹐在風中獵獵作響。主路繼續往西延伸﹐通往
五堂鎮。偶爾能看到成隊的士兵操練著從軍營方向走來。
LONG
    );
    set("outdoors", "road");
    set("exits", ([
	"east"  : __DIR__"south_road1",
	"west"  : "/d/zhenwu/gate",
    ]));

    setup();
    replace_program(ROOM);
}
