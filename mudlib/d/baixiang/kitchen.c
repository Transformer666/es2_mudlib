// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "齋堂");
    set("long", @LONG
一間寬敞明亮的齋堂，幾排長條木桌上擺放著素淨的碗筷。牆邊
的灶台上蒸著白米飯，幾口大鍋裡煮著時蔬豆腐。白象寺的僧人們嚴
守清規，一日兩餐皆為素齋。空氣中瀰漫著淡淡的米香和蔬菜的清甜，
混合著從殿堂飄來的檀香，別有一番禪意。
LONG
    );
    set("exits", ([
        "east" : __DIR__"courtyard",
    ]));

    set("objects", ([
        __DIR__"npc/cook" : 1,
    ]));

    setup();
}
