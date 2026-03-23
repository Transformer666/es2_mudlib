// Room: /d/fengcheng/square.c

inherit ROOM;

void create()
{
    set("short", "風城廣場");
    set("long", @LONG
這裡是風城的中央廣場﹐四周圍繞著高大的石砌建築﹐因為靠近
天山山脈﹐這裡的建築風格與中原大不相同﹐厚重的石牆和寬闊的
屋頂是為了抵禦北方的風雪。廣場中央有一座石造的碑亭﹐上面刻
著風城的由來。來往的行人大多穿著厚實的皮襖﹐步履匆匆。
LONG
    );
    set("objects", ([
        __DIR__"npc/villager" : 2,
    ]));
    set("detail", ([
        "碑亭" : "一座石造的碑亭﹐碑文記載著風城建城的歷史﹐據說此城已有數百年歷史﹐是天山腳下最大的城鎮。\n",
        "石牆" : "厚重的石牆能夠抵禦北方的嚴寒和風沙﹐牆面上還能看到歲月留下的痕跡。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"temple",
        "south" : __DIR__"street1",
        "east"  : __DIR__"store",
        "west"  : __DIR__"inn_hall",
    ]));

    setup();
    replace_program(ROOM);
}
