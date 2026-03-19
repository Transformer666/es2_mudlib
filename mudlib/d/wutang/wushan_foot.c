// Room: /d/wutang/wushan_foot.c

inherit ROOM;

void create()
{
    set("short", "武山山腳");
    set("long", @LONG
這裡是武山的山腳下﹐一條蜿蜒的山路從這裡開始向上延伸﹐消
失在茂密的樹林之中。山腳邊有一塊大石頭﹐上面刻著「武山」兩
個古樸的大字﹐筆劃蒼勁有力。山風吹來﹐帶著一股松木的清香。
LONG
    );
    set("detail", ([
	"大石頭" : "一塊半人多高的大石頭﹐上面刻著「武山」二字﹐字跡古樸蒼勁。\n",
    ]));
    set("exits", ([
	"west" : __DIR__"lane2",
	"up" : __DIR__"wushan_path1",
    ]));

    setup();
    replace_program(ROOM);
}
