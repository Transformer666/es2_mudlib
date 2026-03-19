// Room: /d/wutang/wushan_path3.c

inherit ROOM;

void create()
{
    set("short", "武山山徑");
    set("long", @LONG
山路到這裡分成了兩條岔路﹐一條通往北邊的一個幽暗洞窟﹐洞
口隱約可見一些奇異的光芒﹔另一條往東延伸﹐通向一座若隱若現
的古老神殿。山風在這裡格外強勁﹐吹得松林呼呼作響。
LONG
    );
    set("exits", ([
	"down" : __DIR__"wushan_path2",
	"north" : __DIR__"wushan_cave",
	"east" : __DIR__"temple",
    ]));

    setup();
    replace_program(ROOM);
}
