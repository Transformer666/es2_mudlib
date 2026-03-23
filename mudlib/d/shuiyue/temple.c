// Room: /d/shuiyue/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "水月村土地廟");
    set("long", @LONG
這是一座小巧的土地廟﹐紅磚砌成的神龕裡供奉著一尊土地公
神像。廟雖小﹐卻收拾得乾乾淨淨﹐香爐中的線香還在冒著輕煙﹐
看得出村民們平日裡常來祭拜。廟旁有一棵老槐樹﹐枝繁葉茂。
LONG
    );
    set("detail", ([
        "神像" : "一尊慈眉善目的土地公神像﹐雕工雖然粗糙﹐卻透著一股質樸的韻味。\n",
        "香爐" : "一個小小的銅香爐﹐裡面插著幾柱線香﹐輕煙裊裊。\n",
    ]));
    set("exits", ([
        "south" : __DIR__"square",
    ]));

    setup();
    replace_program(TEMPLE);
}
