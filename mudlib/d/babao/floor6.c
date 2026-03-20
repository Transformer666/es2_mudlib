// Room: /d/babao/floor6.c

inherit ROOM;

void create()
{
    set("short", "八寶樓六樓 - 魔境");
    set("long", @LONG
第六層裝飾得頗為詭異，四壁掛著各種奇形怪狀的符咒和法器，正
中央是一座巨大的祭壇，壇上燃著幾根黑色的蠟燭，散發出幽幽的綠
光。這裡的主人白魚是巫首族人，大漠八魔的首領，年逾兩百，法術通
玄，但為人優柔寡斷。
LONG
    );
    set("objects", ([
        "/d/wutang/npc/baiyu" : 1,
    ]));
    set("detail", ([
        "祭壇" : "祭壇上刻著一些看不懂的符文，散發著詭異的光芒。\n",
        "蠟燭" : "黑色的蠟燭燃著綠色的火焰，令人不寒而慄。\n",
    ]));
    set("exits", ([
        "down" : __DIR__"floor5",
        "up" : __DIR__"floor7",
    ]));

    setup();
    replace_program(ROOM);
}
