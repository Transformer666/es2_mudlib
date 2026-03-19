// Room: /d/wutang/inn_2f.c

inherit ROOM;

void create()
{
    set("short", "醇雨樓二樓");
    set("long", @LONG
二樓的雅座區比樓下安靜了許多﹐幾張雕花桌椅擺放得整整齊齊
﹐靠窗的位置可以眺望整個五堂鎮的廣場。角落裡坐著一個陰沉的
中年男子﹐正默默地喝著茶。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
	__DIR__"npc/haidafu" : 1,
    ]));
    set("exits", ([
	"down" : __DIR__"inn_hall",
	"up" : __DIR__"inn_3f",
    ]));

    setup();
    replace_program(ROOM);
}
