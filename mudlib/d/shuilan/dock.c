// Room: /d/shuilan/dock.c

inherit ROOM;

void create()
{
    set("short", "水嵐碼頭");
    set("long", @LONG
這裡是水嵐縣北邊的一處小碼頭﹐幾條破舊的漁船拴在岸邊的木
樁上﹐隨著水波輕輕搖晃。碼頭上堆放著漁網和魚簍﹐空氣中瀰漫
著濃重的魚腥味。幾個漁民正在岸邊修補漁網﹐不時抬頭望向遠處的
河面。從這裡可以眺望到北邊寬闊的羿水﹐河上偶爾有渡船經過。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/fisherman" : 1,
        __DIR__"npc/boatman" : 1,
    ]));
    set("detail", ([
        "漁船" : "幾條小漁船停泊在岸邊﹐船身因為長年風吹日曬而顯得斑駁。\n",
        "漁網" : "攤在地上的漁網已經修補了好幾處﹐看來漁民的日子並不寬裕。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"ngate",
    ]));

    setup();
    replace_program(ROOM);
}
