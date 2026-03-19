// Room: /d/wutang/smithy.c

inherit ROOM;

void create()
{
    set("short", "鐵匠鋪");
    set("long", @LONG
這裡是五堂鎮的鐵匠鋪﹐爐火熊熊燃燒著﹐空氣中瀰漫著鐵水
的味道。一個碩大的鐵砧擺在鋪子中間﹐旁邊堆放著各種鐵器的半
成品﹐牆上掛滿了鍬鋤鐮刀等農具。
LONG
    );
    set("detail", ([
	"鐵砧" : "一個沈甸甸的大鐵砧﹐上面佈滿了敲打的痕跡。\n",
	"火爐" : "爐火燒得正旺﹐不時有火星迸出。\n",
    ]));
    set("exits", ([
	"north" : __DIR__"street1",
	"east"  : "/d/jianjia/entrance",
    ]));

    setup();
    replace_program(ROOM);
}
