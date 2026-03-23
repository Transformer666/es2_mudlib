// Room: /d/luocheng/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "羅城城隍廟");
    set("long", @LONG
這座城隍廟是羅城最大的廟宇﹐廟門口一對石獅子威風凜凜。大
殿中供奉著城隍爺的神像﹐兩旁侍立著判官和牛頭馬面的塑像﹐莊
嚴肅穆。殿前的大香爐銅光鋥亮﹐可見香火之旺盛。每逢廟會﹐廣
場上更是人山人海。
LONG
    );
    set("detail", ([
        "神像" : "城隍爺的神像高約丈許﹐面容威嚴﹐手持令旗﹐目光似乎能洞察一切。\n",
        "石獅" : "一對石獅子蹲踞在廟門兩側﹐雕工精細﹐栩栩如生。\n",
        "香爐" : "一座碩大的銅香爐﹐香煙繚繞﹐爐壁上雕刻著精美的龍鳳紋飾。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"square",
    ]));

    setup();
    replace_program(TEMPLE);
}
