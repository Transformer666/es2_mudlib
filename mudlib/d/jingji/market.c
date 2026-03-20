// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "京畿市集");
    set("long", @LONG
京畿城內最繁華的市集，各地的珍奇貨物匯聚於此。絲綢莊裡掛
著五彩斑斕的綾羅綢緞，珠寶鋪中陳列著翡翠瑪瑙，茶行裡散發著
各種名茶的幽香。南來北往的商人操著不同的口音討價還價，官府的差
役時不時穿行其間維持秩序。這裡的物價比其他城鎮略高，但貨品的品
質也是最好的。
LONG
    );
    set("exits", ([
        "west" : __DIR__"street",
        "south" : __DIR__"back_alley",
        "east" : __DIR__"weapon_shop",
    ]));
    set("objects", ([
        __DIR__"npc/silk_merchant" : 1,
    ]));

    setup();
}
