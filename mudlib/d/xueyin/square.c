inherit ROOM;

void create()
{
    set("short", "莊前廣場");
    set("long", @LONG
雪吟莊前的一塊空地﹐地面鋪著方石板。廣場中央立著一塊大石碑﹐
上面刻著雪吟莊的莊規﹐字跡蒼勁有力。幾名莊丁在廣場上巡邏﹐西
面是一家商鋪﹐東面有一座小廟。
LONG
    );
    set("exits", ([
        "north" : __DIR__"street",
        "west"  : __DIR__"store",
        "east"  : __DIR__"temple",
    ]));

    setup();
    replace_program(ROOM);
}
