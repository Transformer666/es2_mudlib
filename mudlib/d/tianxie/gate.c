inherit ROOM;

void create()
{
    set("short", "天邪派山門");
    set("long", @LONG
兩根漆黑的石柱矗立在山門兩側﹐柱上刻著猙獰的鬼面紋飾。石柱
之間橫著一塊黑色的匾額﹐上面以血紅色的大字寫著「天邪」二字﹐字
跡如刀刻般鋒利。山門內外瀰漫著一股肅殺之氣。
LONG
    );
    set("exits", ([
        "south" : __DIR__"hidden_path",
        "north" : __DIR__"yard",
    ]));

    setup();
    replace_program(ROOM);
}
