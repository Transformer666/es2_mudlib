// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "菩提林");
    set("long", @LONG
大雄寶殿後方的一片幽靜樹林，數十棵菩提樹枝葉交織，遮天蔽
日。林間鋪著鵝卵石小路，路旁散落著幾塊巨石，石上刻著歷代住持的
偈語。一縷縷陽光穿過枝葉灑落在地上，形成斑駁的光影。林中鳥語花
香，不時有松鼠在枝頭跳躍，一派祥和寧靜的景象。
LONG
    );
    set("exits", ([
        "south" : __DIR__"main_hall",
    ]));

    set("objects", ([
        __DIR__"npc/gardener" : 1,
    ]));

    setup();
}
