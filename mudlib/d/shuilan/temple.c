// Room: /d/shuilan/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "水嵐城隍廟");
    set("long", @LONG
這座城隍廟雖然規模不大﹐但在水嵐縣百姓心中的地位卻不容小
覷。廟內供奉著一尊城隍爺的神像﹐據說十分靈驗﹐每到初一十五﹐
善男信女絡繹不絕。大殿兩側的牆壁上畫著因果報應的壁畫﹐色彩
雖已斑駁﹐但畫中人物的神態仍然栩栩如生。
LONG
    );
    set("detail", ([
        "神像" : "城隍爺的神像面目慈祥﹐手持如意﹐身旁還侍立著兩個小鬼差。\n",
        "壁畫" : "牆上的壁畫描繪著善惡有報的故事﹐雖然年代久遠﹐但仍能看出畫師的功力。\n",
        "香爐" : "一座青銅香爐﹐爐中的香灰已經堆得很厚了﹐可見香火之旺盛。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"street2",
    ]));

    setup();
    replace_program(TEMPLE);
}
