// Room: /d/luocheng/wgate.c

inherit ROOM;

void create()
{
    set("short", "羅城西門");
    set("long", @LONG
這裡是羅城的西門﹐城門高大堅固﹐門洞上方刻著「通濟門」三
個大字。城門外是一條通往西方的官道﹐據說沿著這條路走﹐可以到
達李家村和雪亭鎮方向。來往的商隊和旅人絡繹不絕﹐守城的兵士
仔細盤查著每一個進城的人。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/guard" : 2,
    ]));
    set("exits", ([
        "east"      : __DIR__"square",
        "southwest" : "/d/lee/r2",
    ]));

    setup();
    replace_program(ROOM);
}
