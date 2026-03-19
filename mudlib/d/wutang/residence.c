// Room: /d/wutang/residence.c

inherit ROOM;

void create()
{
    set("short", "御史別院");
    set("long", @LONG
這裡是官府後面的別院﹐院子不大但收拾得十分整潔。幾株梅樹
沿著院牆種植﹐雖然不是花開時節﹐枝幹依然蒼勁有力。院中有一
口古井﹐井邊放著一個石凳﹐似乎有人常常在此靜坐思考。
LONG
    );
    set("detail", ([
	"梅樹" : "幾株老梅樹﹐枝幹蒼勁﹐看得出來已有些年頭了。\n",
	"古井" : "一口年代久遠的石井﹐井水清澈見底。\n",
    ]));
    set("exits", ([
	"west" : __DIR__"court",
	"east" : "/d/buxuan/entrance",
    ]));

    setup();
    replace_program(ROOM);
}
