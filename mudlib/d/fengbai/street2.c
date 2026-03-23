// Room: /d/fengbai/street2.c

inherit ROOM;

void create()
{
    set("short", "楓柏村南路");
    set("long", @LONG
泥土小路繼續向南延伸﹐路旁的楓樹越來越密﹐枝葉交錯成了一
片天然的涼棚。路邊有幾畦菜地﹐種著些蘿蔔白菜。一位老農正蹲
在地頭拔草﹐見人經過也不抬頭。遠處隱約可見村子的南口。
LONG
    );
    set("outdoors", "village");
    set("detail", ([
        "菜地" : "幾畦整整齊齊的菜地﹐看得出主人是個勤快人。\n",
        "楓樹" : "一排高大的楓樹﹐枝葉繁茂﹐在路上投下斑駁的樹影。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"street1",
        "south" : __DIR__"sgate",
        "west"  : __DIR__"herb_garden",
    ]));

    setup();
    replace_program(ROOM);
}
