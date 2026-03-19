// Room: /d/wutang/wushan_path1.c

inherit ROOM;

void create()
{
    set("short", "武山山徑");
    set("long", @LONG
山路越來越陡﹐兩旁古木參天﹐樹冠將天空遮蔽得只剩下零星的
光斑灑落在地面上。路邊偶爾可以看到一些不知名的野花﹐空氣中
瀰漫著泥土和樹葉的清香。
LONG
    );
    set("exits", ([
	"down" : __DIR__"wushan_foot",
	"up" : __DIR__"wushan_path2",
    ]));

    setup();
    replace_program(ROOM);
}
