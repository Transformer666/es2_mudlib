// Room: /d/wutang/herb_shop.c

inherit ROOM;

void create()
{
    set("short", "濟世堂藥鋪");
    set("long", @LONG
這裡是「濟世堂」藥鋪﹐門口掛著一塊斑駁的木匾﹐上面寫著
「懸壺濟世」四個大字。鋪子裡陳列著一排排的藥櫃﹐每個抽屜上
都貼著黃紙標籤﹐空氣中瀰漫著淡淡的藥香。
LONG
    );
    set("detail", ([
	"藥櫃" : "藥櫃上密密麻麻的小抽屜裡分門別類地放著各種草藥。\n",
	"木匾" : "上面龍飛鳳舞地寫著「懸壺濟世」四個大字﹐落款已經模糊不清了。\n",
    ]));
    set("objects", ([
	__DIR__"npc/obj/golden_herb" : 3,
    ]));
    set("exits", ([
	"south" : __DIR__"lane1",
	"east"  : "/d/wutuo/entrance",
    ]));

    setup();
    replace_program(ROOM);
}
