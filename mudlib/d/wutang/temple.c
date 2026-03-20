// Room: /d/wutang/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "真天神殿");
    set("long", @LONG
這座古老的神殿坐落在武山山頂﹐雖然規模不大﹐但氣勢非凡。
殿中供奉著一座巨大的神像﹐神像面容莊嚴﹐手持寶劍﹐目光似乎
在注視著每一個進入神殿的人。殿前有一座銅鑄的香爐﹐裊裊的青
煙盤旋而上﹐整座神殿瀰漫著一股莊嚴肅穆的氣氛。
LONG
    );
    set("objects", ([
	__DIR__"npc/temple_master" : 1,
    ]));
    set("detail", ([
	"神像" : "一座高大的神像﹐面容莊嚴﹐手持一把寶劍﹐身披金色的袈裟﹐看起來威嚴無比。\n",
	"香爐" : "一座銅鑄的大香爐﹐裊裊的青煙從香爐中升起﹐瀰漫在整座大殿之中。\n",
    ]));
    set("exits", ([
	"west"  : __DIR__"wushan_path3",
	"east"  : "/d/tianshi/path",
	"north" : "/d/xuantian/path",
	"south" : __DIR__"temple_inner",
    ]));

    setup();
    replace_program(TEMPLE);
}
