// Room: /d/fengcheng/forge.c

inherit ROOM;

void create()
{
    set("short", "鐵匠鋪");
    set("long", @LONG
這裡是風城唯一的鐵匠鋪﹐一座矮小的石屋﹐屋頂的煙囪裡不
斷冒出滾滾黑煙。屋內爐火通明﹐一個壯漢赤著上身在鐵砧前揮舞
著大錘﹐叮叮噹噹的打鐵聲震耳欲聾。牆上掛著幾把打好的刀劍﹐
地上散落著鐵屑和碳渣。這裡的鐵匠手藝不錯﹐據說天山附近幾個
門派的兵器都曾在這裡修繕過。
LONG
    );
    set("objects", ([
        __DIR__"npc/blacksmith" : 1,
    ]));
    set("detail", ([
        "鐵砧" : "一座沉重的鐵砧﹐表面佈滿了密密麻麻的錘印﹐顯然已經用了很多年。\n",
        "爐火" : "爐中的炭火燒得通紅﹐熱浪撲面而來﹐讓人忍不住退後幾步。\n",
        "刀劍" : "牆上掛著幾把已經打好的刀劍﹐寒光閃閃﹐看起來十分鋒利。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"market",
    ]));

    setup();
    replace_program(ROOM);
}
