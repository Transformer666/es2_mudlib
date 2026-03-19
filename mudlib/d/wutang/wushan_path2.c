// Room: /d/wutang/wushan_path2.c

inherit ROOM;

void create()
{
    set("short", "武山山徑");
    set("long", @LONG
山路更加陡峭了﹐有些地方甚至需要手腳並用才能攀爬。透過樹
木的間隙﹐可以看到山下五堂鎮的全景﹐房屋鱗次櫛比﹐河流如帶
般蜿蜒而過。遠處的天際隱約可見連綿的山脈。
LONG
    );
    set("exits", ([
	"down" : __DIR__"wushan_path1",
	"up" : __DIR__"wushan_path3",
    ]));

    setup();
    replace_program(ROOM);
}
