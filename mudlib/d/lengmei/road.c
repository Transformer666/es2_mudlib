inherit ROOM;

void create()
{
    set("short", "梅林小路");
    set("long", @LONG
一條幽靜的小路穿過梅林﹐兩旁種滿了梅花樹。雖然不是花開時節﹐
蒼勁的枝幹也別有一番風味。空氣中隱約飄著淡淡的梅花清香﹐地上鋪
著一層薄薄的落葉。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "west" : "/d/snow/egate",
        "east" : __DIR__"gate",
    ]));

    setup();
    replace_program(ROOM);
}
