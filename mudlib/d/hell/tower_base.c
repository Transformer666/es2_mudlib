// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "地氣塔底層");
    set("long", @LONG
一座高聳入雲的黑色石塔矗立在你的面前﹐這便是傳說中的地氣
塔。塔身由漆黑的玄鐵石砌成﹐表面刻滿了密密麻麻的封印符文﹐隱
隱散發著幽暗的光芒。塔門洞開﹐門楣上方刻著「地氣塔」三個大字
﹐字跡蒼勁有力。塔內有一道盤旋而上的石階﹐通往上方。
LONG
    );
    set("detail", ([
        "石塔" : "黑色的石塔高聳入雲﹐塔身粗如合抱之木﹐在迷霧中更顯得陰森詭異。\n",
        "符文" : "塔身上的封印符文閃爍著幽暗的光芒﹐似乎在鎮壓著什麼強大的力量。\n",
    ]));
    set("objects", ([
        __DIR__"npc/tower_guard" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"path",
        "up"    : __DIR__"tower_mid",
    ]));

    setup();
    replace_program(ROOM);
}
