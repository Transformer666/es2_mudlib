// Room: /d/fengcheng/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "風城城隍廟");
    set("long", @LONG
這座城隍廟雖然不大﹐卻是風城百姓信仰的中心。廟內供奉著一
尊城隍爺的神像﹐神像面容威嚴﹐身披官服﹐左手持笏板﹐右手執
判筆。廟前一座鐵鑄的大香爐﹐終年香火不斷﹐裊裊青煙在寒風中
飄散。每逢初一十五﹐城中百姓都會前來上香祈福。
LONG
    );
    set("detail", ([
        "神像" : "城隍爺的神像約有一人多高﹐面容威嚴﹐彷彿能洞察世間一切善惡。\n",
        "香爐" : "一座鐵鑄的大香爐﹐爐中插滿了線香﹐青煙裊裊﹐瀰漫著淡淡的檀香味。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"ngate",
        "south" : __DIR__"square",
        "east"  : __DIR__"yamen",
    ]));

    setup();
    replace_program(TEMPLE);
}
