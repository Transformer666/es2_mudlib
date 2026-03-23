// Room: /d/luocheng/square.c

inherit ROOM;

void create()
{
    set("short", "羅城廣場");
    set("long", @LONG
這裡是羅城的中央廣場﹐羅城地處東方要衝﹐是南來北往的商旅
必經之地﹐因此這個廣場上總是熙熙攘攘﹐人聲鼎沸。廣場周圍商
鋪林立﹐各種叫賣聲此起彼落。廣場中央豎著一根高大的旗杆﹐上
面飄揚著一面繡著「羅」字的大旗。
LONG
    );
    set("objects", ([
        __DIR__"npc/villager" : 2,
    ]));
    set("detail", ([
        "旗杆" : "一根高大的旗杆﹐上面飄揚著羅城的城旗﹐在風中獵獵作響。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"street1",
        "south" : __DIR__"temple",
        "east"  : __DIR__"store",
        "west"  : __DIR__"wgate",
    ]));

    setup();
    replace_program(ROOM);
}
